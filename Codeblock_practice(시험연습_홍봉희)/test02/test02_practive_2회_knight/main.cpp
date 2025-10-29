#include <iostream>
#include <stack>

using namespace std;

struct Offset { int a, b; };
struct Point { int x, y, dir; }; // dir: 이 위치로 들어올 때 사용한 이동 인덱스

// ----- 설정 -----
constexpr int N = 5;            // 보드 크기 (원하면 6,7,8 등으로 변경)
constexpr bool find_all = true; // true: 모든 해 탐색, false: 첫 해에서 종료

// 8가지 나이트 이동
Offset moves[8] = {
    {-2, -1}, {-2,  1}, {-1,  2}, { 1,  2},
    { 2,  1}, { 2, -1}, { 1, -2}, {-1, -2}
};

int board[N][N];     // 방문 순서 기록 (-1: 미방문)
long long numSolutions = 0;

inline void initBoard() {
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) board[i][j] = -1;
}

inline bool inRange(int x, int y) {
    return (0 <= x && x < N && 0 <= y && y < N);
}

inline bool isSafe(int x, int y) {
    return inRange(x, y) && board[x][y] == -1;
}

void showBoard() {
    cout << '\n';
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) cout << board[i][j] << '\t';
        cout << '\n';
    }
}

bool solveKnightTourFrom(int sx, int sy) {
    stack<Point> st;
    initBoard();

    st.push({ sx, sy, -1 });
    board[sx][sy] = 0;

    int resumeDir = 0; // 현재 top에서 다음에 시도할 이동 인덱스

    while (!st.empty()) {
        // 모든 칸 방문 완료
        if ((int)st.size() == N * N) {
            showBoard();
            ++numSolutions;
            if (!find_all) return true;

            // 계속 탐색을 위해 백트래킹
            Point last = st.top();
            st.pop();
            d[last.x][last.y] = -1; //방문 취소


            resumeDir = last.dir +1; //이렇게 재설정 후에
            continue;
            //마찬가지로 백트래킹 하고 dir+1


        }

        Point cur = st.top();
        bool moved = false;

        // 현재 위치에서 resumeDir부터 8방향 시도
        for (int d = resumeDir; d < 8; ++d) {
                //좌표 설정 후
                int nx = cur.x + moves[d].a;
                int nx = cur.y + moves[d].b;

                //isSafe()에 만족 하는 경우
                        //방문순서 기록 한 후에

                            //해당 좌표와 방향을 stack에 저장하고
                            //resumedir를 0으로 설정해서 0부터 다시 재탐색

                if(isSafe(nx,ny)){
                    board[nx][ny] = st.size();

                    st.push({nx,ny,d}); //새로운 이동방향 저장


                    resumeDir = 0;//여기는 아예 dir=0으로 만드는 거 잊지말기
                    moved = true;
                    break;
                }

        }

        if (!moved) {
            // 이 위치에서는 더 갈 곳 없음 → 백트래킹

            //맨 위에 적었던 백트래킹와 완전 동일
            Point last = st.top();
            st.pop();
            d[last.x][last.y]  = -1;
            if(!st.empty()){
                resumeDir = last.dir +1;
            }


        }
        return numSolution > 0;
    }
    return false; // (find_all=false 인 경우에만 의미 있음)
}

int main() {
    int num;
    // 모든 시작점에서 탐색 (원하면 특정 시작점만 시도 가능)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (solveKnightTourFrom(i, j) && !find_all) {
                cout << "\n첫 해를 (" << i << "," << j << ") 시작에서 찾았습니다.\n";
                cout << "총 해 수(누적): " << numSolutions << "\n";
                return 0;
            }
        }
    }
    if (find_all)
        cout << "\n총 해 수: " << numSolutions << "\n";
    else
        cout << "\n해를 찾지 못했습니다.\n";
    cin >> num;
    return 0;
}
