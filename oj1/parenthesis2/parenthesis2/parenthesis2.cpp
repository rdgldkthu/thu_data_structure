#include <iostream>
#define MAX_LEN 201
using namespace std;

//node to store elements in the stack
struct Node {
	char data;
	struct Node* next;
};
struct Node* head = NULL;

//add element to the top of the stack
void push(char x) {
	Node* temp = new Node;
	temp->data = x;
	temp->next = head;
	head = temp;
}

//remove the last element added and return it
char pop() {
	if (head == NULL) { return -1; }
	char d = head->data;
	Node* del = head;
	head = head->next;
	delete del;
	return d;
}

//check if the stack is empty
bool empty() {
	return (head == NULL);
}

//check if all parentheses are in pair and in right location
bool paren(const char exp[]) {
	int i = 0;
	while (exp[i] != '\0') {
		switch (exp[i]) {
		case '(': case '[': case '{': push(exp[i]); break;
		case ')': if ((empty()) || ('(' != pop())) return false; break;
		case ']': if ((empty()) || ('[' != pop())) return false; break;
		case '}': if ((empty()) || ('{' != pop())) return false; break;
		default: break;
		}
		i++;
	}
	return empty();
}

//function to reset the stack when previous check was false(=elements left in the stack)
void reset() {
	while (head != NULL) {
		pop();
	}
}

int main() {	
	//input the number of lines to check
	int n;
	cin >> n;

	//get input and check parentheses
	while (n--) {
		char exp[MAX_LEN];
		cin >> exp;
		//cheack and print result
		cout << paren(exp) << endl;
		reset();
	}
	delete head;
	return 0;
}