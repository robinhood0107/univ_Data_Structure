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


    CircularQueue(int queuecapacity = 4){
        capacity = queuecapacity;
        que = new Point[];
        front = 0;
        rear = 0;
        isEmptyTag = true;
    }

    ~CircularQueue(){
        delete[] que;
    }

    void push(const Point5& it) {
        if(isFull()){
            throw OverflowQueueException("overflow");
        }

        //원형 큐이기 때문에 반드시 (rear+1)%capacity 사용 무조건 하기
        //rear은 항상 빈곳을 나타내기 때문에 반드시
        //넣은 다음에 증가다!!!!

        que[rear] = it;
        rear = (rear+1)%capacity

        isEmptyTag = false;
        //그리고 넣고 반드시 isEmptyTag 조정하기
    }

    Point5 pop() {
        if(isEmpty()){
            throw EmptyQueueException("Empty");
        }

        //원형큐니까 항상 (front+1)%capacity로 증가시키기
        //peek이나 pop도 항상 먼저 읽은 다음에 증가시키는 것!!!(항상 먼저 저장하거나 읽어라)

        Point5 temp = que[front];
        front = (front +1)%capacity;

        if(front == rear){ //이런거 적을때 무조건 == 이거 생각 잘해라
            isEmptyTag == true;
        }
        //반드시 rear==front if문으로 isEmptyTag 조정

        return temp;
    }

    void clear() {
        front = 0;
        rear = 0;
        isEmptyTag = true;
    }

    int getCapacity() const { return capacity; }

    int size() const {
        //항상 1.empty일 때 2.full일때 3.일반(rear>front가 정상)

        if(isEmpty()){
            return 0;
        }

        if(isFull()){
            return capacity; //그냥 capacity 출력 해주면 된다.
        }

        if(rear > front){
            return rear - front;
        } else {
            return rear - front + capacity;
        }
    }

    bool isEmpty() const {
        //여기서는 무조건 isemptytag랑 rear==front가 동시에 만족해야 함!!!
        return (rear==front) && isEmptyTag;
    }

    bool isFull() const {
        return (rear==front) && !isEmptyTag;
    }

    void dump() const {
        //항상 생각해야 하는것
        //int index = (front+1)%capacity로 시작을 index로 정해준 다음에 그걸 출력해야 만 함
        if(isEmpty()){
            throw EmptyQueueException("Empty");
        }

        for(int i=0;i<size();i++){
            int index = (front+1)%capacity;
            cout << que[index] << " ";
            //어쩌피 i용도는 딱 저만큼 반복횟수이고
            //index가 연산하는 것
        }
    }

    Point5 peek() const {
        if(isEmpty()){
            throw EmptyQueueException("Empty");
        }

        return que[front];
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
