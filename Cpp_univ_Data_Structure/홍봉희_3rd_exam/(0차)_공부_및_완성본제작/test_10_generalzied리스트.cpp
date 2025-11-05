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

/*
 * === 코드 전체 설명 ===
 * 이 C++ 코드는 '일반화 리스트(Generalized List, GenList)'를 구현한 프로그램입니다.
 * 일반화 리스트는 데이터(atom) 또는 다른 리스트(list)를 요소로 가질 수 있는
 * 재귀적인 자료구조입니다. (예: (a, (b, c), d))
 *
 * 이 코드는 특히 '참조 카운팅(Reference Counting)'을 이용한 메모리 관리를
 * 구현하여, 여러 리스트가 동일한 '하위 리스트(sublist)'를 공유할 때
 * 발생할 수 있는 '댕글링 참조(dangling reference)' 문제를 방지하려 합니다.
 *
 * --- 1. GenListNode 클래스 ---
 * 리스트를 구성하는 기본 노드입니다.
 * - link: 다음 형제 노드(sibling)를 가리킵니다. (예: (a, b)에서 a의 link는 b)
 * - tag (bool): 노드의 종류를 구분합니다.
 * - false (0): 이 노드가 '데이터(atom)'를 가짐 (union의 'data' 필드 사용)
 * - true (1): 이 노드가 '하위 리스트(list)'를 가짐 (union의 'dlink' 필드 사용)
 * - union: 메모리를 공유하는 영역입니다.
 * - data (int): tag가 0일 때, 실제 정수 데이터를 저장합니다.
 * - dlink (GenListNode*): tag가 1일 때, 하위 리스트의 시작 노드를 가리킵니다.
 * - ref (int): 참조 카운트. 이 노드(리스트)가 몇 번이나 참조되는지 
 * (공유되는지) 횟수를 저장합니다. 'Delete' 함수에서 사용됩니다.
 *
 * --- 2. GenList 클래스 ---
 * 일반화 리스트를 관리하고, 사용자 인터페이스(public 함수)를 제공합니다.
 * - first: 리스트의 첫 번째 노드를 가리킵니다.
 * - av (static): 'Available List'. 삭제된 노드들을 연결해두어,
 * 새 노드 요청 시 재활용(GetNode)하는 메모리 관리 기법입니다.
 * (이 코드에서는 GetNode가 구현되지 않았으나, Delete에서 av로 반환합니다.)
 * - Public 함수 (MakeList, Copy, Depth, Visit):
 * 사용자가 쉽게 호출할 수 있도록 제공되는 '래퍼(Wrapper)' 함수들입니다.
 * 실제 복잡한 작업은 'private' 재귀 함수들이 담당합니다.
 *
 * --- 3. 주요 재귀 함수 상세 설명 ---
 *
 * * void GenList::MakeList(GenListNode* s) (Private)
 * 사용자 입력을 받아 재귀적으로 리스트를 생성합니다.
 * 'GetData()' 함수를 통해 사용자 입력을 받습니다.
 * - 0: 현재 레벨의 리스트 생성을 종료합니다.
 * - 1: '하위 리스트(dlink)' 생성을 의미. 'tag'를 true(1)로 설정하고,
 * 'MakeList'를 *재귀 호출*하여 하위 리스트를 생성한 뒤 'dlink'에 연결합니다.
 * - 2 이상: '데이터(atom)'를 의미. 'tag'를 false(0)로 설정하고,
 * 입력받은 값을 'data'에 저장합니다.
 *
 * * GenListNode* GenList::Copy(GenListNode* p) (Private)
 * 리스트 전체를 '깊은 복사(Deep Copy)'하는 재귀 함수입니다.
 * 'p'가 가리키는 노드 'q'를 새로 생성합니다.
 * - tag가 0 (데이터)이면, 'data'를 복사합니다.
 * - tag가 1 (하위 리스트)이면, 'Copy'를 *재귀 호출*하여 'dlink'가 
 * 가리키는 하위 리스트 전체를 복사하고 그 주소를 'q->dlink'에 저장합니다.
 * - 마지막으로, 'Copy'를 *재귀 호출*하여 'p->link' (다음 형제)를 
 * 복사하고 'q->link'에 연결합니다.
 *
 * * void GenList::Visit(GenListNode* p) (Private)
 * 리스트를 재귀적으로 '중위 순회(In-order Traversal)'와 유사하게 
 * 방문하며 LISP 스타일로 출력합니다.
 * - tag가 0 (데이터)이면, 'data'를 출력합니다.
 * - tag가 1 (하위 리스트)이면, '<'를 출력하고 'Visit'를 *재귀 호출*하여
 * 'dlink'의 하위 리스트를 방문한 뒤, '>'를 출력합니다.
 * - 마지막으로, 'Visit'를 *재귀 호출*하여 'p->link' (다음 형제)를 방문합니다.
 *
 * * int GenList::Depth(GenListNode* s) (Private)
 * 리스트의 최대 중첩 깊이를 재귀적으로 계산합니다.
 * 현재 레벨('s'에서 'link'를 따라가며)을 순회합니다.
 * - tag가 0 (데이터)이면 깊이에 영향을 주지 않습니다.
 * - tag가 1 (하위 리스트)이면, 'Depth'를 *재귀 호출*하여
 * 'dlink'의 하위 리스트 깊이('n')를 계산합니다.
 * - 현재 레벨에서 찾은 최대 하위 깊이('m')를 갱신합니다.
 * - 순회가 끝나면 (최대 하위 깊이 'm' + 현재 레벨 '1')을 반환합니다.
 *
 * * int equal(GenListNode* s, GenListNode* t) (Friend)
 * 두 리스트가 구조적, 내용적으로 동일한지 재귀적으로 검사합니다.
 * - 두 노드의 'tag'가 같은지 확인합니다.
 * - tag가 0 (데이터)이면, 'data' 값이 같은지 확인합니다.
 * - tag가 1 (하위 리스트)이면, 'equal'을 *재귀 호출*하여 'dlink'가 
 * 가리키는 하위 리스트들이 같은지 확인합니다.
 * - 위 조건이 참이면, 'equal'을 *재귀 호출*하여 'link' (다음 형제)가 
 * 같은지 확인합니다.
 *
 * --- 4. 참조 카운팅 및 Delete 함수 ---
 * * void GenList::Delete(GenListNode* x) (Private)
 * 이 함수는 '참조 카운팅'을 기반으로 리스트를 삭제합니다.
 * - [가정]: 공유되는 하위 리스트의 헤드 노드는 특별한 'tag' (예: 2)를 
 * 가지고, 'ref' 필드에 자신을 참조하는 횟수를 저장한다고 가정합니다.
 * - `if (x->tag == 2) x->ref--;`:
 * 이 코드는 'x'가 참조 카운트 노드(tag=2로 가정)일 경우, 
 * 참조 카운트('ref')를 1 감소시킵니다.
 * - [주의]: 현재 코드에서 `GenListNode`의 `tag`는 `bool`로 선언되어 있어,
 * `x->tag == 2`는 `x->tag == true` (즉, 1)와 동일하게 처리될 수 있습니다.
 * 원래 의도(0=data, 1=dlink, 2=ref)대로 동작하려면 `tag` 선언이 
 * `int tag;`로 변경되어야 할 수 있습니다.
 * - `if (!x->ref)`: 참조 카운트가 0이 되면, 노드(리스트)를 
 * 실제로 삭제(반환)합니다.
 * - `if (y->tag == 1) Delete(y->dlink);`: 삭제 과정에서 만나는
 * 모든 하위 리스트('tag'=1)에 대해 'Delete'를 *재귀 호출*합니다.
 * - `y->link = av; av = x;`: 삭제할 리스트의 노드들을 
 * 'av' (사용 가능 리스트)에 통째로 반환하여 메모리를 재활용합니다.
 *
 * --- 5. main() 함수 ---
 * 사용자에게 메뉴(m: make, c: copy, d: depth, v: visit, q: quit)를
 * 제공하고, 'GenList' 클래스의 public 함수들을 호출하여
 * 일반화 리스트 기능을 테스트하는 '드라이버' 코드입니다.
 */

// 좀 쉬운 설명
/*
1. 일반화 리스트(GenList)란?
이 코드는 **'일반화 리스트'**를 만듭니다. 일반화 리스트는 두 종류의 요소를 가질 수 있는 특별한 리스트입니다.
데이터(Atom): int 타입의 정수 값.
하위 리스트(Sublist): 그 자체가 또 다른 '일반화 리스트'인 리스트.
이 구조 때문에 (10, (20, 30), 40)처럼 리스트 안에 또 다른 리스트가 중첩되어 들어갈 수 있습니다.

2. 핵심 구조: GenListNode
리스트의 모든 요소는 GenListNode로 만들어집니다.
link: 같은 레벨(depth)에 있는 다음 요소를 가리키는 포인터입니다.
tag: 이 노드가 무엇을 저장하는지 알려주는 bool 값(꼬리표)입니다.
false (0): 이 노드는 **데이터(int)**를 저장합니다.
true (1): 이 노드는 **하위 리스트(GenList)**를 저장합니다.
union (공용체): tag 값에 따라 둘 중 하나의 역할만 수행합니다.
data: tag가 0일 때, 실제 정수 값이 저장됩니다.
dlink: tag가 1일 때, 하위 리스트의 시작 노드를 가리키는 포인터가 저장됩니다.

3. 재귀(Recursion)가 핵심인 이유
이 자료구조는 정의 자체가 재귀적입니다. ("리스트는 '데이터' 또는 '리스트'의 목록이다.") 
따라서 이 구조를 처리하는 거의 모든 함수도 재귀적이어야 합니다.
어떤 함수(예: Visit)가 GenList를 처리하다가 tag가 1인 하위 리스트를 만나면, 
그 하위 리스트를 처리하기 위해 자기 자신(예: Visit)을 다시 호출해야 합니다.

🔄 MakeList (생성)
목표: 사용자 입력으로 리스트를 만듭니다.

재귀 동작:
사용자가 2 이상의 숫자를 입력하면, tag=0인 데이터 노드를 만듭니다.
사용자가 1을 입력하면(하위 리스트 생성), MakeList 함수를 재귀 호출합니다.
재귀 호출이 반환한 하위 리스트의 시작 주소를 dlink에 저장하고 tag=1로 설정합니다.
0을 입력받을 때까지 link로 노드들을 연결합니다.

🔄 Visit (출력)
목표: 리스트의 모든 요소를 ( ) 형식으로 출력합니다.

재귀 동작:
노드를 순회(link 사용)합니다.
tag=0 (데이터)이면, data 값을 출력합니다.
tag=1 (하위 리스트)이면, (를 출력하고 Visit 함수를 재귀 호출하여 dlink가 가리키는 하위 리스트 전체를 출력하게 합니다. 재귀 호출이 끝나면 )를 출력합니다.

🔄 Copy (복사)
목표: 리스트 전체를 새로운 메모리 공간에 똑같이 복제(깊은 복사)합니다.

재귀 동작:
노드를 순회(link 사용)하며 새 노드를 만듭니다.
tag=0 (데이터)이면, data 값을 새 노드에 복사합니다.
tag=1 (하위 리스트)이면, Copy 함수를 재귀 호출하여 dlink가 가리키는 하위 리스트 전체를 복사하고, 그 결과(새로 복사된 하위 리스트의 주소)를 새 노드의 dlink에 저장합니다.

🔄 Depth (깊이 계산)
목표: 리스트가 얼마나 깊게 중첩되었는지 계산합니다. (예: (10)은 1, (10, (20))은 2)

재귀 동작:
현재 레벨의 노드들을 순회(link 사용)하며 최대 깊이를 찾습니다.
tag=0 (데이터)이면, 깊이에 영향을 주지 않습니다.
tag=1 (하위 리스트)이면, Depth 함수를 재귀 호출하여 dlink가 가리키는 하위 리스트의 깊이를 계산합니다.
재귀 호출로 얻은 깊이 값들 중 가장 큰 값을 찾습니다.
최종적으로 (가장 깊었던 하위 리스트의 깊이) + 1 (현재 레벨)을 반환합니다.

🔄 Delete (삭제)
목표: 리스트와 그 안의 모든 하위 리스트가 사용하던 메모리를 해제합니다.

재귀 동작:
리스트의 노드들을 순회(link 사용)합니다.
tag=1 (하위 리스트)이면, Delete 함수를 재귀 호출하여 dlink가 가리키는 하위 리스트부터 먼저 삭제합니다.
모든 하위 리스트 삭제가 끝나면, 현재 레벨의 노드들을 av(재활용 리스트)에 반환합니다.
(ref는 "참조 카운트"로, 여러 리스트가 하나의 하위 리스트를 공유할 때, 참조가 0이 되어야만 삭제하도록 제어하는 기능입니다.)
*/


#include <iostream>
using namespace std;

// 함수 전방 선언
int GetData();
class GenList; 

/*
 * 클래스: GenListNode
 * 목적: 일반화 리스트의 노드 구조체입니다.
 */
class GenListNode
{
    friend class GenList;
    friend int operator==(const GenList&, const GenList&);
    friend int equal(GenListNode*, GenListNode*);
private:
    GenListNode* link; // 다음 노드(형제)를 가리키는 포인터
    bool tag; // 0(false) = data, 1(true) = dlink (하위 리스트)
    union {
        int data; // tag가 0일 때 사용
        GenListNode* dlink; // tag가 1일 때 사용 (하위 리스트 포인터)
        int ref; // 참조 카운트 (헤드 노드에서 사용)
    };
};

/*
 * 클래스: GenList
 * 목적: 일반화 리스트를 관리하는 메인 클래스입니다.
 */
class GenList
{
    friend int operator==(const GenList&, const GenList&);
    friend int equal(GenListNode*, GenListNode*);
private:
    GenListNode* first; // 리스트의 시작(헤드) 노드 포인터
    static GenListNode* av; // 사용 가능한 노드 리스트 (메모리 재활용)

    /* --- Private 재귀 함수들 --- */
    GenListNode* Copy(GenListNode*); // (private) 재귀적 복사
    void Visit(GenListNode*);        // (private) 재귀적 순회 (출력)
    int Depth(GenListNode*);         // (private) 재귀적 깊이 계산
    GenListNode* MakeList(GenListNode*); // (private) 재귀적 리스트 생성
    void Delete(GenListNode*);       // (private) 재귀적 삭제 (참조 카운팅)
public:
    /* --- Public 래퍼(Wrapper) 함수들 --- */
    void Copy(const GenList&); // (public) 복사 생성 래퍼
    void Visit();              // (public) 순회(출력) 래퍼
    ~GenList();                // 소멸자
    int Depth();               // (public) 깊이 계산 래퍼
    void MakeList();           // (public) 리스트 생성 래퍼
};

/* 소멸자: 리스트 전체 삭제 */
GenList::~GenList()
{
    Delete(first);
    first = 0;
}

/* (public) Copy 래퍼 */
void GenList::Copy(const GenList& l)
{
    first = Copy(l.first);
}

/* (public) Visit 래퍼: 리스트 전체 순회 (출력) */
void GenList::Visit()
{
    cout << "<";
    Visit(this->first);
    cout << ">";
}

/* 두 리스트의 동일성 비교 (재귀 equal 호출) */
int operator==(const GenList& l, const GenList& m)
{
    return equal(l.first, m.first);
}

/* (private) Delete: 참조 카운트 기반의 재귀적 삭제 */
void GenList::Delete(GenListNode* x)
{
    // [참조 카운팅 로직]
    // tag == 2는 이 노드가 '참조 카운트'를 가진 헤드 노드임을 의미 (주석 참고)
    if (x->tag == 2) x->ref--; 
    
    if (!x->ref) // 참조 카운트가 0이면 삭제 진행
    {
        GenListNode* y = x;
        while (y->link) // 리스트의 끝까지 이동
        {
            y = y->link;
            if (y->tag == 1) Delete(y->dlink); // 하위 리스트(tag=1) 재귀 삭제
        }
        y->link = av; // 리스트를 av에 반환
        av = x;
    }
}

/* (public) Depth 래퍼 */
int GenList::Depth()
{
    return Depth(first);
}

/* (public) MakeList 래퍼 */
void GenList::MakeList()
{
    first = MakeList(first);
}

/* (private) MakeList: 사용자 입력을 받아 재귀적으로 리스트 구조 생성 */
GenListNode* GenList::MakeList(GenListNode* s)
{
    GenListNode* p, * q, * r;
    bool tag_head = true; // 현재 레벨의 첫 번째 노드인지 확인
    q = new GenListNode; // 새 리스트(또는 노드) 시작
    r = q; // 현재 레벨의 시작 포인터 'r'
    
    while (int x = GetData()) // 0이 입력될 때까지 반복
    {
        if (x == 1) // 1: 하위 리스트(dlink) 생성
        {
            if (tag_head) { // 첫 노드가 하위 리스트인 경우
                q->dlink = MakeList(q); // 재귀 호출로 하위 리스트 생성
                q->tag = true; // tag=1 (dlink)
                q->link = 0;
                tag_head = false;
                continue;
            }
            else // 첫 노드가 아닌 경우
            {
                p = new GenListNode;
                q->link = p; // 이전 노드(q)에 새 노드(p) 연결
                p->tag = true; // tag=1 (dlink)
                p->link = 0;
                q = p; // q를 새 노드로 이동
                q->dlink = MakeList(q); // 재귀 호출
            }
        }
        else { // 2 이상: 데이터 노드 생성
            if (tag_head) { // 첫 노드가 데이터인 경우
                q->data = x; q->tag = false; q->link = 0; // tag=0 (data)
                tag_head = false;
            }
            else { // 첫 노드가 아닌 경우
                p = new GenListNode;
                p->data = x; p->tag = false; p->link = 0;
                q->link = p; // 이전 노드(q)에 새 노드(p) 연결
                q = p; // q를 새 노드로 이동
            }
        }
    }
    return r; // 생성된 리스트의 시작 포인터 반환
}

/* (private) Copy: 리스트를 재귀적으로 깊은 복사(deep copy) */
GenListNode* GenList::Copy(GenListNode* p)
{
    GenListNode* q = 0;
    if (p) { // p가 NULL이 아니면
        q = new GenListNode; // 새 노드 생성
        q->tag = p->tag; // tag 복사
        if (!p->tag) // tag=0 (데이터)
            q->data = p->data; // 데이터 복사
        else // tag=1 (하위 리스트)
            q->dlink = Copy(p->dlink); // 재귀 호출로 하위 리스트 복사
        
        q->link = Copy(p->link); // 재귀 호출로 다음 형제 노드 복사
    }
    return q; // 복사된 노드(리스트)의 시작 포인터 반환
}

/* (private) Visit: 리스트를 재귀적으로 순회하며 출력 (LISP 스타일) */
void GenList::Visit(GenListNode* p)
{
    if (p != nullptr) { // p가 NULL이 아니면
        cout << p->tag << ":"; // tag 값 출력 (0 또는 1)
        if (!p->tag) // tag=0 (데이터)
            cout << p->data << ","; // 데이터 출력
        else { // tag=1 (하위 리스트)
            cout << " <";
            Visit(p->dlink); // 재귀 호출로 하위 리스트 방문
            cout << "> ";
        }
        Visit(p->link); // 재귀 호출로 다음 형제 노드 방문
    }
}

/* (friend) equal: 두 노드(및 그 하위)가 동일한지 재귀적으로 검사 */
int equal(GenListNode* s, GenListNode* t)
{
    int x;
    if ((!s) && (!t)) return 1; // 둘 다 NULL이면 동일 (1)
    
    // 둘 다 NULL이 아니고, tag가 같으면
    if (s && t && (s->tag == t->tag)) { 
        if (!s->tag) // tag=0 (데이터)
            if (s->data == t->data) x = 1; else x = 0; // 데이터 비교
        else // tag=1 (하위 리스트)
            x = equal(s->dlink, t->dlink); // 재귀 호출로 하위 리스트 비교
        
        if (x) return equal(s->link, t->link); // 현재 노드가 같다면, 다음 형제 노드 비교
    }
    return 0; // 그 외의 경우는 모두 다름 (0)
}

/* (private) Depth: 리스트의 최대 중첩 깊이를 재귀적으로 계산 */
int GenList::Depth(GenListNode* s)
{
    if (!s) return 0; // 빈 리스트는 깊이 0
    GenListNode* p = s; 
    int m = 0; // 현재 레벨에서의 최대 하위 깊이
    
    while (p) { // 현재 레벨의 모든 노드 순회
        if (p->tag) { // tag=1 (하위 리스트)
            int n = Depth(p->dlink); // 재귀 호출로 하위 리스트의 깊이 계산
            if (m < n) m = n; // 최대 깊이 갱신
        }
        p = p->link; // 다음 형제 노드로 이동
    }
    return m + 1; // (최대 하위 깊이 m) + (현재 레벨 1)
}

/* 사용자 입력 헬퍼 함수 (0: 종료, 1: 하위 리스트, 2+: 데이터) */
int GetData() {
    cout << endl << "0: exit, 1: dlink, 2 정수입력: ";
    int n;
    cin >> n;
    return n;
}

// static av 포인터 초기화
GenListNode* GenList::av = 0;

/* 메인 함수 (메뉴 구동) */
int main(void)
{
    GenList l;
    GenList m;
    char select;
    int max = 0, x = 0;
    
    cout << "Select command m: make, c: copy, d: depth, v: visit, q : quit =>";
    cin >> select;
    while (select != 'q') // 'q' 입력 시 종료
    {
        switch (select)
        {
        case 'm': // 리스트 생성
            l.MakeList();
            break;
        case 'c': // 리스트 복사
            m.Copy(l);
            cout << "Copy Result" << endl;
            l.Visit(); // 원본 출력
            m.Visit(); // 사본 출력
            cout << endl;
            break;
        case 'd': // 리스트 깊이 계산
            cout << "depth: " << l.Depth();
            cout << endl;
        case 'v': // 리스트 순회 (출력)
            cout << "tag : data (link)" << endl;
            l.Visit();
            cout << endl;
            break;
        case 'q':
            cout << "Quit" << endl;
            break;
        default:
            cout << "WRONG INPUT " << endl;
            cout << "Re-Enter" << endl;
            break;
        }
        cout << "Select command m: make, c: copy, d: depth, v: visit, q : quit =>";
        cin >> select;
    }
    system("pause");
    return 0;
}

