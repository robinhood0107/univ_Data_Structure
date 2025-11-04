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

class LinkedList {
    Node* first;
public:
    LinkedList() {
        first = 0;
    }
    // 소멸자 추가 (메모리 누수 방지)
    ~LinkedList() {
        Node* current = first;
        while (current != 0) {
            Node* next = current->link;
            delete current;
            current = next;
        }
    }
    bool Delete(int);
    void Show();
    void Add(int element);
    bool Search(int data);
    LinkedList operator+(LinkedList&);
};

void LinkedList::Show() {
    Node* p = first;
    while (p != 0) {
        cout << p->data;
        if (p->link != 0) {
            cout << " -> ";
        }
        p = p->link;
    }
    cout << endl;
}

void LinkedList::Add(int element)
{
    Node* newNode = new Node(element);
    if (first == 0) {
        first = newNode;
        return;
    }

    Node* p = first, * q = 0;

    while (p != 0) {
        if (p->data < element) {
            q = p;
            p = p->link;
        }
        else {
            newNode->link = p;
            if (q != 0)
                q->link = newNode;
            else
                first = newNode;
            return;
        }
    }
    q->link = newNode;
}

// [효율성 개선]
// 리스트가 정렬되어 있으므로, 찾는 값보다 큰 데이터를 만나면 즉시 중단합니다.
bool LinkedList::Search(int data) {
    Node* ptr = first;
    // ptr->data <= data 조건이 추가되어 불필요한 탐색을 방지합니다.
    while (ptr != 0 && ptr->data <= data) {
        if (ptr->data == data)
            return true;
        ptr = ptr->link;
    }
    return false;
}

// [효율성 개선]
// Search와 마찬가지로, 정렬 속성을 활용하여 조기 중단합니다.
bool LinkedList::Delete(int element)
{
    Node* current = first;
    Node* q = 0;

    // element보다 값이 커지거나 리스트 끝에 도달하면 중단합니다.
    while (current != 0 && current->data < element)
    {
        q = current;
        current = current->link;
    }

    // 루프가 멈춘 후, 정확히 일치하는지 확인합니다.
    if (current != 0 && current->data == element)
    {
        if (q == 0)
        {
            first = current->link;
        }
        else
        {
            q->link = current->link;
        }
        delete current;
        return true;
    }

    // 여기까지 왔다면 값이 없거나(current == 0) 더 큰 값을 만난 것입니다.
    return false;
}

// [효율성 대폭 개선]
// O(N^2)의 비효율적인 lc.Add() 대신,
// 새 리스트의 '꼬리(tail)' 포인터를 추적하여 O(1)에 노드를 추가합니다.
// 전체 시간 복잡도가 O(M+N)으로 향상됩니다.
LinkedList LinkedList::operator+(LinkedList& lb) {
    LinkedList lc;
    Node* a = this->first;
    Node* b = lb.first;
    Node* lc_tail = 0; // lc의 마지막 노드를 추적하는 꼬리 포인터

    // O(1) 시간 복잡도로 lc 리스트의 꼬리에 노드를 추가하는 람다 함수
    auto add_to_tail = [&](int val) {
        Node* newNode = new Node(val);
        if (lc.first == 0) {
            lc.first = newNode;
            lc_tail = newNode;
        }
        else {
            lc_tail->link = newNode;
            lc_tail = newNode;
        }
    };

    // 메인 병합 루프
    while (a != 0 && b != 0) {
        if (a->data == b->data) {
            add_to_tail(a->data);
            a = a->link;
            b = b->link;
        }
        else if (a->data < b->data) {
            add_to_tail(a->data);
            a = a->link;
        }
        else { // a->data > b->data
            add_to_tail(b->data);
            b = b->link;
        }
    }

    // 남은 노드들 처리
    while (a != 0) {
        add_to_tail(a->data);
        a = a->link;
    }
    while (b != 0) {
        add_to_tail(b->data);
        b = b->link;
    }

    return lc;
}

// 기존 while 루프 구조를 유지한 채 lc.Add() 호출 부분만 O(1) 삽입 로직으로 수정한 코드
// LinkedList LinkedList::operator+(LinkedList& lb) {
//     // 1. 결과를 담을 리스트와 포인터들을 준비합니다.
//     LinkedList lc;
//     Node* a = first;
//     Node* b = lb.first;

//     // 2. [핵심] lc 리스트의 '마지막 노드'를 가리킬 포인터를 만듭니다.
//     Node* lc_tail = 0; 

//     // 3. 'a'와 'b' 둘 다 리스트의 끝이 아닐 동안 루프를 실행합니다.
//     while (a && b) { 

//         int data_to_add; // lc에 추가할 데이터를 임시 저장할 변수

//         // 3a. (구조 유지) 비교 로직은 동일합니다.
//         if (a->data == b->data) {
//             data_to_add = a->data; 
//             a = a->link;   
//             b = b->link;   
//         }
//         // 3b. (구조 유지)
//         else if (a->data < b->data) {
//             data_to_add = a->data;
//             a = a->link;   
//         }
//         // 3c. (구조 유지)
//         else { 
//             data_to_add = b->data;
//             b = b->link;   
//         }

//         // 4. [효율성 개선]
//         //    'lc.Add(data)' 대신 O(1) 꼬리 삽입을 수행합니다.
//         Node* newNode = new Node(data_to_add);
//         if (lc.first == 0) { // lc가 비어있다면,
//             lc.first = newNode; // first와
//             lc_tail = newNode;  // tail이 모두 새 노드를 가리킵니다.
//         } else { // lc가 비어있지 않다면,
//             lc_tail->link = newNode; // 기존 꼬리의 link가 새 노드를 가리키고,
//             lc_tail = newNode;       // 꼬리 포인터를 새 노드로 업데이트합니다.
//         }
//     }

//     // 5. [나머지 처리 1] (꼬리 삽입 로직 동일하게 적용)
//     while (a != 0) {
//         Node* newNode = new Node(a->data);
//         if (lc.first == 0) {
//             lc.first = newNode;
//             lc_tail = newNode;
//         } else {
//             lc_tail->link = newNode;
//             lc_tail = newNode;
//         }
//         a = a->link;
//     }
    
//     // 6. [나머지 처리 2] (꼬리 삽입 로직 동일하게 적용)
//     while (b != 0) {
//         Node* newNode = new Node(b->data);
//         if (lc.first == 0) {
//             lc.first = newNode;
//             lc_tail = newNode;
//         } else {
//             lc_tail->link = newNode;
//             lc_tail = newNode;
//         }
//         b = b->link;
//     }

//     return lc; 
// }


// 기존 코드의 비효율의 원인
// 현재 코드의 가장 큰 비효율은 lc.Add(data) 함수를 호출하는 데 있습니다.
// lc.Add()는 정렬 삽입 함수입니다. 즉, lc에 데이터가 10개 있으면, 
//11번째 데이터를 넣을 위치를 찾기 위해 lc의 **처음부터 다시 탐색(O(N))**합니다.
// 병합(merge)은 이미 정렬된 순서대로 데이터를 뽑아내는데, 
//Add 함수가 이 순서를 무시하고 매번 처음부터 탐색하기 때문에 전체 시간 복잡도가 O((M+N)^2)이 되어 매우 느려집니다.

//기존 코드 O((M+N)^2)
// LinkedList LinkedList::operator+(LinkedList& lb) {
//     // LinkedList 객체를 반환하는 '+' 연산자 오버로딩 함수입니다.
// 	// A + B 연산을 수행하면, A와 B의 합집합(Union)에 해당하는 새로운 LinkedList를 반환합니다.
// 	// (이 코드는 두 리스트가 '정렬'되어 있다고 가정하고 동작합니다.)
//     // 1. 결과를 담을 새로운(비어있는) 연결 리스트 'lc'를 생성합니다.
// 	LinkedList lc;

// 	//새로운 연결리스트에 서로 a>b a<b a=b를 따지면서 집어 넣는다고 생각하면 된다.
// 	//그리고 Add 이후에는 add한것은 다음 노드로 이동시키기

//     // 2. 'a'는 현재 리스트(this)의 첫 번째 노드를 가리킵니다.
//     //    'b'는 더해질 리스트(lb)의 첫 번째 노드를 가리킵니다.
//     Node* a = first, * b = lb.first;

//     // 3. 'a'와 'b' 둘 다 NULL(리스트의 끝)이 아닐 동안 루프를 실행합니다.
//     //    즉, 두 리스트 중 하나라도 끝에 도달하면 이 루프는 종료됩니다.
//     while (a && b) { 

//         // 3a. 두 노드의 데이터가 같은 경우 (교집합)
//         if (a->data == b->data) {
//             lc.Add(a->data); // lc에 데이터를 한 번만 추가합니다.
//             a = a->link;     // a를 다음 노드로 이동합니다.
//             b = b->link;     // b를 다음 노드로 이동합니다.
//         }
//         // 3b. a의 데이터가 b보다 작은 경우
//         else if (a->data < b->data) {
//             lc.Add(a->data); // lc에 a의 데이터를 추가합니다.
//             a = a->link;     // a만 다음 노드로 이동합니다. (b는 그대로)
//         }
//         // 3c. b의 데이터가 a보다 작은 경우 (a->data > b->data)
//         else { 
//             lc.Add(b->data); // lc에 b의 데이터를 추가합니다.
//             b = b->link;     // b만 다음 노드로 이동합니다. (a는 그대로)
//         }
//     }

//     // 4. [나머지 처리 1]
//     //    위 'while' 루프가 끝났을 때, 'a' 리스트의 노드가 아직 남아있는 경우
//     while (a != 0) {
//         lc.Add(a->data); // 'a' 리스트의 남은 노드들을 'lc'에 모두 추가합니다.
//         a = a->link;
//     }

//     // 5. [나머지 처리 2]
//     //    위 'while' 루프가 끝났을 때, 'b' 리스트의 노드가 아직 남아있는 경우
//     while (b != 0) {
//         lc.Add(b->data); // 'b' 리스트의 남은 노드들을 'lc'에 모두 추가합니다.
//         b = b->link;
//     }

//     return lc; 
// }


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