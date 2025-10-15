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
    //row고정하고 col 움직임
    //queen이 있으면(1) false
    for(int j=0; j< COL; j++){
        if(d[crow][j] == 1){ return false;}
    }
    return true;
}


bool checkCol(const vector<vector<int>>& d, int ccol) {
    for(int i=0; i<ROW; i++){
        if(d[i][ccol] == 1){ return false;}
    }
    return true;
}

bool checkDiagSW(const vector<vector<int>>& d, int cx, int cy) { // x++, y-- or x--, y++
    //서로 다르게 증가하는 경우
    for(int x = cx+1, y = cy-1; x < ROW && y >= 0; x++, y--){
        if(d[x][y] == 1) { return false;}
    }
    for(int x = cx-1, y = cy+1; x >=0 && y < COL; x--, y++){
        if(d[x][y] == 1) { return false;}
    }
    return true;
}

bool checkDiagSE(const vector<vector<int>>& d, int cx, int cy) { // x++, y++ or x--, y--
    for(int x = cx+1, y = cy+1; x < ROW && y < COL; x++, y++){
        if(d[x][y] == 1) { return false;}
    }

    for(int x = cx-1, y = cy-1; x >= 0 && y >= 0; x--, y--){
        if(d[x][y] == 1) { return false;}
    }
    return true;
}

bool checkMove(const vector<vector<int>>& d, int x, int y) { // (x,y) 가능?
    return checkRow(d,x) && checkCol(d,y) && checkDiagSW(d,x,y) && checkDiagSE(d,x,y);
}

int nextMove(const vector<vector<int>>& d, int row, int col) { // row에서 다음 col
    //이거 원리를 외워가야 됨. 주어진 row값에서 col 돌리면서 checkMove가 true이면 첫번째 col 반환
    //아니면 return -1;
    //내가 틀린 부분
    if (row >= ROW){
        return -1;
    }//이렇게 row 값이 ROW보다 같거나 커지면(인덱스 벗어나면) 무조건 -1 하도록 해줘야 정상작동하게 됨

    //for문에 어쩌피 내가 구하는 것은 nextcol을 구하는 것이기 때문에 이걸 for문 이터레이터로
    for(int nextCol = col; nextCol < COL; ++nextCol ){
        if(checkMove(d,row,nextCol)) return nextCol;
    }
    return -1;
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

    //1.가장 먼저 0,0에 퀸을 배치 함
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

                //백트래킹 수행
                Point last = st.top(); //저장해두고
                st.pop(); //stack에서 하나 빼기

                //stack에서 제거했으니 해당 퀸을 제거함
                d[last.getX()][last.getY()] = 0;
                //퀸 카운트 하나 내리고
                count--;
                //이제 다음 y로 1을 올려야 하기 때문에
                //옳지 않은 퀸이라 잘못 stack에 올린거 없애버렸으니까 다음 열을 조사하는 것
                ix = last.getX();
                iy = last.getY() + 1;
                //주의!!! 제일 마지막에 반드시 continue; 살아 있어야 함
                continue;
        }

        Point px(ix, iy);
        d[ix][iy] = 1;

        //해당 좌표에 넣는 과정 및 다음으로 넘어가기(iy는 0으로 하고)

        //퀸이 들어갈 자리가 맞다면 해당 좌표를 스택에 넣어버리면 됨
        //그리고 찾았으니까 행 올리면 된다
        st.push(px);
        count++; //카운트 올리는거 잊지마라
        ix++;
        iy = 0; //이제 다음행 처음부터!

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
