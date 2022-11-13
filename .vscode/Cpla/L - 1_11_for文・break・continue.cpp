#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int N;
  cin >> N;
  int A;
  cin >> A;
  int sum = A;

  for (int i = 0; i < N; i++) {
    string P;
    cin >> P;
    int B;
    cin >> B;
 
    if (P == "+"){
    sum += B;
    }
    if (P == "-"){
    sum += (- B);
    }
    if (P == "*"){
    sum = sum * B;
    }
    if (P == "/"){
      if(B==0){
        cout << "error" <<endl;
        break;
      }
      else{
      sum = sum / B;
      }
    }
    cout << i + 1 << ":" << sum << endl;
  }
}