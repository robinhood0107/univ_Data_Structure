#include <iostream>
#include <cstdlib> // rand
#include <ctime>   // time

using namespace std;

// [조건 1] Node 클래스 정의 (요구사항 엄수)
class Node {
public: 
    int key;
    Node *left, *right;   
    // 생성자
    Node(int k) : key(k), left(NULL), right(NULL) {}
};

class BST {
public:
    Node* root = NULL; // 생성자 대신 초기화

    // [조건 2] Insert: 교과서 5.7의 반복문(Iterative) 로직 유지
    // p(현재), q(부모) 포인터 사용
    void Insert(int key) {
        
    }

    // [조건 3] Search: 반복문 로직
    Node* Search(int key) {
        
    }

    // [조건 4] Delete: Inorder Successor를 이용한 삭제 (재귀가 가장 간결함)
    Node* Delete(Node* t, int key) {
        
    }

    // [조건 5] Successor: Root부터 탐색 (부모 포인터 없음)
    Node* GetSuccessor(int key) {
        
    }
    
    // Predecessor: 논리는 Successor와 반대
    Node* GetPredecessor(int key) {
        
    }

    // [조건 6] Rank & Print: Inorder 응용 (하나로 통합하여 암기량 감소)
    // mode 0: k-Rank 찾기, mode 1: 1~k등 출력
    void RankOp(Node* t, int k, int& count, Node*& result, int mode) {

    }

    // Inorder 출력 (정렬 확인용)
    void Inorder(Node* t) {

    }

    // [추가] 트리의 X (Height)
    int Height(Node* t) {
        
    }
};

int main() {
    srand((unsigned int)time(NULL));
    BST tree;
    int data[100]; 

    // [시나리오 1] 난수 100개 생성 및 삽입
    cout << "1. Insert 100 Random Numbers" << endl;
    for (int i = 0; i < 100; i++) {
        data[i] = rand() % 1000;
        tree.Insert(data[i]);
    }

    // [시나리오 2] 정렬 결과 확인 (Inorder)
    cout << "\n2. Sorted Result: ";
    tree.Inorder(tree.root); cout << endl;

    // [시나리오 3] Rank (10번째 값) & 1~10등 출력
    int k = 10, count = 0;
    Node* result = NULL;
    
    cout << "\n3. Rank Check (k=" << k << ")" << endl;
    tree.RankOp(tree.root, k, count, result, 0); // 0: 찾기 모드
    if (result) cout << k << "-th Smallest: " << result->key << endl;

    count = 0; // 카운트 초기화 필수
    cout << "1 to " << k << "-th Values: ";
    tree.RankOp(tree.root, k, count, result, 1); // 1: 출력 모드
    cout << endl;

    // [시나리오 4] Successor / Predecessor
    int target = data[50]; // 배열 중간값으로 테스트
    // 혹시 중복 제거로 삭제되었으면 랭크 1위 값으로 대체
    if (!tree.Search(target) && result) target = result->key;

    Node* s = tree.GetSuccessor(target);
    Node* p = tree.GetPredecessor(target);

    cout << "\n4. Target: " << target << endl;
    if (p) cout << "Predecessor: " << p->key << endl; else cout << "Predecessor: None" << endl;
    if (s) cout << "Successor: " << s->key << endl; else cout << "Successor: None" << endl;

    // [시나리오 5] 트리의 X (Height)
    cout << "\n5. Tree Height: " << tree.Height(tree.root) << endl;

    // [시나리오 6] Delete 테스트
    cout << "\n6. Delete " << target << endl;
    tree.root = tree.Delete(tree.root, target); // 루트 갱신 중요
    if (!tree.Search(target)) cout << "Deleted Successfully!" << endl;

    return 0;
}


/*
### 1. Node 클래스 & 초기화
* **핵심**: 멤버 변수 접근을 위해 무조건 `public:`으로 선언.
* **코드**: `int key; Node *left, *right;` + 생성자(초기화).

### 2. Insert (삽입) - 반복문
* **핵심**: 포인터 2개 (`p`: 현재, `q`: 부모).
* **로직**:
    1.  `while(p)` 도는 동안 `q = p` 저장 후 `p` 이동.
    2.  `while` 끝나면 `q`의 자식으로 `new Node` 연결.

### 3. Delete (삭제) - 재귀
* **핵심**: 탐색 파트와 삭제 파트(Case 3가지) 분리.
* **로직**:
    1.  **탐색**: `key < t->key`면 `t->left = Delete(...)`. (반대도 동일)
    2.  **자식 0/1개**: 남은 자식(혹은 NULL) 리턴하고 `delete t`.
    3.  **자식 2개**:
        * `t->right`에서 **최소값(Left 끝)** 찾기 (=Successor).
        * 값 복사 (`t->key = succ->key`).
        * **재귀 호출**로 Successor 노드 삭제 (`t->right = Delete(...)`).

### 4. Successor (후속자) - 반복문
* **핵심**: Root부터 시작. `t`가 나보다 크면 `succ` 후보.
* **로직**:
    1.  **탐색 중**: `key < t->key` (왼쪽 이동) → **`succ = t` 저장** (현재 `t`가 나보다 크니까).
    2.  **찾은 후**: `t->right`가 있으면 → **오른쪽 가서 왼쪽 끝**이 진짜 `succ`.

### 5. Rank (k번째 값) - 재귀 (Inorder)
* **핵심**: `L -> V -> R` 순서에 카운팅 추가.
* **로직**:
    1.  `Left` 재귀.
    2.  `count++` 수행 후 `if (count == k)` 체크.
    3.  `Right` 재귀.

### 6. Height (높이) - 재귀
* **핵심**: `1 + max(왼쪽, 오른쪽)`.
* **로직**: `if (!t) return 0;` → `return 1 + (l > r ? l : r);`

### 7. Vector 입력 처리
* **핵심**: 오버로딩.
* **로직**: `Insert(vector& v)` 함수 만들고, 내부에서 `for(int x : v) Insert(x);` 호출.

---

**시험장 암기 요약표:**

| 함수 | 방식 | 핵심 포인트 |
| :--- | :--- | :--- |
| **Insert** | 반복문 | `q = p` (부모 추적) |
| **Delete** | 재귀 | 자식 2개일 때 **값 복사** 후 **재귀 삭제** |
| **Successor** | 반복문 | 왼쪽 갈 때 `succ` 저장 |
| **Rank** | 재귀 | `Inorder` 중간에 `count++` |
| **Height** | 재귀 | `1 + max(L, R)` |
*/