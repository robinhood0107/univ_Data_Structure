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
            if(key == p->key) { return; }
            else if (key < p->key) { p = p->left; }
            else { p = p->right; }
        }

        //이제 여기서 새로운 q와 연결
        Node* newNode = new Node(key);
        //(내가 틀린 부분)이거 꼭 기억하자 이렇게 하는 거다
        if(!root) { root = newNode; }
        //여기서 주의!!! q->key랑 비교해서 작으면 left, 크면 right로 집어 넣어야 한다
        else if (key < q->key ) {q->left = newNode;} //이렇게 q->left = newNode로 연결시키기
        else {q->right = newNode;}
        
    }
    
    void Insert(vector<int>& vec) {
        for(auto lt: vec){
            Insert(lt);
        }
    }

    Node* Search(int key) {
        Node* t = root;

        while(t){
            if(key == t->key) { return t;}
            else if (key < t->key) {t = t->left;}
            else {t = t->right;}
        }
        return NULL;
    }

    void Inorder(Node* t) {
        //Inorder 출력문의 경우 크게 if(t)만 해주면 된다
        if(t){
            Inorder(t->left);
            cout << t->key << " ";
            Inorder(t->right);
        }
    }
    
    int Height(Node* t) { 
        if(!t) { return 0;} //0을 반환하면 됨
        int l = Height(t->left);
        int r = Height(t->right);
        return 1 + max(l,r);
    }

    Node* Delete(Node* t, int key) {
        if (!t) return NULL; //null 반환으로 끝내면 됨

        //(내가 틀린 부분) 일단 삭제할 노드로 이동부터 해야 한다
        if (key < t->key) { t = t-> left; }
        else if (key < t->key) { t = t-> right; }
        else {
            //같은 경우

            //case1. 0개거나 1개인 자식
            if(!t->left) {Node* temp = t->right; delete t; return temp;}
            //이렇게 null 판단으로 한다 left가 비어있을 경우 right를 temp으로 옮기고 t 삭제 
            //(잊지 말것) 마지막에 꼭 temp return 해주기
            else if(!t->right) {Node* temp = t->left; delete t; return temp;}
            

            //case2. righttree의 min(successor) 찾기
            Node* succ = t->right; //right tree로 접속
            while(succ->left) succ = succ->left; //left 끝까지 내려감

            //(내가 틀린부분)
            t->key = succ->key; //t->key에 succ->key를 저장한다
            //그리고 succ 키를 delete 재귀로 보내버려서 삭제
            t->right = Delete(t->right,succ->key);
            //주의 할 것이 t->right에 있는 succ->key만 삭제하는 거라서 이렇게 재귀 보내는 거임 이걸 기억해야 해
            //t->right에 있는 succ->key

        }
        return t; //내가 틀린 부분 t 반환인거 잊지마라
    }

    //k번째 원소 찾기 (GetRank) //전형적인 중위순회로 inorder 하던거 똑같이 하면 됨
    void GetRank(Node* t, int k, int& count, Node*& result) {
        //중위순회 하기
        //t->받을 키, k->원하는 랭크, count 현재등수, result->result값

        if(!t || result != NULL) return;

        GetRank(t->left, k,count, result);

        count++;
        if(count == k){//count == k 인 조건이면 무조건 멈춤
            result = t;
            return;
        }

        GetRank(t->right, k,count, result);
    }
    
    //1등 ~ k등 출력하기 (PrintRank)
    void PrintRank(Node* t, int k, int& count) {

        if(!t || count >= k) { return; }

        PrintRank(t->left, k,count);

        if(count < k){//count < k에만 출력한다
            cout << t->key << " ";
            count++; //count++; 인거 꼭 기억하기
        }

        PrintRank(t->right, k,count);
        
    }

    Node* GetSuccessor(int key) {
        //내 자식들 중 가장 큰놈

        //Search에서 left 판별할 때 잠재적 succ로 규정하는 것만 넣어주면 됨
        Node* succ = NULL;
        Node* t = root;

        //그리고 마지막에 반환할 NULL까지

        while(t){
            if(key < t->key){
                succ = t; //잠재적 succ
                t = t->left;
            }else if (key > t->key){
                t = t->right;
            }else{
                //찾았을 경우

                //여기에서 right이 있을 경우 if(t->right) 여기에서의 succleft 찾으면 됨
                //당연히 right tree들어간 다음에 succ left 무한 내려가기

                if(t->right){
                    Node* temp = t->right; //위의 succ 대신 temp쓴것 뿐
                    while(temp->left) temp = temp->left;
                    succ = temp;
                }
                break; //이거 꼭 해라
            }
        }
        return succ;
    }
    
    Node* GetPredecessor(int key) {
        
        
    }

    
    Node* FindLCA_Iter(Node* root, int u, int v) {
        Node* t = root; //현재로 설정
        while(t){
            //1.두 값이 현재 노드보다 작으면 -> 왼쪽으로 이동
            if (t->key > u && t->key > v) {
                t = t->left;
            }
            //2.두 값이 현재 노드보다 크면 -> 오른쪽으로 이동
            else if (t->key < u && t->key < v) {
                t = t->right;
            }
            //3. 갈라질경우(하나는 작고 하나는 큼)이나 일치 --> 여기가 LCA
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
