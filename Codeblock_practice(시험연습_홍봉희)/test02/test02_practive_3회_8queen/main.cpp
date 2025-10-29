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
    //row 고정
}

bool checkCol(const vector<vector<int>>& d, int ccol) {
    //ccol고정
}

bool checkDiagSW(const vector<vector<int>>& d, int cx, int cy) { // x++, y-- or x--, y++

}

bool checkDiagSE(const vector<vector<int>>& d, int cx, int cy) { // x++, y++ or x--, y--

}

bool checkMove(const vector<vector<int>>& d, int x, int y) { // (x,y) 가능?
    return //4개 전부 and로 묶어주면 됨
}

int nextMove(const vector<vector<int>>& d, int row, int col) { // row에서 다음 col
    if(row >= ROW){
        return -1;
    }
    for(int nextCol = col; nextCol < COL; nextCol++){
        if (checkMove(d, row, nextCol)) return nextCol;
        }
    return false;

}

/* ===== vector 버전 출력 ===== */
void showQueens(const vector<vector<int>>& data) {
    //for 중첩 그냥 하면 됨
}

/* ===== STL stack 사용 버전 ===== */
void solveQueen(vector<vector<int>>& d) {
    int count = 0;
    int ix = 0, iy = 0;

    std::stack<Point> st;          // ← STL stack

    //초깃값 설정
    d[ix][iy] = 1;
    st.emplace(ix,iy);
    count++;


    ix++;

    while (true) {
        if (st.empty() && ix == 8)
            break;

        if ((iy = nextMove(d, ix, iy)) == -1) {
            if (st.empty())
                break;

                //백트래킹
                Point last = st.top();
                st.pop();
                d[last.getX()][last.getY()] = 0; //퀸 삭제

                //내가 틀린 부분!!!!
                count--; //카운트 무조건 감소시켜!!!!

                //ix, iy를 반드시 재지정하기!!!
                ix = last.getX();
                iy = last.getY()+1;
                continue;//이거 필수다

        }

        Point px(ix, iy);
        d[ix][iy] = 1;

        st.push(px);
        count++;
        //여기는 반드시 ix를 증가시키고 y를 0으로 하기



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
