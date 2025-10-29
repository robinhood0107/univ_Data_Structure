/*
* doubly linked list
* 8단계- 원형 객체 이중 연결 리스트의 available list, getNode, retNode
* head node를 갖고 있고 삭제된 노드들은 available list에 리턴한다.
* CircularDoublyList를 대상으로 한 iterator를 구현한다.
* template 버전으로 구현 
*/
#include <iostream>
#include <time.h>
using namespace std;
class DoublyListNode;
class CircularDoublyList;
class CircularDoublyListIterator;
class Employee {
	friend class DoublyListNode;
	friend class CircularDoublyList;
	friend class CircularDoublyListIterator;
private:
	string eno;
	string ename;
	int salary;
public:
	Employee() {}
	Employee(string sno, string sname, int salary) :eno(sno), ename(sname), salary(salary) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator>(Employee&);
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
bool Employee::operator>(Employee& emp) {

}
char Employee::compare(const Employee* emp) const {


}
class CircularDoublyList;
class CircularDoublyListIterator;
class DoublyListNode {
	friend class CircularDoublyList;
	friend class CircularDoublyListIterator;
public:
	DoublyListNode() {
		data = *p; llink = rlink = this;
	}
	DoublyListNode() {
		llink = rlink = this;
	}
private:
	T data;
	DoublyListNode* llink, * rlink;
};

class CircularDoublyList {
	friend class CircularDoublyListIterator;
public:
	CircularDoublyList() { last = new DoublyListNode; }
	friend ostream& operator<<(ostream&, CircularDoublyList&);
	bool Delete(string);
	void Show();
	void Add(T*);//sno로 정렬되도록 구현
	bool Search(string);
	DoublyListNode* GetNode();
	void RetNode(DoublyListNode*);
	void Erase();
	CircularDoublyList& operator+(CircularDoublyList&);
private:
	DoublyListNode* last;
	static DoublyListNode* av;
};


class CircularDoublyListIterator {
public:
	CircularDoublyListIterator(const CircularDoublyList& l) : list(l)
	{

	}
	~CircularDoublyListIterator();
	bool NotNull();
	bool NextNotNull();
	T* First();
	T* Next();
	T* GetCurrent();
private:
	const CircularDoublyList& list;
	DoublyListNode* current;
};

DoublyListNode* CircularDoublyList::GetNode()
{ //provide a node for use

}

void CircularDoublyList::RetNode(DoublyListNode* x)
{ //free the node pointed to by x

}

void CircularDoublyList::Show() { // 전체 리스트를 순서대로 출력한다.

}

void CircularDoublyList::Add(T* element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	DoublyListNode* newNode = GetNode(); newNode->data = *element;
	DoublyListNode* first = last->rlink;
	DoublyListNode* p = first->rlink;

}

bool CircularDoublyList::Search(string eno) { // sno를 갖는 레코드를 찾기
	DoublyListNode* first = last->rlink;
	DoublyListNode* p = first->rlink;

}

bool CircularDoublyList::Delete(string eno) // delete the element
{
	DoublyListNode* first = last->rlink;
	DoublyListNode* p = first->rlink;

}

void CircularDoublyList::Erase() {

}


ostream& operator<<(ostream& os, CircularDoublyList& l)
{

}

CircularDoublyList& CircularDoublyList::operator+(CircularDoublyList& lb) {
	T* p, * q;
	CircularDoublyListIterator Aiter(*this); CircularDoublyListIterator Biter(lb);
	CircularDoublyList lc;
	p = Aiter.First(); q = Biter.First();

}


bool CircularDoublyListIterator::NotNull() {

}

bool CircularDoublyListIterator::NextNotNull() {

}

T* CircularDoublyListIterator::First() {

}

T* CircularDoublyListIterator::Next() {

}

T* CircularDoublyListIterator::GetCurrent() {

}

CircularDoublyListIterator::~CircularDoublyListIterator() {
}

//int printAll(const List& l);//list iterator를 사용하여 작성하는 연습
//int sumProductFifthElement(const List& l);//list iterator를 사용하여 작성하는 연습

int sum(const CircularDoublyList& l)
{

}

double avg(const CircularDoublyList& l)
{

}

int min(const CircularDoublyList& l)
{

}

int max(const CircularDoublyList& l)
{

}

enum Enum {
	Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

DoublyListNode* CircularDoublyList::av = 0;
/*
Node* CircularDoublyList::av = NULL;//static 변수의 초기화 방법을 기억해야 한다
*/
void main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee* data;
	bool result = false;
	CircularDoublyList<Employee> la, lb, lc;
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
			cout << *data;
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
			cout << *data;
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
