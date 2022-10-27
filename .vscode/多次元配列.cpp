#include <bits/stdc++.h>
using namespace std;

int main() {
 // int型の2次元配列(3×4要素の)の宣言
    vector<vector<int>> data(3, vector<int>(4));
    // 入力 (2重ループを用いる)
    for (int i = 0; i < 3; i++){
        for(int J = 0; j < 4 j++){
            cin >> data.at.(i).at(j);//i行目j列
        }
    }

int count = 0;

for (int i = 0; i < 3; i++){
    for(int j = 0; j<4; j++){
        if (data.at(i).at(j) == 0){
            count++;
        }
    }
}

cout << count <<endl;

}

data.size()//3行
data.at(0).size()//4列

//考え方
//1次元配列
vector<要素の型> 変数名(要素数,初期値);
//二次元配列
vector<要素の型> 変数名(行数,vector<要素の型>(各行の要素数,行の初期値))
