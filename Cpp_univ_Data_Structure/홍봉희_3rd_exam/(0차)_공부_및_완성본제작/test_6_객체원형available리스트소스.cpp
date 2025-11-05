/*
* 6단계- 원형 객체 연결 리스트의 available list, getNode, retNode
* head node를 갖고 있고 삭제된 노드들은 available list에 리턴한다.
* CircularList를 대상으로 한 iterator를 구현한다.
* template version으로 구현 
*/

/*
 * === 코드 전체 설명 ===
 * * 이 C++ 코드는 '직원(Employee)' 정보를 '원형 연결 리스트(CircularList)' 자료구조로 관리하는 프로그램입니다.
 * C++의 클래스, 포인터, 연산자 오버로딩, 이터레이터(Iterator) 개념을 사용하여 구현되었습니다.
 *
 * --- 1. Employee 클래스 ---
 * 직원의 정보(사원번호 eno, 이름 ename, 급여 salary)를 저장하는 기본 데이터 단위입니다.
 * friend 선언을 통해 Node, CircularList 등이 private 멤버에 접근할 수 있도록 허용합니다.
 * cout 출력을 위한 ostream << 연산자, 정렬을 위한 < 연산자, 비교를 위한 == 및 compare 함수가 정의되어 있습니다.
 *
 * --- 2. Node 클래스 ---
 * 연결 리스트의 각 요소를 구성하는 '노드'입니다.
 * 실제 데이터(Employee data)와 다음 노드의 메모리 주소를 가리키는 포인터(Node* link)로 구성됩니다.
 *
 * --- 3. CircularList 클래스 ---
 * 핵심 자료구조인 '원형 연결 리스트'를 관리합니다.
 * 이 리스트는 데이터가 없는 '헤더 노드(Header Node)'를 사용합니다.
 * 리스트의 '첫 번째' 노드가 아닌 '마지막 데이터 노드'를 가리키는 'last' 포인터 하나로 리스트 전체를 관리합니다.
 * (last->link는 헤더 노드, last->link->link는 첫 번째 데이터 노드입니다.)
 * 리스트가 비어있을 때는 last가 헤더 노드를 가리키고, 헤더 노드는 자신을 가리킵니다 (last == last->link).
 *
 * * 주요 멤버 함수:
 * - CircularList(): 생성자. 헤더 노드만 가진 빈 리스트 상태로 초기화합니다.
 * - Add(Employee*): 직원을 사원번호(eno) 순서대로 정렬하여 리스트에 삽입합니다.
 * - Delete(string eno): 사원번호로 노드를 찾아 리스트에서 제거하고, 노드를 av 리스트로 반환합니다.
 * - Search(string eno): 사원번호로 노드를 검색하여 존재 여부(true/false)를 반환합니다.
 * - Show(): 리스트의 모든 데이터를 순서대로 출력합니다.
 * - Erase(): 리스트의 모든 데이터 노드를 av 리스트로 반환하고, 리스트를 빈 상태로 초기화합니다.
 * - operator+(CircularList&): 두 리스트를 병합(merge)하여 *정렬된* 새 리스트(lc)를 생성하여 (값으로) 반환합니다.
 *
 * * static Node* av (Available List):
 * '사용 가능 리스트' 또는 '프리 리스트(Freelist)'입니다.
 * static으로 선언되어 모든 CircularList 객체가 이 리스트를 공유합니다.
 * Delete()로 삭제된 노드를 이곳에 저장했다가, Add() 시 GetNode()를 통해 재사용합니다.
 * 이는 new/delete 호출 횟수를 줄여 메모리 관리 효율을 높입니다.
 * - GetNode(): av 리스트에서 노드를 가져오거나 (없으면) 새로 생성합니다.
 * - RetNode(Node*): 사용이 끝난 노드를 av 리스트에 반환(추가)합니다.
 *
 * --- 4. ListIterator 클래스 ---
 * '순회자' 클래스입니다. 리스트의 내부 구조(Node)를 직접 노출하지 않고,
 * 리스트의 요소(Employee)에 처음부터 끝까지 순차적으로 접근할 수 있는 표준화된 방법을 제공합니다.
 * sum, avg, min, max 같은 외부 함수들이 이 이터레이터를 사용해 리스트 데이터를 읽습니다.
 *
 * * 주요 멤버 함수:
 * - ListIterator(const CircularList&): 생성자. 순회할 리스트를 받고, current 포인터를 첫 번째 *데이터* 노드로 초기화합니다.
 * - NotNull(): current가 헤더 노드가 아니면(즉, 유효한 데이터 노드이면) true를 반환합니다.
 * - NextNotNull(): 다음 노드(current->link)가 헤더 노드가 아니면(즉, 현재가 마지막 노드가 아니면) true를 반환합니다.
 * - First(): 첫 번째 데이터(Employee*)를 반환합니다. (위치 이동 없음)
 * - GetCurrent(): 현재 위치의 데이터(Employee*)를 반환합니다. (위치 이동 없음)
 * - operator++() (전위): current를 다음 노드로 이동시킵니다. (예: ++li)
 * - operator*() / operator->(): 현재 위치의 데이터에 접근합니다. (예: *li 또는 li->getSalary())
 *
 * --- 5. 전역 함수 (sum, avg, min, max) ---
 * ListIterator를 사용하여 CircularList의 급여(salary)에 대한 통계(합계, 평균, 최소, 최대)를 계산합니다.
 *
 * --- 6. main() 함수 ---
 * 사용자에게 메뉴(Add, Delete, Show, Merge 등)를 보여주고, 입력을 받아
 * CircularList의 각 기능을 실행하고 테스트하는 역할을 합니다.
 * Add 시 new로 생성한 Employee 객체는 Add 함수에서 노드로 복사된 후, 
 * 메모리 누수(leak)를 방지하기 위해 main에서 delete 합니다.
 * Merge 시에도 lc에 기존 데이터가 있다면 Erase()로 메모리를 반환한 후 새 병합 결과를 받습니다.
 */



#include <iostream>
#include <string>
#include <ctime> /* C++ 스타일 헤더 <ctime> 사용 권장 */
using namespace std;

/*
 * 클래스: Employee
 * 목적: 직원의 정보(사원번호, 이름, 급여)를 저장하는 데이터 객체입니다.
 */
class Employee {
    /* * friend 선언:
     * Node, CircularList, ListIterator 클래스가 Employee의 private 멤버에
     * 직접 접근할 수 있도록 허용합니다.
     */
    friend class Node;
    friend class CircularList;
    friend class ListIterator;
private:
    string eno;    /* 사원번호 */
    string ename;  /* 사원 이름 */
    int salary; /* 급여 */
public:
    /* 기본 생성자 */
    Employee() {}
    /* 멤버 초기화 생성자 */
    Employee(string sno, string sname, int salary) :eno(sno), ename(sname),
        salary(salary) {}

    /* ostream 연산자 오버로딩 (cout으로 바로 출력) */
    friend ostream& operator<<(ostream& os, Employee&);
    
    /* 비교 연산자 오버로딩 (정렬에 사용) */
    bool operator<(Employee&);
    bool operator==(Employee&);

    /*
     * compare 함수:
     * 두 Employee 객체(의 포인터)를 비교하여 결과를 문자로 반환합니다.
     * 리스트 병합(operator+)에서 사용됩니다.
     */
    char compare(const Employee* emp) const;

    /* 급여 값을 반환하는 getter 함수 */
    int getSalary() const {
        return salary;
    }
    
    /* 사원번호 값을 반환하는 getter 함수 (검색, 삭제에 필요) */
    string getEno() const {
        return eno;
    }
};

/* Employee 객체를 cout으로 출력하는 방식 정의 */
ostream& operator<<(ostream& os, Employee& emp) {
    os << "<" << emp.eno << ", " << emp.ename << ", " << emp.salary << ">";
    return os;
}

/* Employee 객체 비교 (==) */
bool Employee::operator==(Employee& emp) {
    bool result = false;
    if (eno == emp.eno)
        /* [수정] ename과 emp.ename을 비교 */
        return (ename == emp.ename); 
    else
        return false;
}

/* Employee 객체 비교 (<) : Add 함수에서 정렬 기준으로 사용 */
bool Employee::operator<(Employee& emp) {
    bool result = false;
    if (eno == emp.eno)
        /* [수정] ename과 emp.ename을 비교 */
        return (ename < emp.ename); 
    else
        return (eno < emp.eno);
}

/* Employee 객체 비교 (compare) : Merge 함수에서 정렬 기준으로 사용 */
char Employee::compare(const Employee* emp) const {
    if (this->eno > emp->eno)
        return '>';
    else if (this->eno < emp->eno)
        return '<';
    else
        return '=';
}

/*
 * 클래스: Node
 * 목적: Employee 데이터를 담는 공간(data)과 
 * 다음 노드를 가리키는 포인터(link)를 가지는 리스트의 기본 단위입니다.
 */
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

/*
 * 클래스: CircularList
 * 목적: Node들을 원형으로 연결하여 관리하는 핵심 자료구조 클래스입니다.
 * 특징: '헤더 노드'를 사용하며, 리스트의 '마지막 데이터 노드'를 가리키는
 * 'last' 포인터 하나로 리스트 전체를 관리합니다.
 */
class CircularList {
    friend class ListIterator;
    Node* last; /* 리스트의 마지막 *데이터* 노드를 가리킴 */
    
    /* * static Node* av:
     * 'Available List' (사용 가능 리스트).
     * 삭제된 노드들을 임시 저장하여 재사용하기 위한 공간입니다.
     * static이므로 모든 CircularList 객체가 이 공간을 공유합니다.
     */
    static Node* av; 
public:
    /*
     * 생성자:
     * 비어있는 리스트(헤더 노드만 존재)를 생성합니다.
     * last 포인터는 헤더 노드를 가리키고, 헤더 노드는 자신을 가리킵니다.
     */
    CircularList() {
        last = new Node(); 
        last->link = last;
    }
    bool Delete(string);
    void Show();
    void Add(Employee*);
    bool Search(string);
    Node* GetNode(); /* av 리스트에서 노드를 가져오거나 새로 생성 */
    void RetNode(Node*); /* 노드를 av 리스트에 반환 */
    void Erase(); /* 리스트의 모든 노드를 삭제(av에 반환) */
    
    /* [수정] 로컬 변수 참조 반환 오류를 막기 위해 값(value) 반환으로 변경 */
    CircularList operator+(CircularList&); 
    
    friend ostream& operator<<(ostream& os, CircularList& l);
};

/*
 * 클래스: ListIterator
 * 목적: 리스트의 내부 구조(Node)를 숨긴 채, 
 * 리스트의 요소(Employee)에 순차적으로 접근할 수 있도록 돕는
 * '순회자' 클래스입니다.
 */
// --- 이터레이터(Iterator) 클래스 ---
// 이터레이터: 리스트 순회(traversal)를 위한 헬퍼 클래스.
// 리스트의 내부 구조(Node)를 직접 노출하지 않고,
// 리스트의 요소(Employee)에 순차적으로 접근할 수 있게 해줍니다.
class ListIterator {
public:
    /* 생성자: 순회할 리스트(lst)를 받아 초기화합니다. */
    ListIterator(const CircularList& lst);
    ~ListIterator();

    /* NotNull: 현재 위치(current)가 헤더 노드가 아닌지 (유효한 데이터 노드인지) 확인 */
    bool NotNull();
    /* NextNotNull: 다음 위치(current->link)가 헤더 노드가 아닌지 확인 */
    bool NextNotNull();
    /* First: 리스트의 *첫 번째* 데이터(Employee)의 포인터를 반환 (위치 이동 없음) */
    Employee* First();
    /* Next: *다음* 노드로 이동하고, *이동한 위치*의 데이터 포인터를 반환 */
    Employee* Next();
    /* GetCurrent: *현재* 위치의 데이터 포인터를 반환 (위치 이동 없음) */
    Employee* GetCurrent();

    /* --- C++ 표준 이터레이터 연산자 오버로딩 --- */
    
    /* operator*: 현재 위치의 데이터 참조(Employee&) 반환 (dereference) */
    Employee& operator*() const;
    /* operator->: 현재 위치의 데이터 포인터(Employee*) 반환 (dereference) */
    Employee* operator->()const;
    /* operator++ (전위): 다음 노드로 이동 (current = current->link) */
    ListIterator& operator++(); 
    /* operator++ (후위): 현재 위치를 복사해 반환 후, 다음 노드로 이동 */
    ListIterator operator ++(int);
    /* operator !=: 두 이터레이터가 다른 위치인지 비교 */
    bool operator != (const ListIterator) const;
    /* operator ==: 두 이터레이터가 같은 위치인지 비교 */
    bool operator == (const ListIterator) const;
    
private:
    /* current: 현재 순회 중인 노드를 가리키는 포인터 */
    Node* current; 
    /* list: 순회 대상이 되는 원본 리스트 (const 참조) */
    const CircularList& list;
};

/* --- CircularList 멤버 함수 구현 --- */

/* GetNode: av 리스트에 노드가 있으면 재활용하고, 없으면 새로 생성 */
Node* CircularList::GetNode()
{ 
    Node* x;
    if (av) { x = av, av = av->link; }
    else x = new Node;
    return x;
}

/* RetNode: 사용이 끝난 노드 x를 av 리스트의 맨 앞에 추가 */
void CircularList::RetNode(Node* x)
{ 
    x->link = av;
    av = x;
    x = 0;
}

/* Show: 리스트의 모든 데이터를 순서대로 출력 */
void CircularList::Show() { 
    /* last == last->link는 리스트가 비어있다는 의미 (헤더만 존재) */
    if (last == last->link) {
        cout << "(empty list)" << endl;
        return;
    }

    Node* first = last->link; /* first는 헤더 노드를 가리킴 */
    Node* p = first->link; /* p는 첫 번째 *데이터* 노드를 가리킴 */
    
    /* p가 다시 헤더 노드(first)로 돌아올 때까지 순회 */
    while (p != first) { 
        cout << p->data;
        if (p != last) /* p가 마지막 노드가 아니라면 " -> " 출력 */
            cout << " -> ";
        p = p->link;
    }
    cout << endl;
}

/* Add: Employee 데이터를 리스트의 정렬된 위치에 추가 */
void CircularList::Add(Employee* element)
{
    Node* newNode = GetNode(); 
    newNode->data = *element;
    
    Node* first = last->link; /* 헤더 노드 */
    Node* p = first->link;    /* 첫 번째 데이터 노드 (순회용) */
    Node* q = first;          /* p의 이전 노드 (순회용) */

    /* Case 1: 리스트가 비어있을 경우 (p가 헤더를 가리킴) */
    if (p == first) 
    {
        first->link = newNode; /* 헤더 -> 새 노드 */
        newNode->link = first; /* 새 노드 -> 헤더 */
        last = newNode;        /* 새 노드가 마지막 노드가 됨 */
        return;
    }

    /* Case 2: 리스트가 비어있지 않을 경우, 정렬 위치 탐색 */
    while (p != first) { /* p가 헤더로 돌아올 때까지 */
        /* p의 데이터가 새 데이터보다 작으면 (operator< 사용) */
        if (p->data < *element) {
            q = p;
            p = p->link;
            /* Case 2-1: 리스트의 맨 마지막에 도달한 경우 */
            if (p == first) { 
                q->link = newNode;    /* 이전 노드 -> 새 노드 */
                newNode->link = first;/* 새 노드 -> 헤더 */
                last = newNode;       /* 새 노드가 마지막 노드가 됨 */
                return;
            }
        }
        else { 
            /* Case 2-2: 리스트의 중간 또는 맨 앞에 삽입 (q와 p 사이) */
            newNode->link = p;
            q->link = newNode;
            return;
        }
    }
}

/* Search: eno(사원번호)를 가진 노드를 찾아 true/false 반환 */
bool CircularList::Search(string eno) { 
    Node* first = last->link; /* 헤더 노드 */
    Node* p = first->link;    /* 첫 번째 데이터 노드 */
    
    while (p != first) {
        /* [개선] private 멤버이므로 getter 사용 */
        if (p->data.getEno() == eno) 
            return true;
        p = p->link;
    }
    return false;
}

/* Delete: eno(사원번호)를 가진 노드를 찾아 삭제 */
bool CircularList::Delete(string eno)
{
    Node* first = last->link; /* 헤더 노드 */
    Node* p = first->link;    /* 첫 번째 데이터 노드 (삭제 대상 탐색) */
    Node* q = first;          /* p의 이전 노드 */

    /* 리스트가 비어있으면 삭제 불가 */
    if (p == first) return false;

    while (p != first) {
        /* [개선] private 멤버이므로 getter 사용 */
        if (p->data.getEno() == eno) /* 삭제할 노드(p) 발견 */
        {
            /* Case 1: 삭제 대상이 마지막 노드(last)인 경우 */
            if (p == last) {
                /* Case 1-1: 리스트에 노드가 하나뿐인 경우 */
                if (q == first) {
                    first->link = first; /* 헤더 -> 헤더 */
                    last = first;        /* last가 헤더를 가리킴 (빈 리스트) */
                }
                /* Case 1-2: 노드가 여러 개인 경우 */
                else { 
                    q->link = first; /* 이전 노드 -> 헤더 */
                    last = q;        /* 이전 노드(q)가 새 last가 됨 */
                }
                RetNode(p); /* 삭제된 노드(p)를 av에 반환 */
                return true;
            }
            /* Case 2: 삭제 대상이 중간 노드 또는 첫 번째 노드인 경우 */
            q->link = p->link; /* q가 p의 다음 노드를 가리키도록 연결 */
            RetNode(p);
            return true;
        }
        else { /* 삭제 대상을 못 찾으면 다음 노드로 이동 */
            q = p;
            p = p->link;
        }
    }
    return false; /* 삭제할 대상이 없음 */
}

/* Erase: 리스트의 모든 노드를 av로 반환하고, 빈 리스트 상태로 초기화 */
void CircularList::Erase() {
    /* 이미 비어있으면 종료 */
    if (last == last->link) return; 

    Node* header = last->link; /* 1. 헤더 노드 주소 기억 */
    last->link = av;         /* 2. 마지막 노드가 av 리스트를 가리킴 */
    av = header;             /* 3. av의 시작이 헤더가 됨 (모든 노드 반환) */

    /* * 4. [수정] 리스트를 비어있는 초기 상태(생성자처럼)로 리셋
     * (NULL로 만들면 다른 함수에서 오류 발생)
     */
    last = new Node();
    last->link = last;
}

/* operator+: 두 리스트(this와 lb)를 병합하여 새 리스트(lc)를 반환 */
CircularList CircularList::operator+(CircularList& lb) {
    ListIterator Aiter(*this); /* this 리스트(la)의 이터레이터 */
    ListIterator Biter(lb);    /* lb 리스트의 이터레이터 */
    CircularList lc;           /* 병합 결과를 저장할 새 리스트 (로컬 변수) */

    /* NotNull()로 각 리스트가 비어있는지 확인 */
    Employee* p = Aiter.NotNull() ? Aiter.First() : nullptr;
    Employee* q = Biter.NotNull() ? Biter.First() : nullptr;

    /* p와 q가 모두 유효할 동안 (두 리스트 모두 끝에 도달하지 않음) */
    while (p && q) { 
        switch (p->compare(q)) { /* Employee::compare 함수 사용 */
        case '=': /* 같은 경우 (la 기준) */
            lc.Add(p);
            /* 다음 노드로 이동 (다음이 없으면 nullptr) */
            p = Aiter.NextNotNull() ? Aiter.Next() : nullptr;
            q = Biter.NextNotNull() ? Biter.Next() : nullptr;
            break;
        case '<': /* la가 작은 경우 */
            lc.Add(p);
            p = Aiter.NextNotNull() ? Aiter.Next() : nullptr;
            break;
        case '>': /* lb가 작은 경우 */
            lc.Add(q);
            q = Biter.NextNotNull() ? Biter.Next() : nullptr;
            break;
        }
    }
    
    /* la 리스트에 남은 요소들 추가 */
    while (p) {
        lc.Add(p);
        p = Aiter.NextNotNull() ? Aiter.Next() : nullptr;
    }
    /* lb 리스트에 남은 요소들 추가 */
    while (q) {
        lc.Add(q);
        q = Biter.NextNotNull() ? Biter.Next() : nullptr;
    }
    
    /* [수정] 로컬 변수 lc를 값으로 복사하여 반환 */
    return lc; 
}

/* --- ListIterator 멤버 함수 구현 --- */

/* 생성자: current를 첫 번째 *데이터* 노드로 초기화 */
ListIterator::ListIterator(const CircularList& lst) : list(lst),
    current(lst.last->link->link) {
}

/* 소멸자: (하는 일 없음) */
ListIterator::~ListIterator() {
}

/* NotNull: current가 헤더 노드를 가리키면 순회 종료 (false) */
bool ListIterator::NotNull() {
    if (current != list.last->link)
        return true;
    else
        return false;
}

/* NextNotNull: current의 다음 노드가 헤더 노드면 (false) */
bool ListIterator::NextNotNull() {
    if (current->link != list.last->link)
        return true;
    else
        return false;
}

/* First: 첫 번째 데이터 노드의 Employee 데이터 포인터 반환 */
Employee* ListIterator::First() {
    return &list.last->link->link->data;
}

/* Next: current를 다음 노드로 이동시키고, 새 current의 데이터 반환 */
Employee* ListIterator::Next() {
    current = current->link;
    Employee* e = &current->data;
    return e;
}

/* GetCurrent: 현재 current 위치의 데이터 반환 */
Employee* ListIterator::GetCurrent() {
    return &current->data;
}

/* operator*: 현재 노드의 데이터(Employee&) 반환 */
Employee& ListIterator::operator*() const {
    return current->data;
}

/* operator->: 현재 노드의 데이터 포인터(Employee*) 반환 */
Employee* ListIterator::operator->()const {
    return &current->data;
}

/* operator++ (전위): current를 다음 노드로 이동시키고 자신을 반환 */
ListIterator& ListIterator::operator++() {
    current = current->link;
    return *this;
}

/* operator++ (후위): 현재 상태 복사 후, current를 이동시키고 복사본 반환 */
ListIterator ListIterator::operator ++(int) {
    ListIterator old = *this;
    current = current->link;
    return old;
}

/* operator !=: 두 이터레이터의 current 포인터 주소 비교 */
bool ListIterator::operator != (const ListIterator right) const {
    return current != right.current;
}

/* operator ==: 두 이터레이터의 current 포인터 주소 비교 */
bool ListIterator::operator == (const ListIterator right) const {
    return current == right.current;
}

/* ostream << (List): 이터레이터를 사용하여 리스트 내용 출력 */
ostream& operator<<(ostream& os, CircularList& l)
{
    ListIterator li(l);
    /* 리스트가 비어있는지 확인 */
    if (!li.NotNull()) {
        os << "(empty list)";
        return os;
    }
    
    /* [수정] li.First()는 Employee*를 반환하므로, *로 역참조해야 함 */
    os << *li.First(); 

    /* 다음 노드가 헤더가 아닐 때까지 반복 */
    while (li.NextNotNull())
        /* [수정] li.Next()도 Employee*를 반환하므로, *로 역참조 */
        os << " + " << *li.Next(); 
    os << endl;
    return os;
}


/* --- 이터레이터를 활용한 전역 함수 --- */

/* sum: 리스트 모든 직원의 급여 합계 반환 */
int sum(const CircularList& l)
{
    ListIterator li(l); /* 1. 이터레이터 생성 */
    if (!li.NotNull()) return 0; /* 2. 비어있는지 확인 */
    
    /* 3. 첫 번째 값으로 초기화 */
    Employee* emp = li.First();
    int retValue = emp->getSalary();
    
    /* 4. 다음 노드가 있을 때까지 반복 */
    while (li.NextNotNull() == true) {
        /* * [개선] 
         * ++li; (다음 노드로 이동)
         * li.GetCurrent(); (현재 노드 데이터 접근)
         * 두 단계로 분리하여 명확하게 처리
         */
        ++li; 
        retValue = retValue + li.GetCurrent()->getSalary();
    }
    return retValue;
}

/* avg: 리스트 모든 직원의 급여 평균 반환 */
double avg(const CircularList& l)
{
    ListIterator li(l);
    if (!li.NotNull()) return 0;

    int retvalue = li.First()->getSalary();
    int count = 1;
    
    while (li.NextNotNull() == true) {
        ++li; /* 다음 노드로 이동 */
        count++; /* 카운트 증가 */
        retvalue = retvalue + li.GetCurrent()->getSalary(); /* 값 누적 */
    }
    double result = (double)retvalue / count;
    return result;
}

/* min: 리스트에서 최소 급여 반환 */
int min(const CircularList& l)
{
    ListIterator li(l);
    if (!li.NotNull()) return -1; /* 비어있을 경우 -1 */

    int minValue = li.First()->getSalary(); /* 첫 값으로 초기화 */
    
    while (li.NextNotNull() == true) {
        ++li;
        int currentSalary = li.GetCurrent()->getSalary();
        if (minValue > currentSalary)
        {
            minValue = currentSalary; /* 최소값 갱신 */
        }
    }
    return minValue;
}

/* max: 리스트에서 최대 급여 반환 */
int max(const CircularList& l)
{
    ListIterator li(l);
    if (!li.NotNull()) return -1; /* 비어있을 경우 -1 */

    int maxValue = li.First()->getSalary(); /* 첫 값으로 초기화 */
    
    while (li.NextNotNull() == true) {
        ++li;
        int currentSalary = li.GetCurrent()->getSalary();
        if (maxValue < currentSalary)
        {
            maxValue = currentSalary; /* 최대값 갱신 */
        }
    }
    return maxValue;
}

/* 메뉴 선택을 위한 열거형(Enum) 정의 */
enum Enum {
    Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

/* static 변수(av) 초기화 (프로그램 시작 시) */
Node* CircularList::av = NULL; 

/* [수정] main 함수는 int를 반환해야 함 */
int main() {
    Enum menu; 
    int selectMenu, num;
    string eno, ename;
    int pay;
    Employee* data;
    bool result = false;
    CircularList la, lb, lc; /* 리스트 객체 생성 */

    do {
        cout << endl << "0.Add(la), 1.Add(lb), 2.Delete(la), 3.Show, 4.Search(la), ";
        cout << "5.Merge(la+lb=lc), 6.sum(la), 7.avg(la), 8.min(la), 9.max(la), 10.exit" << endl;
        cout << "선택:: ";
        cin >> selectMenu;
        
        switch (static_cast<Enum>(selectMenu)) {
        case Add0:
            cout << "리스트 la에 추가합니다." << endl;
            cout << "사원번호 입력:: "; cin >> eno;
            cout << "사원 이름 입력:: "; cin >> ename;
            cout << "사원 급여:: "; cin >> pay;
            data = new Employee(eno, ename, pay);
            la.Add(data);
            /* [개선] Add에서 데이터 복사가 끝났으므로 원본 data 삭제 (메모리 누수 방지) */
            delete data; 
            break;
        case Add1:
            cout << "리스트 lb에 추가합니다." << endl;
            cout << "사원번호 입력:: "; cin >> eno;
            cout << "사원 이름 입력:: "; cin >> ename;
            cout << "사원 급여:: "; cin >> pay;
            data = new Employee(eno, ename, pay);
            lb.Add(data);
            /* [개선] 메모리 누수 방지 */
            delete data;
            break;
        case Delete:
            cout << "리스트 la에서 삭제합니다." << endl;
            cout << "사원번호 입력:: "; cin >> eno;
            result = la.Delete(eno);
            if (result)
                cout << "eno = " << eno << " 삭제 완료." << endl;
            else
                cout << "eno = " << eno << " 삭제 실패(없음)." << endl;
            break;
        case Show:
            cout << "--- 리스트 la ---" << endl; la.Show();
            cout << "--- 리스트 lb ---" << endl; lb.Show();
            cout << "--- 리스트 lc ---" << endl; lc.Show();
            break;
        case Search:
            cout << "리스트 la에서 검색합니다." << endl;
            cout << "사원번호 입력:: "; cin >> eno;
            result = la.Search(eno);
            if (!result)
                cout << "검색 값 = " << eno << " 데이터가 없습니다." << endl;
            else
                cout << "검색 값 = " << eno << " 데이터가 존재합니다." << endl;
            break;
        case Merge:
            /* [개선] lc에 이미 데이터가 있다면 Erase로 반환 (메모리 누수 방지) */
            cout << "lc.Erase() 호출 (이전 데이터 반환)" << endl;
            lc.Erase(); 
            
            lc = la + lb; /* 병합 연산 (수정된 operator+ 사용) */
            
            cout << "--- 병합 결과 (lc) ---" << endl; lc.Show();
            cout << "--- 리스트 la를 삭제 ---" << endl; la.Erase(); la.Show();
            cout << "--- 리스트 lb를 삭제 ---" << endl; lb.Erase(); lb.Show();
            break;
        case SUM: cout << "sum(la) = " << sum(la) << endl; break;
        case AVG: cout << "avg(la) = " << avg(la) << endl; break;
        case MIN: cout << "min(la) = " << min(la) << endl; break;
        case MAX: cout << "max(la) = " << max(la) << endl; break;
        case Exit: 
            cout << "프로그램을 종료합니다." << endl;
            break;
        }
    } while (static_cast<Enum>(selectMenu) != Exit);
    
    /* * 프로그램 종료 전, 동적으로 할당된 리스트 노드들을 
     * (la, lb, lc 및 av 리스트의 모든 노드) 
     * 실제로는 모두 delete 해제해야 하나,
     * 이 코드에서는 os가 종료되면서 메모리가 반환되는 것에 의존하고 있습니다.
     * (main 함수가 끝나기 전에 la.Erase(), lb.Erase(), lc.Erase() 및
     * av 리스트의 모든 노드를 delete하는 로직이 추가되면 더 좋습니다.)
     */
    
    //cin >> num; /* 프로그램 종료 직전 입력을 기다리는 불필요한 코드 제거 */
    return 0; /* int main()의 반환값 */
}

