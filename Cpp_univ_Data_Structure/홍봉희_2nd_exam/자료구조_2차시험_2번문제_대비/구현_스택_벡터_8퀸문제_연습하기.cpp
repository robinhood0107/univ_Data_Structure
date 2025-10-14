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
    return true;
}

bool checkCol(const vector<vector<int>>& d, int ccol) {
    //마찬가지로 ccol 고정 후 row의 모든 경우 보기
    for(int i=0; i<ROW; i++){
        if(d[i][ccol] == 1) return false;
    }
    return true;
}

bool checkDiagSW(const vector<vector<int>>& d, int cx, int cy) { // x++, y-- or x--, y++
    //서로 다른 증감 --> 남서SW 북동

    //초깃값!! => x가 cx++ y가 cy--일때
    //x,y를 x++ y-- 하겠금 조작
    //조건식은 항상 < Row(인덱스는 7까지..)를 쓰고 >=0을 쓴다
    //if식 검사에서 무조건 x,y집어 넣어서 d[x][y] == 1인지(Queen 존재)로 false여부 결정
    //남서
    for(int x = cx+1, y = cy-1; x < ROW && y >= 0; x++, y--){
        if(d[x][y] == 1) return false;
    }

    //북동
    for(int x = cx-1, y = cy+1; x >= 0 && y < COL; x--, y++){
        if(d[x][y] == 1) return false;
    }

    return true;
}

bool checkDiagSE(const vector<vector<int>>& d, int cx, int cy) { // x++, y++ or x--, y--
    //서로 같은 증감 --> 남동SE 북서

    //반드시 cx+1와 같은 꼴을 사용할 것

    //남동
    for(int x = cx+1, y = cy+1; x < ROW && y < COL; x++, y++){
        if(d[x][y] == 1) return false;
    }

    //북서
    for(int x = cx - 1, y = cy - 1; x >= 0 && y >= 0; x--, y--) {
        if (d[x][y] == 1) return false;
    }

    return true;
}

bool checkMove(const vector<vector<int>>& d, int x, int y) { // (x,y) 가능?
    //여긴 그냥 return값 통채로 외워주면 됨//한줄임
    return checkRow(d,x) && checkCol(d,y) && checkDiagSW(d,x,y) && checkDiagSE(d,x,y);
}

int nextMove(const vector<vector<int>>& d, int row, int col) { // row에서 다음 col
    //주어진 row값에서부터 col을 순회해서 checkMove가 true일 경우 첫번째 col반환
    //주어진 row값에서부터 col을 순회하는데 전부 안되면 -1 출력

    if (row >= ROW) {
        return -1;
    }// [수정] ix가 체스판 범위를 벗어났을 때 안전하게 -1을 반환하도록 함수 수정


    for (int nextCol = col; nextCol < COL; ++nextCol) {
        if (checkMove(d, row, nextCol)) return nextCol;
        //이렇게 check를 통해서 맞을 경우 c를 반환한다
    }
    //전부 돌렸지만 없다면 -1 반환
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
    
    //0행 0열에 퀸을 먼저 배치
    d[ix][iy] = 1;
    st.emplace(ix, iy);
    count++;

    ix++; //위에서 퀸을 먼저 배치했으므로 다음 행(1행)으로 이동한다. 그래서 x(row)를 1 올림.

    while (true) {
        if (st.empty() && ix == 8)
            break;

        //if문 => nextmove를 사용해서 다음행에 놓을 수 없으면(-1일경우) stack에서 꺼내서 pop(삭제) <--이걸 백트래킹(물리기)=이전상태 복원 이라고 함
        //놓을 수 있으면 다시 stack에 집어넣기
        if ((iy = nextMove(d, ix, iy)) == -1) {
            if (st.empty())
                break;

            //주의!!!!!! 항상 top 먼저!!    
            Point last = st.top(); //스택에 있는 top을 last로 이름짓고 //stack stl 사용하려면 이렇게 해줘야 함
            st.pop();
            d[last.getX()][last.getY()] = 0; //해당 퀸 제거
            --count; //카운트 내리고
            //ix, iy를 last.getX(),last.getY()+1으로 지정하는데 last.getY()+1으로 하는 이유는 "방금 제거한 퀸 다음 열을 조사하라는 것"으로 (row, col)은 시도했으니까 다음 "열"로 넘어가는 것
            ix = last.getX();
            iy = last.getY() + 1;
            continue;// [핵심 수정 1] 이 continue를 통해 아래의 퀸 배치 코드를 건너뜀
        }

        Point px(ix, iy);
        d[ix][iy] = 1;
        
        st.push(px);
        count++;
        ix++;
        iy = 0;

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
