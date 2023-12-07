#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

struct Data {
    int sum;
    int num;
    Data(int a, int b) {
        num = a;
        sum = b;
    }
    bool operator==(Data s) {
        return num == s.num;
    }
};

struct cmp {
    bool operator()(const Data s, const Data s1) const {
        return s.sum > s1.sum;
    }
};

int main() {
    int n, d;
    cin >> n >> d;

    vector<map<Data, int, cmp>> all_sum((1 << d) + 1);
    vector<map<int, int>> finder((1 << d) + 1);

    vector<int> opr(n);
    vector<int> points_to_delete(n);
    vector<vector<int>> points(n, vector<int>(d));

    // input data
    for (int i = 0; i < n; i++) {
        cin >> opr[i];
        if (opr[i] == 0) {
            for (int j = 0; j < d; j++) {
                cin >> points[i][j];
            }
        }
        else {
            cin >> points_to_delete[i];
        }
    }

    for (int i = 0; i < n; i++) {
        int max_distance = 0;
        if (opr[i] == 0) { // add
            // iterate through all possible combinations of signs for each dimension
            for (int j = 0; j < (1 << d); j++) { 
                int sum = 0;
                for (int k = 0; k < d; k++) {
                    int t = j & (1 << k);
                    if (t == 0) {
                        sum -= points[i][k];
                    }
                    else {
                        sum += points[i][k];
                    }
                }
                //update new point and its sum
                all_sum[j].emplace(Data(i + 1, sum), i + 1);
                finder[j].emplace(i + 1, sum);
                // track the maximum manhattan distance
                int temp = abs(all_sum[j].begin()->first.sum - all_sum[j].rbegin()->first.sum);
                if (temp > max_distance) {
                    max_distance = temp;
                }
            }
        }
        else { // delete
            // iterate through all possible combinations of signs
            for (int j = 0; j < (1 << d); j++) {
                // find and remove point to be deleted from the map
                int sum = finder[j].at(points_to_delete[i]);
                all_sum[j].erase(Data(points_to_delete[i], sum));
                // track the maximum manhattan distance
                int temp = abs(all_sum[j].begin()->first.sum - all_sum[j].rbegin()->first.sum);
                if (temp > max_distance) {
                    max_distance = temp;
                }
            }
        }
        cout << max_distance << endl;
    }

    return 0;
}
