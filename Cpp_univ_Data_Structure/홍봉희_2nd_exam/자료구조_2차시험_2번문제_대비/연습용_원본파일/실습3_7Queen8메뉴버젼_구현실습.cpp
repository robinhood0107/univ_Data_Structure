/*
* backtracking 알고리즘 
* 1. 8-Queen 문제로 8x8 배열에 8개의 Queen을 가로, 세로, 대각선으로 collision이 발생하게 배치
* 2. 1개의 해를 구하는 경우 선택 실행 > enum으로 메뉴 구현 
* 3. 92개의 해를 모두 구하는 경우 선택 실행 > enum으로 메뉴 구현 
* stack은 template으로 예외 클래스를 구현하여 throw, try {] catch(){} 구현
* recursive 알고리즘으로 구현하면 안되며 stack을 사용한 non-recursive 알고리즘 구현
* nextMove() 함수를 사용하여 구현 필수 
* 후속실습 대상: knight를 8x8에 collision 없이 최대 배치할 때 최대 갯수를 구하는 문제에 도전  
*/
#include <iostream>
#define ROW 8
#define COL 8

using namespace std;

class Point {
private:
    int ix;
    int iy;
public:
    
};


template <class T>
class Stack {
public:
    Stack(int stackCapacity = 10);
    bool IsEmpty() const;
    T& Top() const;
    void Push(const T& item);
    T& Pop();
private:
    T* stack;
    int top;
    int capacity;
};

//사담: stack은 "이전 상태를 저장/복구" 하는 자료구조라고 생각하면 됨. 그래서 BFS,DFS,괄호 검사 등등 여러곳에서 이전상태를 가져와야하면 stack을 씀



bool checkRow(int d[][COL], int crow) {
    //행에 Queen을 놓을 수 있는지
}

bool checkCol(int d[][COL], int ccol) {
    //열에 Queen을 놓을 수 있는지
}

bool checkDiagSW(int d[][COL], int cx, int cy) { // x++, y-- or x--, y++
    //현재 위치가 cx, cy일때 (남서=북동)대각선 1가지 경우(x, y 움직임 다름)
}

bool checkDiagSE(int d[][COL], int cx, int cy) { // x++, y++ or x--, y--
    //현재 위치가 cx, cy일때 (남동=북서)대각선 1가지 경우(x, y 움직임 같음)
}

bool checkMove(int d[][COL], int x, int y) {
    //위의 4가지 함수들을 이용해서 (x,y)에 배치할 수 있는지 검사



    return checkRow(d, x) && checkCol(d, y) && checkDiagSW(d, x, y) && checkDiagSE(d, x, y);
}

int nextMove(int d[][COL], int row, int col) {

    //주어진 행 row의 col부터 시작하여 queen을 배치할 수 있는 첫 번째 col을 반환
    //주어진 행 row의 col부터 나머지 col에 배치할 수 없는 경우라면 -1 반환
    
    // (checkMove(d, row, nextCol))를 사용하여 구현

}

void showQueens(int data[][COL]) {
    
}


//알고리즘 (백트래킹 알고리즘)
int solveQueen(int d[][COL], bool findAll) {
    int count = 0;
    int ix = 0, iy = 0;
    Stack<Point> st(100);
    Point p(ix, iy);
    d[ix][iy] = 1;
    count++;
    st.Push(p);
    
    int solutions = 0;
    while (true) {
        if (ix == 8) {
            showQueens(d);
            solutions++;
            if (!findAll) break; // 하나의 해만 찾으면 종료
            
            continue;
        }
            //if문 => nextmove를 사용해서 다음행에 놓을 수 없으면(-1일경우) stack에서 꺼내서 pop(삭제) <--이걸 백트래킹(물리기)=이전상태 복원 이라고 함
            
            //놓을 수 있으면 다시 stack에 집어넣기

            //카운트가 꽉 찻을 경우(순회 다했을 경우)
            //그 다음 판을 조사
        }
    }
    return solutions;
}

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