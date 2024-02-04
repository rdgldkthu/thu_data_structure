#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
typedef long long int LL;
typedef unsigned int uint;
#define mp(x,y) make_pair(x,y)
const int MAXN = 1000 + 5;
struct Point {
    double x, y;
    Point(double a = 0, double b = 0) :x(a), y(b) {};
};
Point P[MAXN], MP[MAXN * MAXN];
Point MidP(Point a, Point b) {
    return Point((a.x + b.x) / 2, (a.y + b.y) / 2);
}
bool cmp(Point a, Point b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}
int main() {
    int n, t;
    scanf_s("%d", &t);
    while (t--) {
        scanf_s("%d", &n);
        int ans = 0, cnt = 0;
        for (int i = 0;i < n;i++) {
            scanf_s("%lf %lf", &P[i].x, &P[i].y);
        }
        for (int i = 0;i < n;i++) {
            for (int j = i + 1;j < n;j++) {
                Point midP = MidP(P[i], P[j]);
                MP[cnt++] = midP;
            }
        }
        sort(MP, MP + cnt, cmp);
        int idx = 0, tmp = 1;
        for (int i = 1;i < cnt;i++) {
            if (MP[i].x == MP[idx].x && MP[i].y == MP[idx].y) {
                tmp++;
            }
            else {
                ans += tmp * (tmp - 1) / 2;
                idx = i; tmp = 1;
            }
        }
        ans += tmp * (tmp - 1) / 2;
        printf("%d\n", ans);
    }
    return 0;
}