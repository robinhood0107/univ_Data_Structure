#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
using namespace std;

class Point5 {
private:
    int ix, iy;
public:

};

class CircularQueue {
private:
    int front, rear, capacity;
    bool isEmptyTag;
    Point5* que;

public:

    class EmptyQueueException : public runtime_error {
        
    };

    class OverflowQueueException : public runtime_error {

    };

    void push(const Point5& it) {

    }

    Point5 pop() {

    }

    void clear() {

    }

    int getCapacity() const { return capacity; }

    int size() const {

    }

    bool isEmpty() const {

    }

    bool isFull() const {

    }

    void dump() const {

    }

    Point5 peek() const {

    }
};

// 메뉴 열거형
enum Menu { push_op = 1, pop_op, peek_op, dump_op, clear_op, exit_op };

int main() {
    srand(41);
    CircularQueue oq(4); // 최대 4개
    Point5 p;
    int rndx, rndy;
    int menu;

    while (true) {
        cout << "\n현재 데이터 개수: " << oq.size() << " / " << oq.getCapacity() << endl;
        cout << "(1)인큐 (2)디큐 (3)피크 (4)덤프 (5)clear (0)종료 : ";
        cin >> menu;

        if (menu == 0) break;

        switch ((Menu)menu) {
        case push_op:
            rndx = rand() % 20;
            rndy = rand() % 20;
            p = Point5(rndx, rndy);
            cout << "입력 데이터: " << p << endl;
            try {
                oq.push(p);
                cout << "push 완료: size = " << oq.size() << endl;
            }
            catch (const CircularQueue::OverflowQueueException& e) {
                cout << e.what() << endl;
            }
            break;

        case pop_op:
            try {
                p = oq.pop();
                cout << "pop 데이터: " << p << " size = " << oq.size() << endl;
            }
            catch (const CircularQueue::EmptyQueueException& e) {
                cout << e.what() << endl;
            }
            break;

        case peek_op:
            try {
                p = oq.peek();
                cout << "피크 데이터: " << p << endl;
            }
            catch (const CircularQueue::EmptyQueueException& e) {
                cout << e.what() << endl;
            }
            break;

        case dump_op:
            try {
                oq.dump();
            }
            catch (const CircularQueue::EmptyQueueException& e) {
                cout << e.what() << endl;
            }
            break;

        case clear_op:
            try {
                oq.clear();
            }
            catch (const CircularQueue::EmptyQueueException& e) {
                cout << e.what() << endl;
            }
            break;

        case exit_op:
            return 0;
        }
    }
    return 0;
}
