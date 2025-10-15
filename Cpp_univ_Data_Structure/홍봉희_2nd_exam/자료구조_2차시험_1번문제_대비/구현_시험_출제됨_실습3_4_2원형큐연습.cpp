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
    // ~Point5(){}

    int getix(){return ix;}
    int getiy(){return iy;}

    //연산자 오버로딩은 friend ostream& 이걸 쓴다는 것을 무조건 기억해두기
    //그리고 항상 파라미터로 std::ostream 이걸 참고해야 함! 
    //<<은 ostream 내부에서 (std::ostream &,출력할 변수나 객체 &) 이렇게 구성되어 있음
    //그리고 항상 <<오버로딩은 전역함수라 friend 씀 

    friend ostream& operator<<(std::ostream &os, Point5& point){//이런 형태로 적는거 꼭 기억 해야지 // const 쓰지 마라
        //여기 내부는 전역함수니까 항상 멤버함수 호출해야 함
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
    public: //이거 존나 중요함 내가 이거 안해서 시간 많이 까먹음 //이 예외에서도 public을 적용해야지 접근 가능임!!!
        explicit EmptyQueueException(const char* message): std::runtime_error(message) {} //죄다 runtime_error(부모 클래스) 생성자로 넘겨버림
    };

    class OverflowQueueException : public runtime_error {
    public:
        explicit OverflowQueueException(const char* message): std::runtime_error(message) {}
    };


    //이 원형큐는 front=rear=-1 방식이 아니라 front=rear=0과 isEmptyTag을 사용해서 구현한다
    //isEmptyTag 조작은 push랑 clear에서 전부 진행하면 됨

    CircularQueue(int queuecapacity = 4): capacity{queuecapacity}{
        //원형 Queue에서는 항상 front rear는 둘 다 -1로 시작한다
        que = new Point5[getCapacity()];
        //객체배열 만드는 거니까 이게 맞다!!!!
        //객체의 배열이라는 것 꼭 기억
        front = 0;
        rear = 0;
        isEmptyTag = true; //중요 //생성시점에는 비어있으니까!!!
    }

    ~CircularQueue(){
        delete[] que;
        //이거 꼭 기억해라
        //메모리 해제는 무조건 delete[] 이렇게 배열 해제하는 것!!!
    }

    void push(const Point5& it) {
        //반드시 암기하고 있기
        //여기서 마지막에 isEmptyTag조정!!!
        if(isFull()){
            throw OverflowQueueException("오버플로우! 큐가 가득 찼습니다.");
        }

        //빈칸을 가리키는 rear 한칸에 저장
        que[rear] = it;
        //rear를 한칸 앞으로 하면 된다.
        rear = (rear + 1) % capacity;

        //반드시 잊지말고 isEmptyTag를 false로 만들어야 한다.
        isEmptyTag = false;
    }

    Point5 pop() {
        //여기는 return값 있음!!! 주의!! 이럴 때는 항상 [top--]으로 top을 빼낸 다음에 --로 후치감소하면 된다.
        //원형 큐이므로 반드시 이렇게 작성
        //여기서 마지막에 반드시 isEmptyTag조정!!! //이거 조정 안하면 큰일남

        if(isEmpty()){
            throw EmptyQueueException("비어있음");
        }
        
        //(암기) front를 한칸 앞으로 움직인다
        //front = (front + 1) % capacity;
        //이 원형큐는 isEmptyTag를 사용하므로 front == rear && isEmptyTag == true을 사용!!!!
        Point5 temp = que[front];
        front = (front + 1) % capacity;

        //매우 중요(여기서 rear=front를 무조건 다시 검사해야 함!!! isEmptyTag == 0 이면 반드시 )
        //여기 조정하는게 중요
        if (front == rear) {
            isEmptyTag = true;
        }
        
        return temp; 
        //void여도 굳이 소멸 시킬 필요 없다!!! 그냥 줄이기만 하면 됨
    }

    void clear() {
        front=0;
        rear=0;
        isEmptyTag = true;
        //이렇게 전부 다 초기상태도 되돌리기만 하면 된다.
    }

    int getCapacity() const { return capacity; }

    int size() const {
        //여기서 Empty, full, 일반 이렇게 3가지로 나누어야 함

        //1. 비어있는 경우
        if (isEmpty()) {
            return 0;
        }

        if (isFull()){
            return capacity;
        }

        //이 일반적인 경우 출력이 매우 중요하다!!!
        //rear>front인 경우하고 rear<front인 경우를 나누어서 생각해야 함!!!
        if(rear > front){
            //rear가 front보다 큼 --> 정상적으로 rear가 더 뒤에 있음 --> 걍 빼면 됨
            return rear - front;
        } 
        else {//rear < front
            //여기서 중요한게 배열을 넘어서 돌아올 것임 --> rear-front하면 음수일 것이거든? 거기에 capacity 더하면 양수로 정상값 나옴...! (capacity - front) + rear을 이용하면 됨!!!! 
            return (capacity - front) + rear;
        }
    }

    bool isEmpty() const {
        //원형 큐에서 Full인 조건과 Empty인 조건은 모두 front == rear 인 상태이다!!!! (여기서는 한 칸 남겨두고 full인지 empty인지 구분하는 방법을 사용하지 않고 그냥 front == rear 이거 딱 1개만 봄)
        //그리고 반드시 isEmptyTag가 true여야함
        return (front == rear) && isEmptyTag;
    }

    bool isFull() const {
        //원형 큐에서 Full인 조건과 Empty인 조건은 모두 front == rear 인 상태이다!!!! (여기서는 한 칸 남겨두고 full인지 empty인지 구분하는 방법을 사용하지 않고 그냥 front == rear 이거 딱 1개만 봄)
        //그리고 반드시 isEmptyTag가 fasle여야함
        return (front == rear) && !isEmptyTag; //느낌표 잊지마!!!
    }

    void dump() const {
        if (isEmpty()) {
            throw EmptyQueueException("덤프할 데이터가 없습니다.");
        }
        // [수정] i를 0부터 순회하면 안 되고, front부터 시작해서 원형으로 돌아야 합니다.
        for (int i = 0; i < size(); ++i) {
            int index = (front + i) % capacity;
            cout << que[index] << " ";
        }
        cout << endl;
    }

    Point5 peek() const {
        if(isEmpty()){
            throw EmptyQueueException("비어있음");
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
