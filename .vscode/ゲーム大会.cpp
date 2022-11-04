#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<vector<int>> data(3, vector<int>(4));
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 4; j++) {
            cin >> data.at(i).at(j);
        }
    }

    int count = 0;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 4; j++){
            if (data.at(i).at(j) == 0){
                count++; 
            }
        }
    }

    cout << count << endl;
}