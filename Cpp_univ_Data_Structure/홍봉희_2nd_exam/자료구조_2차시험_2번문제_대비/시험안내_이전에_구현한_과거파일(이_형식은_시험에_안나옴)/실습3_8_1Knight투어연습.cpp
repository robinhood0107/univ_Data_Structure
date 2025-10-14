#include <iostream>
#include <stack>

using namespace std;

struct Offset { int a, b; };
struct Point { int x, y, dir; }; // dir: 이 위치로 들어올 때 사용한 이동 인덱스

// ----- 설정 -----
constexpr int N = 5;            // 보드 크기 (원하면 6,7,8 등으로 변경) 
//왜 7이나 8로 하면 안됨?
/*
8의 경우....

모든 가능성을 하나씩 시도하는 단순 백트래킹(backtracking) 방식이라 8x8 체스판의 모든 해를 찾는 데는 수십 년 이상, 혹은 수백 년이 걸릴 수도 있습니다.

나이트 투어의 해는 경로의 종류에 따라 크게 두 가지로 나뉩니다.

열린 경로 (Open Tours): 시작점과 끝점이 다른 경우입니다.

총 19,591,828,170,979,904개 (약 1경 9591조 개)

닫힌 경로 (Closed Tours): 나이트가 마지막 칸에서 한 번 더 움직여 시작점으로 돌아올 수 있는 경우입니다.

총 26,534,728,821,064개 (약 26조 5347억 개)

사용자께서 작성하신 코드는 시작점과 끝점이 다를 수 있는 열린 경로를 찾는 방식입니다.

혹시 더 공부하고 싶으면 바른스도르프 규칙(Warnsdorff's rule)을 찾아봐라
*/
constexpr bool find_all = false; // true: 모든 해 탐색, false: 첫 해에서 종료

// 8가지 나이트 이동
Offset moves[8] = {
    {-2, -1}, {-2,  1}, {-1,  2}, { 1,  2},
    { 2,  1}, { 2, -1}, { 1, -2}, {-1, -2}
};

int board[N][N];     // 방문 순서 기록 (-1: 미방문)
long long numSolutions = 0;

// (내가 작성)보드를 -1로 초기화하는 함수
inline void initBoard() {
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) board[i][j] = -1;
}

// (내가 작성)(x, y)가 보드 범위 내에 있는지 확인하는 함수
inline bool inRange(int x, int y) {
    return (0 <= x && x < N && 0 <= y && y < N);
}

// (내가 작성)(x, y)로 이동할 수 있는지 (범위 내이고 아직 방문하지 않았는지) 확인하는 함수
inline bool isSafe(int x, int y) {
    return inRange(x, y) && board[x][y] == -1;
}

// (내가 작성)현재 보드 상태를 출력하는 함수
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

    // 시작점 처리
    st.push({ sx, sy, -1 }); // dir: 시작점은 이동해서 온 것이 아니므로 -1
    board[sx][sy] = 0;       // 0번째 방문

    int resumeDir = 0; // 현재 top에서 다음에 시도할 이동 인덱스 즉, // N-Queens의 iy(다음 시도할 열)와 같은 역할

    while (!st.empty()) {
        // 모든 칸 방문 완료 
        //(내가 적음 = (N-Queens에서 count == 8과 동일한 논리))
        if ((int)st.size() == N * N) {
            showBoard();
            ++numSolutions;
            if (!find_all) return true;

            // 계속 탐색을 위해 백트래킹
            //empty break는 안해도 됨 while문이 커버해주고 있음
            
            // 모든 해를 찾기 위해 백트래킹 (N-Queens에서 해를 찾고 백트래킹하는 부분과 동일)
            Point last = st.top();
            st.pop();
            board[last.x][last.y] = -1; // 방문 기록 취소(백트래킹)

            // 핵심: 이전 위치로 돌아가서, 'last'로 올 때 시도했던 방향(dir)의 "다음" 방향부터 탐색 재개
            resumeDir = last.dir + 1; // 이전 위치에서 시도했던 방향 다음부터 탐색
            continue; // 루프의 시작으로 돌아가 탐색 계속 // while 루프의 처음으로 돌아가 새 resumeDir로 탐색 시작 
        }

        Point cur = st.top();
        bool moved = false;

        // 현재 위치에서 resumeDir부터 8방향 시도 
        // (내가 적음) 현재 위치에서 다음 이동 8가지 탐색 (N-Queens의 nextMove 찾는 과정과 유사)
        for (int d = resumeDir; d < 8; ++d) {
            int nx = cur.x + moves[d].a;
            int ny = cur.y + moves[d].b;

            if (isSafe(nx, ny)) {
                // 다음 위치를 찾았을 경우 (N-Queens에서 퀸을 놓을 자리를 찾은 것과 동일)
                board[nx][ny] = st.size(); // 방문 순서 기록
                st.push({ nx, ny, d }); // 다음 위치와 '이동한 방향'을 스택에 저장
                
                resumeDir = 0; // 새로운 위치에서는 0번 방향부터 다시 탐색
                moved = true;
                break; // 다음 위치를 찾았으므로 for 루프 탈출
            }
        }

        if (!moved) {
            // 이 위치에서는 더 갈 곳 없음 → 백트래킹

            //(내가 적음)
            // 백트래킹
            Point last = st.top();
            st.pop();
            board[last.x][last.y] = -1; // 현재 위치 방문 기록 취소
            if (!st.empty()) {
                 // 이전 위치로 돌아가서, 이전에 시도했던 방향(last.dir) 다음부터 탐색
                resumeDir = last.dir + 1;
            }
        }
    }
    return false; // (find_all=false 인 경우에만 의미 있음) //(numSolutions > 0)와 같음
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
