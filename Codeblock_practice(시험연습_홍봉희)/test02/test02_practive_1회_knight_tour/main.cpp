#include <iostream>
#include <stack>

using namespace std;

struct Offset { int a, b; };
struct Point { int x, y, dir; };

// ----- 설정 -----
constexpr int N = 5;

constexpr bool find_all = false; // true: 모든 해 탐색, false: 첫 해에서 종료

// 8가지 나이트 이동
Offset moves[8] = {
    {-2, -1}, {-2,  1}, {-1,  2}, { 1,  2},
    { 2,  1}, { 2, -1}, { 1, -2}, {-1, -2}
};

int board[N][N];     // 방문 순서 기록 (-1: 미방문)
long long numSolutions = 0;


inline void initBoard() {
    //initBoard니까 처음인 미방문인 -1로 초기화하는 함수임
    //2중 for문으로 전부 초기화
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            board[i][j] == -1;
        }
    }
}


inline bool inRange(int x, int y) {
    //inRange 말그대로 범위 내에 있는지 확인
    //0~N 사이어야만 함 그리고 인덱스니까 당연 <N 이고
    return (0 <= x) && (x < N) && (0 <= y) && (y < N);
}


inline bool isSafe(int x, int y) {
    //(x,y)가 아직 미방문 한것 찾는 함수(미방문이어야 true)
    //-1이면 미방문이라 참

    //inRange에 있으면서 board가 -1이면 됨
    return inRange(x,y) && board[x][y] == -1;
}


void showBoard() {
    cout << '\n';
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
}

bool solveKnightTourFrom(int sx, int sy) {
    //여기도 매우 중요함
    //여기를 좀 빡세게 외워줘야 함

    //백트래킹이 2개인 이유 --> nqueen은 움직이는게 1개였고(y) knight는 움직이는게 2개니까

    stack<Point> st;
    initBoard();

    //여기 point의 경우에는 꼭 push({,,}) 이렇게 넣어라

    //1.입력받은 시작점을 stack에 집어넣고 방문처리 하기(0으로)
    st.push({ sx, sy, -1 }); //시작점의 경우 초깃값dir이라 -1로 설정해줘야 함.
    board[sx][sy] = 0;

    int resumeDir = 0; //이 변수가 nqueen에서 iy와 같이 "다음에 탐색할 dir"임

    while(!st.empty()){
        //항상 백트래킹 할때 3가지 경우 생각을 하셈

        //1.모든칸을 전부 방문했을 경우 "백트래킹으로 다음 dir로"
        //2.지금상태 저장 후에 8가지 탐색 isSafe()할 경우 stack에 올바르게 저장 후 resumeDir=0으로 초기화
        //3.최종 실패했을 경우도 마찬가지로 1과 같이 "백트래킹으로 다음 dir로"(1과 정확하게 똑같음)

        //이 3가지 if문을 만들면 됨

        if(st.size() == N * N){ //전부 다 방문해서 stack이 N*N만큼 된 경우
            //출력
            showBoard();
            ++numSolutions; //내가 구하고자하는 최종 답임
            if(!find_all) return true;

            //여기서는 원래는 st.empty계속 체크 해야 하는데 whlie문에서 계속 체크해주고 있는 상태임

            //백트래킹(다음 dir로 이동함!)
            Point last = st.top();
            st.pop();
            board[last.x][last.y] = -1; //방문 취소
            resumeDir = last.dir +1; //다음 dir로!

            //last.dir보다 1크게 방문!
            continue;
        }

        Point cur = st.top(); //현재 저장
        bool moved = false; //실패했는지 아닌지 확인


        //이 함수 짜는것도 엄청 중요함
        for (int d = resumeDir; d < 8; ++d){
            int nx = cur.x + moves[d].a;
            int ny = cur.y + moves[d].b; //cur에 move 더하기

            //isSafe일 경우 stack에 저장하고 resumeDir = 0; moved = true; 하고 바로 break로 빠져나오기
            if(isSafe(nx,ny)){
                board[nx][ny] = st.size(); //방문순서 기록함
                st.push({ nx, ny, d });

                resumeDir = 0;
                moved = true;
                break;
            }
        }

        //최종 실패했을 경우
        //moved 값으로 판별함
        if (!moved) {
            //백트래킹(1번과 같이 위랑 진짜 똑같음)
            Point last = st.top();
            st.pop();
            board[last.x][last.y] = -1; //방문 취소
            resumeDir = last.dir +1; //다음 dir로!
        }
    }
    //마지막에 false 반환 꼭 해주기(한번 더 해라는 뜻)
    return false;
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

