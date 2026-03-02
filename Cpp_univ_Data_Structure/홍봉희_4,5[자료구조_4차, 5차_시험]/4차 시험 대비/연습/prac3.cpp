#include <iostream>
#include <cstdlib> // rand
#include <ctime>   // time
#include <vector>
#include <string>

using namespace std;

class Node {
public: 
    int key;
    Node *left, *right;   
    Node(int k) : key(k), left(NULL), right(NULL) {}
};

class BST {
public:
    Node* root = NULL; // 생성자 대신 초기화

    void Insert(int key) {
        Node* p = root;
        Node* q = NULL;

        while(p){
            
        }
    }

    Node* Search(int key) {

    }

    void Inorder(Node* t) {

    }
    
    int Height(Node* t) { 

    }

    Node* Delete(Node* t, int key) {
        
    }

    void GetRank(Node* t, int k, int& count, Node*& result) {
        
    }
    
    void PrintRank(Node* t, int k, int& count) {

    }

    Node* GetSuccessor(int key) {

    }
    
    Node* GetPredecessor(int key) {
        
        
    }

    
    Node* FindLCA_Iter(Node* root, int u, int v) {
        
    }
};

int main() {
    srand((unsigned int)time(NULL));
    BST tree;
    
    // [시나리오 1] 벡터에 난수 100개 생성 후 Insert(vector) 오버로딩 사용
    vector<int> dataVec;
    cout << "1. Insert 100 Random Numbers using Vector" << endl;
    for (int i = 0; i < 100; i++) {
        dataVec.push_back(rand() % 1000);
    }
    tree.Insert(dataVec); // 오버로딩된 함수 호출

    // [시나리오 2] 정렬 결과 확인 (Inorder)
    cout << "\n2. Sorted Result (Inorder): " << endl;
    tree.Inorder(tree.root); 
    cout << endl;

    // [시나리오 3] Rank (10번째 값 찾기 & 1~10등 출력)
    // 작성하신 코드에 맞춰 GetRank와 PrintRank를 각각 호출합니다.
    int k = 10;
    int count = 0;
    Node* result = NULL;
    
    cout << "\n3. Rank Check (k=" << k << ")" << endl;
    
    // 3-1. k번째 값 찾기
    tree.GetRank(tree.root, k, count, result);
    if (result) cout << k << "-th Smallest: " << result->key << endl;
    else cout << "Rank not found (Tree might be smaller than k)" << endl;

    // 3-2. 1~k등 출력하기
    count = 0; // 카운트 초기화 필수!
    cout << "1 to " << k << "-th Values: ";
    tree.PrintRank(tree.root, k, count);
    cout << endl;

    // [시나리오 4] Successor / Predecessor
    // 타겟 설정 (GetRank로 찾은 10번째 값을 타겟으로 하거나, 없으면 벡터의 첫 번째 값 사용)
    int target = (result) ? result->key : dataVec[0];

    Node* s = tree.GetSuccessor(target);
    Node* p = tree.GetPredecessor(target);

    cout << "\n4. Successor/Predecessor Check" << endl;
    cout << "Target: " << target << endl;
    cout << "Predecessor: " << (p ? to_string(p->key) : "None") << endl;
    cout << "Successor: " << (s ? to_string(s->key) : "None") << endl;

    // [시나리오 5] LCA (Lowest Common Ancestor) 테스트 - FindLCA_Iter 사용
    // 벡터에 있는 임의의 두 값을 뽑아서 테스트
    if (dataVec.size() >= 2) {
        int u = dataVec[0];
        int v = dataVec[5]; // 임의의 인덱스
        cout << "\n5. LCA Test (Iterative)" << endl;
        cout << "Node u: " << u << ", Node v: " << v << endl;
        
        Node* lca = tree.FindLCA_Iter(tree.root, u, v);
        if (lca) cout << "-> LCA: " << lca->key << endl;
        else cout << "-> LCA not found." << endl;
    }

    // [시나리오 6] 트리의 높이 (Height)
    cout << "\n6. Tree Height: " << tree.Height(tree.root) << endl;

    // [시나리오 7] Delete 테스트
    cout << "\n7. Delete Target (" << target << ")" << endl;
    tree.root = tree.Delete(tree.root, target); // 루트 갱신 중요
    
    // 삭제 확인 (Search 사용)
    if (!tree.Search(target)) cout << "Deleted Successfully!" << endl;
    else cout << "Delete Failed." << endl;

    return 0;
}
