/*
* 9단계: Linked List를 사용한 스택과 큐의 구현
* template 버전으로 구현 
*/

//Stack node & Queue Node
#include <stdio.h>
#include <iostream>
using namespace std;
class Employee {
	friend class Node;
	friend class LinkedList;
	string eno;
	string ename;
public:
	Employee() {}
	Employee(string sno, string sname) :eno(sno), ename(sname) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator==(Employee&);
};
ostream& operator<<(ostream& os, Employee& emp) {

}
bool Employee::operator==(Employee& emp) {

}
bool Employee::operator<(Employee& emp) {

}
 class Stack; //forward declaration
 class Queue;

class StackNode {
	friend class Stack;
private:
	int* data;
	StackNode* link;
public:
	StackNode(int* d = 0) : data(d) { link = 0; }//constructor
};


class QueueNode {
	friend class Queue;
private:
	int* data;
	QueueNode* link;
public:
	QueueNode(int* d = 0) : data(d) { link = 0; }//constructor
};


class Stack {
public:
	Stack() { top = 0; }//constructor
	void Add(int*);
	int* Delete();
	void Show();
private:
	StackNode* top;
	void StackEmpty();

};


class Queue {
public:
	Queue() { front = rear = 0; }//constructor
	void Add(int*);
	int* Delete();
	void ShowQueue();
private:
	QueueNode* front;
	QueueNode* rear;
	void QueueEmpty();

};


void Stack::Add(int* y) {

}


void Stack::StackEmpty() {

}

void Stack::Show() {

}

int* Stack::Delete()
//delete the top node from stack and return a pointer to its data
{

}


void Queue::Add(int* y) {

}


int* Queue::Delete()
//delete the first node in queue and return a pointer to its data
{

}


void Queue::QueueEmpty() {
	if (front == 0)
		cout << "Queue is empty" << endl;
	else
		cout << "Queue is non empty" << endl;
}

void Queue::ShowQueue() {

}
enum Enum {
	PushStack, PopStack, ShowStack, AddQueue, DeleteQueue, ShowQueue, Exit
};

void main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	bool result = false;
	Stack<Employee> st;
	Queue<Employee> qu;
	Employee* data;
	do {
		cout << "0.PushSintack, 1.PopStack, 2.ShowStack, 3.AddQueue, 4.DeleteQueue, 5.ShowQueue, 6.Exit:: ";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case PushStack:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			st.Add(data);
			break;
		case PopStack:
			data = st.Delete();
			cout << *data;
			break;
		case ShowStack:
			st.Show();
			break;
		case AddQueue:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			qu.Add(data);
			break;
		case DeleteQueue:
			data = qu.Delete();
			cout << *data;
			break;
		case ShowQueue:
			qu.ShowQueue();
			break;

		case Exit: // 꼬리 노드 삭제
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}

