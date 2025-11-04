/*
* 1단계-정수 연결 리스트: 단순한 linked list에서 add, delete하는 알고리즘을 코딩
* template 버전으로 만들기 
*/

//링크드 리스트 공부

//링크드 리스트란?
/*
연결리스트로

배열=순차적으로 연결된 공간에 데이터를 나열 하는 것이란면
링크드리스트=순차적이지 않은(랜덤한) 공간에 데이터를 나열하는 것이다.

링크드 리스트를 구성하는 요소는 다음과 같다
1.노드(저장하는 곳) 2.포인터(노드에 붙어있는 다음노드의 주소를 저장해둠.)
그리고 링크드리스트 전체에서 2가지의 부분을 따로 저장해 놓는다.
3.헤드(링크드리스트에서 가장 처음 위치하는 노드), 4.테일(링크드리스트에서 가장 마지막에 위치하는 노드)

링크드리스트는 확장되어서
양방향(doubly) 링크드리스트 --노드가 포인터를 2개(이전, 이후)를 가짐 [원래는 포인터(이후) 1개만 가지잖아]
원형 링크드리스트 --마지막 노드가 처음 노드를 참조함.(마지막 노드 포인터는 처음 노드 주소를 가리킨다.)

가장 필수적으로 링크드 리스트가 구현해야 할 클래스 개수(이거 기억하고 있어야 함. 지운다고 했음.)
Node() //필수, LinkedList와 friend 관계로 노드라는 기본단위

LinkedList() //기본 생성자
bool LinkedList::Delete(int); //필수, 노드 삭제
void LinkedList::Add(int element); //필수, 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
LinkedList::LinkedList& operator+(LinkedList&);  //필수, merge에 해당함, 객체+객체로 연결리스트 2개 연결함
bool LinkedList::Search(int data); //(졸라 간단함) //말그대로 데이터 찾아줌
void LinkedList::Show(); //(졸라 간단함) //전체 리스트를 순서대로 출력한다.

교수님이 merge delete insert 이 3개는 무조건 구현할 줄 알아야 한다고 함

즉 node, linkedlist, delete, add(insert), merge(operator+)를 가장 먼저 구현
Search, Show는 간단하게 구현가능함

삽입 삭제시 생각해야 하는 케이스

헤드 부분에 추가, 삭제
중간 부분에 추가, 삭제
꼬리 부분에 추가, 삭제

이것 부분만 잘 기억해서 구성하면 금방 구현이 가능하다.

*/
#include <iostream>
#include <time.h>
using namespace std;

class Node {
	friend class LinkedList;
	int data;
	Node* link;
public:
	Node(int element) {
		data = element;
		link = 0;
	}
};


//리스트는 node,pointer,head,tail 필요하다고 했잖아
//이거는 일반 링크드 리스트라서 node(data),pointer(link),head(first)라는 이름으로 만든 것!
class LinkedList {
	Node* first; //head를 이렇게 first라는 포인터로 가리켜 준다.
public:
	LinkedList() {
		first = 0; //c++11이하는 걍 0으로 해도 됨//이거 원래 원본은 0이었음 
	}
	bool Delete(int);
	void Show();
	void Add(int element);//정렬되도록 구현
	bool Search(int data);
	LinkedList operator+(LinkedList&);
    
    ~LinkedList();
	LinkedList& operator=(const LinkedList& other);
	LinkedList(const LinkedList& other);
};


void LinkedList::Show() { // 전체 리스트를 순서대로 출력한다.
	Node* p = first; //일단 당연 head 위치부터 시작(가져오기)

	while(p!=0){
		cout << p->data; //head포인터에 해당하는 data 가져오기(->는 포인터-간접지정연산자다.)(항상 구두점이랑 (역참조=)간접지정연산자(에스터리스크)는 다른것!!!)
		if(p->link != 0){ //(!=인거 조심)p->link가 nullptr이 아니라 존재한다면(!=이니까!!) //c++11 이전에는 0도 nullptr로 취급했는데 이후엔 이렇게 nullptr로 명시하기
			cout << " -> ";
		}
		p = p->link;
	}
	cout << endl;
}

void LinkedList::Add(int element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	Node* newNode = new Node(element); //새로운 node생성
	if (first == 0){ //head까지 비어있을 경우 //아예 빈 링크드리스트일 경우
		first = newNode;
		return; //Node(element)인 newNode를 바로 first에 연결시키고 바로 종료
	}

	Node *p = first, *q=0; //p는 head(first), q의 역할은 이전 노드(Previous Node) 포인터(sorted linked list 구현할때 필요함)
	//q는 p의 '이전 노드'를 기억하여, newNode가 삽입될 때 newNode의 '왼쪽' 노드(q)와 '오른쪽' 노드(p)를 올바르게 연결해주는 핵심적인 포인터
	//기존에 노드가 있을 경우에는 순서가 유지되도록 삽입할 노드 검색
	//여기서 항상 헤드 부분에 추가, 중간 부분에 추가, 꼬리 부분에 추가 3가지 기억하고 있으면 된다.

	while(p!=0){ //head부터 node끝까지 탐색하겠다
		if(p->data < element){  //이때는 스킵!!! 아직 삽입할 위치가 아니다.
			//현재 오름차순임. 지금 node보다 클 경우 오름차순이 되려면 새 노드는 이 노드(p)보다 더 뒤에 와야 하기 때문에 아직 삽입할 위치가 아닙니다.
			q = p; //[q가 현재 p의 위치를 기억합니다.](중요)[삽입할때는 총 2가지 연결 작업이 필요하기 때문]좀 있다가 p->data > element이 되는 순간이 element를 삽입해야 하는 순간인데 이때 1.newNode의 다음(link)을 p에 연결합니다. (newNode->link = p;) 2.q의 다음(link)을 newNode에 연결합니다. (q->link = newNode;) 이렇게 연결을 해줘야 한다.
			p = p->link; //바로 다음 노드로 이동
		}
		else { //바로 여기가 삽입할 위치 //p->data > element이 되는 순간(역전되는 순간)이 바로 q->data와 p->data 사이에 새로운 node를 넣을 위치
			
			//q->data와 p->data 사이에 넣는 것이므로 
			//(중요)newNode 기준으로는 이전은 q, 다음포인터(newNode->link)는 p가 됨
			newNode->link = p; //newNode의 다음 포인터는 p!!!

			//여기서 중요 
			//1.q가 존재하면 q->newNode->p가 되고, 
			//2.q가 nullptr이면(head가 없으면) 이 노드는 head가 됨
			//이걸 나누어 줘야 한다.
			if(q != 0)
				q->link = newNode; //newNode의 이전 포인터는 q!!!(q->newNode->p)
			else
				first = newNode; //이전(q)이 없으니까 내가 head
			return; //지정완료 했으니 
		}
	//node중에 element랑 같은 경우는 따질 필요조차 없음(같은데 왜 추가함?)(그냥 자연스럽게 순회 돌고 아무짓도 안함)
	}

	// 4. [버그 수정] 'while' 루프가 끝까지 돌았다면
    //    이 'newNode'가 가장 큰 값이므로 리스트의 "맨 뒤"에 추가합니다.
    q->link = newNode;
}

bool LinkedList::Search(int data) { // 말 그대로 해당 data가 리스트에 있으면 true을 출력한다(없으면 false)
	Node *ptr = first;
	while (ptr != 0) {
		if (ptr->data == data) 
			return true;
		ptr = ptr->link;
	}
	return false;
}

bool LinkedList::Delete(int element) // delete the element
{
	//Node* q, * current = first; q = current; 
	//이거 C++문법인데 이렇게 선언할 경우 Node* q는 쓰레기값, Node* current = first로 초기화 되는거다
	//그니까 char *a,*b = hello; 라고 한다면 *a는 그냥 선언만 되는 것 (cpp 컴파일러가 원래 이래) 
	//이런 오류를 막기 위해서 따로 선언초기화 해라

    // current: 현재 검사 중인 노드
    // q: current의 바로 "이전" 노드를 따라가는 포인터
    Node *current = first;
    Node *q = 0; // 'q'는 NULL(0)로 시작해야 합니다. (이전 노드가 없다는 뜻)

    // 1. 리스트를 순회하며 element를 찾습니다.
    while (current != 0) 
    {
        if (current->data == element) // 2. 삭제할 노드를 찾았습니다!
        {
            if (q == 0) // 혹은 (current == first)
			//둘이 완전히 똑같은 의미!!!!!
            {
                // 2a. [첫 번째 노드를 삭제하는 경우]
                // 'q'가 0이라는 것은 우리가 아직 한 칸도 이동하지 않았다는 의미,
                // 즉 'current'가 'first' 노드임을 의미합니다.
                first = current->link; // 리스트의 시작(first)을 다음 노드로 변경합니다.
            }
            else
            {
                // 2b. [중간 또는 마지막 노드를 삭제하는 경우]
                // 'q' (이전 노드)의 링크가 'current'의 다음 노드를 가리키도록 하여
                // 'current' 노드를 건너뛰게(bypass) 만듭니다.
                q->link = current->link; 
            }
			delete current; // 'current' 노드의 메모리를 해제합니다.
            return true;    // 삭제 성공을 알립니다.
        }
        else // 3. 아직 못 찾았습니다. 다음 노드로 이동합니다.
        {
            // 포인터들을 한 칸씩 전진시킵니다.
            q = current;             // q가 current의 현재 위치를 기억하고,
            current = current->link; // current가 다음 노드로 이동합니다.
        }
    }

    // 4. 'while' 루프가 끝날 때까지 노드를 찾지 못했습니다.
    // 리스트에 해당 'element'가 없는 것입니다.
    return false; // 삭제 실패를 알립니다.
}



//원래 코드의 오류와 그에 대한 설명
/*
/////LinkedList&와 댕글링 참조 (기초)/////
댕글링 참조(Dangling Reference)란?
**참조(&)**는 "별명"입니다. int& b = a;는 "b는 a의 또 다른 이름이다"라는 뜻입니다. 원본(a)과 완벽하게 동일한 메모리 공간을 가리킵니다.
**댕글링(Dangling)**은 "매달려있다"는 뜻으로, 원본이 사라졌는데도 "별명"만 공중에 붕 떠있는 상태를 말합니다.
즉, **"이미 사라진(소멸된) 메모리를 가리키는 별명"**입니다.

//즉, 이미 함수가 호출 종료(소멸자 호출되서 사라짐)인데도 반환값은 포인터라서 사라진(소멸된) 메모리를 가리키는 경우를 이야기
// 1. 반환 타입이 '참조(&)'입니다.

예시)
LinkedList& LinkedList::operator+(LinkedList& lb) {
    
    // 2. 'lc'는 이 함수 안에서만 존재하는 '지역 변수'입니다.
    LinkedList lc;

    // ... (중략) ...
    // 3. lc에 2 -> 5 -> 12 -> ... 노드들이 잘 추가됩니다.

    // 4. 💥💥💥 버그 발생 💥💥💥
    //    이 함수가 끝나면 '사라질' 지역 변수 'lc'의 '참조(별명)'를 반환합니다.
    return lc; 
} 
// 5. 함수가 여기서 끝나면서 'lc'가 소멸(destroy)됩니다.
// 6. 'lc'의 소멸자(~LinkedList())가 호출되어 2, 5, 12 ... 모든 노드를 'delete' 합니다.

예시 설명)
main 함수는 la + lb가 반환한 "별명"을 받습니다. 하지만 그 "별명"의 **원본(lc)**은 이미 6번에서 소멸되었고, 노드들도 모두 delete 되었습니다.
main의 lc = ... 코드는 이미 삭제된 쓰레기 메모리를 가리키는 "별명"을 받게 됩니다.
그다음 lc.Show()를 호출하면, 이미 delete된 메모리에 접근해서 3이나 4 같은 쓰레기 값을 읽어오거나 프로그램이 다운되는 것입니다.
*/


//해결 방법 1: 힙(Heap) 이용 (메모리 누수 감수) (매우 매우 매우 비추천)
/*
"함수가 끝나도 사라지지 않는 객체"의 참조를 반환하면 댕글링 참조를 피할 수 있습니다. 힙(Heap)에 생성된 객체는 함수가 끝나도 사라지지 않습니다.

해결 방법: new 키워드를 사용합니다.

예시)
LinkedList& LinkedList::operator+(LinkedList& lb) {
    
    // 1. 'lc'를 스택(지역)이 아닌 '힙(Heap)'에 생성합니다.
    //    'lc'는 이제 포인터입니다.
    LinkedList* lc = new LinkedList();

    Node* a = first, * b = lb.first;

    // 2. 'lc'가 포인터이므로 '->' 연산자로 Add를 호출합니다.
    while (a && b) { 
        if (a->data == b->data) {
            lc->Add(a->data); 
            // ... (이하 로직 동일) ...
        }
        else if (a->data < b->data) {
            lc->Add(a->data);
            a = a->link;
        }
        else { 
            lc->Add(b->data);
            b = b->link;
        }
    }
    // ... (while(a), while(b) 로직 동일) ...

    // 3. 힙에 생성된 객체(*lc)의 '참조'를 반환합니다.
    return *lc; 
}
// 4. 함수가 끝나도 'new'로 만든 *lc는 소멸하지 않습니다.

예시 결과)
main 함수는 힙에 살아있는 객체의 참조를 받습니다.
소멸자가 호출되지 않았으므로 노드들도 delete 되지 않습니다.
lc.Show()가 올바르게 전체 리스트를 출력합니다!
하지만... Merge를 호출할 때마다 LinkedList 객체가 힙에 계속 쌓입니다. 
아무도 이 객체들을 delete 해주지 않습니다. 이것이 바로 "메모리 누수(Memory Leak)" 버그입니다.

메모리 누수는 개발자가 가장 경계해야 하는 버그로 주의해야 합니다.
*/














//해결 방법 2: C++의 정석 (올바른 해결책)
/*
가장 올바르고, 안전하며, C++ 표준이 권장하는 방식입니다.

**"값(Value)으로 반환"**하고, **"Rule of Three"**를 준수하는 것입니다.

1단계: 반환 타입을 LinkedList (값)로 변경
&를 제거하여 "별명"이 아닌 "복사본"을 반환하도록 합니다.

예시)
// 1. 반환 타입에서 '&'를 제거
LinkedList LinkedList::operator+(LinkedList& lb) {
    
    LinkedList lc; // 2. 지역 변수 생성

    // ... (중략) ...
    // 3. lc에 2 -> 5 -> 12 -> ... 노드들이 잘 추가됨
    
    // 4. 'lc'를 "값"으로 반환합니다.
    //    C++가 'lc'의 '복사본'을 안전하게 main으로 전달합니다.
    return lc; 
}
// 5. 함수가 끝나면서 'lc'는 소멸하지만, 
//    이미 '복사본'이 넘어갔기 때문에 아무 문제가 없습니다.


2단계: "Rule of Three"로 "깊은 복사" 구현

(소멸자로 LinkedList의 메모리 누수 방지.) <-- 클래스 내부에 멤버 1개라도 new로 선언했으면 소멸자는 필수다.
**operator=**는 **"깊은 복사"**를 구현합니다.
**복사 생성자**는 **"깊은 복사"**를 구현합니다.


1) 소멸자 (Destructor)
역할: 객체가 소멸할 때 new로 생성했던 모든 노드 메모리를 delete 하여 메모리 누수(Memory Leak)를 방지합니다.

LinkedList::~LinkedList() {
    Node* current = first;
    while (current != 0) {
        Node* next = current->link; // 다음 노드를 미리 저장
        delete current;             // 현재 노드 삭제
        current = next;             // 다음 노드로 이동
    }
}



2) 복사 생성자 (Copy Constructor)
역할: LinkedList lb = la; 처럼 새 객체를 생성과 동시에 복사할 때, **"깊은 복사(Deep Copy)"**를 수행합니다.

동작: other 리스트의 모든 노드를 순회하며 this->Add()로 새로운 노드를 만들어 추가합니다.

LinkedList::LinkedList(const LinkedList& other) {
    first = 0; // 1. 'this'의 리스트를 비어있는 상태로 초기화

    // 2. 'other'의 노드를 "새로 생성"하며 복사 (깊은 복사)
    Node* p = other.first;
    while (p != 0) {
        this->Add(p->data); // Add 함수가 'new Node'를 해줌
        p = p->link;
    }
}



3) 복사 대입 연산자 (Copy Assignment Operator)
역할: lc = la; 처럼 이미 존재하는 객체에 다른 객체를 대입할 때, **"깊은 복사(Deep Copy)"**를 수행합니다.

동작:
la = la; 같은 자기 자신 대입인지 확인합니다.
this가 원래 가지고 있던 노드들을 모두 delete 합니다 (기존 리스트 청소).
other 리스트의 모든 노드를 순회하며 this->Add()로 새로운 노드를 만들어 추가합니다.

LinkedList& LinkedList::operator=(const LinkedList& other) {
    // 1. 자기 자신 대입 방지 (예: la = la;)
    if (this == &other) {
        return *this;
    }

    // 2. 'this'가 원래 가지고 있던 노드들을 모두 삭제
    Node* current = first;
    while (current != 0) {
        Node* next = current->link;
        delete current;
        current = next;
    }
    first = 0; // 리스트 비우기

    // 3. 'other'의 노드를 "새로 생성"하며 복사 (깊은 복사)
    Node* p = other.first;
    while (p != 0) {
        this->Add(p->data); // Add 함수가 'new Node'를 해줌
        p = p->link;
    }

    return *this;
}

----------------------------------------"Rule of Three"에 대한 설명----------------------------------------
동적 메모리(dynamic memory)를 직접 관리하는 클래스가 버그를 피하기 위해 지켜야 할 C++의 필수 규칙
클래스에서 new를 사용해 메모리를 할당했다면, 이 규칙이 적용됩니다.


1. 3가지 핵심 함수 (The Three)
이 규칙은 "이 셋 중 하나라도 직접 구현했다면, 나머지 둘도 반드시 직접 구현해야 한다"는 의미입니다.

소멸자 (Destructor): ~LinkedList()

복사 생성자 (Copy Constructor): LinkedList(const LinkedList& other)

복사 대입 연산자 (Copy Assignment Operator): operator=(const LinkedList& other)



2. 왜 이 규칙이 필요한가?
**"얕은 복사(Shallow Copy)"**라는 버그를 막기 위해서입니다.

소멸자를 구현하는 이유: LinkedList가 new로 노드(Node)들을 만들었기 때문에, 
메모리 누수(Memory Leak)를 막으려면 소멸자(~LinkedList)에서 delete로 노드들을 직접 해제해야 합니다.

버그 발생 시점: 소멸자만 구현하고, 나머지 두 개(복사 생성자, operator=)를 구현하지 않으면, 
C++ 컴파일러가 이 둘을 자동으로 만들어 줍니다.

문제는, 이 '자동' 버전들은 **"얕은 복사(Shallow Copy)"**를 수행한다는 것입니다.

얕은 복사란? la 리스트를 lb로 복사할 때(LinkedList lb = la;), 
lb가 la의 노드를 새로 복제하는 것이 아니라, la.first 포인터의 주소값만 그대로 복사해옵니다.
결과적으론 la와 lb가 똑같은 메모리(노드)를 공유하게 됩니다.



이로 인해 2가지 재앙적인 버그가 발생합니다:

버그 1) 이중 해제 (Double Free):

lb가 소멸할 때, lb의 소멸자(~LinkedList())가 노드들을 delete 합니다.
그 후, la가 소멸할 때, la의 소멸자가 이미 delete 된 메모리를 또 delete 하려고 시도합니다.

결과: 프로그램이 다운됩니다.

버그 2) 댕글링 포인터 (Dangling Pointer):
(처음 원본의 lc = la + lb;에서 겪은 문제입니다.)
operator+의 임시 객체(temp)가 소멸하면서 노드들을 delete 합니다.
lc는 얕은 복사로 temp와 같은 주소를 가리켰기 때문에, 이미 삭제된 쓰레기 메모리를 가리키게 됩니다.

결과: lc = 3처럼 쓰레기 값이 출력됩니다.



3. "Rule of Three"의 해결책
이 "얕은 복사" 버그를 막기 위해 "Rule of Three"가 필요합니다.
논리: "소멸자를 직접 구현했다는 것" = "동적 메모리를 쓴다는 뜻"
규칙: "그러므로 '얕은 복사'를 하는 '기본 복사 생성자'와 '기본 operator='는 버그를 유발할 것이다."

결론: "따라서 이 두 함수도 **'깊은 복사(Deep Copy)'**를 하도록 반드시 직접 구현해야 한다."

**깊은 복사(Deep Copy)**란, other의 노드들을 new를 통해 새로운 노드로 만들어서 복제하는, 
내가 operator=와 복사 생성자에 구현한 바로 그 코드를 의미합니다.
*/




//방법 2) 값으로 반환하고 깊은 복사 구현하기
LinkedList LinkedList::operator+(LinkedList& lb) {
    // LinkedList 객체를 반환하는 '+' 연산자 오버로딩 함수입니다.
	// A + B 연산을 수행하면, A와 B의 합집합(Union)에 해당하는 새로운 LinkedList를 반환합니다.
	// (이 코드는 두 리스트가 '정렬'되어 있다고 가정하고 동작합니다.)
    // 1. 결과를 담을 새로운(비어있는) 연결 리스트 'lc'를 생성합니다.
	LinkedList lc;

	//새로운 연결리스트에 서로 a>b a<b a=b를 따지면서 집어 넣는다고 생각하면 된다.
	//그리고 Add 이후에는 add한것은 다음 노드로 이동시키기
    
    // 2. 'a'는 현재 리스트(this)의 첫 번째 노드를 가리킵니다.
    //    'b'는 더해질 리스트(lb)의 첫 번째 노드를 가리킵니다.
    Node* a = first, * b = lb.first;

    // 3. 'a'와 'b' 둘 다 NULL(리스트의 끝)이 아닐 동안 루프를 실행합니다.
    //    즉, 두 리스트 중 하나라도 끝에 도달하면 이 루프는 종료됩니다.
    while (a && b) { 
        
        // 3a. 두 노드의 데이터가 같은 경우 (교집합)
        if (a->data == b->data) {
            lc.Add(a->data); // lc에 데이터를 한 번만 추가합니다.
            a = a->link;     // a를 다음 노드로 이동합니다.
            b = b->link;     // b를 다음 노드로 이동합니다.
        }
        // 3b. a의 데이터가 b보다 작은 경우
        else if (a->data < b->data) {
            lc.Add(a->data); // lc에 a의 데이터를 추가합니다.
            a = a->link;     // a만 다음 노드로 이동합니다. (b는 그대로)
        }
        // 3c. b의 데이터가 a보다 작은 경우 (a->data > b->data)
        else { 
            lc.Add(b->data); // lc에 b의 데이터를 추가합니다.
            b = b->link;     // b만 다음 노드로 이동합니다. (a는 그대로)
        }
    }

    // 4. [나머지 처리 1]
    //    위 'while' 루프가 끝났을 때, 'a' 리스트의 노드가 아직 남아있는 경우
    while (a != 0) {
        lc.Add(a->data); // 'a' 리스트의 남은 노드들을 'lc'에 모두 추가합니다.
        a = a->link;
    }
    
    // 5. [나머지 처리 2]
    //    위 'while' 루프가 끝났을 때, 'b' 리스트의 노드가 아직 남아있는 경우
    while (b != 0) {
        lc.Add(b->data); // 'b' 리스트의 남은 노드들을 'lc'에 모두 추가합니다.
        b = b->link;
    }

    return lc; 
}

//소멸자
//객체가 소멸할 때 new로 생성했던 모든 노드 메모리를 delete 하여 메모리 누수(Memory Leak)를 방지
LinkedList::~LinkedList() {
    Node* current = first;
    while (current != 0) {
        Node* next = current->link; // 다음 노드를 미리 저장
        delete current;             // 현재 노드 삭제
        current = next;             // 다음 노드로 이동
    }
}

//복사생성자
//LinkedList lb = la; 처럼 새 객체를 생성과 동시에 복사할 때, **"깊은 복사(Deep Copy)"**를 수행
LinkedList::LinkedList(const LinkedList& other) {
    first = 0; // 1. 'this'의 리스트를 비어있는 상태로 초기화

    // 2. 'other'의 노드를 "새로 생성"하며 복사 (깊은 복사)
    Node* p = other.first;
    while (p != 0) {
        this->Add(p->data); // Add 함수가 'new Node'를 해줌
        p = p->link;
    }
}


//operator=
//lc = la; 처럼 이미 존재하는 객체에 다른 객체를 대입할 때, **"깊은 복사(Deep Copy)"**를 수행.
LinkedList& LinkedList::operator=(const LinkedList& other) {
    // 1. 자기 자신 대입 방지 (예: la = la;)
    if (this == &other) {
        return *this;
    }

    // 2. 'this'가 원래 가지고 있던 노드들을 모두 삭제
    Node* current = first;
    while (current != 0) {
        Node* next = current->link;
        delete current;
        current = next;
    }
    first = 0; // 리스트 비우기

    // 3. 'other'의 노드를 "새로 생성"하며 복사 (깊은 복사)
    Node* p = other.first;
    while (p != 0) {
        this->Add(p->data); // Add 함수가 'new Node'를 해줌
        p = p->link;
    }

    return *this;
}



//C++에서 enum은 0부터 시작 (이거 기억하기)
enum Enum {
	Add1, Add2, Delete, Show, Search, Merge, Exit
};
int main() {
	Enum menu; // 메뉴
	int selectMenu;
	int num = 0; bool result = false;
	srand(time(NULL));
	LinkedList la, lb, lc;
	int data = 0;
	do {
		cout << "0.ADD1, 1. Add2, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit 선택::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add1:
			data = rand() % 49;
			la.Add(data);
			break;
		case Add2:
			data = rand() % 49;
			lb.Add(data);
			break;
		case Delete:
			cin >> data;
			result = la.Delete(data);
			if (result)
				cout << "삭제 완료";
			break;
		case Show:
			cout << "리스트 la = ";
			la.Show();
			cout << "리스트 lb = ";
			lb.Show();
			break;
		case Search: // 회원 번호 검색
			int n; cin >> n;
			result = la.Search(n);
			if (!result)
				cout << "검색 값 = " << n << " 데이터가 없습니다.";
			else
				cout << "검색 값 = " << n << " 데이터가 존재합니다.";
			break;
		case Merge:
			lc = la + lb;
			cout << "리스트 lc = ";
			lc.Show();
			break;
		case Exit:
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}

