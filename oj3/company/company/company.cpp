#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int partition(vector<int>& nums, int l, int r) {
	int pos = l;
	int pivot = r;

	for (int j = l;j < r;j++) {
		if (nums[j] > nums[pivot]) {
			swap(nums[pos], nums[j]);
			pos++;
		}
	}
	swap(nums[pos], nums[pivot]);
	return pos;
}

int quickselect(vector<int>& nums, int l, int r, int k) {
	int pivot = partition(nums, l, r);
	if (k - 1 == pivot) {return nums[pivot];}
	else if (k - 1 < pivot) {return quickselect(nums, l, pivot - 1, k);}
	else {return quickselect(nums, pivot + 1, r, k);}
}

int findKthLargest(vector<int>& nums, int k) {
	return quickselect(nums, 0, nums.size() - 1, k);
}

int main() {
	int k;
	vector<int> deposits = {0};
	scanf_s("%d", &k);

	while (k--) {
		int t, x;
		scanf_s("%d %d", &t, &x);
		switch (t) {
		case 1: //hire one employee with savings x
			deposits.push_back(x);
			break;
		case 2: //gain profit, everyone earns x
			for (int &d : deposits) {
				d += x;
			}
			break;
		case 3: {//fire employees with savings below x (print the number of employees fired)
			int count = count_if(deposits.begin(), deposits.end(), [x](int d) {return d <= x;});
			printf("%d\n", count);
			deposits.erase(remove_if(deposits.begin(), deposits.end(), [x](int d) {return d <= x;}), deposits.end());
		}
			break;
		case 4: //find out the savings of x'th wealthiest employee (print the savings amount)
			if (x > deposits.size()) {
				printf("%d\n", -1);
			}
			else {
				int kth = findKthLargest(deposits, x);
				printf("%d\n", kth);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}