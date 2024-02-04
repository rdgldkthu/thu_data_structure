#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct vertex {
    int data;
    int status;
    int inDegree;
    int outDegree;
    int parent;
    vertex(int d) {
        data = d;
        status = 0;
        inDegree = 0;
        outDegree = 0;
        parent = -1;
    }
    vertex() {}
};

struct edge {
    int start;
    int end;
    edge(int s, int e) {
        start = s;
        end = e;
    }
};

struct graph {
    int num;
    int edg;
    vector<vertex> V;
    vector<vector<edge> > E;
    graph(int n, int e) {
        num = n;
        edg = e;
        V.resize(n);
        E.resize(n);
    }
};

int BFS(vertex s, vertex e, graph g) {
    queue<vertex> q;
    q.push(s);
    s.status = 1;
    while (!q.empty()) {
        vertex temp = q.front();
        int d = temp.data;
        q.pop();
        for (int i = 0; i < temp.outDegree; i++) {
            int tmp = (g.E)[d][i].end;
            if ((g.V)[tmp].status)
                continue;
            (g.V)[tmp].status = 1;
            if ((g.V)[tmp].data == e.data)
                return 1;
            q.push((g.V)[tmp]);
        }
    }
    return 0;
}

int main(int argc, const char* argv[]) {
    int N = 0, M = 0, K = 0;
    cin >> N >> M >> K;
    graph G(N, M);
    for (int i = 0; i < N; i++) {
        (G.V)[i] = vertex(i);
    }
    int edges[M][2];
    for (int i = 0; i < M; i++) {
        cin >> edges[i][0] >> edges[i][1];
        edge te(edges[i][0], edges[i][1]);
        (G.E)[edges[i][0]].push_back(te);
        (G.V)[edges[i][0]].outDegree++;
        (G.V)[edges[i][1]].inDegree++;
    }
    graph temp = G;
    int Circle = 0;
    while (temp.num > 0) {
        int flag = 0;
        for (auto& i : temp.V) {
            if (i.inDegree == 0 && i.data > -1) {
                for (auto x : (temp.E)[i.data]) {
                    (temp.V)[x.end].inDegree--;
                }
                i.data = -1;
                temp.num--;
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            Circle = 1;
            break;
        }
    }
    int search[K][2];
    for (int i = 0; i < K; i++) {
        cin >> search[i][0] >> search[i][1];
    }
    if (Circle == 1)
        cout << -1 << endl;
    else {
        for (int i = 0; i < K; i++) {
            if (BFS((G.V)[search[i][0]], (G.V)[search[i][1]], G))
                cout << 1 << endl;
            else if (BFS((G.V)[search[i][1]], (G.V)[search[i][0]], G))
                cout << -1 << endl;
            else
                cout << 0 << endl;
        }
    }
    return 0;
}
