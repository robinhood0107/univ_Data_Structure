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
        os << "(" << point.getX() << "," << point.getY() << ")";
        return os;
    }
};


class Stack {
public:
	Stack(int stackCapacity = 4){
        capacity = stackCapacity;
        st = new Point[capacity];
        top =-1; //내가 틀린 부분: top은 항상 -1로 지정해야 한다.
	}
	~Stack(){
        delete[] st;
	}
	bool IsFull() const{
        return top == capacity-1;
        //항상 인덱스 생각!!!
	}
	bool IsEmpty() const{
        return top == -1;
	}
	Point& Peek() const{
        if(IsEmpty()){
            throw  EmptyStackException();
        }

        return st[top];
	}
	void Push(const Point& item){
        if(IsFull()){
            throw OverflowStackException();
        }

        //반드시 top을 먼저 증가시킨 다음에 넣는다
        //전치 증가
        st[++top] = item;
	}
	Point& Pop(){
        if(IsEmpty()){
            throw  EmptyStackException();
        }

        //반드시 후치감소!!!!! 그래야지 top을 출력 한다음에 삭제 할 수 있음!!!
        return st[top--];
	}
	void Dump(){
        for(int i=0; i<capacity; i++){
            cout << st[i] << " ";
        }
	}
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
	cout << "\n" <<  "0: Push " << "1: Pop, " << "2: Peek, " << "3: Dump, " << "4: Exit\n";
	cout << "선택번호: ";
	cin >> choice;
	return static_cast<Menu>(choice);
}
int main() {
	Stack st(4);  // 용량이 5인 정수 스택 생성
	Menu menu;
	srand(41);
	Point p;
	int rndx, rndy;


	while (true) {
		try {
			menu = SelectMenu();
			switch (menu) {
			case push: {
				rndx = rand() % 20;
                rndy = rand() % 20;
                p = Point(rndx, rndy);
				cout << "push 값: " << p;
				st.Push(p);
				break;
			}
			case pop: {
				cout << "pop 값 = " << st.Pop();
				break;
			}
			case peek: {
				cout << "Peek of stack: " << st.Peek() << endl;
				break;
			}
			case dump: {
				st.Dump();
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
