#include <iostream>
#include <vector>
#include <map>
using namespace std;

int countOfParallelograms(vector<int>& X, vector<int>& Y, int N) {
    map<pair<int, int>, int> cnt; // map to store frequency of mid points
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // division by 2 is ignored, to get rid of doubles
            int midX = X[i] + X[j];
            int midY = Y[i] + Y[j];
            // increase the frequency of mid point
            cnt[make_pair(midX, midY)]++;
        }
    }
    // iterate through all mid points
    int res = 0;
    for (auto it = cnt.begin(); it != cnt.end(); it++) {
        int freq = it->second;
        // increase the count of Parallelograms by applying function on frequency of mid point
        res += freq * (freq - 1) / 2;
    }
    return res;
}

int main() {
    int n; // number of test cases
    cin >> n;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m; // number of points in the test case
        // store x, y coordinates of points into seprate vectors
        int x, y;
        vector<int> X;
        vector<int> Y;
        for (int j = 0; j < m; j++) {
            cin >> x >> y;
            X.push_back(x);
            Y.push_back(y);
        }
        //count the number of parallelograms
        cout << countOfParallelograms(X, Y, m) << endl;
    }
    return 0;
}
