/*
 * === 코드 전체 설명 ===
 * 이 C++ 코드는 '이종 리스트(Heterogeneous List)'를 구현한 프로그램입니다.
 * 이 리스트는 C++의 템플릿과 다형성(polymorphism)을 이용하여 
 * 하나의 리스트 안에 'int', 'char', 'float' 타입의 데이터를 
 * 동시에 저장할 수 있습니다.
 * * 또한, 이 리스트를 원형으로 만들어 '요세푸스 문제(Josephus Problem)'를 
 * 해결하는 기능(SolveJosephus)을 포함하고 있습니다.
 *
 * --- 1. Data 구조체와 Union ---
 * 리스트가 여러 타입을 다루기 위한 핵심 데이터 구조입니다.
 * - union { int i; char c; float f; }:
 * '공용체(union)'는 메모리 공간을 공유합니다. 
 * 즉, 이 구조체는 int, char, float 중 *하나*의 값만 저장할 수 있습니다.
 * - int id:
 * '태그(tag)' 또는 '판별자(discriminator)' 역할을 합니다.
 * id가 0이면 char(c), 1이면 int(i), 2이면 float(f) 데이터가 
 * union에 저장되어 있음을 나타냅니다.
 * - bool operator==(Data const d):
 * 두 Data 객체를 비교하는 연산자입니다. 
 * 먼저 'id'를 비교하여 같은 타입인지 확인하고, 
 * 같은 타입일 경우에만 union 내부의 실제 값을 비교합니다.
 *
 * --- 2. Node (추상 기본 클래스) ---
 * 모든 노드 타입의 '부모' 역할을 하는 '추상 클래스'입니다.
 * - Node* link: 다음 노드를 가리키는 포인터 (단일 연결 리스트).
 * - virtual Data GetData() = 0:
 * '순수 가상 함수'입니다. 이 함수는 "이 노드의 실제 데이터를 
 * 'Data' 구조체 형식으로 반환하라"는 '명령'만 정의합니다.
 * 구현부가 없으므로, 'Node' 클래스의 객체는 직접 생성할 수 없습니다.
 * 이 함수 때문에 'List' 클래스는 'Node*' 포인터만으로 
 * 모든 자식 노드(int, char, float)의 데이터를 통일된 방식으로 
 * 가져올 수 있습니다 (다형성).
 *
 * --- 3. DerivedNode<Type> (템플릿 파생 클래스) ---
 * 'Node'를 상속받는 '구체 클래스(Concrete Class)'입니다.
 * - template<class Type>: 
 * '템플릿'을 사용하여 'Type' 자리에 int, char, float 등
 * 어떤 타입이든 받을 수 있습니다.
 * - Type data: 실제 데이터(int, char, float)를 저장합니다.
 * - Data GetData(): 'Node'의 순수 가상 함수를 '구현'합니다.
 *
 * --- 4. 템플릿 특수화 (Template Specialization) ---
 * 'DerivedNode'의 'GetData()' 함수를 각 타입(int, char, float)에 맞게 
 * '특수화'하여 구현한 부분입니다.
 * - template<> Data DerivedNode<char>::GetData():
 * 'Type'이 'char'일 경우의 'GetData()' 구현입니다.
 * 'Data' 구조체를 생성하고, id=0 (char)로 설정한 뒤, 
 * 자신의 'data'(char 값)를 't.c'에 넣어 반환합니다.
 * - (int, float도 동일하게 id=1, id=2로 설정하여 구현)
 *
 * --- 5. List 클래스 ---
 * 연결 리스트 전체를 관리하는 메인 클래스입니다.
 * - Node* first: 리스트의 '첫 번째' 노드를 가리키는 포인터.
 * - Add(): 
 * 사용자에게 타입(0, 1, 2)과 값을 입력받습니다.
 * 타입에 맞는 'DerivedNode' (예: new DerivedNode<int>(value))를 
 * 생성하여 리스트의 *맨 앞*에 추가합니다.
 * - Delete():
 * 사용자에게 삭제할 '값'을 입력받아 'Data' 구조체(tmp)를 만듭니다.
 * 'Search(tmp)'를 호출하여 삭제할 노드를 찾습니다.
 * (Search 로직이 복잡하여, 삭제할 노드의 '이전' 노드를 찾으려 시도합니다.)
 * 포인터 연결을 끊고(s->link = s->link->link) 노드를 'delete' 합니다.
 * - Search(Data):
 * 이터레이터를 사용하여 'Data' 값과 일치하는 노드를 찾습니다.
 * 이 코드의 Search는 삭제를 돕기 위해, 현재 노드 *또는* * 다음 노드가 일치하면 '현재' 노드 포인터를 반환하는 
 * (즉, 이전 노드를 반환하려는) 복잡한 로직을 가집니다.
 *
 * --- 6. SolveJosephus() 함수 (요세푸스 문제) ---
 * 리스트를 원형으로 만들어 K번째 사람을 계속 제거하는 알고리즘입니다.
 * 1. (N 계산): 리스트를 순회하여 전체 크기(N)를 계산하고, 
 * '마지막 노드(lastNode)'를 찾습니다.
 * 2. (원형 리스트 생성): 'lastNode->link = first;'를 실행하여 
 * 리스트를 임시로 '원형'으로 만듭니다.
 * 3. (포인터 설정): 'prev' 포인터를 'lastNode'로 설정합니다.
 * 'prev'는 항상 *삭제할 노드의 직전 노드*를 가리키게 됩니다.
 * 4. (N-1번 반복): 생존자가 1명 남을 때까지 N-1번 반복합니다.
 * 5. (K-1번 이동): 'prev' 포인터를 'K-1'번 이동시킵니다.
 * (이동 후 'prev->link'가 K번째, 즉 제거될 노드입니다.)
 * 6. (삭제 대상 식별): 'target = prev->link;'로 삭제할 노드를 지정합니다.
 * 7. (포인터 조작): 'prev->link = target->link;'
 * 'prev' 노드가 'target' 노드를 건너뛰고 
 * 그다음 노드를 가리키도록 연결을 끊습니다.
 * 8. (first 포인터 갱신): 만약 삭제된 'target'이 'first' 노드였다면,
 * 'first' 포인터를 다음 노드('prev->link')로 갱신해야 합니다.
 * 9. (메모리 해제): 'delete target;'로 노드를 삭제합니다.
 * 10. (생존자 처리): 루프가 끝나면 'prev' (또는 'survivor')가
 * 최후의 생존자를 가리킵니다.
 * 11. (원상 복구): 'survivor->link = 0;'으로 원형 고리를 끊고,
 * 'first = survivor;'로 리스트를 정상 상태로 복구합니다.
 *
 * --- 7. ListIterator 클래스 ---
 * 'List'를 안전하게 순회하기 위한 헬퍼 클래스입니다.
 * - 'current' 포인터로 현재 위치를 추적합니다.
 * - GetCurrent(): 
 * 'current->GetData()'를 호출합니다. 이 때 'Node'의 가상 함수 
 * 기능이 동작(다형성)하여, 'current'가 가리키는 실제 
 * 'DerivedNode'의 'GetData()' (char용, int용, float용)가 
 * 자동으로 호출됩니다.
 * - operator++(), NotNull(), NextNotNull(): 표준적인 이터레이터 
 * 도우미 함수들입니다.
 *
 * --- 8. PrintAll 및 main 함수 ---
 * - PrintAll(const List& l): 
 * 이터레이터를 사용하여 리스트의 모든 데이터를 순회하며 출력합니다.
 * - main():
 * 사용자 메뉴(a: Add, d: Delete, j: Josephus, p: Print, q: Quit)를
 * 제공하고, 선택에 따라 'List'의 해당 멤버 함수를 호출하는 
 * 메인 실행 루프입니다.
 */

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
