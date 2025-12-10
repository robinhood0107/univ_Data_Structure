/*
🔥 All-Pairs Shortest Paths 문제란?

그래프에서

모든 정점 i → 모든 정점 j까지의 최단 거리를 구하는 문제

대표 알고리즘: Floyd–Warshall

✨ 왜 Dynamic Programming 문제인가?
✔ 이유 1 — Optimal Substructure (최적 부분 구조)

i → j 까지 가는 최단 경로가
어떤 중간 정점 k를 거친다면,
그 경로는 i → k 최단 경로 + k → j 최단 경로 로 구성되어야 한다.

즉, 전체 최적해는 작은 최적해로 구성됩니다.

✔ 이유 2 — Overlapping Subproblems (중복 부분 문제)

Floyd–Warshall 점화식:


D[k][i][j]=min(D[k−1][i][j], D[k−1][i][k]+D[k−1][k][j])

D[k][i][j] 값을 구할 때
D[k-1][i][k] 와 D[k-1][k][j] 를 계속 반복해서 참조

i, j, k 조합이 반복 사용됨 → DP 테이블의 특성

즉, 똑같은 (i,k), (k,j) 부분 경로가 계속 다시 사용됨
→ 저장해두고 재활용하는 방식 → DP가 적합

📌 Floyd-Warshall 점화식 (DP식)

k 번째 정점을 경유 가능하도록 허용했을 때의 최단 경로:


의미
k를 거치지 않고 가는 기존 경로
k를 거쳐서 가면 더 짧아지는가? 비교

즉,

k 정점을 추가로 사용할 수 있다는 사실만 반영하며
최단 거리 테이블을 반복 갱신 → DP

All-Pairs Shortest Paths는
최적 부분 구조 + 중복 부분 문제를 만족하므로
Dynamic Programming 문제이다.

특히 Floyd–Warshall 알고리즘의 점화식이
DP의 원형 형태 그 자체입니다.
*/
#include <iostream>
#include <vector>
#include <list>
#include <limits.h>
#include <utility>
using namespace std;

const int MAX_WEIGHT = 9999999;
const int nmax = 100;
// Graph class with adjacency list
class Graph {
private:
    int n; // number of nodes
    int length[nmax][nmax]; //connection matrix
    int a[nmax][nmax];
    vector<list<pair<int, int>>> HeadNodes; // adjacency list (node, weight)
    vector<int> dist;
    vector<bool> s;
    vector<int> newdist;

public:
    Graph(int nodeSize) : n(nodeSize), HeadNodes(nodeSize), dist(nodeSize), s(nodeSize), newdist(nodeSize) {
        for (int i = 0; i < nmax; i++) {
            for (int k = 0; k < nmax; k++) {
                length[i][k] = MAX_WEIGHT;
            }
        }
    }

    void insertEdge(int start, int end, int weight);
    void showAdjacencyList();
    void ShortestPath(const int v);
    void ShortestPath_display(const int v);
    void BellmanFord(const int v);
    void BellmanFord2(const int v);
    void AllLengths();
    int choose();
    void show_dist_array(int startNode);
    void Graph::showGraphMatrix(int n);
    bool isNonNegativeEdgeCost();

    // Helper functions for output
    void displaySet();
    void Graph::showAdjacencyMatrix();
};

void Graph::insertEdge(int start, int end, int weight) {
    if (start >= n || end >= n || start < 0 || end < 0) {
        cout << "The input node is out of bound, the largest node is " << (n - 1) << endl;
        return;
    }
    HeadNodes[start].emplace_back(end, weight);//리스트 맨 뒤에 새 객체를 직접 생성
    //push_back(x) >  리스트 맨 뒤에 x를 추가 >>  이미 만들어진 객체를 복사(또는 이동) 해서 넣음
    length[start][end] = weight;
}

void Graph::showAdjacencyList() {
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << " -> ";
        for (auto& edge : HeadNodes[i]) {
            //std::pair는 두 개의 값(첫 번째 값과 두 번째 값)을 저장하는 템플릿 클래스이며,
            //각각의 값은 멤버 변수 first와 second를 통해 접근
            cout << "(" << edge.first << ", weight=" << edge.second << ") ";
        }
        cout << endl;
    }
}

void Graph::show_dist_array(int startNode) {
    for (int i = 0; i < n; i++) {
        if (i == startNode) {
            cout << "0, ";
        }
        else if (dist[i] == MAX_WEIGHT) {
            cout << "∞, ";
        }
        else {
            cout << dist[i] << ", ";
        }
    }
    cout << endl;
}

bool Graph::isNonNegativeEdgeCost() {
    for (int i = 0; i < n; i++) {
        for (auto& edge : HeadNodes[i]) {
            if (edge.second < 0) return false;
        }
    }
    return true;
}

void Graph::ShortestPath(const int v) {
    //dist[j], 0<=j<=n, is set to the length of the shortest path from vertex v to vertex j
    // in a digraph G with n vertices and edge lengths given by length[i][j]
    for (int i = 0; i < n; i++) {// initialize
        s[i] = false;
        dist[i] = length[v][i];
    }

    dist[v] = 0;
    s[v] = true;

    for (int i = 0; i < n - 2; i++) { // determine n-1 paths from vertex v
        int u = choose();  // choose returns a value u such that:
            // dist[u] = minimum dist[w], where s[w] = false
        if (u == -1) break;
        s[u] = true;
        for (int w = 0; w < n; w++)
            if (!s[w])
                if (dist[u] + length[u][w] < dist[w])
                    dist[w] = dist[u] + length[u][w];
        show_dist_array(v);
    } //end of for (i=0;...)
}

void Graph::ShortestPath_display(const int v) {
    for (int i = 0; i < n; i++) {// initialize
        s[i] = false;
        dist[i] = length[v][i];
    }
    dist[v] = 0;
    s[v] = true;

    for (int i = 0; i < n - 1; i++) {
        displaySet();
        show_dist_array(v);

        int u = choose();
        if (u == -1) break;

        s[u] = true;
        for (auto& edge : HeadNodes[u]) {
            int w = edge.first, weight = edge.second;
            if (!s[w] && dist[u] != MAX_WEIGHT && dist[u] + weight < dist[w]) {
                dist[w] = dist[u] + weight;
            }
        }
    }
    displaySet();
    show_dist_array(v);
}

int Graph::choose() {
    int minDist = MAX_WEIGHT;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (!s[i] && dist[i] < minDist) {
            minDist = dist[i];
            index = i;
        }
    }
    return index;
}

void Graph::displaySet() {
    cout << "[";
    for (int i = 0; i < n; i++) {
        if (s[i]) cout << i << ", ";
        else cout << "  ";
    }
    cout << "] ";
}


void Graph::BellmanFord(const int v) { //PCCP 시험 대비 학습 필요
    //single source all destination shortest paths with negative edge lengths
    for (int i = 0; i < n; i++)
        dist[i] = length[v][i];//initialize dist[]
    //
    cout << endl;
    int k = 0;
    for (k = 1; k <= n - 1; k++) {
        cout << "k = " << k << ", ";
        show_dist_array(v);
        for (int u = 0; u < n; u++) {//for (each u such that u != v and u has at least
                    // one incoming edge)
            if (u != v) {
                for (int i = 0; i < n; i++) {//for (each <i,u> in the graph)
                    if ((u != i) && (length[i][u] < MAX_WEIGHT)) {
                        if (dist[u] > dist[i] + length[i][u]) {
                            dist[u] = dist[i] + length[i][u];
                        }
                    }
                }
            }
        }
    }
    //cout << "k = " << k << ", ";
    //show_dist_array(n);
}

void Graph::BellmanFord2(const int v)
// Single source all destination shortest paths with negative edge lengths
{
    for (int i = 0; i < n; i++)
        dist[i] = length[v][i]; // initialize dist
    for (int k = 2; k <= n - 1; k++) {
        for (int l = 0; l < n; l++)
            newdist[l] = dist[l];
        for (int u = 0; u < n; u++)
            if (u != v) {
                for (int i = 0; i < n; i++)
                    if ((u != i) && (length[i][u] < MAX_WEIGHT))
                        if (newdist[u] > dist[i] + length[i][u])
                            newdist[u] = dist[i] + length[i][u];
            }
        for (int i = 0; i < n; i++)
            dist[i] = newdist[i];
    }
}
void Graph::showGraphMatrix(int n) {
    //cout << endl;
    for (int i = 0; i < n; i++) {
        cout << "startNode = " << i << ": ";
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cout << "0 " << "  ";
            }
            else if (a[i][j] > MAX_WEIGHT - 100000)//100000 is one a big enough number
                cout << "∞" << "  ";
            else cout << a[i][j] << "  ";
        }
        cout << endl;
    }
}
void Graph::AllLengths()
// length[n][n] is the adjacency matrix of a graph with n vertices.
// a[i][j] is the length of the shortest path between i and j
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = length[i][j];   // copy length into a

    int k = 0;
    for (; k < n; k++) {  // for a path with highest vertex index k
        cout << "\n A[" << k - 1 << "]" << endl;
        showGraphMatrix(n);
        for (int i = 0; i < n; i++)  // for all possible pairs of vertices
            for (int j = 0; j < n; j++)
                if ((a[i][k] + a[k][j]) < a[i][j])
                    a[i][j] = a[i][k] + a[k][j];
    }
    cout << "\n A[" << k - 1 << "]" << endl;
    showGraphMatrix(n);
}

void Graph::showAdjacencyMatrix() {
    for (int i = 0; i < n; i++) {
        bool exists = false;
        for (int k = 0; k < n; k++) {
            if (length[i][k] == MAX_WEIGHT) continue;
            exists = true;
            cout << i << " -> " << k << "(weight=" << length[i][k] << "), ";
        }
        if (exists) cout << endl;
    }
}





vector<vector<int>> makeGraph1() {
    return {
        {0, 6, 5, 7, 0, 0, 0},
        {6, 0, 2, 0, 1, 0, 0},
        {5, 2, 0, 2, 1, 0, 0},
        {7, 0, 2, 0, 0, 1, 0},
        {0, 1, 1, 0, 0, 0, 3},
        {0, 0, 0, 1, 0, 0, 8},
        {0, 0, 0, 0, 3, 8, 0}
    };
}

vector<vector<int>> makeGraph2() {
    return {
        {0, 300, 1000, 0, 0, 0, 0, 1700},
        {300, 0, 800, 0, 0, 0, 0, 0},
        {1000, 800, 0, 1200, 0, 0, 0, 0},
        {0, 0, 0, 1200, 1500, 1000, 0, 0},
        {0, 0, 0, 1500, 0, 250, 0, 0},
        {0, 0, 0, 1000, 250, 0, 900, 1400},
        {0, 0, 0, 0, 0, 900, 0, 1000},
        {1700, 0, 0, 0, 0, 1400, 1000, 0}
    };
}
void showMatrix(vector<vector<int>> matrix) {
    for (auto row : matrix){
        for (auto col : row) {
            cout << col << " ";
        }
        cout << "\n";
    }
}
int main() {
    int num;
    int select;
    Graph* g = nullptr;
    int start, end, weight;
    cout << "1: Graph with Negative Weights, 2: 도시간 거리 그래프\n";
    cin >> select;

    if (select == 1) {
        auto matrix = makeGraph1();
        showMatrix(matrix);
        g = new Graph(7);
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] != 0) {
                    g->insertEdge(i, j, matrix[i][j]);
                }
            }
        }
    }
    else if (select == 2) {
        auto matrix = makeGraph2();
        showMatrix(matrix);
        g = new Graph(8);
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] != 0) {
                    g->insertEdge(i, j, matrix[i][j]);
                }
            }
        }
    }
    else {
        cout << "Invalid input. Exiting." << endl;
        return 0;
    }
    while (select != '0')
    {
        cout << "\nSelect command 1: Edge 추가, 2: AdjacencyLists, 3: singleSource/all destinations(non-negative edge cost)"
            << "4:  single source/all destinations(negative edge costs), 5. All-pairs shortest paths, 6. Quit => ";
        cin >> select;
        switch (select) {
        case 1:
            cout << "edge 추가: " << endl;
            cout << "start node: ";
            cin >> start;
            cout << "end  node: ";
            cin >> end;
            cout << "weight: ";
            cin >> weight;

            g->insertEdge(start, end, weight);
            break;
        case 2:
            //display
            g->showAdjacencyMatrix();
            break;
        case 3:
            cout << "\nsingle source/all destinations: non-negative edge costs: " << endl;
            if (!g->isNonNegativeEdgeCost()) {
                cout << "Negative edge cost exists!!" << endl;
                cout << "Please re-build the graph with non-negative edge costs." << endl;
                break;
            }

            cout << "\n ----------> Input start node: ";
            cin >> start;

            g->ShortestPath_display(start);
            break;
        case 4:
            cout << "\nsingle source/all destinations: negative edge costs: " << endl;
            cout << "\n ----------> Input start node: ";
            cin >> start;

            g->BellmanFord(start);
            break;
        case 5:
            cout << "\nAll-pairs shortest paths:" << endl;
            g->AllLengths();
            break;
        case 6:
            exit(0);
        default:
            cout << "WRONG INPUT  " << endl;
            cout << "Re-Enter" << endl;
            break;
        }
    }

    cin >> num;
    delete g;
    return 0;
}
