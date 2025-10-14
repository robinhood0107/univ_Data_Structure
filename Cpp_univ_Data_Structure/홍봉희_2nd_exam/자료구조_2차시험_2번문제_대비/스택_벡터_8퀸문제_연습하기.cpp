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
    //checkrow의 경우 row가 고정된 상태에서 처음부터 끝까지 순회하는 것!!!
    //Queen이 이미 있다면(==1) false인 것 기억하기
    for(int j=0; j<COL; j++){
        if(d[crow][j] == 1) return false;
    }
}

bool checkCol(const vector<vector<int>>& d, int ccol) {
    //마찬가지로 ccol 고정 후 row의 모든 경우 보기
    for(int i=0; i<ROW; i++){
        if(d[i][ccol] == 1) return false;
    }
}

bool checkDiagSW(const vector<vector<int>>& d, int cx, int cy) { // x++, y-- or x--, y++
    //서로 다른 증감 --> 남서SW 북동

    //초깃값!! => x가 cx++ y가 cy--일때
    //x,y를 x++ y-- 하겠금 조작
    //조건식은 항상 < Row(인덱스는 7까지..)를 쓰고 >=0을 쓴다
    //if식 검사에서 무조건 x,y집어 넣어서 d[x][y] == 1인지(Queen 존재)로 false여부 결정
    //남서
    for(int x = cx++, y = cy--; x < ROW && y >= 0; x++, y--){
        if(d[x][y] == 1) return false;
    }

    //북동
    for(int x = cx--, y = cy++; x >= 0 && y < COL; x--, y++){
        if(d[x][y] == 1) return false;
    }
}

bool checkDiagSE(const vector<vector<int>>& d, int cx, int cy) { // x++, y++ or x--, y--
    //서로 같은 증감 --> 남동SE 북서
    //남동
    for(int x = cx++, y = cy++; x < ROW && y < COL; x++, y++){
        if(d[x][y] == 1) return false;
    }

    //북서
    for(int x = cx--, y = cy--; x < ROW && y < COL; x--, y--){
        if(d[x][y] == 1) return false;
    }
}

bool checkMove(const vector<vector<int>>& d, int x, int y) { // (x,y) 가능?
    //여긴 그냥 return값 통채로 외워주면 됨//한줄임
    return checkRow(d,x) && checkCol(d,y) && checkDiagSW(d,x,y) && checkDiagSE(d,x,y);
}

int nextMove(const vector<vector<int>>& d, int row, int col) { // row에서 다음 col
    //주어진 row값에서부터 col을 순회해서 checkMove가 true일 경우 첫번째 col반환
    //주어진 row값에서부터 col을 순회하는데 전부 안되면 -1 출력
    if (checkMove(d, row, nextCol))

}

/* ===== vector 버전 출력 ===== */
void showQueens(const vector<vector<int>>& data) {
    for(const auto& lt : data){
        for(const auto& at : lt){
            cout << at << ' ';
        }
        cout << "\n";
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
