#include <iostream>
#define MAX_TIME_START 50000
#define MAX_TIME_NEEDED 2000
using namespace std;

//class for people crossing the bridge
class Person {
private:
	int weight;
	int time_start;
	int time_needed;
public:
	Person* next;
	Person(int w, int ts, int tn) {
		weight = w;
		time_start = ts;
		time_needed = tn;
		next = nullptr;
	}
	int GetWeight() {
		return weight;
	}
	int GetTS() {
		return time_start;
	}
	int GetTN() {
		return time_needed;
	}
};

//Queue class
class Queue {
private:
	int total_weight;
public:
	Person* head;
	Person* tail;

	Queue() {
		head = nullptr;
		tail = nullptr;
		total_weight = 0;
	}
	~Queue() {
		if (head == nullptr) { return; }
		Person* temp = head;
		Person* nextTemp;
		while (temp != nullptr) {
			nextTemp = temp->next;
			delete temp;
			temp = nextTemp;
		}
	}

	void enqueue(int w, int ts, int tn) {
		if (head == nullptr) {
			head = new Person(w, ts, tn);
			tail = head;
		}
		else {
			tail->next = new Person(w, ts, tn);
			tail = tail->next;
		}
		total_weight += w;
	}
	int dequeue() {
		if (head == nullptr) { return -1; }
		int w = head->GetWeight();
		if (head == tail) {
			total_weight = 0;
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			total_weight -= w;
			Person* temp = head;
			head = head->next;
			delete temp;
		}
		return w;
	}
	int GetTotalWeight() {
		return total_weight;
	}
	void PrintAll() {
		if (head == nullptr) return;

		Person* temp = head;
		cout << total_weight << " : ";
		while (temp != nullptr) {
			cout << temp->GetWeight() << " ";
			temp = temp->next;
		}

		cout << "\n";
	}

};

//main function
int main() {
	//number of people, maximum weight
	int N, M_MAX;
	//input initial variables 
	cin >> N >> M_MAX;
	//variables for each person
	int weight, time_start, time_needed;
	//create a queue
	Queue bridge;
	for (int i = 0; i < N; i++) {
		if (bridge.GetTotalWeight() > M_MAX) {
			cout << i << endl;
			return 0;
		}
		//input each instance
		cin >> weight >> time_start >> time_needed;
		//add to the queue
		bridge.enqueue(weight, time_start, time_needed);
		//the time when the head person is supposed to get off the bridge 
		//if someone who came later than this time is added, then head will be removed from queue
		int head_leave_time;
		if (bridge.head == nullptr) { head_leave_time = MAX_TIME_START + MAX_TIME_NEEDED; }
		else { head_leave_time = bridge.head->GetTS() + bridge.head->GetTN(); }
		//remove people that have crossed the bridge already
		while (time_start >= head_leave_time) {
			bridge.dequeue();
			if (bridge.head == nullptr) { head_leave_time = MAX_TIME_START + MAX_TIME_NEEDED; }
			else { head_leave_time = bridge.head->GetTS() + bridge.head->GetTN(); }
		}
	}
	//if everyone has crossed the bridge safely, print out "safe"
	cout << "safe" << endl;
}