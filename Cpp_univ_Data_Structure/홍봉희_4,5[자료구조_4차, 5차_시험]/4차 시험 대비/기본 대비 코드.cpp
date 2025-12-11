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
        Node* p = root;
        Node* q = NULL;

        while (p) {
            q = p;
            if (key == p->key) return; // 중복 값은 무시
            if (key < p->key) p = p->left;
            else p = p->right;
        }

        Node* newNode = new Node(key);
        if (!root) root = newNode;
        else if (key < q->key) q->left = newNode;
        else q->right = newNode;
    }

    // [조건 3] Search: 반복문 로직
    Node* Search(int key) {
        Node* t = root;
        while (t) {
            if (key == t->key) return t;
            if (key < t->key) t = t->left;
            else t = t->right;
        }
        return NULL;
    }

    // Inorder 출력 (정렬 확인용)
    void Inorder(Node* t) {
        if (t) {
            Inorder(t->left);
            cout << t->key << " ";
            Inorder(t->right);
        }
    }

    // [추가] 트리의 X (Height)
    int Height(Node* t) {
        if (!t) return 0;
        int l = Height(t->left);
        int r = Height(t->right);
        return 1 + (l > r ? l : r);
    }

    // [조건 4] Delete: Inorder Successor를 이용한 삭제 (재귀가 가장 간결함)
    Node* Delete(Node* t, int key) {
        if (!t) return NULL;
        
        // 1. 삭제할 노드 찾기
        if (key < t->key) t->left = Delete(t->left, key);
        else if (key > t->key) t->right = Delete(t->right, key);
        else {
            // 2. 삭제 수행
            // Case 1: 자식이 0개 또는 1개
            if (!t->left) { Node* temp = t->right; delete t; return temp; }
            else if (!t->right) { Node* temp = t->left; delete t; return temp; }
            
            // Case 2: 자식이 2개 -> Right Subtree의 Min(Successor) 찾기
            Node* succ = t->right;
            while (succ->left) succ = succ->left;
            
            t->key = succ->key; // 값 교체
            t->right = Delete(t->right, succ->key); // Successor 노드 삭제
        }
        return t;
    }

    // [조건 5] Successor: Root부터 탐색 (부모 포인터 없음)
    Node* GetSuccessor(int key) {
        Node* succ = NULL;
        Node* t = root;
        while (t) {
            if (key < t->key) { // Target보다 내가 크면, 나는 잠재적 Successor
                succ = t;
                t = t->left;
            } else if (key > t->key) {
                t = t->right;
            } else { // Target 찾음
                if (t->right) { // 오른쪽 자식이 있다면 그 중 최소값
                    Node* temp = t->right;
                    while (temp->left) temp = temp->left;
                    succ = temp;
                }
                break;
            }
        }
        return succ;
    }
    
    // Predecessor: 논리는 Successor와 반대
    Node* GetPredecessor(int key) {
        Node* pred = NULL;
        Node* t = root;
        while (t) {
            if (key < t->key) t = t->left;
            else if (key > t->key) { // Target보다 내가 작으면, 나는 잠재적 Pred
                pred = t;
                t = t->right;
            } else { // Target 찾음
                if (t->left) { // 왼쪽 자식이 있다면 그 중 최대값
                    Node* temp = t->left;
                    while (temp->right) temp = temp->right;
                    pred = temp;
                }
                break;
            }
        }
        return pred;
    }

    // // [조건 6] Rank & Print: Inorder 응용 (하나로 통합하여 암기량 감소)
    // // mode 0: k-Rank 찾기, mode 1: 1~k등 출력
    // void RankOp(Node* t, int k, int& count, Node*& result, int mode) {
    //     if (!t || (mode == 0 && result) || (mode == 1 && count >= k)) return;

    //     RankOp(t->left, k, count, result, mode); // L

    //     count++; // V
    //     if (mode == 0 && count == k) { result = t; return; }
    //     if (mode == 1 && count <= k) cout << t->key << " ";

    //     RankOp(t->right, k, count, result, mode); // R
    // }

    //k번째 원소 찾기 (GetRank)
    // t: 현재 노드, k: 찾는 등수, count: 현재 등수(참조), result: 결과 담을 포인터(참조)
    void GetRank(Node* t, int k, int& count, Node*& result) {
        // 1. 노드가 없거나, 이미 결과를 찾았으면 그만함
        if (!t || result != NULL) return;

        // L (왼쪽 파기)
        GetRank(t->left, k, count, result);

        // V (방문 - 카운트 세기)
        count++;
        if (count == k) {
            result = t; // 찾았다!
            return;     // 뒤도 안 돌아보고 종료
        }

        // R (오른쪽 파기)
        GetRank(t->right, k, count, result);
    }
    
    //1등 ~ k등 출력하기 (PrintRank)
    // t: 현재 노드, k: 출력할 한계 등수, count: 현재 등수(참조)
    void PrintRank(Node* t, int k, int& count) {
        // 1. 노드가 없거나, 이미 k개를 다 출력했으면 그만함
        if (!t || count >= k) return;

        // L (왼쪽)
        PrintRank(t->left, k, count);

        // V (방문 - 출력하기)
        if (count < k) { // 아직 k개를 다 못 채웠으면
            cout << t->key << " ";
            count++; // 출력했으니 카운트 증가
        }
        
        // R (오른쪽)
        PrintRank(t->right, k, count);
    }

    // [추가 구현] LCA (Lowest Common Ancestor)
    Node* FindLCA_Iter(Node* root, int u, int v) {
        Node* t = root;
        while (t) {
            // 1. 두 값이 모두 현재 노드보다 작으면 -> 왼쪽으로 이동
            if (t->key > u && t->key > v) {
                t = t->left;
            }
            // 2. 두 값이 모두 현재 노드보다 크면 -> 오른쪽으로 이동
            else if (t->key < u && t->key < v) {
                t = t->right;
            }
            // 3. 갈라지는 지점(하나는 작고 하나는 큼) 또는 일치 -> 여기가 LCA
            else {
                return t;
            }
        }
        return NULL;
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
Insert 함수 암기: 교수님이 "이게 안 되면 나머지 절단"이라고 강조하셨습니다. while문 돌면서 자리 찾고, new Node 하고, 부모(q)랑 연결하는 3단계를 꼭 외우세요.

출력 확인: main 함수에서 [Step 1]처럼 입력 데이터를 먼저 찍어주는 것이 "순서대로 알려주고"라는 요구사항을 만족시키는 핵심입니다.

다음 주 예고: 교수님이 말씀하신 "다이내믹 프로그래밍(DP)"과 "그리디"는 다음 주 화요일 주제라고 하셨으니, 이번 시험(BST) 끝나면 바로 그쪽 공부로 넘어가셔야 합니다.
*/

/*
교수님이 **"내일모레 목요일날 할 거, 이거는 바이네믹 서치트리(BST) 얘가 기본이야"**라고 명시하셨습니다.
특히 **"입력이 안 되면 나머지 절단"**이라며 강력하게 경고하셨으니, 아래 코드는 **반드시 암기**해서 가야 합니다.

* **필수 구현 항목 (체크리스트):**
    1.  **난수 생성 및 저장:** `rand()`로 정수 100개를 생성하여 **먼저 배열(또는 벡터)에 담고**, 이를 **순서대로 출력(확인)**시켜야 합니다. ("100개를 순서대로 알려주고 해가지고 와... 입력이 안 되면 나머지 절단이지")
    2.  **Insert 함수 (암기 필수):** 생성한 난수를 BST에 삽입하는 로직. ("난소를 트리에 있었다는 거는 암기를 하던데 해야 되잖아요.")
    3.  **기능 구현:** 트리가 만들어진 후 다음 기능들이 돌아가야 점수가 나옵니다.
        * **Inorder Traversal:** 정렬된 결과 출력
        * **Rank:** k번째 작은 수 찾기
        * **Successor / Predecessor:** 특정 노드의 직후/직전 값 찾기
        * **Height:** 트리의 높이 구하기
*/