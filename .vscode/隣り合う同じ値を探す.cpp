#include <bits/stdc++.h>
using namespace std;
 
int main() {
  vector<int> data(5);
  for (int i = 0; i < 5; i++) {
    cin >> data.at(i);
  }
  // dataの中で隣り合う等しい要素が存在するなら"YES"を出力し、そうでなければ"NO"を出力する
  int judge = data.at(0) - data.at(1);
  
  for(int i = 0; i < data.size() - 1; i++){
    judge = judge * (data.at(i) - data.at(i+1));
  }

  if(judge == 0){
    cout << "YES" << endl;
  }
  else{
    cout << "NO" << endl;
  }
}