//소스 코드4.8: Generalized List
//Devise a function that produces a gen list from the input l = (a,(b,c))
/*
* 단계 10
* 
소스 코드 실습 대상
1. copy하여 copy 전과 후의 결과를 출력
2. 2개의 gen list를 ==
3. depth 결과를 출력
4. reference count 사용하여 getnode, retnode 구현, gen list 반환 코드 구현 테스트
5. template version으로 만드는 것 – int data;를 T data;로 변경하고 T는 coef, exp로 사용하는 구현한다
*/
#include <iostream>

using namespace std;
int GetData();

class GenList; // forward declaration

class GenListNode
{
	friend class GenList;
	friend int operator==(const GenList&, const GenList&);
	friend int equal(GenListNode*, GenListNode*);
private:
	GenListNode* link;
	bool tag; // 0 for data, 1 for dlink, 2 for ref
	union {
		int data;
		GenListNode* dlink;
		int ref;
	};
};

class GenList
{
	friend int operator==(const GenList&, const GenList&);
	friend int equal(GenListNode*, GenListNode*);
private:
	GenListNode* first;
	static 	GenListNode* av;
	GenListNode* Copy(GenListNode*);
	void Visit(GenListNode*);//driver
	int Depth(GenListNode*);
	GenListNode* MakeList(GenListNode*);
	void Delete(GenListNode*);
public:
	void Copy(const GenList&);
	void Visit();//workhorse
	~GenList();
	int Depth();
	void MakeList();
};

GenList::~GenList()
//Each head node has a reference count. We assume first != 0
{
	Delete(first);
	first = 0;
}
void GenList::Copy(const GenList& l)
{
	first = Copy(l.first);
}

void GenList::Visit()//public function으로 구현
{
	cout << "<";
	Visit(this->first);
	cout << ">";
}
/*
GenList::~GenList( )//구현하는 실습을 한다.
{
Delete(first);
first = 0;
}
*/

int operator==(const GenList& l, const GenList& m)
{
	return equal(l.first, m.first);
}

//Workhorse - 반환시에 문제 발생함
void GenList::Delete(GenListNode* x)
{

}

int GenList::Depth()
{
	return Depth(first);
}

void GenList::MakeList()
{
	first = MakeList(first);
}

//copy, visit, equal 등의 recursive 함수를 먼저 공부한 후에 MakeList( )를 이해하는 것이 좋다 
GenListNode* GenList::MakeList(GenListNode* s)
{
	
}

GenListNode* GenList::Copy(GenListNode* p) //private function
{
	
}

void GenList::Visit(GenListNode* p)
{
	
}

int equal(GenListNode* s, GenListNode* t)
{
	
}

int GenList::Depth(GenListNode* s)
{
	
}


int GetData() {
	cout << endl << "0: exit, 1: dlink, 2 정수입력: ";
	int n;
	cin >> n;
	return n;
}
GenListNode* GenList::av = 0;

enum Enum {
	Make, Copy, Depth, Visit, Quit
};

void main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	GenList l;
	GenList m;
	char select;
	int max = 0, x = 0;


	do {
		cout << "0.Make, 1.Copy, 2.Depth, 3.Visit, 4.Quit:: ";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Make:
			l.MakeList()
			break;
		case Copy:
			m.Copy(l);
			cout << "Copy Result" << endl;
			l.Visit();
			m.Visit();
			break;
		case Depth:
			cout << "depth: " << l.Depth();
			cout << endl;
			break;
		case Visit:
			cout << "tag : data (link)" << endl;
			l.Visit();
			cout << endl;
			break;
		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
			break;
		case Quit: // 꼬리 노드 삭제
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Quit);
	cin >> num;
}

