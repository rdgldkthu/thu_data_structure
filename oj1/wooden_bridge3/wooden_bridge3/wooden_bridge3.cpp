#include <iostream>
#define MAX_TIME_START 50001
#define MAX_TIME_NEEDED 2001
using namespace std;

//struct for people crossing the bridge
struct Person {
	int weight;
	int time_start;
	int time_needed;
	int time_end;
	Person* next;
	Person(int w, int ts, int tn) : weight(w), time_start(ts), time_needed(tn), time_end(ts+tn), next(NULL) {}
};
int total_weight = 0;
Person* head = NULL;
Person* tail = NULL;

void enqueue(int w, int ts, int tn) {
	if (head == NULL) {
		head = new Person(w, ts, tn);
		tail = head;
	}
	else {
		tail->next = new Person(w, ts, tn);
		tail = tail->next;
	}
	total_weight += w;
}

void dequeue() {
	if (head == NULL) { return; }
	if (head == tail) {
		total_weight = 0;
		delete head;
		head = NULL;
		tail = NULL;
	}
	else {
		total_weight -= head->weight;
		Person* temp = head;
		head = head->next;
		delete temp;
	}
}

void PrintAll() {
	if (head == NULL) return;

	Person* temp = head;
	cout << total_weight << " : ";
	while (temp != NULL) {
		cout << "( weight: " << temp->weight << ", " << "endtime: " << temp->time_end << " ) ";
		temp = temp->next;
	}

	cout << "\n";
}

void deleteQueue() {
	if (head == NULL) { return; }
	Person* temp = head;
	Person* nextTemp;
	while (temp != NULL) {
		nextTemp = temp->next;
		delete temp;
		temp = nextTemp;
	}
}

//main function
int main() {
	//number of people, maximum weight
	int N, M_MAX;
	//input initial variables 
	cin >> N >> M_MAX;
	//variables for each person
	int weight, time_start, time_needed;
	//create a queue
	for (int i = 1; i <= N; i++) {
		//input each instance
		cin >> weight >> time_start >> time_needed;
		//remove people that have crossed the bridge already
		while ((head != NULL) && (head->time_end <= time_start)) {
			dequeue();
		}
		//add to the queue
		enqueue(weight, time_start, time_needed);
		//if the total weight of people on bridge exceeds the maximum weight, then print out the last person to get on the bridge
		if (total_weight > M_MAX) {
			cout << i << endl;
			return 0;
		}
	}
	//if everyone has crossed the bridge safely, print out "safe"
	cout << "safe" << endl;
	deleteQueue();
	return 0;
}