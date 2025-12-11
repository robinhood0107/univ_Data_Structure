#include <iostream>
#include <cstdlib> // rand
#include <ctime>   // time
#include <vector>
#include <string>

using namespace std;
//이 경우 상하 대소는 보장 못하는데 좌우 대소는 확실하게 보장함(그게 BST고 상하대소까지 보장하는게 HEAP구조이고 HEAP은 vector 사용해서 부모가 N이면 왼쪽자식은 (N) * 2, 오른쪽 자식은 (N) * 2 + 1)
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
        Node* p  = root;
        Node* q = NULL;
        //일단 시작할때는 root 설정
        //root는 p(현재)이고 부모(q)는 없으므로 null

        //q의 역할은 p의 부모노드를 기억하기 위한 것
        //이유: p가 NULL(삽입할 빈 자리)에 도달했을 때, 
        //새 노드를 연결하려면 부모(q)의 주소가 필요하기 때문입니다.

        while(p){ //위치를 찾는 루프이다!!!! (p가 NULL이 될 때까지(즉, 빈 자리를 찾을 때까지) 반복) (새로 만드는게 아니라 위치 찾는 while 문)
            q=p; // [핵심] p가 이동하기 전, 현재 위치를 q에 저장 (q가 부모가 됨)
            //q는 항상 p의 바로 뒤를 따라다닙니다.

            if (key == p->key){ return; } //새로 넣으려는 key가 p(현재)와 같을 경우 무시
            if (key < p->key){ p = p-> left; } //새로 넣으려는 key값이 p(현재)보다 작다면? --> left로
            else p = p-> right;
            //이 방식으로 p는 쭉쭉 아래로 트리를 타고 내려간다
        }

        //여기 오게 되면 p는 무조건 null을 가리키고 q는 p의 부모로 제일 마지막 leaf node인 상태!!!!
        //여기서 새로운 노드인 newNode를 삽입해 주면 된다

        Node* newNode = new Node(key);
        if(!root) root = newNode; //!root라는 것은 root가 null 즉, 트리에 진짜 아무것도 없다는 것으로 root에 newNode 하나 추가해준다
        else if (key < q->key) q->left = newNode;
        //중요 여기서 else if로 반드시 (q) 부모와 비교!! 새로운 값(key)가 부모보다 작으면 left 부모보다 크면 right
        else q->right = newNode;
    }
    
    //만약 main에서 for문으로 100번 집어 넣는게 아니라 이미 완성된 vector 난수 100개가 파라미터로 들어온다면?
    //함수오버로딩으로 해결 for문 범위기반 반복으로 insert 집어넣음
    void Insert(vector<int>& vec) {
        for(auto lt : vec){
            Insert(lt);
        }
    }

    // [조건 3] Search: 반복문 로직
    Node* Search(int key) {
        //이거 insert에서 사용했던 while(p)로 트리 타고 내려가는 방식이랑 완전히 같음
        Node* t = root; //현재값 t

        while(t){
            if(key == t->key){ return t; } //일단 key값과 t(현재) 같을경우 중복이므로 출력후 종료
            if(key < t->key){ t = t->left; } //t->key(현재)보다 작으면 left
            else t = t->right;
        }
        //이런식으로 while(t)를 돌리면 t가 null이 되어 버림(즉 트리내에 중복되는(Search)되는 값이 없다는 것)
        return NULL;
    }

    // Inorder 출력 (정렬 확인용) //중위 순회이다
    // 왼쪽 출력하고 나 출력하고 오른쪽 출력함
    void Inorder(Node* t) {
        if(t) {
            Inorder(t->left);
            cout << t->key << " ";
            Inorder(t->right);
        }
    }
    //이건 통채로 외워줘라
    /*
        //중위 순회 설명

        \*\*중위 순회(Inorder Traversal)\*\*는 이진 탐색 트리(BST)에서 **데이터를 오름차순(작은 수 → 큰 수)으로 정렬**해서 보여주는 마법 같은 순회 방법입니다.

        가장 쉽게 이해하는 핵심 공식은 \*\*"L - V - R"\*\*입니다.

        1.  **L (Left)**: 왼쪽 자식으로 먼저 간다.
        2.  **V (Visit)**: 나(현재 노드)를 출력한다.
        3.  **R (Right)**: 오른쪽 자식으로 간다.

        이 순서가 \*\*재귀적(계속 반복)\*\*으로 적용됩니다.

        -----

        ### 1\. 그림으로 보는 순서

        위 그림을 보면서 따라가 보세요. 로직은 다음과 같습니다.

        1.  **"무조건 왼쪽 끝까지 파고 들어갑니다."** (작은 수가 왼쪽에 있으니까요)
        2.  더 이상 왼쪽이 없으면 **그때서야 숫자를 출력**합니다.
        3.  출력했으면 **오른쪽**에 자식이 있는지 봅니다. 있다면 거기로 가서 다시 1번(왼쪽 파기)을 반복합니다.

       
        -----

        ### 2\. 우리가 순회할 트리 (Level 2)

        ```text
            [50]       <-- Level 0 (루트)
            /    \
        (20)    (80)   <-- Level 1 (자식)
        /  \    /  \
        (10)(30)(70)(90) <-- Level 2 (손자)
        ```

        **규칙:** 무조건 \*\*왼쪽(L)\*\*을 다 털어야 \*\*나(V)\*\*를 출력하고, 그래야 \*\*오른쪽(R)\*\*으로 갈 수 있다.

        -----

        ### 3\. 시뮬레이션 시작 (따라오세요)

        **1단계: 50번 노드 (대장)**

        * 나(50) 찍을 수 있나요? **아니요\!**
        * 왼쪽 자식(20)이 있잖아요. **20한테 가\! (L)**

        **2단계: 20번 노드**

        * 나(20) 찍을 수 있나요? **아니요\!**
        * 왼쪽 자식(10)이 또 있잖아요. **10한테 가\! (L)**

        **3단계: 10번 노드 (왼쪽 끝)**

        * 나(10) 찍을 수 있나요? 잠시만요... 왼쪽 자식 있나요? **없음(NULL).**
        * **드디어 출력\! `[10]`** (V)
        * 이제 오른쪽 자식 있나요? **없음(NULL).**
        * 할 일 끝\! **부모(20)에게 복귀.**

        **4단계: 다시 20번 노드**

        * 아까 왼쪽(10)은 처리하고 왔죠?
        * 이제 **나(20)를 출력\! `[20]`** (V)
        * 이제 오른쪽 자식(30) 처리하러 **30한테 가\! (R)**

        **5단계: 30번 노드**

        * 왼쪽 있나요? 없음.
        * **나(30) 출력\! `[30]`** (V)
        * 오른쪽 있나요? 없음.
        * 할 일 끝\! **부모(20)에게 복귀.**

        **(중간 점검)**: 20번 노드도 왼쪽(10), 나(20), 오른쪽(30) 다 끝났으니 **더 위의 부모(50)에게 복귀.**

        **6단계: 다시 50번 노드**

        * 아까 왼쪽 덩어리(20네 가족)는 싹 다 끝났죠?
        * 드디어 **나(50)를 출력\! `[50]`** (V)
        * 이제 오른쪽 덩어리(80네 가족) 처리하러 **80한테 가\! (R)**

        **7단계: 80번 노드**

        * 나(80) 바로 찍나요? **아니요\!** 왼쪽(70) 있잖아요.
        * **70한테 가\! (L)**

        **8단계: 70번 노드**

        * 왼쪽 없음 -\> **나(70) 출력\! `[70]`** -\> 오른쪽 없음.
        * 끝. **부모(80)에게 복귀.**

        **9단계: 다시 80번 노드**

        * 왼쪽(70) 끝남.
        * **나(80) 출력\! `[80]`**
        * 오른쪽(90) 남음. **90한테 가\! (R)**

        **10단계: 90번 노드**

        * 왼쪽 없음 -\> **나(90) 출력\! `[90]`** -\> 오른쪽 없음.
        * 끝.

        -----

        ### 4\. 최종 결과

        순서대로 찍힌 걸 볼까요?

        `10` -\> `20` -\> `30` -\> `50` -\> `70` -\> `80` -\> `90`

        보시다시피 **작은 수부터 큰 수까지 완벽하게 정렬**되어 나옵니다.

        **암기 요령:**
        트리를 **왼쪽 벽에 대고 찌부러뜨려서** 바닥에 떨어지는 순서라고 생각하면 편합니다. (제일 왼쪽 10부터 툭, 툭, 툭 떨어짐)

        ### 5\. 코드와 매칭 (이게 중요\!)

        작성하신 코드를 한 줄씩 해석하면 이렇습니다.

        ```cpp
        void Inorder(Node* t) {
            if (t) {
                // 1. 야, 일단 내 왼팔(작은 애들) 싹 다 처리하고 와. (재귀)
                Inorder(t->left);        

                // 2. 왼쪽 애들 다 왔어? 그럼 이제 나(중간) 줄 서볼게. (출력)
                cout << t->key << " ";   

                // 3. 이제 내 오른팔(큰 애들) 처리하러 가. (재귀)
                Inorder(t->right);       
            }
        }
        ```

        ### 요약

        * **중위 순회 = 왼쪽 훑고 -\> 나 찍고 -\> 오른쪽 훑기.**
        * BST에서는 왼쪽이 제일 작고, 오른쪽이 제일 크기 때문에 이 순서대로 돌면 **자동으로 정렬**이 됩니다.
    
    */

    // [추가] 트리의 X (Height)
    int Height(Node* t) { //후위순회로 이진트리 높이 구하기
        if (!t) return 0; // null 일 경우에는 return 0;로 종료한다 (재귀이기 때문에 null일 경우 종료 조건이 아주 명확해야 한다)
        
        //왼쪽 자식과 오른쪽 자식으로 재귀 호출을 보내 바닥부터 높이를 구해옵니다.
        int l = Height(t->left);  //이렇게 재귀로 null까지 left를 보내버려서 축적된 return 값 l에 저장
        int r = Height(t->right); //이렇게 재귀로 null까지 right를 보내버려서 축적된 return 값 r에 저장
        
        //1+max(l,r)를 쓰던가 아님 삼위연산자 쓰던가로 둘중 큰거 고르기
        return 1+ (l > r ? l : r);
    }

    // [조건 4] Delete: Inorder Successor를 이용한 삭제 (재귀가 가장 간결함)
    Node* Delete(Node* t, int key) {
        if (!t) return NULL; //t값이 null 값이면 바로 종료 //삭제할 것이 없으니까

        //1.삭제할 노드 찾기
        if (key < t->key) t->left = Delete(t->left,key);//key값이 작을경우(검색 실패시, Delete로 다시 보내버림)
        else if (key > t->key) t->right = Delete(t->right,key);//key값이 클경우(검색 실패시, Delete로 다시 보내버림)
        else {
            //정확하게 딱 맞을 경우

            //삭제 수행
            //Case 1: 자식이 0개이거나 1개일 경우 --> 0개이면 그냥 삭제하면 되고, 
            //1개일 경우에도 Successor(후속자, 나 다음으로 큰 숫자(자식))이 딱 1개가 되어 버리니까 이걸 그냥 올려버리면 됨
            if(!t->left){Node* temp = t->right; delete t; return temp;}
            //left가 없는 경우에는 right(자식)1개밖에 없는 상황-->Successor니까 temp에 잠깐 저장하고 t를 아얘 삭제시킴 
            else if (!t->right) {Node* temp = t->left; delete t; return temp;}
            //이 경우는 right이 없는 경우 //혹시 모르니 else if로 범위 좁히기

            // Case 2: 자식이 2개 -> Right Subtree의 Min(Successor) 찾기
            //Successor를 둘중 골라야 되는데 근데 이건 BST라서 무조건 right가 무조건 크다!!!!(이거 무조건임)
            //현재 삭제하려는게 t인 상태 --> t의 오른쪽 트리의 가장 작은값인(left)를 찾아 내려간다
            //즉 right tree의 min값(Successor) 찾기
            Node* succ = t->right;
            while (succ->left) succ = succ->left;

            //찾았으면 그걸 t로 교체해버린다!!!
            //그리고 사용한 succ 재귀로 보내버려서 지워버리기
            t->key = succ->key;
            t->right = Delete(t->right,succ->key);
            //이게 재귀로 삭제가 되는 이유가 succ는 무조건 자식이 없기 때문에 delete에서 //Case 1: 자식이 0개이거나 1개일 경우 --> 0개이면 그냥 삭제하면 되고 여기에 걸려서 바로 삭제되어 버림 if(!t->left){Node* temp = t->right; delete t; return temp;}
            //원래 Successor 삭제: 이제 트리에 똑같은 값이 2개가 되었습니다(위쪽 t와 아래쪽 succ). 진짜 succ 노드는 필요 없으니 재귀 호출로 삭제해 버립니다.
            //참고: Successor는 "왼쪽 끝"에 있는 놈이라 왼쪽 자식이 절대 없습니다. 그래서 상황 A 로직에 의해 아주 쉽게 삭제됩니다.
        }
        return t;
    }

    /*
    왜 tightTree의 succ->left를 찾아 들어가는지 설명
    아니요, 절대 그렇지 않습니다\! 오히려 \*\*Successor야말로 왼쪽 자식들보다는 크고, 오른쪽 자식들보다는 작은 "딱 중간값"\*\*이기 때문에 선택된 것입니다.
    질문하신 \*\*"너무 작은 값이 되는 것 아니냐?"\*\*는 걱정을 해결하기 위해, 실제 숫자를 넣은 트리를 그려서 **왜 Successor가 완벽한 대타인지** 보여드릴게요.

    -----
    ### 상황: 루트 노드 `50`을 삭제하려고 합니다.

    아래와 같은 트리가 있다고 칩시다.

    ```text
            [50]  <-- 삭제 대상 (부모)
            /    \
        (20)    (70)
                /  \
            (60)  (80)
            /
        [55] <-- 얘가 바로 Successor!
    ```

    * **왼쪽 서브트리 (20)**: 50보다 작은 애들의 왕국입니다.
    * **오른쪽 서브트리 (70, 60, 80, 55)**: 50보다 큰 애들의 왕국입니다.

    ### 1\. 왜 55가 Successor(대타)인가?

    코드 로직: `succ = t->right; while(succ->left) succ = succ->left;`

    1.  **오른쪽으로 간다 (70):** 일단 50보다는 큰 쪽으로 왔습니다. (즉, 왼쪽 왕국 `20`보다는 무조건 큽니다.)
    2.  **왼쪽 끝까지 간다 (60 -\> 55):** 오른쪽 왕국 안에서는 가장 작은 값을 찾습니다.

    결과적으로 **55**가 선택됩니다.

    ### 2\. "55가 너무 작지 않나요?" (검증)

    이제 50 자리에 55를 앉혀봅시다.

    ```text
            [55]  <-- 50 자리에 55가 옴 (값 복사)
           /    \
        (20)    (70)
               /  \
            (60)  (80)
            /
        (x)  <-- 원래 55는 삭제됨
    ```

    이 트리가 \*\*BST 규칙(왼쪽 \< 부모 \< 오른쪽)\*\*을 어기는지 볼까요?

    1.  **왼쪽이랑 비교:**

        * 새 주인 `55` vs 왼쪽 자식 `20`
        * **55 \> 20** (통과\!).
        * **이유:** Successor는 애초에 **오른쪽 서브트리 출신**입니다. 오른쪽 동네에서 아무리 쭈구리(가장 작은 값)라도, 왼쪽 동네 대장보다는 무조건 큽니다.

    2.  **오른쪽이랑 비교:**

        * 새 주인 `55` vs 오른쪽 자식 `70` (그리고 그 밑에 `60`)
        * **55 \< 70** (통과\!).
        * **이유:** Successor는 오른쪽 동네에서 \*\*"가장 작은 놈"\*\*을 뽑아왔기 때문입니다. 55를 위로 올리면, 나머지 오른쪽 애들(60, 70, 80)은 다 55보다 큽니다.

    ### 결론: Successor는 "황금 밸런스"입니다.

    질문하신 것처럼 \*\*"너무 작은 값"\*\*이 되는 게 아니라,
    **"오른쪽 놈들 중에선 제일 작아서 위로 올려도 밑에 놈들이 불만이 없고,**
    **태생이 오른쪽이라 왼쪽 놈들보다는 무조건 큰"**
    유일한 숫자가 바로 Successor입니다.

    그래서 족보가 꼬이지 않고 완벽하게 삭제가 가능한 것입니다. 이해가 되셨나요?
    */

    // [조건 5] Successor: Root부터 탐색 (부모 포인터 없음)
    Node* GetSuccessor(int key) {
        //내 자식들 중에서 나 다음으로 큰놈 찾기
        Node* succ = NULL;
        Node* t = root; //현재

        //마찬가지로 while(t)로 내려가는데, 행동이 좀 다름 //left의 경우 작으므로 잠재적 succ로 계속 설정하면서 내려감
        while (t) {
            if(key < t->key){
                succ = t; //일단 잠재적 succ로 지정
                t = t->left; //트리 아래로 내려가기
            } else if (key > t->key){
                t = t->right;
            } else { 
                //target 찾음 key와 같은걸 찾았다는 것
                //여기도 마찬가지로 righttree의 min(successor)를 찾아 계속 succ->left를 찾아 들어가면 된다
                //단지 여기 succ를 쓰고 있으니까 temp로 바꿔서 쓰자
                if(t->right){ //만약 오른쪽 자식이 있다면 그 중 최솟값이 succ이 되는 것임
                //if(t->right) 이것만 좀 제대로 외워두면 된다.
                    Node* temp = t->right; //일단 right tree로 들어간다
                    while(temp->left) temp = temp->left;
                    succ = temp;
                }
                break; //break 꼭 하는거 잊지말기
            }
        }
        return succ;
        //최종 succ 출력 //꼭 해주기
    }
    
    // Predecessor: 논리는 Successor와 반대
    Node* GetPredecessor(int key) {
        //나보다 작은 애들 중에서, 가장 큰 놈
        //정확하게 Successor랑 반대로 해주면 된다
        Node* pred = NULL;
        Node* t = root;

        while(t){
            if(key < t->key) t=t->left;
            else if(key > t->key){
                pred = t; //잠재적 pred
                t=t->right; 
            } 
            else{
                if(t->left){
                    Node* temp = t->left;
                    while(temp->right) temp = temp->right;
                    pred = temp;
                }
                break; //break 꼭 하는거 잊지말기
            }
        }
        return pred;
    }

    //k번째 원소 찾기 (GetRank) //전형적인 중위순회로 inorder 하던거 똑같이 하면 됨
    void GetRank(Node* t, int k, int& count, Node*& result) {
        //t는 현재 찾는 원소, k는 찾는 등수, count는 현재 등수, result는 결과 포인터
        
        if(!t || result != NULL ) return;
        //노드가 없거나, result를 찾았을 시 종료
        
        GetRank(t->left,k,count,result); //왼쪽 파기

        count++;
        if(count == k){
            result = t;
            return; //찾았으면 바로 종료
        }

        GetRank(t->right,k,count,result); //오른쪽 파기
    }
    
    //1등 ~ k등 출력하기 (PrintRank)
    void PrintRank(Node* t, int k, int& count) {
        //출력도 마찬가지로 GetRank처럼 하면 됨
        //대신 여기는 result필요 없음 처음부터 전부 순회하면 되니까

        // 1. 노드가 없거나, 이미 k개를 다 출력했으면 그만함
        if (!t || count >= k) return;
        //대신 여기서 종료조건은 count >= k 로 k전부 출력했으면 그만

        PrintRank(t->left, k, count);

        // V (방문 - 출력하기)
        if (count < k) { // 아직 k개를 다 못 채웠으면
            cout << t->key << " ";
            count++; // 출력했으니 카운트 증가
        }

        // R (오른쪽)
        PrintRank(t->right, k, count);
    }

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