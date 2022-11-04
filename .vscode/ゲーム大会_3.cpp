//あるゲーム大会にはN人が参加しM試合が行われました。
//各参加者には1からNの番号が割り当てられています。
// M回の試合がすべて終了した時点での試合結果の表を作成し、出力してください。
//標準入力
//N M 
//A B
//A2 B2...

//例えば
//3 2
//1 2
//3 1

//つまり
//2* Mの行列を入力として受け取り
//N*Nの行列を出力する

//パターン分けとして
//Rabは●、Rbaは×、それ以外は-

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
	//つまり{A,A2,A3}の行列と、{B,B1,B2}といった行列ができている状態。

	vector<vector<char>> data(N,vector<char>(N));//N*N配列の枠を宣言

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){//この条件分岐が惜しい気がする、ここまでで回すと「out of range」になる
			if (i == A.at(i) && j == B.at(j))
			{
				data.at(i).at(j) = 'o';
			}
			else if (i == B.at(i) && j == A.at(j))
				{
					data.at(i).at(j) = 'x';
				}
			else{
				data.at(i).at(j) = '-';
			}
		}
	}

	for (int i = 0; i < N*N; i++)//表の出力
	{
		cout << data.at(i);
		if (i/N == 0)
		{
			cout << endl; // 末尾なら改行
		}
		else
		{
			cout << " "; // それ以外なら空白
		}
	}
}
