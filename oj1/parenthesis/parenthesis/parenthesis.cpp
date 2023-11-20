#include <iostream>
#include <stack>
using namespace std;

//check if all parentheses are in pair and in right location
bool paren(const char exp[], int lo, int hi) {
    stack<char> S;
	for (int i = lo; i <= hi; i++) {
		switch (exp[i]) {
		case '(': case '[': case '{': S.push( exp[i] ); break;
		case ']': 
			if (S.empty()) { return false; break; }
			else if ('[' == S.top()) { S.pop(); break; }
			else { return false; break; }
		case '}':
			if (S.empty()) { return false; break; }
			else if ('{' == S.top()) { S.pop(); break; }
			else { return false; break; }
		case ')':
			if (S.empty()) { return false; break; }
			else if ('(' == S.top()) { S.pop(); break; }
			else { return false; break; }
		default: break;
		}
	}
	return S.empty();
}

int main() {
	//input the number of lines to check
	int n;
	cin >> n;

	//get input and check parentheses
	while (n--) {
		char exp[205];
		cin >> exp;
		cout << paren(exp, 0, 205) << endl;
	}
	return 0;
}
