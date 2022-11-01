//入力形式
// N人が参加してM試合行われた
// Aが勝利Bが敗北
// N M
// A B
// A B(これがM行続く)

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
    vector<string> sheet = {
        "〇",
        "〇",
        "×",
        "-",
    }; // (ここで"試合結果の表"の2次元配列を宣言)
    for (int i = 0; i < (M - 1) * (M - 1); i++)
    {
        cout << sheet.at(i);
        if (i = (M - 1))
        {
            cout << endl; // 末尾なら改行
        }
        else
        {
            cout << " "; // それ以外なら空白
        }
    }
}