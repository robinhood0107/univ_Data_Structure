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
        capacity = stackCapacity;
        st = new Point[capacity];
        top = -1; //인덱스 라서 -1 시작인거 꼭 기억!!!!!
	}
	bool IsFull() const{
        //내가 틀린 부분: ㅅㅂ 내가 이러니까 계속 틀리는거다
        //top는 인덱스다!! 그래서 capacity-1로 해야 함!!
        return top == capacity -1;
	}
	bool IsEmpty() const{
        //내가 틀린 부분: ㅅㅂ 내가 이러니까 계속 틀리는거다
        //top는 인덱스다!! -1이면 빈 것
        return top == -1;
	}
	Point& Peek() const{
        if(IsEmpty()){
            throw EmptyStackException();
        }
        return st[top];
	}
	void Push(const Point& item){
        if(IsFull()){
            throw OverflowStackException();
        }
        st[++top] = item;
	}
	Point& Pop(){
        if(IsEmpty()){
            throw EmptyStackException();
        }
        return st[top--];
	}
	void Dump(){
        if(IsEmpty()){
            throw EmptyStackException();
        }
        for (int i = 0; i <= top; i++) {
            std::cout << st[i] << " ";
        }
            std::cout << "\n";
	}
private:
	Point* st;
	int top;
	int capacity;
};

//main도 수정해야 한다!!!!


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
