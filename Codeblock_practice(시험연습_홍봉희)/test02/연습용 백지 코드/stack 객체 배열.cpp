#include <iostream>
#include <memory>
#include <exception>  // 예외 처리를 위한 헤더

using namespace std;

//--- 실행시 예외: 스택이 비어 있음 ---//
class EmptyStackException : public std::exception {
public:
	EmptyStackException() {}
	//*
	const char* what() const noexcept override {
		return " 빈 Stack.";
	}
	//*/
};

//--- 실행시 예외: 스택이 가득 참 ---//
class OverflowStackException : public std::exception {
public:
	OverflowStackException() {}
	//*
	const char* what() const noexcept override {
		return "full Stack.";
	}
	//*/
};

class Point {
private:
	int ix;
	int iy;
public:
    Point(): ix{0}, iy{0}{}
    Point(int rndx, int rndy): ix{rndx}, iy{rndy}{}

    int getX(){ return ix; }
    int getY(){ return iy; }

    friend ostream& operator<<(ostream& os, Point& point){
        os << "(" << point.getX() << "," << point.getY();
        return os;
    }
};


class Stack {
public:
	Stack(int stackCapacity = 4){
	}
	bool IsFull() const;
	bool IsEmpty() const;
	Point& Peek() const;//예외 - 빈 스택
	void Push(const Point& item);////예외 - full 스택
	Point& Pop();//예외 - 빈 스택
	void Dump();//예외 - 빈 스택
private:
	Point* st;
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
