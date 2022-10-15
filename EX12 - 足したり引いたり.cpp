#include <bits/stdc++.h>
using namespace std;
 
int main() {
  string str;
  cin >> str;
 
 //+の計算
  int count = 1;
  for (int i = 0; i < str.size(); i++) {
    if (str.at(i) == '+') {
      count++;
    }
  }
 //-の計算
   for (int i = 0; i < str.size(); i++) {
    if (str.at(i) == '-') {
      count--;
    }
  }
  cout << count << endl;
}