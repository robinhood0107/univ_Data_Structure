//원형 연결리스트는 기본적으로 tail 노드의 *link가 head 노드를 가리킨다고 알고 있으면 됨.

//기본 필요한 요소들

//add()
//delete()
//Show()
//Search()
//merge()

//getNode() new는 필요에 의해서 해라(아마 사용하란 뜻이겠지? 메모리 제한 걸어둘 꺼니까)

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <sstream>
using namespace std;



class Node {
    friend class CircularList;
    int data;
    Node* link;
public:
    Node() { }
    Node(int element) {
        data = element;
        link = nullptr;
    }
};

class CircularList {
public:
    CircularList() {
        //처음에 더미 head()노드 초기값을 만들어줌.
        //이 더미 head에는 실제 데이터를 담지 않고 리스트의 시작과 끝을 표시만 함(아예 데이터를 담지 않는다는게 포인트)
        last = new Node(); 
        last->link = last;
    }
    //연결리스트 핵심 4가지 함수들
    void Add(int element);
    bool Delete(int element);
    void Show();
    bool Search(int element);
    CircularList operator+(const CircularList& lb); //merge 함수다

    int SolveJosephus(vector<int> &testData, int K);


    Node* GetNode(); //리스트에서 새 노드를 추가할 때(Add()) new Node()를 매번 하는게 아니라 av리스트에서 재사용할 노드가 있는지 먼저 탐색해보는 코드
    //만약 av리스트에 노드가 있다면 -> 거기서 하나를 가져와서 사용
    //av리스트가 비어있다면 -> new Node()로 새로 만들어줌
    void RetNode(Node*);//리스트에서 노드 삭제시 delete()를 이용하는 것이 아니라 av에 반납(av리스트에 연결시킴) 함 //delete Node[]이걸 사용하는게 아니라 av반납에 사용
    void Erase(); 
private:
    friend class ListIterator;
    Node* last;// (수정) 리스트의 '헤더 노드(Dummy Node)'를 가리킴
                //last->link가 첫 번째 '데이터' 노드가 됩니다.
                //리스트가 비어있으면 last->link == last 입니다.
    static Node* av; //현재 사용하지 않고 '놀고 있는(비어있는)' 노드들을 따로 모아둔 리스트의 시작점
    //static이므로 av리스트는 CircularList 인스턴스들이 전부 1개로 공유
};

//밑에서 무조건 static 초기화 해줘야 한다.


//원형리스트 구현
Node* CircularList::GetNode(){ //provide a node for use
    Node* x;
    if (av) { x = av, av = av->link; }
    else x = new Node;
    return x;
    //av에 노드가 있으면 av의 리스트를 할당해줌
    //없다면 new Node;로 새로운 노드 1개 만들어줌
}

void CircularList::RetNode(Node* x){ //free the node pointed to by x
    x->link = av;
    av = x;
    //x = 0; //필요 없는 코드 
}

void CircularList::Show(){ //Show 함수 //Show 필요하면 show는 간단히 cout << *this로 빠르게 끝내기

    //여기서 header는 last인거 꼭 기억하고 있기
    
    Node* header = last; //last는 헤더노드를 가리키므로 header라는 변수로 명확하게 함
    
    Node* current = header->link; //'current' 포인터가 첫 번째 '데이터' 노드를 가리키게 합니다. 
    //(헤더 노드의 다음 노드)

    //리스트가 비어있는지 확인합니다.
    //첫 데이터 노드(current)가 헤더 자신이라면, 리스트가 빈 것입니다.
    if (current == header) {
        cout << "[ 리스트가 비어있습니다. ]" << endl;
        return;
    }

    //리스트 순회: 'current'가 다시 'header'로 돌아올 때까지 반복합니다.
    cout << "[";
    while(current != header){
        cout << current->data; //현재 노드의 데이터 출력
        current = current->link; //다음 노드로 이동
        if (current != header) { //다음 노드가 헤더가 아니라면(즉, 마지막 노드가 아니라면) 구분자 출력
            cout << " -> ";
        }
    }
    cout << "]" << endl;
}

void CircularList::Add(int element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	Node* newNode = GetNode();
    newNode->data = element; // 가져온 노드에 데이터 저장

    //[헤더 노드] 'first' 대신 'last' (헤더)를 기준으로 포인터를 준비합니다.
    Node* header = last;
    Node* q = header;       // q는 '이전 노드' (헤더에서 시작)
    Node* p = header->link; // p는 '현재 노드' (첫 번째 데이터 노드에서 시작)

    // 3. [삽입 위치 탐색]
    // p가 헤더로 돌아오지 않았고, p의 데이터가 element보다 작은 동안 반복
    // q와 p를 한칸씩 올리면서 삽입할 위치를 탐색함 (궁극적으로 p->data > element를 찾는 것)
    while (p != header && p->data < element) {
        q = p;           // q가 p를 따라잡고
        p = p->link;     // p는 다음 노드로 이동
    }

    // 헤더 노드 덕분에 리스트가 비어있든(Case 1), 
    // 맨 앞에 삽입하든(Case 2), 중간에 삽입하든(Case 3), 
    // 맨 뒤에 삽입하든(Case 4),
    // 아래의 단 두 줄로 모든 삽입 로직이 처리됩니다.
    newNode->link = p; // 새 노드의 다음은 p가 됩니다.
    q->link = newNode;     // q의 다음은 새 노드가 됩니다. (q -> newNode -> p)
}

bool CircularList::Delete(int element){

    // 1. [헤더 노드] 'last' (헤더)를 기준으로 포인터를 준비합니다.
    Node* header = last;
    Node* q = header;       // q는 '이전 노드' (헤더에서 시작)
    Node* p = header->link; // p는 '현재 노드' (첫 번째 데이터 노드에서 시작)

    // 2. [삽입 위치 탐색]
    // p가 헤더로 돌아오지 않는 동안 반복합니다.
    // 전체 전부 탐색
    while (p != header) {
        
        // 3. 삭제할 노드를 찾았는지 확인
        if (p->data == element) {
            // 4. [삭제] 찾았다! p를 건너뛰도록 q의 링크를 수정합니다.
            // q -> p -> (p->link)  ==>  q -> (p->link)
            q->link = p->link; 

            // 5. [Available Space] p를 삭제(delete)하지 않고, av 리스트로 반납합니다.
            RetNode(p);

            return true; // 삭제 성공
        }
        else {
            // 6. [탐색] 아직 못 찾음. 다음 노드로 이동합니다.
            q = p;
            p = p->link;
        }
    }

    // 7. [탐색 실패] while 루프가 끝날 때까지 (p가 헤더로 돌아올 때까지)
    //    노드를 찾지 못했습니다.
    return false;
}

bool CircularList::Search(int element) {
    //오름차순이니까 이게 가능함
    
    // 1. 헤더 노드를 기준으로 시작합니다.
    Node* header = last;
    Node* current = header->link; // 첫 번째 '데이터' 노드

    // 2. 탐색 루프
    //    - current가 헤더로 돌아오지 않았고,
    //    - current의 데이터가 element보다 "작거나 같은" 동안만 계속합니다.
    // 1. 끝에 도달하거나
    // 2. 찾는 값보다 '큰' 값을 만날 때까지
    while (current != header && current->data <= element) {
        // 3. 정확히 일치하는 값을 찾았는지 확인
        if (current->data == element) {
            return true; // 찾았습니다!
        }
        // 4. 일치하지 않으면 다음 노드로 이동
        current = current->link;
    }

    // 5. 루프가 종료된 이유:
    //    a) current == header (리스트를 다 돌았는데 못 찾음)
    //    b) current->data > element (찾는 값보다 큰 값을 만남)
    //    두 경우 모두 리스트에 값이 없는 것입니다.
    return false;
}

void CircularList::Erase() {
    // 1. 헤더 노드와 첫 번째 데이터 노드를 식별합니다.
    Node* header = last;
    Node* firstData = header->link;

    // 2. 리스트가 이미 비어있는지 확인합니다. (헤더가 자신을 가리킴)
    if (firstData == header) {
        return; // 비어있으므로 할 일이 없음
    }

    // 3. 리스트의 '마지막 데이터 노드'를 찾습니다.
    Node* current = firstData;
    while (current->link != header) {
        current = current->link; // 헤더 직전까지 이동
    }
    // 'while'이 끝나면 'current'는 마지막 데이터 노드를 가리킵니다.

    // 4. 리스트의 끝과 'av' 리스트를 연결합니다.
    // [10 -> 20 -> current] -> [header] (기존 리스트)
    // [av_node1 -> av_node2] (av 리스트)
    //
    // [10 -> 20 -> current] -> [av_node1 -> av_node2] (연결!)
    current->link = av; // 마지막 데이터 노드가 'av'의 시작을 가리키게 함

    // 5. 'av' 포인터가 새 리스트의 시작을 가리키게 합니다.
    av = firstData;

    // 6. (가장 중요) 'CircularList'를 빈 상태로 리셋합니다.
    //    'last' (헤더) 포인터는 절대 NULL이 되면 안 됩니다.
    header->link = header; // 헤더가 자기 자신을 가리키게 하여 빈 리스트로 만듦
}

//merge 함수
CircularList CircularList::operator+(const CircularList& lb) {

    //1. 병합된 결과를 담을 새 리스트 'lc' 생성 (헤더 노드 자동 생성됨)
    CircularList lc;
    
    // 4. 각 리스트의 포인터 준비
    Node* headerA = this->last; // 나의 헤더
    Node* headerB = lb.last;    // lb의 헤더
    Node* headerC = lc.last;    // lc의 헤더

    Node* pA = headerA->link; // 'A' 리스트를 순회할 포인터
    Node* pB = headerB->link; // 'B' 리스트를 순회할 포인터

    // 5. [중요] 'lc' 리스트의 꼬리를 추적할 포인터 (효율성 핵심)
    //    'q'는 항상 lc의 '마지막 데이터 노드'를 가리킵니다.
    //    처음에는 헤더에서 시작합니다.
    Node* q = headerC;

    // 6. 메인 병합 루프 (A와 B 모두 노드가 남아있는 동안)
    while (pA != headerA && pB != headerB) {
        
        // 7. [Available Space] 'av'에서 새 노드를 가져옴
        //    (operator+는 멤버 함수라 GetNode() 호출 가능)
        Node* newNode = GetNode(); 

        // 8. 데이터 비교
        if (pA->data < pB->data) {
            newNode->data = pA->data;
            pA = pA->link; // A만 다음 칸으로
        }
        else if (pA->data > pB->data) {
            newNode->data = pB->data;
            pB = pB->link; // B만 다음 칸으로
        }
        else { // (pA->data == pB->data)
            newNode->data = pA->data; // 중복된 값은 하나만 추가
            pA = pA->link; // A와 B 모두 다음 칸으로
            pB = pB->link;
        }

        // 9. [효율적 삽입] 'lc'의 꼬리(q)에 새 노드를 직접 연결 (O(1))
        newNode->link = headerC; // 새 노드는 헤더를 가리킴
        q->link = newNode;     // 이전 꼬리가 새 노드를 가리킴
        q = newNode;           // 새 노드가 이제 꼬리가 됨 (q -> newNode -> headerC)
    }

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

int CircularList::SolveJosephus(vector<int> &testData, int K) { //배열길이, 제거 간격
    
    // 1. 리스트를 깨끗하게 비웁니다.
    this->Erase(); 

    //2. vector 받아서 리스트 삽입
    for (int i = 0; i < testData.size(); i++) {
        this->Add(testData[i]);
    }

    cout << "\n[요세푸스 시작 리스트]: ";
    this->Show();

    Node* header = last;
    Node* p = header; // 'p'는 삭제할 노드의 '이전 노드'를 가리킵니다.

// 3. N-1명을 제거합니다.
// (N명 중 1명만 남아야 하므로, N-1번의 제거(삭제) 과정이 필요합니다.)
    for (int i = 0; i < testData.size() - 1; i++) {
        //
        // 4. 삭제할 노드 '직전'까지 포인터 'p'를 이동시킵니다.
        //
        //    'p'는 삭제할 노드의 '이전 노드' (predecessor)를 가리킵니다.
        //    'p'가 header에서 시작했으므로, K=3일 때 1, 2 (두 번) 이동하면
        //    'p'는 2번 노드를 가리키고, 삭제할 대상(q)은 3번 노드가 됩니다.
        //    따라서 (K-1)번 이동합니다.
        //
        for (int j = 0; j < K - 1; j++) {

                // 'p'를 다음 노드로 한 칸 이동시킵니다.
                p = p->link;

                // [예외 처리 1: 'p'가 헤더를 밟은 경우]
                // 이동한 'p'가 데이터 노드가 아닌 '헤더'를 가리킨다면,
                // (예: ... -> 7번 -> header -> 1번 ...)
                // 이 노드는 카운트에서 제외하고, 즉시 다음 노드(데이터 노드)로
                // 한 칸 더 이동합니다.
                // 이렇게 해야 K번째 '데이터 노드'를 정확히 셀 수 있습니다.
                if (p == header) { 
                    p = p->link;
                }
            } // (for 'j' 루프가 끝나면 'p'는 삭제할 노드의 '직전' 노드에 위치합니다)


            // 5. 삭제할 노드 'q'를 확정합니다.
            //
            //    'p'가 직전 노드이므로, 'p'의 다음 노드(p->link)가
            //    우리가 제거할 대상인 'q'가 됩니다.
            Node* q = p->link;


            // [예외 처리 2: 'q'가 헤더를 가리키는 경우]
            // 'p'가 리스트의 마지막 데이터 노드(예: 7번)에 멈췄다면,
            // 'q = p->link'는 'header'를 가리키게 됩니다.
            // 하지만 우리는 'header'를 지울 수 없습니다.
            if (q == header) { 
                // 실제 삭제 대상 'q'는 헤더의 다음 노드(예: 1번)입니다.
                q = q->link;
                // 'q'가 바뀌었으므로, 'q'의 직전 노드인 'p'도
                // 한 칸 이동시켜 'header'가 되도록 맞춥니다.
                // (p(header) -> q(1번) 관계 유지)
                p = p->link;
            }


            // 6. 'q' 노드를 리스트에서 연결 해제(삭제)합니다.
            //
            //    [p] -> [q] -> [q의 다음 노드]  라는 연결을
            //    [p] --------> [q의 다음 노드]  로 변경합니다.
            //
            //    'p'의 link가 'q'를 건너뛰고 'q'의 다음 노드를 가리키게 만듭니다.
            //    이제 리스트에서 'q'는 완벽히 분리되었습니다.
            p->link = q->link; 
            
            // 분리된 'q' 노드를 'delete'하지 않고,
            // 나중에 재사용할 수 있도록 'av' (available space) 리스트로 반납합니다.
            RetNode(q);
            
            // (중요) 'p' 포인터는 다음 'i' 루프를 위해
            // 현재 위치(방금 삭제된 노드의 직전 위치)에 그대로 머무릅니다.
            // 다음 카운트는 'p->link' (새로 연결된 노드)부터 다시 시작됩니다.
    }

    // 7. 마지막 남은 노드 (헤더의 다음 노드)
    Node* survivor = header->link;
    cout << "[최종 생존자]: " << survivor->data << endl;
    
    return survivor->data;
}



/*
enum Menu {JOSEPHUS,QUIT}; //그냥 이렇게 선언할 경우 0부터 시작한다

///매우 중요///////////
Node* CircularList::av = nullptr;
//static이므로 이거 무조건 해줘야 한다!!!! 반드시 기억

int main() {
    CircularList myList; // 요세푸스 문제를 풀 리스트
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
*/




//다른 여러가지 입력들도 고려한 버전

enum Menu {
    Add1,     // 0
    Add2,     // 1
    Delete,   // 2
    Show,     // 3
    Search,   // 4
    Merge,    // 5
    Josephus, // 6
    make_list,  // 7
    Exit      // 8
};

///매우 중요///////////
Node* CircularList::av = nullptr;
//static이므로 이거 무조건 해줘야 한다!!!! 반드시 기억

int main() {
    int selectMenu;
    int num = 0; bool result = false;
    vector<int> testData;
    
    // rand()를 위한 시드 초기화
    srand(time(NULL)); 

    CircularList la, lb, lc; // CircularList 사용 (이름만 la, lb, lc로 변경)
    int data = 0;
    
    do {
        cout << "\n0.Add1, 1.Add2, 2.Delete, 3.Show, 4.Search, 5.Merge, 6.Josephus, 7.make_list, 8.Exit 선택::";
        cin >> selectMenu;

        switch (static_cast<Menu>(selectMenu)) {
            
            case Add1: // 0. A에 랜덤 데이터 추가
                data = rand() % 49 + 1; // 1~49 사이의 랜덤 숫자
                la.Add(data);
                cout << "  리스트 la에 " << data << " 추가됨." << endl;
                break;

            case Add2: // 1. B에 랜덤 데이터 추가
                data = rand() % 49 + 1; // 1~49 사이의 랜덤 숫자
                lb.Add(data);
                cout << "  리스트 lb에 " << data << " 추가됨." << endl;
                break;

            case Delete: // 2. A에서 삭제
                cout << "  삭제할 데이터 입력: ";
                cin >> data;
                result = la.Delete(data);
                if (result)
                    cout << "  " << data << " 삭제 완료.";
                else
                    cout << "  " << data << "를 찾지 못했습니다.";
                break;

            case Show: // 3. 모든 리스트 보기
                cout << "  리스트 la = "; la.Show();
                cout << "  리스트 lb = "; lb.Show();
                cout << "  리스트 lc = "; lc.Show();
                break;

            case Search: // 4. A에서 검색
                cout << "  검색할 데이터 입력: ";
                cin >> data; // data 변수 재활용
                result = la.Search(data);
                if (!result)
                    cout << "  검색 값 = " << data << " 데이터가 없습니다.";
                else
                    cout << "  검색 값 = " << data << " 데이터가 존재합니다.";
                break;

            case Merge: // 5. 병합
                lc = la + lb;
                cout << "  리스트 lc = ";
                lc.Show();
                break;

            case Josephus: { // 6. 요세푸스 문제 ({}로 지역변수 범위 생성)
                int n, k;
                n = testData.size();
                cout << "  요세푸스 문제. 총 인원 (N): " << n;
                cout << "  제거 간격 (K): ";
                cin >> k;
                if (n > 0 && k > 0) {
                    la.SolveJosephus(testData, k); 
                } else {
                    cout << " N과 K는 0보다 커야 합니다." << endl;
                }
                break;
            }

            case make_list: { // 7. 한 줄의 입력을 받아 vector로 추가
                cout << "  리스트 la에 추가할 숫자들을 한 줄로 입력하세요 (예: 20 10 50 40 5):" << endl;
                cin.ignore();

                string line;
                getline(cin, line);
                stringstream ss(line);
                
                int number;
                while (ss >> number) {
                    testData.push_back(number); // 뽑아낸 숫자를 testData에 추가
                }
                
                cout << "[";
                for(int i=0; i<testData.size();i++){
                    cout << testData[i];
                    if(i!=testData.size()-1){
                        cout << " -> ";
                    }
                }
                cout << "]";
                break;
            }

            //쉼표로 파싱해야 할 경우 다음 코드 사용
            // case make_list: { // 7-1. 쉼표로 구분한 것 파싱, 한 줄의 입력을 받아 vector로 추가
            //     cout << "리스트 la에 추가할 숫자들을 쉼표(,)로 구분해 입력하세요 (예: 20, 10, 50, 40, 5):" << endl;
            //     string line;
            //     getline(cin, line);
            
            //     stringstream ss(line);
            //     string token;  
            //     int count = 0;

            //     while (getline(ss, token, ',')) {
            //         // 'token' (string)을 'num' (int)로 변환 (stoi 사용)
            //         int num = std::stoi(token); 
            //         testData.push_back(num); // 정수로 변환된 숫자를 la에 추가
            //         count++;
            //     }

            //     for(auto lt: testData){
            //         cout << lt;
            //     }
            //     break;
            // }

            case Exit: // 8. 종료
                cout << "프로그램을 종료합니다." << endl;
                break;

            default:
                cout << "잘못된 선택입니다. (0~7 사이 숫자)" << endl;
                break;
        } // end of switch
    } while (static_cast<Menu>(selectMenu) != Exit); // end of do-while
    
    cin >> num; // 프로그램 종료 전 입력 대기 (참고 코드 반영)
    return 0;
}
