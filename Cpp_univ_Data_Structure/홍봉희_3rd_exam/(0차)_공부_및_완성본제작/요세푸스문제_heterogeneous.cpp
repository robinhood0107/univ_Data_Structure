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

    void SolveJosephus();
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
template<>
Data DerivedNode<char>::GetData() {
	Data t; t.id = 0; t.c = data; return t;
}
template<>
Data DerivedNode<int>::GetData() {
	Data t; t.id = 1; t.i = data; return t;
}
template<>
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

//기존 Delete() 함수를 사용하지 않고, 포인터를 직접 조작하여 K번째 노드를 제거합니다. 
//(이종 리스트의 데이터가 중복될 경우 Delete(Data)는 잘못된 노드를 지울 수 있기 때문입니다.)
void List::SolveJosephus()
{
    int K;
    cout << "Please input K (step): ";
    cin >> K;
    if (K <= 0) {
        cout << "K must be positive." << endl;
        return;
    }

    // --- 1. 현재 리스트의 크기(N) 계산 ---
    int N = 0;
    Node* p = first;
    if (!p) { // 리스트가 비어있음
        cout << "List is empty." << endl;
        return;
    }
    while (p->link != 0) {
        N++;
        p = p->link;
    }
    N++; // 마지막 노드 카운트
    Node* lastNode = p; // 'p'는 이제 마지막 노드를 가리킴

    if (N <= 1) {
        cout << "Need at least 2 items to start." << endl;
        return;
    }

    cout << "Starting Josephus with N=" << N << ", K=" << K << endl;
    cout << "Initial list: ";
    PrintAll(*this);
    cout << endl;

    // --- 2. 리스트를 (임시로) 원형으로 만듦 ---
    // (멤버 함수이기에 first와 link에 접근 가능)
    lastNode->link = first;

    // 'prev'는 항상 삭제할 노드의 '직전' 노드를 가리킴
    Node* prev = lastNode; // 원형이므로 first의 직전은 lastNode

    // --- 3. N-1번 제거 루프 실행 ---
    for (int i = 0; i < N - 1; i++) {
        
        // --- 4. K-1번 이동하여 'prev' 위치 찾기 ---
        // (현재 'prev->link'가 1번째 카운트)
        for (int j = 0; j < K - 1; j++) {
            prev = prev->link;
        }

        // --- 5. 제거할 노드(target) 식별 ---
        Node* target = prev->link;
        Data d = target->GetData(); // 삭제 전 데이터 저장
        cout << "  > Deleting: " << d << endl;

        // --- 6. 노드 제거 (포인터 직접 조작) ---
        prev->link = target->link; // 'prev'가 'target'을 건너뛰게 함
        
        // (중요) 만약 'first' 포인터가 가리키던 노드가 삭제되면?
        if (target == first) {
            first = prev->link; // 'first' 포인터를 다음 노드로 업데이트
        }
        
        delete target; // 노드 메모리 해제

        // 'prev'는 현재 위치에 머무름. 다음 카운트는 'prev->link'부터 시작.
    }

    // --- 7. 최후 생존자 처리 ---
    Node* survivor = prev; // 마지막 남은 노드
    Data survivorData = survivor->GetData();
    cout << "[Survivor]: " << survivorData << endl;

    // --- 8. 리스트 원상 복구 (원형 고리 끊기) ---
    // (리스트에는 생존자 1명만 남음)
    survivor->link = 0; 
    first = survivor; // 리스트의 'first'를 생존자로 설정
}



//float sum(l); //sum of all floating points
int main(void)
{
    List l;
    char select;

    // ⭐ 2. 'j' 메뉴 옵션을 프롬프트에 추가합니다.
    cout << "Select command a: add, d: delete, j: josephus, p: print, q : quit =>";
    cin >> select;
    while (select != 'q')
    {
        switch (select)
        {
        case 'a':
            l.Add();
            break;
        case 'd':
            l.Delete();
            break;

        // ⭐ 3. 'j' 케이스를 switch 문에 추가합니다.
        case 'j':
            l.SolveJosephus();
            break;

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
		cout << "Select command a: add, d: delete, j: josephus, p: print, q : quit =>";
		cin >> select;
	}
	system("pause");
	return 0;
}
