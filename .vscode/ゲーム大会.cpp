//あるゲーム大会にはN人が参加しM試合が行われました
//M回の試合がすべて終了した時点での試合結果の表を作成し、出力してください

// input
//勝った人の番号 負けた人の番号
//勝った人の番号 負けた人の番号
//勝った人の番号 負けた人の番号
//(これがM行続く)

// output
//     1さん 2さん 3さん
//1さん   -  〇    ×
//2さん  ×   -    - 
//3さん  〇   -    -

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, M;//N人が参加してM試合行われた
    cin >> N >> M;
    vector<int> A(M), B(M);//Aは勝った人の番号の配列、Bは負けた人の番号の配列
    for (int i = 0; i < M; i++)
    {
        cin >> A.at(i) >> B.at(i);//i試合目、左の数値はAに、右の数値はBに入れる
    }

    // ここにプログラムを追記
    // (ここで"試合結果の表"の2次元配列を宣言)

    //結果を受け取るフェーズ
    //表を書き出すフェーズ(aとbを計算して配列で渡せるようにすれば、表が書けるはず)
    vector<int> a = {1, 2, 3};
    for (int i = 0; i < 3; i++){
        cout << a.at(i);
        if(i == 2){
        cout << endl;
        }
        else{
        cout << " ";
        }
    }
    vector<int> b = {1, 2, 3};
    for (int i = 0; i < 3; i++)
    {
        cout << b.at(i);
        if (i == 2)
        {
            cout << endl;
        }
        else
        {
            cout << " ";
        }
    }
}