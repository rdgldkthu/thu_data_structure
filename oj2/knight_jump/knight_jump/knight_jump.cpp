#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int x;
    int y;
    int rank;
    Node* parent;
    Node(int _x, int _y) {
        x = _x;
        y = _y;
        rank = 0;
        parent = nullptr;
    }
};

int Move[8][2] = {
    1, 2,
    1, -2,
    2, 1,
    2, -1,
    -1, 2,
    -1, -2,
    -2, 1,
    -2, -1
};


int BFS(Node* start_point, int l, int r, int u, int d, int board_status[201][201], int x_final, int y_final) {
    queue<Node*> Q;
    Q.push(start_point);
    int x_new, y_new = 0;
    while (!Q.empty()) {
        Node* temp = Q.front();
        Q.pop();
        for (int i = 0; i < 8; i++) {
            x_new = temp->x + Move[i][0];
            y_new = temp->y + Move[i][1];
            if (x_new < l || y_new < d || r < x_new || u < y_new) {
                continue;
            }
            if (board_status[100 + x_new][100 + y_new] == 1) {
                continue;
            }
            Node* Next = new Node(x_new, y_new);
            Next->rank = temp->rank + 1;
            Next->parent = temp;
            if (x_new == x_final && y_new == y_final) {
                return Next->rank;
            }
            Q.push(Next);
            board_status[100 + x_new][100 + y_new] = 1;
        }
    }
    return -1;
}

int main(int argc, const char* argv[]) {
    int x_final, y_final = 0;
    cin >> x_final >> y_final;
    int num = 0;
    cin >> num;
    vector<vector<int>> dents(num, vector<int>(2));
    int board[201][201] = { 0 };
    for (int i = 0; i < num; i++) {
        cin >> dents[i][0] >> dents[i][1];
        board[100 + dents[i][0]][100 + dents[i][1]] = 1;
    }
    Node* Start = new Node(0, 0);
    int flag = BFS(Start, -100, 100, 100, -100, board, x_final, y_final);
    if (flag == -1) {
        cout << "fail" << endl;
    }
    else {
        cout << flag << endl;
    }
    return 0;
}
