#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N;
	cin >> N;
	// N × (3 × 3)要素の配列を宣言
	vector<vector<vector<char>>> data(N, vector<vector<char>>(3, vector<char>(3)));

	// 入力
	for (int i = 0; i < N; i++)
	{
		// i番目の状態を読む
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cin >> data.at(i).at(j).at(k);
			}
		}
	}

	// 'o'の数を数える
	int count = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				// 「i番目の状態」「上からj番目」「左からk番目」の要素が'o'か判定
				if (data.at(i).at(j).at(k) == 'o')
				{
					count++;
				}
			}
		}
	}

	cout << count << endl;
}