#include <iostream>
#include <vector>
#include <stack>

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
    int getX() { return ix; }
    int getY() { return iy; }
    void setX(int x) { ix = x; }
    void setY(int y) { iy = y; }
    friend ostream& operator<<(ostream& os, Point px);
};

ostream& operator<<(ostream& os, Point px) {
    os << "(" << px.ix << ", " << px.iy << ")" << endl;
    return os;
}

/* ===== vector 인자 검사 함수들 ===== */
bool checkRow(const vector<vector<int>>& d, int crow) {
}

bool checkCol(const vector<vector<int>>& d, int ccol) {

}

bool checkDiagSW(const vector<vector<int>>& d, int cx, int cy) { // x++, y-- or x--, y++

}

bool checkDiagSE(const vector<vector<int>>& d, int cx, int cy) { // x++, y++ or x--, y--

}

bool checkMove(const vector<vector<int>>& d, int x, int y) { // (x,y) 가능?
  
}

int nextMove(const vector<vector<int>>& d, int row, int col) { // row에서 다음 col

        if (checkMove(d, row, nextCol))

}

/* ===== vector 버전 출력 ===== */
void showQueens(const vector<vector<int>>& data) {
   
    }
}

/* ===== STL stack 사용 버전 ===== */
void solveQueen(vector<vector<int>>& d) {
    int count = 0;
    int ix = 0, iy = 0;

    std::stack<Point> st;          // ← STL stack

    ix++;

    while (true) {
        if (st.empty() && ix == 8)
            break;

        if ((iy = nextMove(d, ix, iy)) == -1) {
            if (st.empty())
                break;



        }

        Point px(ix, iy);
        d[ix][iy] = 1;


        if (count == 8) {
            showQueens(d);

            continue;
        }
    }
}

void main() {
    const int row = ROW, col = COL;
    vector<vector<int>> data(row, vector<int>(col, 0)); // 배열 → vector
    solveQueen(data);
    system("pause");
    return;
}
