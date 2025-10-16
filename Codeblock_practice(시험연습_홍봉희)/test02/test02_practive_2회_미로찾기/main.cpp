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
            //여기 합치는 거는 조건 확실히 기억해  0 0 13 16 암튼 최외곽 벽을 1로 무조건 초기화
            //나머지는 maze[]에 input i-1,j-1 집어넣기
            if((i==0) || (j==0) || (i==13)|| (j==16)){
                maze[i][j] = 1;
            }else{
                //주의할 부분 i-1,j-1인 것 꼭 기억!!!
                maze[i][j] = input[i-1][j-1];
            }

            mark[i][j] = 0;
        }
    }

    cout << "Maze initialized.\n";
}

void showMatrix(int d[][100], int row, int col) {
    //2중 for문으로 보여주면 됨
    for (int i = 0; i <= row; i++) {
        for (int j = 0; j <= col; j++) {
            cout << d[i][j] << " ";
        }
            cout << endl;
        }

}

void findPath(int m, int p) {
    try {
    //백트래킹 시작은 항상 초깃값 설정부터하고 해당값 stack에 넣기
    stack<items> st;
    items temp;
    temp.x = 1;
    temp.y = 1;
    temp.dir = E;//동쪽부터 시작
    st.push(temp);

    while(!st.empty()){

        //외워야 할 흐름
        //1.stack의 top요소들 변수에 저장하고 "pop 꼭 해야 한다!!!!!"
        //2.while(d<8)을 이용한 8방향 탐색
            //여기서 int g = i+moves[d].a; 이 방식 사용한다.
        //2-1. 출구를 찾았을 경우 (g,j)가 m,p일 경우임
            //이때는 g,h랑 i,j(현위치) 2로 만들고 return으로 빠져나오기
        //2-2. 아직 미로 중간일 경우
            //이건 외워주기 maze[g][h] == 0 && mark[g][h] == 0 인 경우
            //이때는 g,h 방문했다고 하고 백트리킹을 하는데 temp를 i,j로 재설정한 후에 dir을 하나 늘리고 push해준다
        //2-3. 전부 다 실패시는 그냥 else로 d++;를 해주면 된다

        //마지막에 반드시 백트래킹으로 전부 실패시 while안 제일 마지막에 현위치의 mark와 maze를 0으로 설정
        temp = st.top();
        st.pop();
        int i = temp.x;
        int j = temp.y;
        int d = temp.dir;

        while(d<8){
            int g = i + moves[d].a;
            int h = j + moves[d].b;

            if((g==m)&&(h==p)){
                mark[g][h] = 2;
                mark[i][j] = 2;
                return;
            }

            if((maze[g][h] == 0)&&(mark[g][h] == 0)){
                mark[g][h] = 1;

                //다음 시도할 방향 stack에 up
                temp.x = i;
                temp.y = j;
                temp.dir = d + 1;
                st.push(temp);


                //gh중립으로 제설정
                i = g;
                j = h;
                d = N;
            }else{
                d++;
            }

        }
        mark[i][j];
        maze[i][j];
    }



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
