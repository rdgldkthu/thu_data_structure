#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(NULL) {}
};

//function to create a circular linked list with N nodes
void createCircle(Node* head, int N) {
    Node* itr = head;
    for (int i = 2; i <= N; i++) {
        itr->next = new Node(i);
        itr = itr->next;
    }
    itr->next = head;
}

//function to receive a node as argument and remove the next node
void removeNextNode(Node* prev) {
    Node* toBeRemoved = prev->next;
    Node* toBeConnected = toBeRemoved->next;
    prev->next = toBeConnected;
    delete toBeRemoved;
}

/* functions used for debugging
void deleteCircle(Node* head) {
    Node* temp = head->next;
    head->next = NULL;
    Node* nextTemp;
    while (temp != NULL) {
        nextTemp = temp->next;
        delete temp;
        temp = nextTemp;
    }
}

void printCircle(Node* head, int N) {
    Node* itr = head;
    while (N--) {
        cout << itr->data;
        itr = itr->next;
    }
    cout << endl;
}
*/

int main()
{
    //number of people in the line, number of steps before step out
    int N, M; 
    cin >> N >> M;

    //create circle
    Node* head = new Node(1);
    createCircle(head, N);

    //every M'th person steps out = after M-2 steps, the next person steps out 
    int steps_taken = M - 2;
    Node* itr = head;
    while (itr != itr->next) {
        while (steps_taken--) {
            itr = itr->next;
        }
        removeNextNode(itr);
        itr = itr->next;
        steps_taken = M - 2;
    }

    //print result
    cout << itr->data;
    delete itr;
    return 0;
}