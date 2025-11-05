/*
* 6단계- 원형 객체 연결 리스트의 available list, getNode, retNode
* head node를 갖고 있고 삭제된 노드들은 available list에 리턴한다.
* CircularList를 대상으로 한 iterator를 구현한다.
* template version으로 구현 
*/
#include <iostream>
#include <time.h>
using namespace std;

class Employee {
	friend class Node;
	friend class CircularList;
	friend class ListIterator;
private:
	string eno;
	string ename;
	int salary;
public:
	Employee() {}
	Employee(string sno, string sname, int salary) :eno(sno), ename(sname), salary(salary) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator==(Employee&);
	char compare(const Employee* emp) const;
	int getSalary() const {
		return salary;
	}
};
ostream& operator<<(ostream& os, Employee& emp) {

}
bool Employee::operator==(Employee& emp) {

}
bool Employee::operator<(Employee& emp) {

}
char Employee::compare(const Employee* emp) const {


}

class Node {
	friend class ListIterator;
	friend class CircularList;
	Employee data;
	Node* link;
public:
	Node() { }
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};

class CircularList {
	friend class ListIterator;
	Node* last;//last 노드를 가리키는 last 변수를 사용하는 버젼으로 구현 실습 
	static Node* av;
public:
	CircularList() {
		last = new Node(); last->link = last;
	}
	bool Delete(string);
	void Show();
	void Add(Employee*);//sno로 정렬되도록 구현
	bool Search(string);
	Node* GetNode();
	void RetNode(Node*);
	void Erase();
	CircularList& operator+(CircularList&);
	friend ostream& operator<<(ostream& os, CircularList& l);
};
class ListIterator {
public:
	ListIterator(const CircularList& lst);
	~ListIterator();
	bool NotNull();
	bool NextNotNull();
	Employee* First();
	Employee* Next();
	Employee& operator*() const;
	Employee* operator->()const;
	ListIterator& operator++(); //Next()
	ListIterator operator ++(int);
	bool operator != (const ListIterator) const;
	bool operator == (const ListIterator) const;
	Employee* GetCurrent();
private:
	Node* current; //pointer to nodes
	const CircularList& list;//existing list
};

Node* CircularList::GetNode()
{ //provide a node for use

}

void CircularList::RetNode(Node* x){

}
ostream& operator<<(ostream& os, CircularList& l)
{

}
void CircularList::Show() { // 전체 리스트를 순서대로 출력한다.

}
void CircularList::Add(Employee* element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	Node* newNode = GetNode(); newNode->data = *element;
	Node* first = last->link;
	Node* p = first->link;
	Node* q = first;
	
}
bool CircularList::Search(string eno) { // sno를 갖는 레코드를 찾기

}
bool CircularList::Delete(string eno) // delete the element
{

}
void CircularList::Erase() {


}
CircularList& CircularList::operator+(CircularList& lb) {
	Employee* p, * q;
	ListIterator Aiter(*this); ListIterator Biter(lb);
	CircularList lc;
	p = Aiter.First(); q = Biter.First();

}
ListIterator::ListIterator(const CircularList& lst) : list(lst), current(lst.last->link->link) {
}
bool ListIterator::NotNull() {

}
bool ListIterator::NextNotNull() {

}
Employee* ListIterator::First() {

}
Employee* ListIterator::Next() {

}

Employee* ListIterator::GetCurrent() {
	return &current->data;
}

ListIterator::~ListIterator() {
}

Employee& ListIterator::operator*() const {
	return current->data;
}

Employee* ListIterator::operator->()const {
	return &current->data;
}

ListIterator& ListIterator::operator++() {
	current = current->link;
	return *this;
}

ListIterator ListIterator::operator ++(int) {
	ListIterator old = *this;
	current = current->link;
	return old;
}

bool ListIterator::operator != (const ListIterator right) const {
	return current != right.current;
}

bool ListIterator::operator == (const ListIterator right) const {
	return current == right.current;
}
//int printAll(const List& l);//list iterator를 사용하여 작성하는 연습
//int sumProductFifthElement(const List& l);//list iterator를 사용하여 작성하는 연습
int sum(const CircularList& l)
{
	ListIterator li(l);

}

double avg(const CircularList& l)
{
	ListIterator li(l);

}

int min(const CircularList& l)
{
	ListIterator li(l);

}

int max(const CircularList& l)
{
	ListIterator li(l);

}

enum Enum {
	Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

Node* CircularList::av = NULL;//static 변수의 초기화 방법을 기억해야 한다

void main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee* data;
	bool result = false;
	CircularList la, lb, lc;
	Employee* s;
	do {
		cout << endl << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6. sum, 7.avg, 8.min, 9.max, 10.exit 선택::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add0:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			cout << "사원 급여:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			la.Add(data);
			break;
		case Add1:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			cout << "사원 급여:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			lb.Add(data);
			break;
		case Delete:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = la.Delete(eno);
			if (result)
				cout << "eno = " << eno << " 삭제 완료.";
			break;
		case Show:
			cout << "리스트 la = ";
			la.Show();
			cout << "리스트 lb = ";
			lb.Show();
			break;
		case Search:
			cout << "사원번호 입력:: ";
			cin >> eno;
			result = la.Search(eno);
			if (!result)
				cout << "검색 값 = " << eno << " 데이터가 없습니다.";
			else
				cout << "검색 값 = " << eno << " 데이터가 존재합니다.";
			break;
		case Merge:
			lc = la + lb;
			cout << "리스트 lc = ";
			lc.Show();
			cout << "리스트 la를 삭제" << endl;
			la.Erase();
			cout << "리스트 lb를 삭제" << endl;
			lb.Erase();
			cout << "리스트 la = ";
			la.Show();
			cout << endl << "리스트 lb = ";
			lb.Show();
			break;
		case SUM:  cout << "sum() = " << sum(la) << endl; break;
		case AVG:  cout << "avg() = " << avg(la) << endl; break;
		case MIN:  cout << "min() = " << min(la) << endl; break;
		case MAX:  cout << "max() = " << max(la) << endl; break;
		case Exit: // 꼬리 노드 삭제
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}
