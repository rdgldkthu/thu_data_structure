#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define NULL -1
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EStatus;

struct Vertex {
    int data;
    int dTime;
    int parent;
    int inDegree, outDegree;
    VStatus status;
    Vertex(int d) : data(d), dTime(-1), parent(-1), inDegree(0), outDegree(0), status(UNDISCOVERED) {}
};

struct Edge {
    int data;
    EStatus status;
    Edge(int d) : data(d), status(UNDETERMINED) {}
};

struct  Graph {
    int n; //number of vertices
    int e; //number if edges
    vector<Vertex> V;
    vector<vector<Edge>> E;

    // constructor, destructor
    Graph() { n = e = 0; }
    Graph(int N) {
        n = 0;
        e = 0;
        V.resize(N, Vertex(NULL));
        E.resize(N, vector<Edge>(N, Edge(NULL)));
    }
    ~Graph() {}

    // vertex operations
    void insert(int const& vertex) {
        if (V[vertex].data != NULL) return;
        V[vertex] = Vertex(vertex); n++;
    }
    VStatus& status(int i) { return V[i].status; }
    int firstNbr(int i) { return nextNbr(i, n); }
    int nextNbr(int i, int j) { while ((-1 < j) && (!exists(i, --j))); return j; }
    int& vertex(int i) { return V[i].data; }
    int& dTime(int i) { return V[i].dTime; }
    int& parent(int i) { return V[i].parent; }

    // edge operations
    void insert(int const& edge, int i, int j) {
        if (exists(i, j)) return;
        E[i][j] = Edge(edge);
        e++; V[i].outDegree++; V[j].inDegree++;
    }
    EStatus& status(int i, int j) { return E[i][j].status; }
    bool exists(int i, int j) { return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j].data != NULL; }

    // topological sort
    stack<int>* tSort(int s) {
        int clock = 0;
        int v = s;
        stack<int>* S = new stack<int>;
        do {
            if (UNDISCOVERED == status(v)) {
                if (!TSort(v, clock, S)) {
                    while (!S->empty()) {
                        S->pop(); break;
                    }
                }
            }
        } while (s != (v = (++v % n)));
        return S;
    }
    bool TSort(int v, int& clock, stack<int>* S) {
        dTime(v) = ++clock; status(v) = DISCOVERED;
        for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
            switch (status(u)) {
            case UNDISCOVERED:
                parent(u) = v;
                status(v, u) = TREE;
                if (!TSort(u, clock, S)) return false;
                break;
            case DISCOVERED:
                status(v, u) = BACKWARD;
                return false;
            default:
                status(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
            }
        }
        status(v) = VISITED; S->push(vertex(v));
        return true;
    }
};

int checkAncestor(Graph g, int v1, int v2) {
    int result = 0;
    for (int u = g.firstNbr(v1); -1 < u; u = g.nextNbr(v1, u)) {
        if (u == v2) {
            result++;
            break;
        }
        result += checkAncestor(g, u, v2);
    }
    return result;
}

int main() {
    int N; // number of vertices
    int M; // number of edges
    int K; // number of searches
    cin >> N >> M >> K;

    // construct graph
    Graph G(N);
    int V1, V2; // vertex1 and vertex2 (V1 -> V2)
    for (int i = 0; i < M; i++) {
        cin >> V1 >> V2;
        G.insert(V1);
        G.insert(V2);
        G.insert(i, V1, V2);
    }

    // topological sort
    stack<int>* tSorted = G.tSort(0);
    bool isNotDAG = tSorted->empty();
    if (isNotDAG) {
        cout << -1 << endl;
        return -1;
    }

    // make searches
    for (int i = 0; i < K; i++) {
        cin >> V1 >> V2;
        if (V1 == V2) {
            cout << 0 << endl;
        }
        else {
            bool hasRelationship = false;
            if (checkAncestor(G, V1, V2) >= 1) {
                hasRelationship = true;
                cout << 1 << endl;
            }

            else if (checkAncestor(G, V2, V1) >= 1) {
                hasRelationship = true;
                cout << -1 << endl;
            }
            if (!hasRelationship) {
                cout << 0 << endl;
            }
        }
    }
    return 0;
}
