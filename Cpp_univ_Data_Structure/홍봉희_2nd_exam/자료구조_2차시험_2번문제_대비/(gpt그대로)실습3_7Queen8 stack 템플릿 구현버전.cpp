#include <iostream>
#include <cstring>
#define ROW 8
#define COL 8

using namespace std;

class Point {
private:
    int ix;
    int iy;
public:
    Point() : ix(0), iy(0) {}
    Point(int x, int y) : ix(x), iy(y) {}
    int getX() const { return ix; }
    int getY() const { return iy; }
    Point& operator=(const Point& other) {
        ix = other.ix; iy = other.iy;
        return *this;
    }
};

// --- 간단한 Stack 템플릿 (요구한 인터페이스: constructor, Push, Pop, IsEmpty) ---
template <class T>
class Stack {
public:
    Stack(int stackCapacity = 10);
    ~Stack();
    bool IsEmpty() const;
    void Push(const T& item);
    T Pop();
private:
    T* stack;
    int top;
    int capacity;
};

template <class T>
Stack<T>::Stack(int stackCapacity) {
    capacity = stackCapacity;
    stack = new T[capacity];
    top = -1;
}
template <class T>
Stack<T>::~Stack() {
    delete[] stack;
}
template <class T>
bool Stack<T>::IsEmpty() const {
    return top == -1;
}
template <class T>
void Stack<T>::Push(const T& item) {
    if (top + 1 >= capacity) {
        // 간단 처리: 재할당 없이 에러 출력 (원하면 재할당 추가 가능)
        cerr << "Stack overflow\n";
        return;
    }
    stack[++top] = item;
}
template <class T>
T Stack<T>::Pop() {
    if (IsEmpty()) {
        cerr << "Pop from empty stack\n";
        return T(); // 기본값 반환
    }
    return stack[top--];
}

// --- 다음 함수들은 사용자가 이미 구현해 둔 것으로 가정 ---
// bool checkRow(...), checkCol(...), checkDiagSW(...), checkDiagSE(...), checkMove(...)
// int nextMove(int d[][COL], int row, int col);
// void showQueens(int d[][COL]);
// (이전 답변의 안정적인 구현을 그대로 사용하세요.)

// 아래는 nextMove와 showQueens의 예시 구현 (필요하면 대체하세요).
bool checkRow(int d[][COL], int crow) {
    for (int j = 0; j < COL; ++j) if (d[crow][j] == 1) return false;
    return true;
}
bool checkCol(int d[][COL], int ccol) {
    for (int i = 0; i < ROW; ++i) if (d[i][ccol] == 1) return false;
    return true;
}
bool checkDiagSW(int d[][COL], int cx, int cy) {
    for (int x = cx+1, y = cy-1; x < ROW && y >= 0; ++x, --y) if (d[x][y] == 1) return false;
    for (int x = cx-1, y = cy+1; x >= 0 && y < COL; --x, ++y) if (d[x][y] == 1) return false;
    return true;
}
bool checkDiagSE(int d[][COL], int cx, int cy) {
    for (int x = cx+1, y = cy+1; x < ROW && y < COL; ++x, ++y) if (d[x][y] == 1) return false;
    for (int x = cx-1, y = cy-1; x >= 0 && y >= 0; --x, --y) if (d[x][y] == 1) return false;
    return true;
}
bool checkMove(int d[][COL], int x, int y) {
    return checkRow(d,x) && checkCol(d,y) && checkDiagSW(d,x,y) && checkDiagSE(d,x,y);
}
int nextMove(int d[][COL], int row, int col) {
    for (int c = col; c < COL; ++c) if (checkMove(d, row, c)) return c;
    return -1;
}
void showQueens(int data[][COL]) {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) cout << data[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}

// ===================== 요청하신 형태를 최대한 따른 solveQueen =====================
int solveQueen(int d[][COL], bool findAll) { // 주어진 코드 구조를 따름 (Stack<T> 사용)
    // 로컬 변수 초기화
    int count = 0;
    int ix = 0, iy = 0;
    Stack<Point>* st = new Stack<Point>(100);

    // 초기 포인트 생성하여 스택에 넣기 (질문에서 주어진 방식 유지)
    Point *p = new Point(ix, iy);
    d[ix][iy] = 1;
    count++;
    st->Push(*p);

    // 다음 행부터 탐색 시작 (이미 0행(0,0) 채워졌으므로)
    ix = 1;
    iy = 0;

    int solutions = 0;
    Point *px = nullptr;

    while (true) {
        // 해를 찾았는지 (count가 ROW일 때)
        if (count == ROW) {
            showQueens(d);
            ++solutions;
            // 다음 해를 찾기 위해 백트래킹 (마지막에 놓은 퀸을 제거)
            if (st->IsEmpty()) break;
            Point last = st->Pop();
            d[last.getX()][last.getY()] = 0;
            --count;
            ix = last.getX();
            iy = last.getY() + 1;
            continue;
        }

        // 현재 행 ix에서 iy부터 가능한 칸을 찾음
        if ((iy = nextMove(d, ix, iy)) == -1) {
            // 더 놓을 곳이 없다 -> 백트래킹
            if (st->IsEmpty()) break;
            Point last = st->Pop();
            d[last.getX()][last.getY()] = 0;
            --count;
            ix = last.getX();
            iy = last.getY() + 1;
            continue;
        }

        // (ix, iy)에 놓을 수 있으니 놓고 스택에 push
        // px 포인터 방식(요청대로 사용)
        px = new Point(ix, iy);
        d[ix][iy] = 1;
        st->Push(*px);
        ++count;

        // 다음 행으로 이동
        ++ix;
        iy = 0;
    }

    cout << "Total solutions (with initial (0,0) placed): " << solutions << '\n';

    // 정리
    delete p;
    delete px;
    delete st;
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
