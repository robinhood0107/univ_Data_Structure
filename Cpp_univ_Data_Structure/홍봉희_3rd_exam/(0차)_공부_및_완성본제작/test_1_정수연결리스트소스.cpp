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

