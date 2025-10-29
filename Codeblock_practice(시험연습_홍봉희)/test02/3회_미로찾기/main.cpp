#pragma once
#include <iostream>
#include <memory>
#include <fstream>

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
            if ((i == 0) || (j == 0) || (i == 13) || (j == 16)) maze[i][j] = 1;
            else maze[i][j] = input[i-1][j-1];
            mark[i][j] =0

        }
    }

    cout << "Maze initialized.\n";
}

void showMatrix(int d[][100], int row, int col) {

}

void findPath(int m, int p) {
    try {

    //1.stack에 top요소들 저장
    //while을 통해 8방향 탐색
        //여기서 gj f랑 mp 같을 때
        //여기서 maze랑 mark 암기

    temp = st.top();
    st.pop();
    int i = temp.x;
    int j = temp.y;
    int d = temp.dir;

    while(d<8){
        int g = i+ moves[d].a;
        int h = j+ moves[d].a;

        if((g==m)&&(h==p)){
        //걍 바로 종료시키기
            mark[g][h] = 2;
            mark[i][j] = 2;
        return;
        }

        if((maze[g][h] == 0)&&(mark[g][h] == 0)){
            //일단 체크
            mark[g][h] = 1;

            //temp에해당 좌표 넣고 stack에 올림

        //gh중립으로 제설정
            i = g;
            j = h;
            d = N;

        }
        else
            d++;
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
