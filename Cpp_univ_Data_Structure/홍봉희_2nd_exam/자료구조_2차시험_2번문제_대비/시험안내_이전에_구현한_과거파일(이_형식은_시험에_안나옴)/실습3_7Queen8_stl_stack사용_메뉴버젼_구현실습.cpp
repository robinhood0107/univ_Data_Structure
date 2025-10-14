/*
* backtracking 알고리즘 
* 1. 8-Queen 문제로 8x8 배열에 8개의 Queen을 가로, 세로, 대각선으로 collision이 발생하게 배치
* 2. 1개의 해를 구하는 경우 선택 실행 > enum으로 메뉴 구현 
* 3. 92개의 해를 모두 구하는 경우 선택 실행 > enum으로 메뉴 구현 
* recursive 알고리즘으로 구현하면 안되며 stack을 사용한 non-recursive 알고리즘 구현
* nextMove() 함수를 사용하여 구현 필수 
* 후속실습 대상: knight를 8x8에 collision 없이 최대 배치할 때 최대 갯수를 구하는 문제에 도전  
*/
#include <iostream>
#include <stack>
#include <cstring>
#define ROW 8
#define COL 8

using namespace std;

class Point {
private:
    int ix;
    int iy;
public:
    //이 부분 내가 구현해야 함
    Point() { ix = 0; iy = 0; }
    Point(int x, int y) {
    ix = x;
    iy = y;
    }
    int getX() {
        return ix;
    }
    int getY() {
        return iy;
    }
};


// template <class T>
// class Stack {
// public:
//     Stack(int stackCapacity = 10);
//     bool IsEmpty() const;
//     T& Top() const;
//     void Push(const T& item);
//     T& Pop();
// private:
//     T* stack;
//     int top;
//     int capacity;
// };

//일단 stack stl을 사용해서 구현하는거로 초벌작업 해두자
//사담: stack은 "이전 상태를 저장/복구" 하는 자료구조라고 생각하면 됨. 그래서 BFS,DFS,괄호 검사 등등 여러곳에서 이전상태를 가져와야하면 stack을 씀
//embrace() stl 파티션 나누기


bool checkRow(int d[][COL], int crow) {
    //행에 Queen을 놓을 수 있는지
    for (int j = 0; j<COL; ++j){
        //이미 queen이 있다면(==1) false
        if (d[crow][j] == 1) return false;
    }
    return true; //없다면 true
}

bool checkCol(int d[][COL], int ccol) {
    //열에 Queen을 놓을 수 있는지
    for (int i = 0; i<ROW; ++i){
        //이미 queen이 있다면(==1) false
        if (d[i][ccol] == 1) return false;
    }
    return true;
}

bool checkDiagSW(int d[][COL], int cx, int cy) { // x++, y-- or x--, y++
    //현재 위치가 cx, cy일때 (남서=북동)대각선 1가지 경우(x, y 움직임 다름)


    //남서방향(아래로)
    for (int x = cx+1, y = cy-1; x < ROW && y >= 0; ++x, --y){ //ROW보단 < 작아야 하고(인덱스 7까지니까), y는 0보다 커야 함.
        if(d[x][y] == 1) return false;
    }      

    //북동방향(위로)
    for (int x = cx-1, y = cy+1; x >= 0 && y < COL; --x, ++y){ //COL보단 < 작아야 하고(인덱스 7까지니까), y는 0보다 커야 함.
        if(d[x][y] == 1) return false;
    }
    return true; //모두 확인해도 없으면 true    
}

bool checkDiagSE(int d[][COL], int cx, int cy) { // x++, y++ or x--, y--
    //현재 위치가 cx, cy일때 (남동=북서)대각선 1가지 경우(x, y 움직임 같음)


    //남동방향(아래로)
    for (int x = cx+1, y = cy+1; x < ROW && y < COL; ++x, ++y){ //둘다 인덱스 7보단 작아야 하니까 <
        if(d[x][y] == 1) return false;
    }      

    //북서방향(위로)
    for (int x = cx-1, y = cy-1; x >= 0 && y >= 0; --x, --y){ //COL보단 < 작아야 하고(인덱스 7까지니까), y는 0보다 커야 함.
        if(d[x][y] == 1) return false;
    }
    return true; //모두 확인해도 없으면 true    
}

bool checkMove(int d[][COL], int x, int y) {
    return checkRow(d, x) && checkCol(d, y) && checkDiagSW(d, x, y) && checkDiagSE(d, x, y);
    //이렇게 모든 함수들이 전부 1이면 되기 때문에 4개를 전부 AND로 묶어줌
}

int nextMove(int d[][COL], int row, int col) {

    //주어진 행 row의 col부터 시작하여 queen을 배치할 수 있는 첫 번째 col을 반환
    //주어진 행 row의 col부터 나머지 col에 배치할 수 없는 경우라면 -1 반환
    for (int nextCol = col; nextCol < COL; ++nextCol) {
        if (checkMove(d, row, nextCol)) return nextCol;
        //이렇게 check를 통해서 맞을 경우 c를 반환한다
    }
    //전부 돌렸지만 없다면 -1 반환
    return -1;
    
    // (checkMove(d, row, nextCol))를 사용하여 구현

}

void showQueens(int data[][COL]) {
    //2중 for문으로 보기좋게 출력
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) cout << data[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}


//알고리즘 (백트래킹 알고리즘)
//초기엔 (0,0)을 놓고 스택에 emplace로 넣음 
//→ 다음 행으로 진행 
//→ 더 이상 놓을 곳이 없으면 스택에서 pop(백트래킹) 
//→ pop한 위치의 다음 열부터 재시도 
//→ 해를 찾으면 출력 후 백트래킹하여 다음 해 탐색

int solveQueen(int d[][COL], bool findAll) {
    int count = 0;
    int ix = 0, iy = 0;
    stack<Point> st;
    Point p(ix, iy);
    d[ix][iy] = 1;
    count++;
    st.emplace(p);
    
    //지금 이 코드처럼 ix,iy가 0,0으로 이미 stack에 들어가있는 상태라면 반드시 ix=1, iy=0인 상태로 시작해야 한다.
    ix = 1;
    iy = 0;
    
    int solutions = 0;
    while (true) {
        //카운트가 꽉 찻을 경우(순회 다했을 경우)
        //그 다음 판을 조사
        if (count == 8) { //ix ==8; 이랑 count==8; 이랑 똑같은 말임.
            // 모든 행 순회했다면 해를 찾았다는 것 //count==8과 같음
            showQueens(d);
            solutions++;
            if (!findAll) break; // 하나의 해만 찾으면 종료 break로 종료해라 (참고 => "return solutions를 쓰나 break;써서 whlie문 빠져나오나 똑같음"

            //해를 찾았으면 마지막에 놓인 퀸을 제거하고 그 위치의 다음 열부터 시도한다. //나머지 stack을 처리하는 것
            if (st.empty()) break;
            //주의!!!!!! 항상 top 먼저!!
            Point last = st.top(); //스택에 있는 top을 last로 이름짓고 //stack stl 사용하려면 이렇게 해줘야 함
            st.pop();
            d[last.getX()][last.getY()] = 0; //해당 퀸 제거
            --count; //카운트 내리고
            //ix, iy를 last.getX(),last.getY()+1으로 지정하는데 last.getY()+1으로 하는 이유는 "방금 제거한 퀸 다음 열을 조사하라는 것"으로 (row, col)은 시도했으니까 다음 "열"로 넘어가는 것
            ix = last.getX();
            iy = last.getY() + 1;

            continue;
        }
            //if문 => nextmove를 사용해서 다음행에 놓을 수 없으면(-1일경우) stack에서 꺼내서 pop(삭제) <--이걸 백트래킹(물리기)=이전상태 복원 이라고 함
            //놓을 수 있으면 다시 stack에 집어넣기
            if((iy = nextMove(d, ix , iy)) == -1){ //내가 틀린 부분 반드시 괄호로 (iy = nextMove(d, ix , iy)) 이렇게 먼저 감싸주기
                //더이상 놓을 곳이 없으면 백트래킹을 한다
                if (st.empty()) break;
                Point last = st.top();//마찬가지로 위처럼 백트래킹 똑같이 해주면 됨.
                st.pop();
                d[last.getX()][last.getY()] = 0;
                --count;
                ix = last.getX();
                iy = last.getY() + 1;
                continue;
            }

            // (ix, nm)에 퀸을 놓고 스택에 emplace
            //col에 nextMove값이 들어가는거 잊지 말기!!!!

            //방법1
            /*
            d[ix][iy] = 1;
            st.emplace(ix, iy); // emplace 사용
            ++count;
            // 다음 행으로 이동
            ++ix;
            iy = 0;
            */

            //방법2
            d[ix][iy] = 1;
            st.push(Point(ix, iy));
            ++count;
            // 다음 행으로 이동
            ++ix;
            iy = 0;
        }
        return solutions; //"findAll == false", 즉 “해 하나만 찾고 멈출 때” 사용하기 위해 존재
    }

    /*
    여기서 만약 0,0으로 Point를 넣지 않는다면
    1,0으로 만드는 수고를 아예 안하고 그냥 넣어도 됨
    
    int ix = 0, iy = 0;
    stack<Point> st;
    int solutions = 0;

    while (true) {
        int nm = nextMove(d, ix, iy);
        if (nm == -1) { // 더 놓을 곳 없음 -> 백트래킹
            if (st.empty()) break; // 되돌릴 곳 없음 -> 종료
            Point last = st.top(); st.pop();
            d[last.getX()][last.getY()] = 0;
            ix = last.getX();
            iy = last.getY() + 1;
        } else { // 퀸 놓기
            d[ix][nm] = 1;
            st.emplace(ix, nm);
            ++ix;
            iy = 0;
            if (ix == ROW) { // 해를 찾았음
                showQueens(d);
                ++solutions;
                // 마지막 퀸 제거하고 다음 백트래킹
                Point last = st.top(); st.pop();
                d[last.getX()][last.getY()] = 0;
                --ix;
                iy = last.getY() + 1;
            }
        }
    }

    return solution;
    }
    */

// 메뉴 옵션을 위한 enum
enum MenuOption { FIND_ONE_SOLUTION = 1, FIND_ALL_SOLUTIONS, EXIT };

int main() {
    int board[ROW][COL] = { 0 };
    MenuOption choice;
    int input;

    while (true) {
        cout << "1. Find One Solution\n2. Find All Solutions\n3. Exit\n";
        cout << "Choose an option: ";
        cin >> input;
        choice = static_cast<MenuOption>(input);

        switch (choice) {
        case FIND_ONE_SOLUTION: {
            memset(board, 0, sizeof(board));
            cout << "Finding one solution...\n";
            solveQueen(board, false);
            break;
        }
        case FIND_ALL_SOLUTIONS: {
            memset(board, 0, sizeof(board));
            cout << "Finding all solutions...\n";
            int totalSolutions = solveQueen(board, true);
            cout << "Total solutions: " << totalSolutions << endl;
            break;
        }
        case EXIT:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}

/*
5) 백트래킹(Backtracking) 원리 — 간단명료

문제를 단계(보통 재귀에서는 깊이, 비재귀에서는 행/단계 변수)별로 나눕니다. 여기서는 "행(row)"이 단계입니다.

각 단계에서 가능한 모든 선택(여기서는 각 행의 가능한 열)을 시도합니다.

한 선택을 하면(퀸을 놓으면) 다음 단계로 넘어갑니다.

만약 다음 단계에서 더 이상 진행할 수 없으면(충돌이 발생하거나 가능한 위치가 없으면), 마지막 선택을 되돌리고(퀸 제거) 다른 선택을 시도합니다 — 이것이 바로 "백트랙".

목표(8개의 퀸을 모두 놓음)를 달성하면 해(solution)를 기록하고, 문제에 따라 탐색을 멈추거나(하나만 찾기) 계속해서 다른 해도 찾습니다(모두 찾기).

스택 기반(비재귀)에서는 이 되돌리기/복구를 스택의 push/pop 로 관리합니다:

push: 선택(퀸 배치) —> 나중에 되돌릴 수 있게 현재 선택 상태를 스택에 저장.

pop: 되돌리기(퀸 제거) —> 스택에서 꺼낸 정보를 이용해 "어디서부터 다음 선택을 시도할지" 결정.
*/