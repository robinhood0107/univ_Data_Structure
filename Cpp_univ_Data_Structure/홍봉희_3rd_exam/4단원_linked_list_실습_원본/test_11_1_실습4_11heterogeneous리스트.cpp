//소스 코드4.9: Heterogeneous Linked List
#include <iostream>
#include <string>
#include <cctype>

using namespace std;
enum boolean { FALSE, TRUE };
struct Data
{
	int id; //id = 0, 1, 2 if the node contains char, int, float
	union {
		int i;
		char c;
		float f;
	};
	bool operator==(Data const d);
};

/*
class CombinedNode {
//use union to merge different node types into one class definition
	friend class List;
	friend class ListIterator;
private:
	Data data;
	CombinedNode* link;
};
class List {
	friend class ListIterator;
public:
private:
	CombinedNode* first;
};
void printNode(const CombinedNode* p) {
	switch (p->data.id) {
	case 0: cout << p->data.c; break;
	case 1: cout << p->data.i; break;
	case 2: cout << p->data.f; break;
	}
}
*/

/*
즉, 타입 정보는 enum 태그(id)로 직접 관리합니다.

id와 실제로 읽는 union 멤버가 안 맞으면 **UB(정의되지 않은 동작)**입니다.
→ 프로그래머가 항상 조심해야 하는 구조
*/


/*
Node는 추상 클래스 (직접 객체 생성 불가)
*/
class Node {
	friend class List;
	friend class ListIterator;
protected:
	Node* link;
	virtual Data GetData() = 0;
};

/*
DerivedNode 는 concrete class
*/
template<class Type>
class DerivedNode : public Node {
	friend class List;
	friend class ListIterator;
public:
	DerivedNode(Type item) : data(item) { link = 0; }
private:
	Type data;
	Data GetData();
};

class List {
	friend class ListIterator;
public:
	List() { first = 0; };
	~List() { };
	void Add();
	void Delete();
	Node* Search(Data);
private:
	Node* first;
};

class ListIterator {
public:
	ListIterator(const List& l) : list(l), current(l.first) { };
	ListIterator& operator ++();
	ListIterator operator ++(int);
	Data* First();
	Node* Next();
	bool NotNull();
	bool NextNotNull();
	Data GetCurrent();
	Node* CurrentPointer();
private:
	const List& list;
	Node* current;
	Data temp;
};

bool Data::operator==(Data const d)
{
	switch (d.id)
	{
	case 0:
		if (this->c == d.c)
			return TRUE;
		break;
	case 1:
		if (this->i == d.i)
			return TRUE;
		break;
	case 2:
		if (this->f == d.f)
			return TRUE;
		break;
	}
	return FALSE;
}
/*
실제로 들어가는 노드는 DerivedNode<int>, DerivedNode<char>, DerivedNode<float> 같은 서브클래스 인스턴스.
*/
Data DerivedNode<char>::GetData() {
	Data t; t.id = 0; t.c = data; return t;
}

Data DerivedNode<int>::GetData() {
	Data t; t.id = 1; t.i = data; return t;
}

Data DerivedNode<float>::GetData() {
	Data t; t.id = 2; t.f = data; return t;
}

void List::Add()
{
	int value;
	float num;
	char c;
	cout << "Please input data type. 0 = char, 1 = int, 2 = float" << endl;
	cin >> value;
	if (!first)
		switch (value)
		{
		case 0:
			cin >> c;
			first = new DerivedNode<char>(c);
			break;
		case 1:
			cin >> value;
			first = new DerivedNode<int>(value);
			break;
		case 2:
			cin >> num;
			first = new DerivedNode<float>(num);
			break;
		default:
			break;
		}
	else
	{
		switch (value)
		{
		case 0:
		{
			cin >> c;
			Node* n = new DerivedNode<char>(c);
			n->link = first;
			first = n;
			break;
		}
		case 1:
		{
			cin >> value;
			Node* na = new DerivedNode<int>(value);
			na->link = first;
			first = na;
			break;
		}
		case 2:
		{
			cin >> num;
			Node* nb = new DerivedNode<float>(num);
			nb->link = first;
			first = nb;
			break;
		}
		default:
			break;
		}
	}

}

void List::Delete()
{
	int value;
	char c;
	float num;
	Data tmp;

	if (first == NULL) cout << " List is empty" << endl;
	else
	{
		cout << "Please input data type. 0 = char, 1 = int, 2 = float" << endl;
		cin >> value;
		cin.clear();
		switch (value)
		{
		case 0:
			cin >> c;
			tmp.c = c;
			tmp.id = 0;
			break;
		case 1:
			cin >> value;
			tmp.i = value;
			tmp.id = 1;
			break;
		case 2:
			cin >> num;
			tmp.f = num;
			tmp.id = 2;
			break;
		default:
			break;
		}
		Node* s = Search(tmp);
		if (s == first && !(s->link->GetData() == tmp))
		{
			Node* tmp;
			tmp = s;
			s = s->link;
			first = s;
			delete tmp;
		}
		else if (s)
		{
			Node* tmp;
			tmp = s->link;
			s->link = s->link->link;
			delete tmp;
		}
	}
}

Node* List::Search(Data tmp)
{
	ListIterator li(*this);
	while (li.NotNull())
	{
		if (li.GetCurrent() == tmp)
			return li.CurrentPointer();
		else if (li.Next()->GetData() == tmp)
			return li.CurrentPointer();
		++li;
	}
	return NULL;
}

Data* ListIterator::First() {
	if (list.first) {
		temp = list.first->GetData();
		return &temp;
	}
	return 0;
}

Data ListIterator::GetCurrent() {
	return current->GetData();
}

Node* ListIterator::Next()
{
	return current->link;
}

Node* ListIterator::CurrentPointer()
{
	return current;
}

ListIterator& ListIterator::  operator ++()
{
	current = current->link;
	return *this;
}

ListIterator ListIterator:: operator ++(int)
{
	ListIterator old = *this;
	current = current->link;
	return old;
}

bool ListIterator::NotNull()
{
	if (current) return TRUE;
	else return FALSE;
}
bool ListIterator::NextNotNull()
{
	if (current->link) return TRUE;
	else return FALSE;
}

ostream& operator<<(ostream& os, Data& retvalue)
{
	switch (retvalue.id)
	{
	case 0:
		cout << retvalue.c;
		break;
	case 1:
		cout << retvalue.i;
		break;
	case 2:
		cout << retvalue.f;
		break;
	default:
		break;
	}
	return os;
}

void PrintAll(const List& l)
{
	ListIterator li(l);
	if (!li.NotNull()) return;
	Data retvalue = *li.First();
	cout << retvalue;
	if (li.NextNotNull())
		cout << " + ";
	while (li.NextNotNull() == true) {
		++li;//current를 증가시킴
		//retvalue = retvalue + *li.Next( );
		retvalue = li.GetCurrent();//현재 current가 가르키는 node의 값을 가져옴
		cout << retvalue;
		if (li.NextNotNull())
			cout << " + ";
	}
}

//float sum(l); //sum of all floating points
int main(void)
{
	List l;
	//implement heterogeneous linked stacks and queues
	char select;
	int max = 0, x = 0;
	cout << "Select command a: add data, d: delete data, p: print all, q : quit =>";
	cin >> select;
	while (select != 'q')
	{
		switch (select)
		{
		case 'a':
			l.Add();
			break;
			//case ‘c’: l.Copy( ); //구현실습
		case 'd':
			l.Delete();
			break;
			//case ‘e’: l.Equal( ); //구현실습
		case 'p':
			cout << "print all: ";
			PrintAll(l);
			cout << endl;
			break;
		case 'q':
			cout << "Quit" << endl;
			break;

		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
			break;
		}
		cout << "Select command a: add data, d: delete data, p: print all, q : quit =>";
		cin >> select;
	}
	system("pause");
	return 0;
}
