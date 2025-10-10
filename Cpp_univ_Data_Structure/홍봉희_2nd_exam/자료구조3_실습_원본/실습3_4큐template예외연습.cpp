#include <iostream>
#include <memory>
#include <exception>  // 예외 처리를 위한 헤더

using namespace std;

//--- 실행시 예외: 스택이 비어 있음 ---//
class EmptyQueueException : public std::exception {

};

//--- 실행시 예외: 스택이 가득 참 ---//
class OverflowQueueException : public std::exception {

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


// Menu 열거형 정의
enum Menu { push, pop, front, peek, dump, Exit };

// 메뉴를 선택하는 함수
Menu SelectMenu() {
	
}
int main() {
	Queue<int> queue(5);  // 용량이 5인 정수 Queue 생성
	Menu menu;

	while (true) {
		try {
			menu = SelectMenu();
			switch (menu) {
			
		}
		catch () {
			
		}
		catch () {
			
		}
		catch () {
			
		}
	}


	return 0;
}