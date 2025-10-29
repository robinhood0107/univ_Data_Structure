#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
using namespace std;



//원형 큐 그냥 이거 연습하면 된다고 하심.

class Point5 {
private:
    int ix, iy;
public:
    Point5():ix{0}, iy{0}{}
    Point5(int rndx, int rndy): ix{rndx}, iy{rndy}{}
    int getix(){return ix;}
    int getiy(){return iy;}
    friend ostream& operator<<(std::ostream &os, Point5& point){
        os << point.getix() << "," << point.getiy();
        return os;
    }
};



class CircularQueue {
private:
    int front, rear, capacity;
    bool isEmptyTag;
    Point5* que;

public:

    class EmptyQueueException : public runtime_error {
    public:
        explicit EmptyQueueException(const char* message): std::runtime_error(message) {}
    };

    class OverflowQueueException : public runtime_error {
    public:
        explicit OverflowQueueException(const char* message): std::runtime_error(message) {}
    };


    CircularQueue(int queuecapacity = 4): {
        capacity = queuecapacity;
        que = new Point[capacity];
        front = rear = 0;
        isEmptyTag = true;
    }

    ~CircularQueue(){
        delete[] que;
    }

    void push(const Point5& it) {
        if(isFull()){
            throw OverflowQueueException('a');
        }

        st[rear] = it;
        rear = (rear+1)%capacity;

        isEmptyTag = false;

    }

    Point5 pop() {
        if(isEmpty()){
            throw EmptyQueueException('a');
        }

        //항상 미리 빼두기

        Point temp = st[front];
        front = (front +1)%capacity;

        if(rear == front){
            isEmptyTag = true;
        }

        return temp;
    }

    void clear() {
        front = 0;
        rear = 0;
        isEmptyTag = true;
    }

    int getCapacity() const { return capacity; }

    int size() const {
        if(isEmpty()){
            return 0;
        }
        if(isFull()){
            return capacity;
        }
        if(rear > front){
            return rear-front;
        }else{
            return rear-front+capacity;
        }
    }

    bool isEmpty() const {
        return (rear == front) && isEmptyTag;
    }

    bool isFull() const {
        return (rear == front) && !isEmptyTag;
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
