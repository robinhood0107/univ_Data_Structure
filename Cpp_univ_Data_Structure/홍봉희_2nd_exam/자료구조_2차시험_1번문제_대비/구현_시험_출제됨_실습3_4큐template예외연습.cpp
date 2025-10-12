#include <iostream>
#include <memory>
#include <exception>  // 예외 처리를 위한 헤더

using namespace std;

//--- 실행시 예외: 스택이 비어 있음 ---//
class EmptyQueueException : public std::exception {
	EmptyQueueException(){}

	const char* what() const noexcept override{
		return "빈 Queue.";
	}
};

//--- 실행시 예외: 스택이 가득 참 ---//
class OverflowQueueException : public std::exception {
	const char* what() const noexcept override {
		return "Overflow Queue.";
	}
};

class Point {
private:
	int ix;
	int iy;
public:

};

template <class T>
class Queue
{
public:
	Queue(int queueCapacity = 10);
	~Queue();
	T& Front();
	T& Rear();
	void Push(T const& x);
	void Pop();
	bool IsFull() const;
	bool IsEmpty() const;
	T& Peek() const;
	void Dump();
private:
	T* queue;
	int front;
	int rear;
	int capacity;
};


//보니까 사실상 원형 큐 구현임 선형큐는 없음....
//이거 원형큐이긴 한데 교수님이 그냥 선형큐도 하라고 하셨으니까 원형큐 기본 연습하면서 선형큐도 구현 연습(빵구 메우는 연습하기)

//이건 원형 큐 구조이며, IsFull()과 IsEmpty()를 구분하기 위해 배열의 한 칸을 비워두는 방식을 사용

template <class T>
Queue<T>::Queue(int queueCapacity) :queueCapacity{10} {
	queue = new T[capacity];
	front = rear = -1;
	//front는 앞 인덱스, rear은 뒤 인덱스를 가리킨다!!! (당연히 -1로 초기화하는거 암기)
}

template <class T>
Queue<T>::~Queue()
{
    delete[] queue;
}

template <class T>
T& Queue<T>::Front() {
	//아주 중요
	// 큐의 맨 앞 원소 반환
	if(IsEmpty()){
		throw EmptyQueueException();
	}

    // front는 빈 공간을 가리키므로, 실제 원소는 (front + 1) % capacity 에 있음
	// 한칸 띄우는것 때문에 이렇다.
    return queue[(front + 1) % capacity];

	//front만 이러니까 주의해서 반드시 기억하셈
}
template <class T>
T& Queue<T>::Rear() {
	//아주 중요
	// 큐의 맨 뒤 원소 반환
	if(IsEmpty()){
		throw EmptyQueueException();
	}
	
	return queue[rear];
}

template <class T>
void Queue<T>::Push(T const& x) {
	//아주 중요
	//선형큐도 이거랑 똑같이 쓴다
	// 큐의 맨 뒤에 원소 추가 (enqueue)
	if(IsFull()){
		throw OverflowQueueException();
	}

	//push에서는 rear를 한칸 앞으로
	rear = (rear + 1) % capacity; // rear를 한 칸 앞으로
	queue[rear] = x;
	//원형, 선형 전부 똑같이 쓴다.
}
template <class T>
void Queue<T>::Pop() {
	//이건 void니까 .~T() 이 방식 써라
	// 큐의 맨 앞 원소 제거 (dequeue)

	if(IsEmpty()){
		throw EmptyQueueException();
	}
	
	//pop에서는 front를 한칸 앞으로
	front = (front + 1) % capacity; // front를 한 칸 앞으로 //원형이던지 선형이던지 이렇게 구현하면 된다.
	queue[front].~T( );
}
template <class T>
bool Queue<T>::IsFull() const{

	//**큐가 비어있는 상태(front == rear)**와 꽉 찬 상태를 구분하기 위해, 배열의 한 칸은 항상 비워두는 것
	//따라서 큐는 rear의 다음 위치가 front와 같아질 때 "꽉 찼다"고 판단합니다.

	// rear를 한 칸 앞으로 옮겼을 때 front와 위치가 같다면 큐는 꽉 찬 상태입니다.
    // 나머지 연산(%)을 사용하는 이유는 rear가 배열의 끝에 도달했을 때
    // 다시 배열의 처음(0번 인덱스)으로 돌아오게 하기 위함입니다.
	return (rear++) % capacity == front;
	
	//그니깐 (rear++) % capacity은 끝에 도달하면 rear은 앞으로 와야 하니까 이런 나머지 연산꼴로 쓰는 것이고
	
	//이론적으로는 rear == front인 상태가 full인 상태임

	//원형큐에서는 rear == front은 empty일수도 있고 full일수도 있음. 그래서 이걸 구분해 주는 것이 3.4.2에서 isEmptyTag이다.
}
template <class T>
bool Queue<T>::IsEmpty() const{
	return rear == front;
	//앞인덱스랑 뒤인덱스가 같은 상태가 빈 상태인거 기억!!
	//여기는 걍 rear == front 쓰면 됨.(무조건임)
	//IsFull()에서 한 칸을 비워두는 규칙 덕분에, 큐가 꽉 찼을 때는 front == rear 조건이 절대로 성립하지 않습니다. 따라서 이 조건은 오직 큐가 비어있을 때만 참이 됩니다.
}

template <class T>
T& Queue<T>::Peek() const{
	//peek, 즉 옅보다. 인덱스 안건들이고 그냥 보기만 함.
	if(IsEmpty()){
		throw EmptyQueueException();
	}
	//front랑 똑같이 작성하면 된다...
	return queue[(front + 1) % capacity];
}
template <class T>
void Queue<T>::Dump(){
	if(IsEmpty()){
		throw EmptyQueueException();
	}

	//순회 이렇게 해야 함.
	//front로 i 초깃값을 하고, rear가 아닐때까지만 반복 
	//실제 시작은 (front + 1) % capacity이고 하나씩 올리면 됨 --> 그게 i = (i + 1) % capacity;
    int i = front;
    while (i != rear)
    {
        i = (i + 1) % capacity;
        std::cout << queue[i] << " ";
    }
    std::cout << std::endl;
}



// Menu 열거형 정의
enum Menu { push, pop, front, peek, dump, Exit };

// 메뉴를 선택하는 함수


//와... 이젠 여기까지 뚫어두는 거임?
//일단 이거도 외우긴 외우는데 물론 중점은 본체 구현임.


//어쩌피 이거 구현하라 안시킴. 위에 있는 거랑 선형큐나 연습하고 3.4.2나 연습해라


// Menu SelectMenu() {
	
// }
// int main() {
// 	Queue<int> queue(5);  // 용량이 5인 정수 Queue 생성
// 	Menu menu;

// 	while (true) {
// 		try {
// 			menu = SelectMenu();
// 			switch (menu) {
			
// 		}
// 		catch () {
			
// 		}
// 		catch () {
			
// 		}
// 		catch () {
			
// 		}
// 	}


// 	return 0;
// }


//선형큐 예제
/*
#include <iostream>

template <class T>
class LinearQueue
{
public:
    // 생성자
    LinearQueue(int queueCapacity = 10);
    // 소멸자
    ~LinearQueue();

    // 큐가 비어있는지 확인
    bool IsEmpty() const;
    // 큐가 꽉 찼는지 확인
    bool IsFull() const;

    // 큐의 맨 뒤에 원소 추가
    void Push(const T& x);
    // 큐의 맨 앞 원소 제거
    void Pop();

    // 큐의 맨 앞 원소 반환
    T& Front() const;
    
    // (디버깅용) 큐의 현재 상태와 배열 전체 출력
    void Dump() const;

private:
    T* queue;
    int front;
    int rear;
    int capacity;
};

// 생성자 구현
template <class T>
LinearQueue<T>::LinearQueue(int queueCapacity) : capacity(queueCapacity)
{
    if (capacity < 1) throw "Capacity must be > 0";
    queue = new T[capacity];
    front = 0;
    rear = 0;
}

// 소멸자 구현
template <class T>
LinearQueue<T>::~LinearQueue()
{
    delete[] queue;
}

// 큐가 비어있는지 확인
template <class T>
bool LinearQueue<T>::IsEmpty() const
{
    // front와 rear가 같으면 비어있는 상태
    return front == rear;
}

// 큐가 꽉 찼는지 확인 (선형 큐의 문제점)
template <class T>
bool LinearQueue<T>::IsFull() const
{
    // rear가 배열의 끝에 도달하면 꽉 찬 것으로 간주
    return rear == capacity;
}

// 원소 추가
template <class T>
void LinearQueue<T>::Push(const T& x)
{
    if (IsFull())
    {
        std::cerr << "Error: Queue is full. Cannot push." << std.endl;
        return;
    }
    queue[rear] = x;
    rear++;
}

// 원소 제거 (비효율 발생 지점)
template <class T>
void LinearQueue<T>::Pop()
{
    if (IsEmpty())
    {
        std::cerr << "Error: Queue is empty. Cannot pop." << std::endl;
        return;
    }
    // 단순히 front 인덱스만 증가시켜 맨 앞 원소를 접근 불가능하게 만듦
    // 이로 인해 배열 앞부분에 사용하지 않는 공간이 쌓이게 됨
    front++;
}

// 맨 앞 원소 반환
template <class T>
T& LinearQueue<T>::Front() const
{
    if (IsEmpty())
    {
        throw "Queue is empty. No front element.";
    }
    return queue[front];
}

// 상태 출력
template <class T>
void LinearQueue<T>::Dump() const
{
    std::cout << ">> Queue (front=" << front << ", rear=" << rear << "): ";
    if (IsEmpty())
    {
        std::cout << "Empty" << std::endl;
        return;
    }

    for (int i = front; i < rear; i++)
    {
        std::cout << queue[i] << " ";
    }
    std::cout << " | Full Array View: [";
    for (int i = 0; i < capacity; i++)
    {
        // front 이전의 버려진 공간을 'x'로 표시
        if (i < front) std::cout << "x ";
        else if (i < rear) std::cout << queue[i] << " ";
        else std::cout << "_ ";
    }
    std::cout << "]" << std::endl;
}


// --- main 함수를 사용한 테스트 ---
int main()
{
    LinearQueue<int> q(5);

    std::cout << "--- Pushing 3 elements ---" << std::endl;
    q.Push(10);
    q.Push(20);
    q.Push(30);
    q.Dump();

    std::cout << "\n--- Popping 2 elements ---" << std::endl;
    q.Pop();
    q.Pop();
    q.Dump(); // 앞의 두 공간(x x)이 낭비되는 것을 확인

    std::cout << "\n--- Pushing more elements ---" << std::endl;
    q.Push(40);
    q.Push(50);
    q.Dump();

    std::cout << "\nIs queue full? " << std::boolalpha << q.IsFull() << std::endl;
    
    std::cout << "\n--- Attempting to push to a 'full' queue ---" << std::endl;
    // ⚠️ 배열의 앞부분(0, 1번 인덱스)은 비어있지만, rear가 끝에 도달했기 때문에
    // "Full"로 인식되어 Push가 실패함
    q.Push(60); 
    q.Dump();

    return 0;

	//여기서 push에서 capacity 2배로 늘리고 deep copy하는 것으로 적용하면 될듯?
}




*/