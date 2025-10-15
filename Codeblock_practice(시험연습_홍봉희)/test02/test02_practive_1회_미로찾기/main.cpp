#pragma once
#include <iostream>
#include <memory>
#include <fstream>
#include <stack>

using namespace std;
#define MaxSize 100
const int DefaultSize = 100;

struct items {
    int x, y, dir;
};

//--- 실행시 예외: 스택이 비어 있음 ---//
class EmptyStackException : public std::exception {
public:
    EmptyStackException() {}
    const char* what() const noexcept override {
        return " 빈 Stack.";
    }
};

//--- 실행시 예외: 스택이 가득 참 ---//
class OverflowStackException : public std::exception {
public:
    OverflowStackException() {}
    const char* what() const noexcept override {
        return "full Stack.";
    }
};

template <class T>
class Bag {
public:
    Bag(int bagCapacity = 10);
    ~Bag();
    bool IsFull();
    int Size() const;
    bool IsEmpty() const;
    virtual T& Pop();
    virtual void Push(const T&);
protected:
    T* array;
    int capacity;
    int top;
};



template <class T>
class Stack : public Bag<T> {
public:
    Stack(int MaxStackSize = DefaultSize);
    T& Pop();
    void Push(const T&);
    T& Peek() const;
    void Dump();
};


struct offsets {
    int a, b;
};

enum directions { N, NE, E, SE, S, SW, W, NW };
offsets moves[8];
int maze[100][100];
int mark[100][100];

// 메뉴 옵션을 위한 enum
enum MenuOption { INIT_MAZE = 1, FIND_PATH, SHOW_RESULT, EXIT };

void initializeMaze() {
    int input[12][15] = {
        { 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1 },
        { 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1 },
        { 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0 },
        { 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1 },
        { 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1 },
        { 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1 },
        { 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 },
        { 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0 },
    };

    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 17; j++) {
            /*
            * maze[], mark[] 테이블 초기화
            */

            //이게 굉장히 중요함
            //여기는 maze와 mark를 합친다고 생각해야 한다 !!!!
            //합성은 if else로 하는데
            //if 제일 벽은 무조건 1 ((i == 0)(!i도 됨) || (j == 0)(!j도 됨) || (i == 13) || (j == 16))
            //else(나머지는 maze에가다 내 input지도를 [i-1][j-1]로 하나하나 박아 넣으면 됨)
            //이건 거의 반드시 낼 것 같아서 그대로 암기해주기

            if ((i == 0) || (j == 0) || (i == 13) || (j == 16)){
                maze[i][j] == 1;
            }
            else{
                maze[i][j] = input[i-1][j-1];
            }
            mark[i][j] = 0; //미로 기록용 mark는 모든 원소를 0으로 초기화
        }
    }

    cout << "Maze initialized.\n";
}

void showMatrix(int d[][100], int row, int col) {
    for (int i = 0; i <= row; i++) {
        for (int j = 0; j <= col; j++) {
            cout << d[i][j] << " ";
        }
            cout << endl;
        }
}

void findPath(int m, int p) {
    try {

        //항상 모든 백트래킹의 시작은 시작점 정하는 것부터 시작임
        //시작은 1,1이라고 주어짐
        //출발점 (1,1), 이동 방향 dir = 2(동쪽)을 스택에 push (물론 상황 맞춰야겠지만 일단 이게 기본)
        stack<items> st;
        items temp;
        temp.x = 1;
        temp.y = 1;
        temp.dir = E;
        st.push(temp);

        while(!st.empty()){

            //stack의 top의 요소들 꺼내서 변수에 저장
            temp = st.top();
            st.pop();
            int i = temp.x;
            int j = temp.y;
            int d = temp.dir;

            //8방향 탐색
            while (d < 8){
                int g = i + moves[d].a;
                int h = j + moves[d].b;
                //다음 이동 좌표는 이런식으로 적는다
                //knight에서 cur+move[d].a 했던껏처럼 진짜 똑같이 함
                //g, h는 의미없는 걍 ijk...이런 이름

                    //1. 출구 찾았을 경우
                //출구가 m,p로 파라미터로 주어짐
                //이동좌표랑 findPath의 파라미터의 m,p랑 같으면 성공한거
                if ((g == m) && (h == p)){
                    mark[g][h] = 2;
                    mark[i][j] = 2;
                    //현재 위치와 출구를 전부 2로 표시
                    cout << "the term near the exit: " << i << " " << j << endl;
                    cout << "exit: " << m << " " << p << endl;
                    return;
                    //걍 출구 찾았으므로 return;으로 함수 자체를 걍 빠져나오면 된다
                }


                    //2.아직 미로 중간

                    //여기 if 조건은 maze도 0이고 mark도 0인, 갈수 있고 방문 한걸 if 조건문으로 넣기
                    //간단히 말해서 (maze[g][h] == 0) && (mark[g][h] == 0) 이렇게 동시에 0되는 조건

                    //2.1 갈수 있으면
                    if ((maze[g][h] == 0) && (mark[g][h] == 0)){
                            mark[g][h] = 1;//방문했다고 표시하고

                            //백트래킹!!!!
                            temp.x = i;
                            temp.y = j;
                            temp.dir = d + 1; //dir 하나 증가시키기
                            st.push(temp);


                            //찾았으니까 방향은 처음으로 다시 설정함
                            i = g;
                            j = h;
                            d = N;
                    }
                    else{//못간다면
                        d++; //다음 direction으로 //이거 중요함
                    }
            }
            // 8방향 다 막혔을 때 (백트래킹)
            mark[i][j] = 0;
            maze[i][j] = 0;
            //while문 안에 제일 마지막에 이렇게 다 막혔다고 0으로 기록
            }
        cout << "no path in maze " << endl;
    }
    catch (const EmptyStackException& e) {
        cout << "스택 empty 예외 발생." << endl;
    }
    catch (const OverflowStackException& e) {
        cout << "스택 overflow 예외 발생." << endl;
    }
}

int main() {
    moves[N].a = -1; moves[N].b = 0;
    moves[NE].a = -1; moves[NE].b = 1;
    moves[E].a = 0; moves[E].b = 1;
    moves[SE].a = 1; moves[SE].b = 1;
    moves[S].a = 1; moves[S].b = 0;
    moves[SW].a = 1; moves[SW].b = -1;
    moves[W].a = 0; moves[W].b = -1;
    moves[NW].a = -1; moves[NW].b = -1;

    int choice;
    while (true) {
        cout << "1. Initialize Maze\n2. Find Path\n3. Show Result\n4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case INIT_MAZE:
            initializeMaze();
            break;
        case FIND_PATH:
            findPath(12, 15);
            break;
        case SHOW_RESULT:
            showMatrix(mark, 12, 15);
            break;
        case EXIT:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
