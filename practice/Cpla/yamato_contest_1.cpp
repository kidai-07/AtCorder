#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N, X;
	cin >> N >> X;

	vector<int> P(N);
	for (int i = 0; i < N; i++)
	{
		cin >> P.at(i);
	}

	for (int i = 0; i < N; i++)
	{
		if(P.at(i) == X){
			cout << (i+1);
		}
	}
}