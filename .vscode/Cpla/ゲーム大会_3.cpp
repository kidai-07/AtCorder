#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N, M;
	cin >> N >> M;
	vector<int> A(M), B(M);
	for (int i = 0; i < M; i++)
	{
		cin >> A.at(i) >> B.at(i);
	}
	//つまり{A,A2,A3}の行列(勝った人一覧)と、{B,B1,B2}(負けた人一覧)といった行列ができている状態。
	vector<vector<char>> data(N, vector<char>(N)); // N*N配列の枠を宣言
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			//配列「data」の、i行目j列の情報の定義
			if (i == j)
			{
				data.at(i).at(j) = '-'; //同じ人が当たるマスは「-」
			}
			else
			{
				for (int k = 1; k < M; k++)
				{
					if (i == A.at(k) && j == B.at(k))
					{
						data.at(i).at(j) = 'o'; // iの数字が「A」にあった場合
					}
					else if (i == B.at(k) && j == B.at(k))
					{
						data.at(i).at(j) = 'x'; // iの数字が「B」にあった場合
					}
					else
					{
						data.at(i).at(j) = '-'; //どちらでもないマスは「-」
					}
				}
			}
		}
	}
	//表の出力
	//配列dataを出力する
	for (int x = 0; x < N; x++)
	{
		for (int i = 0; i < N; i++)
		{
			cout << data.at(x).at(i);
			if (i == (N - 2))
			{
				cout << endl; // 末尾なら改行
			}
			else
			{
				cout << " "; // それ以外なら空白
			}
		}
	}
}