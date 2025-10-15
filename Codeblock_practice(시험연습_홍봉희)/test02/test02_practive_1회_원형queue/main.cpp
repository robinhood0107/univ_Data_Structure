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
        que = new Point5[capacity];

        front = rear = 0;
        //주의 이거 잊지마라 여기선 원형큐인데도 front=rear=0을 쓰는 대신 isEmptyTag에 구분할때 사용하는 것!!!! 암튼 이거 조정하는 위치 전부 암기
        //isEmptyTag 조정
        isEmptyTag = true;
    }

    ~CircularQueue(){
        delete[] que;
    }

    void push(const Point5& it) {
        if(isFull()){
            throw OverflowQueueException("overflow");
        }


        //반드시 먼저 rear에 넣은 다음에 rear를 증가시키는거다!!!

        //내가 틀린 부분
        //빈칸을 가리키는 rear 한칸에 저장
        que[rear] = it;
        //rear를 한칸 앞으로 하면 된다.
        rear = (rear + 1) % capacity;

        //내가 잊어먹은 부분 반드시 여기를 isEmptyTag = false로 만들어 줘야 한다.
        //내가 넣었잖아!
        isEmptyTag = false;
    }

    Point5 pop() {
        if(isEmpty()){
            throw EmptyQueueException("empty");
        }

        //Queue에서 삭제는 항상 front를 한칸 뒤로 증가시키는 것!!!
        //원형큐이므로 반드시 (front+1)%capacity사용한다(원형큐 꼴은 전부 이거 사용한다 생각)

        Point5 temp = que[front];//주의할 점은 temp라는 임시에 내가 출력할 top(front 미리 뽑아놓으셈
        front = (front + 1)%capacity;

        if(rear==front){ //내가 틀린 지점 -> 무조건 ==으로 적어!!!
            isEmptyTag = true;
        }//잊지 말 것) isEmptyTag 조정!!!   마지막에 front == rear 검사해서 같으면 empty로 판별하기

        return temp;
    }

    void clear() {
        front=0;
        rear=0;
        isEmptyTag=true;
    }

    int getCapacity() const { return capacity; }

    int size() const {
        //이걸 외워주는 게 중요함

        //반드시 3가지로 나누어 준다
        //Empty, full, 일반경우 이렇게 3가지로 나누어야 함

        if(isEmpty()){
            return 0;
        }
        if(isFull()){
            return capacity; //꽉 채워졌을 경우에는 원형큐이기 때문에 capacity임이 가능한 것 rear가 삥 돌아서 front 만났다는 거니까
        }

        if(rear > front){
            //정상적인 경우
            //그냥 빼면 개수가 나옴
            return rear-front;
        } else{
            //rear < front로 rear-front 하면 음수나옴
            //음수니까 capacity 더해주면 양수되면서 개수가 나온다!!
            //rear-front+capacity
            return rear-front+capacity;

        }


    }

    bool isEmpty() const {
        //여기에서 front=rear인 여부와 isEmptytag 여부를 무조건 살펴야 한다
        return (front==rear) && (isEmptyTag==true);
        //괄호 꼭 해야 함!!!
    }

    bool isFull() const {
        //여기에서 front=rear인 여부와 isEmptytag 여부를 무조건 살펴야 한다
        //꽉 차 있으니까 비어있지 않은것!!!
        return (front==rear) && (isEmptyTag == false);
    }

    void dump() const {
        if(isEmpty()){
                throw EmptyQueueException("empty");
        }

        //내가 틀린 부분 //반드시 index 시작을 (front + i) % capacity으로 고정해야 함!!!!
        // [수정] i를 0부터 순회하면 안 되고, front부터 시작해서 원형으로 돌아야 합니다.
        for (int i = 0; i < size(); ++i) {
            int index = (front + i) % capacity;
            cout << que[index] << " ";
        }
    }

    Point5 peek() const {
        if(isEmpty()){
            throw EmptyQueueException("empty");
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

