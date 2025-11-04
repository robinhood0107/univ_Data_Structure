#include <iostream>
#include <string>
#include <vector>
using namespace std;


//이중 연결 리스트는 '다음'(rlink)과 **'이전'(llink)**을 모두 알아야 함
//이중 연결 리스트의 핵심 장점은 p = p->llink;로 '이전 노드'로 돌아갈 수 있다는 것인데, 요세푸스 문제는 이 기능이 전혀 필요하지 않습니다.

class Node {
    friend class ListIterator;
    friend class CircularList;
    int data;
    Node* llink; // '이전' 노드를 가리키는 포인터
    Node* rlink; // '다음' 노드를 가리키는 포인터
public:
    Node() { }
    Node(int element) {
        data = element;
        llink = nullptr;
        rlink = nullptr;
    }
};

class CircularList {
public:
    CircularList() {
        last = new Node(); 
        last->llink = last; // 헤더의 '이전'은 헤더 자신
        last->rlink = last; // 헤더의 '다음'도 헤더 자신
    }
    void Add(int element);
    bool Delete(int element);
    void Show();
    bool Search(int element);
    CircularList operator+(const CircularList& lb); //merge 함수다

    int SolveJosephus(vector<int> &testData, int K);


    Node* GetNode(); 
    void RetNode(Node*);
    void Erase(); 
private:
    friend class ListIterator;
    Node* last;
    static Node* av; 
};

Node* CircularList::GetNode(){ 
    Node* x;
    if (av) { 
        x = av;
        av = av->rlink;// 'link' 대신 'rlink'를 av 리스트용으로 사용
    }
    else x = new Node;
    return x;
}

void CircularList::RetNode(Node* x){ 
    x->rlink = av; // 'link' 대신 'rlink'를 av 리스트용으로 사용
    av = x;
    // x->llink는 av 리스트에서 사용하지 않으므로 무시
}

void CircularList::Show(){ 
    Node* header = last; 
    Node* current = header->rlink; 


    if (current == header) {
        cout << "[ 리스트가 비어있습니다. ]" << endl;
        return;
    }


    cout << "[";
    while(current != header){
        cout << current->data; 
        current = current->rlink;
        if (current != header) { 
            cout << " -> ";
        }
    }
    cout << "]" << endl;
}

// Add(int element) (오름차순 삽입)
// 단일 리스트: q -> newNode -> p를 위해 2개의 포인터를 수정했습니다.

// 이중 리스트: q <-> newNode <-> p를 위해 4개의 포인터를 수정해야 합니다.

void CircularList::Add(int element){
	Node* newNode = GetNode();
    newNode->data = element; 

    Node* header = last;
    Node* q = header;       // q = prevNode
    Node* p = header->rlink; // p = currNode (rlink 사용)


    // 1. 위치 탐색 (rlink 사용)
    while (p != header && p->data < element) {
        q = p;
        p = p->rlink; 
    }

    // 2. [ 4-way 링킹 ]
    //    q <-> p 사이를 끊고 q <-> newNode <-> p 로 연결
    // (1) 새 노드가 앞/뒤 노드를 가리킴
    newNode->rlink = p;
    newNode->llink = q;
    
    // (2) 앞/뒤 노드가 새 노드를 가리킴 // ❌ 이게 단일 리스트에는 없던 부분
    q->rlink = newNode;
    p->llink = newNode;
}

// Delete(int element)
// 단일 리스트: q -> p -> (p->link)에서 q->link = p->link;로 1개만 수정했습니다.

// 이중 리스트: q <-> p <-> (p->rlink)에서 q <-> (p->rlink)로 2개를 수정해야 합니다. (이중 리스트는 p만 알아도 p->llink로 q를 알 수 있어서 더 편합니다.)

bool CircularList::Delete(int element){// 'element'를 가진 노드 'p'를 삭제

    Node* header = last;
    Node* q = header;
    Node* p = header->rlink; // p = targetNode


    // 1. 삭제할 노드 'p' 탐색 (rlink 사용)
    while (p != header) {
        if (p->data == element) {
            
            // 2. [ 2-way 바이패스 ]
            //    (p->llink) <-> p <-> (p->rlink)  연결을 끊음
            //    (p->llink) <--------> (p->rlink)  로 바로 연결
            
            // (1) p의 '이전' 노드가 p의 '다음' 노드를 가리킴
            (p->llink)->rlink = p->rlink;
            
            // (2) p의 '다음' 노드가 p의 '이전' 노드를 가리킴
            (p->rlink)->llink = p->llink; // ❌ 단일 리스트에는 없던 부분

            RetNode(p); // p 반납
            return true;
        }
        p = p->rlink;
    }
    return false;
}

//Show(), Search(), Erase(), operator+(), SolveJosephus() 등 리스트를 순회(traverse)하는 모든 함수에서
//아래의 나머지 함수들도 전부 p = p->link;는 p = p->rlink;으로 바뀌어야 함

bool CircularList::Search(int element) {
    Node* header = last;
    Node* current = header->rlink;

    while (current != header && current->data <= element) {
        if (current->data == element) {
            return true;
        }
        current = current->rlink;
    }
    return false;
}

void CircularList::Erase() {
    Node* header = last;
    Node* firstData = header->rlink;
    if (firstData == header) {
        return;
    }
    Node* current = firstData;
    while (current->rlink != header) {
        current = current->rlink; 
    }
    current->rlink = av;

    av = firstData;

    header->rlink = header;
    header->llink = header;
    //Erase()처럼 헤더 노드를 리셋하는 함수는 header->rlink = header;와 header->llink = header; 두 개를 모두 리셋해야 합니다.
}


CircularList CircularList::operator+(const CircularList& lb) {
    CircularList lc;
    
    Node* headerA = this->last;
    Node* headerB = lb.last;    
    Node* headerC = lc.last;    

    Node* pA = headerA->rlink; 
    Node* pB = headerB->rlink;

    // 'q'는 lc 리스트의 '꼬리(tail)' 노드를 추적합니다.
    Node* q = headerC;

    // 1. A와 B에 모두 노드가 남아있는 동안
    while (pA != headerA && pB != headerB) {
        Node* newNode = GetNode(); 

        if (pA->data < pB->data) {
            newNode->data = pA->data;
            pA = pA->rlink;
        }
        else if (pA->data > pB->data) {
            newNode->data = pB->data;
            pB = pB->rlink;
        }
        else {
            newNode->data = pA->data; 
            pA = pA->rlink;
            pB = pB->rlink;
        }

        // [ 4-way 링킹 ]
        // q <-> newNode <-> headerC 로 연결
        newNode->rlink = headerC; // (1) 새 노드의 '다음'은 헤더
        newNode->llink = q;       // (2) (수정!) 새 노드의 '이전'은 꼬리(q)
        q->rlink = newNode;     // (3) 꼬리(q)의 '다음'은 새 노드
        headerC->llink = newNode; // (4) (수정!) 헤더의 '이전'은 새 노드
        
        q = newNode;            // 꼬리(q)를 새 노드로 업데이트
    }

    // 2. [ (수정!) 남은 노드 처리 (A) ]
    // A 리스트에 노드가 남아있다면, 모두 lc의 꼬리에 붙입니다.
    while (pA != headerA) {
        Node* newNode = GetNode();
        newNode->data = pA->data;
        pA = pA->rlink;

        newNode->rlink = headerC;
        newNode->llink = q;
        q->rlink = newNode;
        headerC->llink = newNode;
        q = newNode;
    }
    
    // 3. [ (수정!) 남은 노드 처리 (B) ]
    // B 리스트에 노드가 남아있다면, 모두 lc의 꼬리에 붙입니다.
    while (pB != headerB) {
        Node* newNode = GetNode();
        newNode->data = pB->data;
        pB = pB->rlink;

        newNode->rlink = headerC;
        newNode->llink = q;
        q->rlink = newNode;
        headerC->llink = newNode;
        q = newNode;
    }

    // (참고) A, B가 동시에 끝나므로 2, 3번 중 하나만 실행됩니다.
    
    return lc;
}

//요세푸스 문제(Josephus Problem)란?
//이 문제는 N명의 사람이 원형으로 둘러앉아 있을 때, 
//특정 규칙에 따라 사람들을 제거해 나갈 때 최후에 살아남는 사람이 몇 번째 사람인지 맞추는 문제입니다.

// 기본 규칙:
// 1. N명의 사람(예: 1~N번)이 원형으로 앉습니다.
// 2. K라는 숫자가 주어집니다.
// 3. 1번 사람부터 시작해서, 시계 방향으로 K번째 사람을 제거합니다.
// 4. 제거된 사람의 다음 사람부터 다시 K번째 사람을 셉니다. (즉, 원이 한 칸 줄어듭니다.)
// 5. 이 과정을 N-1번 반복하여 1명만 남을 때까지 계속합니다.
// 6. 목표: 마지막에 남는 1명의 원래 번호를 찾는 것입니다.

/*
예시: N=7, K=3
시작: [1, 2, 3, 4, 5, 6, 7]

1차: 1번에서 3번째인 3번 제거. -> [1, 2, 4, 5, 6, 7]
2차: 4번에서 3번째인 6번 제거. -> [1, 2, 4, 5, 7]
3차: 7번에서 3번째인 2번 제거. -> [1, 4, 5, 7]
4차: 4번에서 3번째인 7번 제거. -> [1, 4, 5]
5차: 1번에서 3번째인 5번 제거. -> [1, 4]
6차: 1번에서 3번째인 1번 제거. -> [4]
생존자: 4
*/

//이 문제는 CircularList로 구현하기 완벽합니다. Delete 연산을 반복적으로 수행하면 되니까요.




int CircularList::SolveJosephus(vector<int> &testData, int K) {
    
    this->Erase(); 

    // 1. vector의 데이터로 정렬된 리스트를 만듭니다.
    for (int i = 0; i < testData.size(); i++) {
        this->Add(testData[i]);
    }

    cout << "\n[시작 리스트]: ";
    this->Show();

    Node* header = last;
    Node* p = header; // 'p'는 삭제할 노드의 '이전 노드'

    // 2. vector 크기(N)만큼 N-1번 제거
    for (int i = 0; i < testData.size() - 1; i++) {
        
        // 3. K-1번 이동 (rlink 사용, 헤더 건너뛰기)
        for (int j = 0; j < K - 1; j++) {
            p = p->rlink;
            if (p == header) { 
                p = p->rlink;
            }
        }

        // 4. 'q' (삭제할 노드) 식별 (헤더 건너뛰기)
        Node* q = p->rlink;
        if (q == header) { 
            q = q->rlink;
            p = p->rlink;
        }

        //
        // 5. [ (핵심 수정) 이중 연결 삭제 ]
        //
        //    (p) <-> (q) <-> (q->rlink)  연결을
        //    (p) <-----------> (q->rlink)  로 변경
        
        // (1) 'p'의 '다음(rlink)'이 'q'의 다음 노드를 가리키게 함
        p->rlink = q->rlink; 
        
        // (2) (!!!) 'q'의 다음 노드의 '이전(llink)'이 'p'를 가리키게 함
        (q->rlink)->llink = p; 
        RetNode(q); // 'av' 리스트로 반납
    }

    // 6. 마지막 남은 노드
    Node* survivor = header->rlink;
    cout << "[최종 생존자]: " << survivor->data << endl;
    
    return survivor->data;
}


enum Menu {JOSEPHUS,QUIT}; 


Node* CircularList::av = nullptr;
//static이므로 이거 무조건 해줘야 한다!!!! 반드시 기억

int main() {
    CircularList myList;
    int choice;
    vector<int> testData = {20, 10, 50, 40, 5, 30, 25, 15, 35, 45};

    while (true) {
        cout << "\n==========[ 원형 리스트 (int) ]==========" << endl;
        cout << "0. 요세푸스 문제 풀기" << endl;
        cout << "1. 종료" << endl;
        cout << "==========================================" << endl;
        cout << "선택: ";
        
        // cin 버퍼 비우기 (숫자 아닌 값 입력 대비)
        while (!(cin >> choice)) {
            cout << "숫자를 입력하세요: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (static_cast<Menu>(choice)) {
            
            case JOSEPHUS: { // 2. 요세푸스 문제
                int n, k;
                cout << "  총 인원 (N): ";
                cin >> n;
                cout << "  제거 간격 (K): ";
                cin >> k;
                if (n > 0 && k > 0) {
                    myList.SolveJosephus(testData, k); // 클래스 멤버 함수 호출
                } else {
                    cout << "  N과 K는 0보다 커야 합니다." << endl;
                }
                break;
            }

            case QUIT: // 3. 종료
                cout << "프로그램을 종료합니다." << endl;
                return 0;

            default:
                cout << "잘못된 선택입니다. 1~3 사이의 숫자를 입력하세요." << endl;
                break;
        } // end of switch
    } // end of while
    
    return 0;
}

