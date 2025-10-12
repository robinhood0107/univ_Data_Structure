#include <iostream>
#include <memory>
#include <exception>  // 예외 처리를 위한 헤더

using namespace std;

//공부법
//예외 처리를 중점적으로 외워주면 된다.

//혹시 모르니까 이 예외도 외워서 작성할 수 있도록 전부 암기해두기
//그리고 항상 책 기준으로 작성한 것을 외워야 한다. 그래야 타율이 아주 좋음.


//--- 실행시 예외: 스택이 비어 있음 ---//
class EmptyStackException : public std::exception {
public:

};

//--- 실행시 예외: 스택이 가득 참 ---//
class OverflowStackException : public std::exception {
public:

};

template <class T>
Stack<T>::Stack(int stackCapacity){



}

template <class T>
bool Stack<T>::IsFull() const {

}


template <class T>
bool Stack<T>::IsEmpty() const {

}

template <class T>
T& Stack<T>::Peek() const {

}

template <class T>
void Stack<T>::Push(const T& item){

}

template <class T>
T& Stack<T>::Pop(){

}

template <class T>
void Stack<T>::Dump() {

}


template <class T>
class Stack {
public:
	Stack(int stackCapacity = 4);
	bool IsFull() const;
	bool IsEmpty() const;
	T& Peek() const;//예외 - 빈 스택
	void Push(const T& item);////예외 - full 스택
	T& Pop();//예외 - 빈 스택
	void Dump();//예외 - 빈 스택
private:
	T* stack;
	int top;
	int capacity;
};



// Menu 열거형 정의
enum Menu { push, pop, peek, dump, Exit };

// 메뉴를 선택하는 함수
Menu SelectMenu() {
	int choice;
	cout << "0: Push " << "1: Pop, " << "2: Peek, " << "3: Dump, " << "4: Exit\n";
	cout << "선택번호: ";
	cin >> choice;
	return static_cast<Menu>(choice);
}
int main() {
	Stack<int> stack(4);  // 용량이 5인 정수 스택 생성
	Menu menu;

	while (true) {
		try {
			menu = SelectMenu();
			switch (menu) {
			case push: {
				int value;
				cout << "push 값: ";
				cin >> value;
				stack.Push(value);
				break;
			}
			case pop: {
				cout << "pop 값 = " << stack.Pop();
				break;
			}
			case peek: {
				cout << "Peek of stack: " << stack.Peek() << endl;
				break;
			}
			case dump: {
				stack.Dump();
				break;
			}
			case Exit: {
				cout << "Exiting program.\n";
				return 0;
			}
			default: {
				cout << "Invalid choice. Try again.\n";
				break;
			}
			}
		}
		catch (const EmptyStackException& e) {
			cout << "스택 empty 예외 : " << e.what() << endl;
		}
		catch (const OverflowStackException& e) {
			cout << "스택 overflow 예외: " << e.what() << endl;
		}
		catch (...) {
			cout << "An unknown exception occurred." << endl;
		}
	}


	return 0;
}