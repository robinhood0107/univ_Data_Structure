#include <iostream>
#include <memory>
#include <exception>  // 예외 처리를 위한 헤더
#include <algorithm>

using namespace std;

//--- 실행시 예외: 스택이 비어 있음 ---//
class EmptyQueueException : public std::exception {
public:
    EmptyQueueException(){}

	const char* what() const noexcept override{
		return "빈 Queue.";
	}
};

//--- 실행시 예외: 스택이 가득 참 ---//
class OverflowQueueException : public std::exception {
public:
    OverflowQueueException(){}

	const char* what() const noexcept override {
		return "Overflow Queue.";
	}
};

class Point {
private:
	int ix;
	int iy;
public:
    Point():ix{0}, iy{0}{}
    Point(int rndx, int rndy):ix{rndx}, iy{rndy}{}

    int getix(){return ix;}
    int getiy(){return iy;}

    friend ostream& operator<<(ostream& os, Point& point){
        os << point.getix() << "," << point.getiy();
        return os;
    }
};

class Queue
{
public:
	Queue(int queueCapacity = 10);
	~Queue();
	Point& Front();
	Point& Rear();
	void Push(Point const& x);
	void Pop();
	bool IsFull() const;
	bool IsEmpty() const;
	Point& Peek() const;
	void Dump();
private:
	Point* queue;
	int front;
	int rear;
	int capacity;
};


//선형큐

//암기
//만약 front = rear = -1인 상태로 원형 큐를 하고 싶으면 IsFull에서 return (rear+1)%capacity; 로 bool값 구하고 IsEmpty는 rear=front로 구하면 됨.


Queue::Queue(int queueCapacity) : capacity{queueCapacity} {
	queue = new Point[capacity];
	front = rear = 0;
}


Queue::~Queue()
{
    delete[] queue;
}


Point& Queue::Front() {
	//아주 중요
	// 큐의 맨 앞 원소 반환
	if(IsEmpty()){
		throw EmptyQueueException();
	}

    // front는 빈 공간을 가리키므로, 실제 원소는 (front + 1) % capacity 에 있음
	// 한칸 띄우는것 때문에 이렇다.
    return queue[front];

	//front만 이러니까 주의해서 반드시 기억하셈
}

Point& Queue::Rear() {
	//아주 중요
	// 큐의 맨 뒤 원소 반환
	if(IsEmpty()){
		throw EmptyQueueException();
	}
	
    // rear는 다음에 들어올 위치를 가리키므로, 마지막 요소는 rear - 1에 있습니다.
	return queue[rear-1];
    //rear는 다음에 들어올 위치라는거 꼭 기억해두기!!!
}


void Queue::Push(Point const& x) {
	//아주 중요
	// 큐의 맨 뒤에 원소 추가 (enqueue)

    //선형큐는 여기서 capacity 크기 판별해서 queue의 크기를 늘려버림
	if(IsFull()){
        int current_size = rear - front;
        int newcapacity = capacity*2;
		Point* newqueue = new Point[capacity*2];
        copy(queue + front, queue + rear, newqueue);
        // 무조건 시작과 끝은 queue에다가 front 더하는거다 queue + front, queue + rear
        // copy(원본 시작,원본 끝, 복사받는 시작)
        
        // memcpy(복사받을 메모리 포인터, 복사할 메모리 포인터, 총 바이트(byte) 수)
        //int current_size = rear - front;
        //memcpy(newQueue, queue + front, current_size * sizeof(Point));
        
        //걍 copy 쓰자
        
        delete[] queue; // 이전 메모리 해제 //반드시!!!
        queue = newqueue;
        capacity = newcapacity;

        //중요 front,rear 재조정
        front = 0; //queue + front부터 옮겼으니까
        rear = current_size; //복사한 요소의 개수=current_size(미리 계산해 두어야만 함!!!!!) //선형큐라서 이렇게 간단히 가능
	}

	queue[rear++] = x; //선형큐라서 이렇게 그냥 1칸 올리면 됨(원형큐에서는 (rear+1)%capacity로 올렸잖아)
}

void Queue::Pop() {
	// 큐의 맨 앞 원소 제거 (dequeue)
	if(IsEmpty()){
		throw EmptyQueueException();
	}
	
	//pop에서는 front를 한칸 앞으로
	front = (front + 1) % capacity; // front를 한 칸 앞으로 //원형이던지 선형이던지 이렇게 구현하면 된다.
    //void라 출력 없어도 됨.

    if (IsEmpty()) {
        front = rear = 0;
    }
}

bool Queue::IsFull() const{
	return rear == capacity; //선형큐니까!!!
}

bool Queue::IsEmpty() const{
	return front == rear; // front와 rear가 같으면 큐는 비어있습니다.

	//앞인덱스랑 뒤인덱스가 같은 상태가 빈 상태인거 기억!!
	//여기는 걍 rear == front 쓰면 됨.(무조건임)
	//IsFull()에서 한 칸을 비워두는 규칙 덕분에, 큐가 꽉 찼을 때는 front == rear 조건이 절대로 성립하지 않습니다. 따라서 이 조건은 오직 큐가 비어있을 때만 참이 됩니다.
}


Point& Queue::Peek() const{
	//peek, 즉 옅보다. 인덱스 안건들이고 그냥 보기만 함.
	if(IsEmpty()){
		throw EmptyQueueException();
	}
	//front랑 똑같이 작성하면 된다...
	return queue[front];
}

void Queue::Dump(){
    if (IsEmpty()) {
        throw EmptyQueueException();
    }
    for (int i = front; i < rear; i++) {
        cout << queue[i] << " ";
    }
    cout << "\n";

	// //순회 이렇게 해야 함.
	// //front로 i 초깃값을 하고, rear가 아닐때까지만 반복 
	// //실제 시작은 (front + 1) % capacity이고 하나씩 올리면 됨 --> 그게 i = (i + 1) % capacity;
    // int i = front;
    // while (i != rear)
    // {
    //     i = (i + 1) % capacity;
    //     std::cout << queue[i] << " ";
    // }
    // std::cout << std::endl;
    //원형큐일때..
}



// Menu 열거형 정의
enum Menu { push=1, pop, front, Rear, dump, Exit };

int main() {
    srand(41);
    Queue oq(4); // 최대 4개
    Point p;
    int rndx, rndy;
    int menu;

    while (true) {
        cout << "(1)인큐 (2)디큐 (3)front (4)Rear (5)덤프 (0)종료 : ";
        cin >> menu;

        if (menu == 0) break;

        switch ((Menu)menu) {
        case push:
            rndx = rand() % 20;
            rndy = rand() % 20;
            p = Point(rndx, rndy);
            cout << "입력 데이터: " << p << endl;
            try {
                oq.Push(p);
                cout << "push 완료" << endl;
            }
            catch (const OverflowQueueException& e) {
                cout << e.what() << endl;
            }
            break;

        case pop:
            try {
                oq.Pop();
                cout << "pop 수행 완료" << endl;
            }
            catch (const EmptyQueueException& e) {
                cout << e.what() << endl;
            }
            break;

        case front:
            try {
                p = oq.Front();
                cout << "front 데이터: " << p << endl;
            }
            catch (const EmptyQueueException& e) {
                cout << e.what() << endl;
            }
            break;

        case Rear:
            try {
                p = oq.Rear();
                cout << "Rear 데이터: " << p << endl;
            }
            catch (const EmptyQueueException& e) {
                cout << e.what() << endl;
            }
            break;

        case dump:
            try {
                oq.Dump();
            }
            catch (const EmptyQueueException& e) {
                cout << e.what() << endl;
            }
            break;

        case Exit:
            return 0;
        }
    }
    return 0;
}







//cf)
//front = rear = -1 한칸 비우고 큐해서 원형큐에 대해서....

//만약 front = rear = -1인 상태로 원형 큐를 하고 싶으면 IsFull에서 return (rear+1)%capacity; 로 bool값 구하고 IsEmpty는 rear=front로 구하면 됨.
	//**큐가 비어있는 상태(front == rear)**와 꽉 찬 상태를 구분하기 위해, 배열의 한 칸은 항상 비워두는 것
	//따라서 큐는 rear의 다음 위치가 front와 같아질 때 "꽉 찼다"고 판단합니다.

	// rear를 한 칸 앞으로 옮겼을 때 front와 위치가 같다면 큐는 꽉 찬 상태입니다.
    // 나머지 연산(%)을 사용하는 이유는 rear가 배열의 끝에 도달했을 때
    // 다시 배열의 처음(0번 인덱스)으로 돌아오게 하기 위함입니다.

    //그니깐 (rear+1) % capacity은 끝에 도달하면 rear은 앞으로 와야 하니까 이런 나머지 연산꼴로 쓰는 것이고
	
	//이론적으로는 rear == front인 상태가 full인 상태임

	//원형큐에서는 rear == front은 empty일수도 있고 full일수도 있음. 그래서 이걸 구분해 주는 것이 3.4.2에서 isEmptyTag이다.