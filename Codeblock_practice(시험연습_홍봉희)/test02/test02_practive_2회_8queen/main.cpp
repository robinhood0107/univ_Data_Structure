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
    //crow는 고정
    for(int j = 0; j < COL; j++){
        if( d[crow][j] == 1 ) return false;
    }
    return true;
}

bool checkCol(const vector<vector<int>>& d, int ccol) {
    for(int i = 0; i < ROW; i++){
        if( d[i][ccol] == 1 ) return false;
    }
    return true;
}

bool checkDiagSW(const vector<vector<int>>& d, int cx, int cy) { // x++, y-- or x--, y++
    for(int x = cx+1, y = cy-1; x < ROW && y >= 0; x++,y--){
        if( d[x][y] == 1 ) return false;
    }
    for(int x = cx-1, y = cy+1; x < ROW && y >= 0; x++,y--){
        if( d[x][y] == 1 ) return false;
    }
    return true;
}

bool checkDiagSE(const vector<vector<int>>& d, int cx, int cy) { // x++, y++ or x--, y--
    for(int x = cx+1, y = cy+1; x < ROW && y >= 0; x++,y++){
        if( d[x][y] == 1 ) return false;
    }
    for(int x = cx-1, y = cy-1; x < ROW && y >= 0; x--,y--){
        if( d[x][y] == 1 ) return false;
    }
    return true;
}

bool checkMove(const vector<vector<int>>& d, int x, int y) { // (x,y) 가능?
    return checkRow(d,x) && checkCol(d,y) && checkDiagSW(d,x,y) && checkDiagSE(d,x,y);
}

int nextMove(const vector<vector<int>>& d, int row, int col) { // row에서 다음 col

    //이게 중요함
    //row는 checkmove에 고정한 상태로 col부터을 전체적으로 확인하는 것
    // nextcol을 파라미터로
    //맞으면 col, 틀리면 -1

    //반드시 이 row에 대해서 ROW로 범위 제한하기!!! (row >= ROW)면 -1
    if(col >= row){
        return -1;
    }
    for(int nextcol = col; nextcol < COL; nextcol++){
        if(checkMove(d,row,nextcol)) return nextcol;
    }
    return -1;
    //이걸
}

/* ===== vector 버전 출력 ===== */
void showQueens(const vector<vector<int>>& data) {
    for(int i=0; i<ROW; i++){
        for(int j=0; j<COL; j++){
            cout << data[i][j] << ' ';
        }
        cout << "\n";
    }
    cout << "\n";
}

/* ===== STL stack 사용 버전 ===== */
void solveQueen(vector<vector<int>>& d) { //원래는 void였음
    int count = 0;
    int ix = 0, iy = 0;

    std::stack<Point> st;          // ← STL stack



    //내가 틀린 부분~~~~~
    //반드시 기억. 일단 퀸을 초기상태에 놓는 거다!!!
    //초기상태 설정(0,0)
    d[ix][iy] = 0;
    st.emplace(ix,iy);
    count++;

    ++ix;

    while (true) {
        if (st.empty() && ix == 8)
            break;

        if ((iy = nextMove(d, ix, iy)) == -1) {
            if (st.empty())
                break;

                //백트래킹
                Point last = st.top();
                st.pop();
                d[last.getX()][last.getY()] = 0//백트래킹 할때 무조건 전에 있던걸 취소하는 행위는 무조건 해야 함
                ix = last.getX();
                iy = last.getY() +1;
                count--; //카운트 감소 무조건 해주기

                continue;
        }


        //찾았을 경우를 설명
        Point px(ix, iy);
        d[ix][iy] = 1;

        st.push(px);
        count++;
        ix++;
        iy = 0;
        //y를 0으로 초기화하고 x를 1 올린다는 것 기억


        if (count == 8) {
            showQueens(d);
            continue;
        }
    }
}

int main() {
    const int row = ROW, col = COL;
    vector<vector<int>> data(row, vector<int>(col, 0)); // 배열 → vector
    solveQueen(data);
    system("pause");
    return 0;
}
