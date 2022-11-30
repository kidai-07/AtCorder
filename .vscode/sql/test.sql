-- kvs(time, k, v, c)
CREATE TEMPORARY FUNCTION target_start() AS (TIMESTAMP(DATE_ADD(CURRENT_DATE('Asia/Tokyo'), INTERVAL -2 DAY)));
CREATE TEMPORARY FUNCTION target_end() AS (TIMESTAMP(CURRENT_DATE('Asia/Tokyo')));
CREATE TEMPORARY FUNCTION target_dt() AS (DATE_ADD(CURRENT_DATE('Asia/Tokyo'), INTERVAL -1 DAY));
CREATE TEMPORARY FUNCTION key_name() AS ('daily_app_install_retention_installpath_region');

CREATE TEMPORARY FUNCTION time_log_released_datetime() AS (TIMESTAMP('2022-11-15 00:00:00','Asia/Tokyo'));---sessionがAndroidで正しく落ちるようになってから集計

WITH install_users AS 
	(
	SELECT DISTINCT
		installed_at,
		DATE_DIFF(target_dt(), DATE(installed_at, 'Asia/Tokyo'), DAY) AS diff_dt, 
		IF(LOWER(adjust_country) IN (SELECT LOWER(log) FROM `vlive-prod.vlive_master.master_country` WHERE type = 'all'), LOWER(adjust_country), 'others') AS region,---正式名称に変更
		IF(install_path IS NULL, 'organic', install_path) AS install_path,---正式名称に変更
		adjust_device_id
	FROM
		(---生ログを取得
		SELECT
			LOWER((SELECT value FROM UNNEST(content) WHERE key = 'p_network_name' )) AS network_name,
			(SELECT value FROM UNNEST(content) WHERE key = 'p_adid' ) AS adjust_device_id,
			(SELECT value FROM UNNEST(content) WHERE key = 'p_country' ) AS adjust_country,
			(SELECT TIMESTAMP_SECONDS(SAFE_CAST(value AS INT64)) FROM UNNEST(content) WHERE key = 'p_installed_at' ) AS installed_at,
			(SELECT value FROM UNNEST(content) WHERE key = 'p_place' ) AS place
		FROM
			`vlive-prod.vlive_general_data.adjust`
		WHERE
			dt BETWEEN DATE_ADD(target_dt(), INTERVAL -40 DAY) AND target_dt()---[add]パーティション指定の追加
		) A
		LEFT OUTER JOIN
		(
	SELECT
		LOWER(network_name) AS network_name,
		install_path
	FROM
		`vlive-prod.vlive_master.master_installpath`
	) B
		ON A.network_name = B.network_name
	WHERE
		place = 'install'
		AND DATE(installed_at,'Asia/Tokyo') BETWEEN DATE_ADD(target_dt(), INTERVAL -30 DAY) AND target_dt()
	),

install_uu AS 
	(
		SELECT
			DATE_DIFF(target_dt(), DATE(installed_at, 'Asia/Tokyo'), DAY) AS diff_dt, 
			region,
			install_path,
			COUNT(DISTINCT adjust_device_id) AS install_uu
		FROM
			install_users
		WHERE
			diff_dt IN (1, 3, 7, 14, 30)
		GROUP BY
			1,2,3
	),

id_pair AS 
	(
	SELECT DISTINCT
		adjust_device_id,
		vlive_id
	FROM 
		(---生ログを取得
		SELECT
			time,
			(SELECT value FROM UNNEST(content) WHERE key = 'p_vlive_id' ) AS vlive_id,
			(SELECT value FROM UNNEST(content) WHERE key = 'p_adid' ) AS adjust_device_id,
			(SELECT value FROM UNNEST(content) WHERE key = 'p_place' ) AS place
		FROM
			`vlive-prod.vlive_general_data.adjust`
		)
	WHERE
		place = 'session'
		AND dt BETWEEN DATE_ADD(target_dt(), INTERVAL -40 DAY) AND target_dt()---[add]パーティション指定の追加
		AND DATE(time,'Asia/Tokyo') BETWEEN DATE_ADD(target_dt(), INTERVAL -30 DAY) AND target_dt()
	),

retentions AS 
	(
	SELECT DISTINCT
		vlive_id
	FROM
		`vlive-prod.vlive_analytics.snapshot_vlive_id_access`
	WHERE
		DATE(time, 'Asia/Tokyo') = target_dt()---集計日にログインしていたら、継続とする
	),

retention_uu AS 
	(
		SELECT
			diff_dt, 
			region,
			install_path,
			COUNT(DISTINCT install_users.adjust_device_id) AS retention_uu---継続はadjust_device_idをカウントする(複数vlive_idのうち、どれか1つでも継続してれば、継続/複数vlive_idが継続していても、1UUとしてカウント)
		FROM
			install_users
			LEFT OUTER JOIN
			id_pair
			ON install_users.adjust_device_id = id_pair.adjust_device_id
			LEFT OUTER JOIN
			retentions
			ON id_pair.vlive_id = retentions.vlive_id
		WHERE
			retentions.vlive_id IS NOT NULL---集計日にログインしていたら、継続とする
			AND diff_dt IN (1, 3, 7, 14, 30)
		GROUP BY
			1,2,3
	),

uu_by_region_and_path AS 
	(
	SELECT
		A.diff_dt, 
		A.region,
		A.install_path,
		install_uu,
		retention_uu
	FROM
		install_uu A
		LEFT OUTER JOIN
		retention_uu B
		ON 
		A.diff_dt = B.diff_dt
		AND A.region = B.region
		AND A.install_path = B.install_path
	),

make_region_all AS 
	(
	SELECT
		diff_dt,
		COALESCE(region, 'all') AS region,
		install_path,
		install_uu,
		retention_uu
	FROM
		(
		SELECT
			diff_dt, 
			region,
			'all' AS install_path,
			SUM(install_uu) AS install_uu,
			SUM(retention_uu) AS retention_uu
		FROM
			uu_by_region_and_path
		GROUP BY ROLLUP
			(1,2)
		)
	WHERE
		diff_dt IS NOT NULL
	),

make_path_all AS 
	(
		SELECT
			diff_dt, 
			'all' AS region,
			install_path,
			SUM(install_uu) AS install_uu,
			SUM(retention_uu) AS retention_uu
		FROM
			uu_by_region_and_path
		GROUP BY
			1,3
	)

	SELECT
		TIMESTAMP(CONCAT(CAST(target_dt() AS STRING),' 00:00:00+09')) AS time,
		Q.k AS k,
		IF(v IS NULL, 0, v) AS v,
		LOWER(P.log) AS c
	FROM
		(
		SELECT
			log
		FROM
			`vlive-prod.vlive_master.master_country`
		WHERE
			type IN ('organic', 'promotion', 'invite')
			UNION ALL SELECT 'all_all' AS log
			UNION ALL SELECT 'jp_all' AS log
			UNION ALL SELECT 'us_all' AS log
			UNION ALL SELECT 'others_all' AS log
		) P
		LEFT OUTER JOIN
		(
		SELECT
			CONCAT(key_name(),'_',CAST(diff_dt AS STRING)) AS k,
			IF((install_uu != 0 AND retention_uu != 0),retention_uu / install_uu,0) AS v,
			CONCAT(region,'_',install_path) AS region
		FROM
			(
			SELECT
				*
			FROM
				uu_by_region_and_path
			
			UNION ALL
			
			SELECT
				*
			FROM
				make_region_all
			
			UNION ALL
			
			SELECT
				*
			FROM
				make_path_all
			)
		) Q
		ON P.log = LOWER(Q.region)
