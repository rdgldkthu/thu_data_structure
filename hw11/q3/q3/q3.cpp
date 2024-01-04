#include <iostream>
#include <iomanip>
#define INF 999
using namespace std;

int main() {
    int E[8][8] = {
        { 0,  12, INF,  2,  INF,  INF,  7,  INF  },
        { 12, 0,  4,  INF,  INF,  INF,  INF,  INF  },
        { INF,  4,  0,  11, 1,  6,  INF,  10 },
        { 2,  INF,  11, 0,  13, INF,  2,  INF  },
        { INF,  INF,  1,  13, 0,  5,  9,  8  },
        { INF,  INF,  6,  INF,  5,  0,  INF,  7  },
        { 7,  INF,  INF,  2,  9,  INF,  0,  14 },
        { INF,  INF,  10, INF,  8,  7,  14, 0  }
    };
    int P[8][8] = {
        { 1,  2,  3,  4,  5,  6,  7,  8 },
        { 1,  2,  3,  4,  5,  6,  7,  8 },
        { 1,  2,  3,  4,  5,  6,  7,  8 },
        { 1,  2,  3,  4,  5,  6,  7,  8 },
        { 1,  2,  3,  4,  5,  6,  7,  8 },
        { 1,  2,  3,  4,  5,  6,  7,  8 },
        { 1,  2,  3,  4,  5,  6,  7,  8 },
        { 1,  2,  3,  4,  5,  6,  7,  8 }
    };
    for (int k = 0; k < 8; k++) {
        cout << "k=" << k+1 << endl;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (E[i][j] > E[i][k] + E[k][j]) {
                    E[i][j] = E[i][k] + E[k][j];
                    P[i][j] = P[i][k];
                }
            }
        }
        cout << "E:                                     P:" << endl;
        for (int a = 0; a < 8; a++) {
            for (int b = 0; b < 8; b++) {
                if (E[a][b] == INF) {
                    cout << setw(3) << "INF" << " ";
                }
                else {
                cout << setw(3) << E[a][b] << " ";
                }
            }
            cout << "     ";
            for (int c = 0; c < 8; c++) {
                cout << setw(3) << P[a][c] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}