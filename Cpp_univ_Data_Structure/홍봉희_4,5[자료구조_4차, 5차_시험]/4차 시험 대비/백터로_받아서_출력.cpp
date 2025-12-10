#include <iostream>
#include <cstdlib> // rand, srand
#include <ctime>   // time
#include <algorithm> // max
#include <vector>  // [필수] 교수님이 "배열로 만들어서"라고 했으므로 사용
using namespace std;

class Node {
    friend class BST;
    int key;
    Node *left, *right;
};

class BST {
    Node* root = nullptr;
public:
    // 1. 단일 삽입 (기존 유지 - 암기 필수!)
    void Insert(int x) {
        Node* p = root;
        Node* q = nullptr;

        while (p != nullptr) {
            q = p;
            if (x == p->key) return; // 중복 제거
            if (x < p->key) p = p->left;
            else p = p->right;
        }

        Node* newNode = new Node; 
        newNode->key = x;
        newNode->left = nullptr;
        newNode->right = nullptr;

        if (root == nullptr) root = newNode;
        else if (x < q->key) q->left = newNode;
        else q->right = newNode;
    }

    // [추가] 벡터(배열)를 통째로 받는 함수
    // "정수를 배열로 만들어서... 와라"에 대응
    // 만약 백터나 초기화 리스트로 주면 이걸 함수 오버로딩으로 구현해서 깔끔하게 받기
    void Insert(const vector<int>& dataList) {
        for (int x : dataList) {
            Insert(x);
        }
    }

    // 2. Inorder 출력
    void Inorder(Node* t) {
        if (t) {
            Inorder(t->left);
            cout << t->key << " ";
            Inorder(t->right);
        }
    }
    void Display() { Inorder(root); cout << endl; }

    // 3. 트리의 높이
    int GetHeight(Node* t) {
        if (!t) return 0;
        return 1 + max(GetHeight(t->left), GetHeight(t->right));
    }
    int Height() { return GetHeight(root); }

    // 4. Rank (k번째 작은 수)
    void FindRank(Node* t, int& count, int k, int& result) {
        if (!t || count >= k) return;
        
        FindRank(t->left, count, k, result);
        
        count++;
        if (count == k) {
            result = t->key;
            return;
        }
        
        FindRank(t->right, count, k, result);
    }
    int GetRank(int k) {
        int count = 0, result = -1;
        FindRank(root, count, k, result);
        return result;
    }

    // 5. Successor
    int GetSuccessor(int x) {
        Node* t = root;
        Node* succ = nullptr;
        while (t != nullptr) {
            if (t->key > x) {
                succ = t;
                t = t->left;
            } else {
                t = t->right;
            }
        }
        return (succ) ? succ->key : -1;
    }

    // 6. Predecessor
    int GetPredecessor(int x) {
        Node* t = root;
        Node* pred = nullptr;
        while (t != nullptr) {
            if (t->key < x) {
                pred = t;
                t = t->right;
            } else {
                t = t->left;
            }
        }
        return (pred) ? pred->key : -1;
    }
};

int main() {
    srand(time(0));
    BST tree;
    
    // [요구사항 1] 정수를 배열(Vector)로 100개 만들기
    vector<int> data;
    int sample = -1;

    cout << "--- [Step 1] Generate 100 Random Numbers (Raw Data) ---" << endl;
    for (int i = 0; i < 100; i++) {
        int num = rand() % 1000;
        data.push_back(num); // 배열에 저장
        
        // "순서대로 알려주고" -> 여기서 출력해서 보여줌
        cout << num << " "; 
        
        if(i == 50) sample = num; // 테스트용 값 하나 기억
    }
    cout << "\n\n";

    // [요구사항 2] 배열을 트리에 삽입 (이게 안 되면 나머지 절단!)
    tree.Insert(data);

    // [요구사항 3] 정렬 결과 (Inorder)
    cout << "--- [Step 2] Sorted Result (Inorder) ---" << endl;
    tree.Display();
    cout << endl;

    // [요구사항 4] 분석 (높이, Rank, Successor/Predecessor)
    cout << "--- [Step 3] Analysis ---" << endl;
    cout << "1. Tree Height: " << tree.Height() << endl;
    
    // Rank 테스트
    int k = 10;
    cout << "2. Rank (" << k << "th smallest): " << tree.GetRank(k) << endl;
    
    // Successor/Predecessor 테스트
    if(sample != -1) {
        cout << "3. Target Value: " << sample << endl;
        cout << "   - Predecessor: " << tree.GetPredecessor(sample) << endl;
        cout << "   - Successor  : " << tree.GetSuccessor(sample) << endl;
    }

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