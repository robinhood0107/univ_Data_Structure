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
            if ((!i) || (!j) || (i == 13) || (j == 16))
                maze[i][j] = 1;
            else {
                maze[i][j] = input[i - 1][j - 1];
            };
            mark[i][j] = 0;
        }
    }

    cout << "Maze initialized.\n";
}

/*
maze[][], mark[][]를 class의 private data member로 선언
main()에서는 class의 public function의 호출로 미로 찾기
*/
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
        std::stack<items> st;

        // 1. 시작점을 스택에 저장
        // 1. 출발점 (1,1), 이동 방향 dir = 2(동쪽)을 스택에 push
        items temp;
        temp.x = 1;
        temp.y = 1;
        temp.dir = E; // E는 2
        st.push(temp);

        // 2. 스택이 비울 때까지 계속
        // 2. while (stack is not empty)
        while (!st.empty()) 
        {
            // 스택에서 꺼내기
            temp = st.top();
            st.pop(); // unstack
            int i = temp.x;
            int j = temp.y;
            int d = temp.dir;

            // 4. while (there are more moves)
            while (d < 8) // 8방향 탐색
            {
                // 5. (g,h) = 다음 이동 좌표 계산
                int g = i + moves[d].a;
                int h = j + moves[d].b;

                // 출구 찾음
                // 6. if ((g == m) && (h == p)) { success; }
                if ((g == m) && (h == p)) {
                    // 성공: 현재 위치(i,j)와 도착점(g,h)을 경로로 표시
                    mark[g][h] = 2;
                    mark[i][j] = 2;
                    cout << "the term near the exit: " << i << " " << j << endl;
                    cout << "exit: " << m << " " << p << endl;
                    return;
                }

                // 갈 수 있는 길
                // 7. if (갈 수 있는 길이고 && 아직 방문 안 했으면) mark[g][h] = 1; (방문 표시)
                if ((maze[g][h] == 0) && (mark[g][h] == 0)) { // new position
                    // 7-1. mark[g][h] = 1; (방문 표시)
                    mark[g][h] = 1;


                    //push the old temp to the stack, but the direction changes.
                    //Because the neighbor in the direction of d has been checked.
                    // 7-2. 현재 위치(i,j)와 다음 시도할 방향(d+1)을 스택에 push
                    temp.x = i;
                    temp.y = j;
                    temp.dir = d + 1;
                    st.push(temp); // stack it // ← 이전 위치 저장!

                    // 7-3. 새로운 위치로 이동하고, 방향은 처음(N)부터 다시 탐색
                    i = g;
                    j = h;
                    d = N; // moves to (g,h)
                }
                // 8. else d++; (다음 방향 시도)
                else {
                    d++; // try next direction
                }
            }
            // 8방향 다 막혔을 때 (백트래킹)
            mark[i][j] = 0;
            maze[i][j] = 0;
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