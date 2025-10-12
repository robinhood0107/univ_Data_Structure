#include <iostream>
#include <memory>
#include <exception>  // 예외 처리를 위한 헤더

using namespace std;

//공부법
//예외 처리를 중점적으로 외워주면 된다.

//혹시 모르니까 이 예외도 외워서 작성할 수 있도록 전부 암기해두기
//그리고 항상 책 기준으로 작성한 것을 외워야 한다. 그래야 타율이 아주 좋음.

template <class T>
class Stack {
public:
	Stack(int stackCapacity = 4);
	~Stack();
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


//--- 실행시 예외: 스택이 비어 있음 ---//
class EmptyStackException : public std::exception {
public:
	EmptyStackException(){} //그냥 기본 생성자임. EmptyStackException() = default;로 해도 됨.(만약 string 방식으로 하고 싶으면 다르게 적어도 됨. 그거도 연습해두기)

	//가장 간단하게 exception 상속 정의 방법은 what()만 재정의 하는 것임.
	//what의 경우에는 반드시 char* (우리가 아는 c스타일 "~~~" 문장 반환)이라서 반드시 const char* 꼴로 반환시켜야 한다.
	//그리고 상속에서 자식이니까 override는 필수임.
	const char* what() const noexcept override {
		return "빈 Stack.";
	}
};
/*
//(진짜 참고)(연습 안해도 됨)만약 string 방식으로 예외처리 할꺼면? (근데 아마 const char*로 걍 줄것 같음. 어려운것도 아니고)
위에서 #include <string> 추가 후
public:
	EmptyStackException() : msg{"빈 Stack"}{};
	explicit EmptyStackException(std::string m) : msg(std::move(m)) {}
    const char* what() const noexcept override { return msg.c_str(); }
*/

//--- 실행시 예외: 스택이 가득 참 ---//
class OverflowStackException : public std::exception {
public:
	OverflowStackException() {}

	//이 const char* what const noexcept override 선언만 연습해라
	const char* what() const noexcept override {
		return "full Stack.";
	}
};


//진짜 주의!!!//나 이거 진짜 몰랐음

//탬플릿으로 클래스 선언했으면 사용할때는 밖에서 멤버함수들 선언해주려면 
/*

template <class T>
Stack<T>::Stack

*/
//이런 방식으로 선언해주어야 함!!!!

//연습할때는 걍 Stack클래스 내부에다가 만들자
//근데 만약에 셤이 이렇게 밖에 선언되어 있으면 이런방식을 사용하면 된다는 문법을 제대로 알자.
template <class T>
Stack<T>::Stack(int stackCapacity) : capacity{stackCapacity}{

	if(capacity < 1 ) throw "Stack capacity must be > 0"; //0보다 큰값 넣으라고 throw
	stack = new T[capacity];
	top = -1; //top은 항상 -1로 하는 것이다.
}

//주의 생성자 있었으면 소멸자로 무조건 해제도 해라 이건 그냥 따로 기억해두기
//없으면 내가 만들어라
template <class T>
Stack<T>::~Stack(){
	delete[] stack;
}

//그리고 주의해야 하는건 밖에서 선언하려면 이렇게 const도 당연히 똑같이 붙여줘야 함!!! 이거 진짜 잊어먹으면 안됨
template <class T>
bool Stack<T>::IsFull() const {
	return top == capacity-1;//top값이 capacity-1이면 full인 것!!!(이거 외워둬라)
}


template <class T>
bool Stack<T>::IsEmpty() const {
	return top == -1; //top이 -1이면 empty가 true(1)
}

template <class T>
T& Stack<T>::Peek() const {
	//Peek은 옅보다, 집다의 뜻이다!!!
	if(IsEmpty()){
		throw EmptyStackException();
	}
	return stack[top];
	//그냥 꼭대기 top만 출력하면 됨
	
}

//push의 경우는 교수님이 틀린 코드 만들어 두면 그 코드 고쳐서 실행 할 수 있는 상태로 변경하라고 하심.
template <class T>
void Stack<T>::Push(const T& item){
	//push는 교수님이 시험을 어떻게 내실지는 모르겠는데 1.확장 2배를 하는 경우 2.예외 던지는 경우 이 2가지로 코드를 짤 수 있음.
	//일단 어떻게 될지 몰라서 2개 다 전부 외워두기

	//암튼 코드 2가지임. 어쩌피 시험문제는 교수님이 코드 주고 내가 그걸 디버깅하는 형식이다.
	//아무튼 stack[++top] = item; 이런 방식으로 추가되니까 이거 외워두기

	//1.확장 2배를 하는 경우의 코드
	/*
	T* temp = new T[2 * capacity];
	int number = oldSize;
	if (capacity > 2 * capacity) number = 2 * capacity;
	//copy(item, item + number, temp);
	memcpy(temp, item, number);
	delete[ ] item;
	item = temp;
	capacity *= 2; //이거 꼭 해줘야지, 너가 2배 늘렸으면 capacity도 2배 늘려서 확장
	*/

	//2.isfull일 경우 그냥 예외처리하는 경우
	if(IsFull()){
		throw OverflowStackException();
	}
	stack[++top] = item;
}

template <class T>
T& Stack<T>::Pop(){
	if(IsEmpty()){
		throw EmptyStackException();
	}
	return stack[top--];
	//삭제는 이렇게 한다 
	//사실 그냥 stack[top--]만 return 해줘도 지워짐

	//만약 pop()함수가 void일 경우!!!
	//stack[top--].~T(); 

	//반드시 후위감소해야함. 반드시 top--이어야 함.
	//객체.~T() 구문은 해당 객체의 소멸자를 강제로 직접 호출하는 C++의 특별한 문법입니다.    //(보통 소멸자는 delete 키워드를 사용하거나, 지역 변수가 범위를 벗어날 때 자동으로 호출됩니다. 이렇게 직접 호출하는 경우는 메모리 관리나 객체의 생명 주기를 수동으로 제어해야 하는 특별한 상황에 사용됩니다.)
	//즉, 다시말하면 해당 원소가 int라면 stack[top--].~int(); 이렇게 멤버함수를 호출할 경우에는 소멸자를 호출하는 것이니까 바로 지워져버림.
}

template <class T>
void Stack<T>::Dump() {
//디버깅 용으로 지금 stack이 가지고 있는 것을 전부 출력하는 함수임.
	if (IsEmpty()) {
            throw EmptyStackException();
        }
	for (int i = 0; i <= top; i++) {
        std::cout << stack[i] << " ";
    }
	std::cout << "\n";
}


//근데 memory 대신에 vector 사용하라고 할까? 이거는 미로찾기랑 queen 연습 다 하면 이거 하면 될듯?
//일단 stack하고 queen이랑 knight 연습하고 queue 연습하러 가자


// 이거 잘못 들어간 것 같음
// class Point {
// private:
// 	int ix;
// 	int iy;
// public:
// 	Point(int x = 0, int y = 0) : ix(x), iy(y) {}
//     // Point 객체를 출력하기 위한 friend 함수
//     friend ostream& operator<<(ostream& os, const Point& pt) {
//         os << "(" << pt.ix << ", " << pt.iy << ")";
//         return os;
//     }
// };



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