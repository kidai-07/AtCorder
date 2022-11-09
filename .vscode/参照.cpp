#include <bits/stdc++.h>
using namespace std;

int main(){
	int a = 3;
	int &b =a;

	cout << "a:" << a << endl;
	cout << "b:" << b << endl;

	b = 4;

	cout << "a:" << a << endl;
	cout << "b:" << b << endl;
}

#include <bits/stdc++.h>
using namespace std;

int f(int x) {
	x = x * 2;
	return x;
}

int main() {
	int a = 3;
	int b = f(a);
	cout << "a:" << a << endl;
	cout << "b:" << b << endl;
}

#include <bits/stdc++.h>
using namespace std;

int g(int &x){
	x = x * 2;
	return x;
}

int main(){
	int a = 3;
	int b = g(a);
	cout << "a:" << a << endl;
	cout << "b:" << b << endl;
}