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
        // 시작점 (1, 1) 설정
        mark[1][1] = 1;
        std::stack<items> st;

        // 시작 위치 정보(temp)를 생성하고 스택에 Push
        items temp;
        temp.x = 1;     // 시작 x 좌표
        temp.y = 1;     // 시작 y 좌표
        temp.dir = E;   // 시작 탐색 방향 (East)
        st.push(temp);

        // 스택이 비어있지 않은 동안 계속 탐색
        while (!st.empty())
        {
            // 스택에서 현재 위치 정보를 가져옴 (unstack)
            temp = st.top();
            st.pop();
            int i = temp.x;
            int j = temp.y;
            int d = temp.dir;
            
            // 백트래킹을 위해 현재 위치의 마크와 미로 값을 초기화
            mark[i][j] = 0;
            maze[i][j] = 0;

            // 현재 방향(d)부터 8방향 모두 탐색
            while (d < 8)
            {
                // 다음 이동할 위치 (g, h) 계산
                int g = i + moves[d].a;
                int h = j + moves[d].b;

                // 출구에 도달한 경우 (g == m && h == p)
                if ((g == m) && (h == p))
                {
                    // 경로 출력 및 함수 종료
                    mark[g][h] = 2;
                    mark[i][j] = 2;
                    cout << "the term near the exit: " << i << " " << j << endl;
                    cout << "exit: " << m << " " << p << endl;
                    maze[i][j] = 2;
                    maze[g][h] = 2;
                    return;
                }

                // 이동할 수 있는 새로운 위치인 경우 (길이 있고, 방문한 적 없음)
                if ((maze[g][h] == 0) && (mark[g][h] == 0))
                {
                    mark[g][h] = 1; // 새로운 위치를 방문했다고 표시

                    // 현재 위치와 다음 탐색할 방향을 스택에 저장
                    // d방향의 이웃은 이미 확인했으므로 d+1 부터 탐색
                    temp.x = i;
                    temp.y = j;
                    temp.dir = d + 1;
                    st.push(temp);

                    // 현재 위치를 경로의 일부로 표시
                    mark[i][j] = 2;
                    maze[i][j] = 2;

                    // (g, h)로 이동하고, 방향은 처음(N)부터 다시 탐색
                    i = g;
                    j = h;
                    d = N;
                }
                // 이동할 수 없는 경우, 다음 방향 시도
                else
                {
                    d++;
                }
            } // end of inner while loop

            // 8방향 모두 탐색했지만 길이 없을 때, 현재 위치의 마크와 미로 값을 다시 초기화 (백트래킹)
            mark[i][j] = 0;
            maze[i][j] = 0;

        } // end of outer while loop

        // 스택이 모두 비워질 때까지 출구를 찾지 못한 경우
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