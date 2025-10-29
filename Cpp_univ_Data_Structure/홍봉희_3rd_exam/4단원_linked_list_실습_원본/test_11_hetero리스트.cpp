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
*/

class Node {
	friend class List;
	friend class ListIterator;
protected:
	Node* link;
	virtual Data GetData() = 0;
};

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
	
}

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
	

}

void List::Delete()
{
	
}

Node* List::Search(Data tmp)
{
	
	return NULL;
}

Data* ListIterator::First() {
	
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
	
}

ListIterator ListIterator:: operator ++(int)
{
	
}

bool ListIterator::NotNull()
{
	
}
bool ListIterator::NextNotNull()
{
	
}

ostream& operator<<(ostream& os, Data& retvalue)
{
	
	return os;
}

void PrintAll(const List& l)
{
	
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
