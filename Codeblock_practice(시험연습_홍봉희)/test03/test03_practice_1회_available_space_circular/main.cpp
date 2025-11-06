//원형 링크드 리스트 available space

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Node{
private:
    friend class Circularlist;
    int data;
    Node* link;
public:
    Node(){}
    Node(int element){
        data = elenment;
        link = nullptr;
    }
};


class Circularlist{
private:
    Node* last;
    static Node* av;
public:
    //bool반환 2개 void 반환 2개 operator+ 1개
    void Add(int element);
    bool Delete(int element); //이거 반환 값 bool이다!!!!
    void Show();
    bool Search(int element); //이거 반환 값 bool이다!!!!
    Circularlist operator+(const Circularlist& lb);

    int solveJosephus(vector<int> testData,int K);

    Node* GetData();
    void RetNode(Node* x); //이거 파라미터로 Node*를 받는다.
    void Erase();
};

    Node* Circularlist::GetData(){
        //새로운 노드 만들고
        //av 비어있는지 아닌지로 판단
        Node* x;
        if(av){
            x = av;
            av = av->link;
            //내가 틀린 부분
            //그냥 쉽게 x에 av를 집어넣고 av는 오른쪽으로 1칸 !! 이라고 생각하기
        }else{
            x = new Node;
        }
        return x;
    }
    void Circularlist::RetNode(Node* x){
        x->link = av;
        //내가 틀린 지점 av=x;로 av가 반드시 x로 지정하게 해서 완벽하게 이어주기 이거 ㄴ좀 외워라
        av = x;
    }
    void Circularlist::Erase(){
        //그냥 완전히 기억이 안남
        //배껴쓰면서 암기 해보기

        Node* header = last;
        Node* firstData = header->link;

        if(firstData == header){
            return;
        }

        Node* current = firstData;
        while(current->link != header){ //current->link != header 이거 똑바로 외워라
            current = current->link;
        }

        //삭제 작업
        current->link = av;
        av = firstData;

        //헤더 원상 복구
        header->link = header;
    }


    void Circularlist::Add(int element){
        Node* newNode = GetNode;
        //내가 틀린 부분//newNode 만드든거 자체가 element 노드를 만드는 것임
        newNode->data = element;

        Node* header = last;
        Node* q = header;
        Node* p = header->link

        //일단 항상 삽입할 위치 이동
        while(p != header && p->data < element){ //p로만 조건 세우는거 잊지 마라 //p!=header && p->data < element
            q=p;
            p=p->link;
        }

        //내가 틀린부분
        //삽입해야지
        //q-> newnode -> p를 만들어 준다고 생각하라니까?
        q->link = newnode;
        newnode->link = p;
    }
    bool Circularlist::Delete(int element){
        Node* header = last;
        //내가 틀린 부분 delete는 add와 같은 맥락이다!!!
        Node* q = header;
        Node* p = header->link;

        //내가 틀린부분 p->data == element 이면 한칸건너뛰어 연결하고 해당 노드
        //아닐 경우는 q랑 p 둘 다 1칸씩 이동한다
        while(p != header){
            if(p->data == element){
                q->link = p->link;
                //내가 틀린 부분
                //무조건 RetNode() 해줘야 한다!!!!
                RetNode(p);
                return true;
            }else{
                q = p;
                p = p->link;
            }
        }
    return false;
    }



    void Circularlist::Show(){
        Node* header = last;
        Node* current = header->link;

        if(current == header){
            //빈 리스트이므로 그냥 종료
            return;
        }

        cout << "[";
        while(current != header){
            cout << current->data;
            current = current->link; //다음 노드로 이동
            if(current != header){
                cout << "->";
            }
        }
        cout << "]" << "\n";
    }



    bool Circularlist::Search(int element){
        Node* header = last;
        Node* current = header->link;

        while(current != header && current->data <= element){//여기 조건이 매우 중요함 current->data <= element로 element보다 작거나 같은 곳까지 이동하면 된다!!!
            if(current->data == element){
                //찾았으면 바로 true
                return true;
            }
            //내가 틀린 부분
            //아니면 바로 다음 노드로 이동
            current = current->link;
        }
    return false;
    }


    Circularlist Circularlist::operator+(const Circularlist& lb){
        Circularlist lc;

        //각각의 헤더 3개랑 순회용 포인터 2개 만든다고 생각
        Node* headerA = this->last;
        Node* headerB = lb->last;
        Node* headerC = lc->last;

        Node* pA = headerA->link; //pA는 현재 첫 데이터를 가리킴
        Node* pB = headerB->link;

        //꼬리 저장용
        Node* q = headerC;

        while(pA != headerA && pB != headerB){
            //내가 틀린 부분
            //일단 저장할 newNode 만들어야지
            Node* newnode = GetNode();

            //항상 작은 것을 newNode에 넣은 다음에 최종적으로 lc에 넣는다고 생각해라
            if(pA->data<pB->data){
                newNode->data = pA->data;
                pA = pA->link;
            }else if(pA->data>pB->data){
                newNode->data = pB->data;
                pB = pB->link;
            }else{
                newNode->data = pA->data;
                pA = pA->link;
                pB = pB->link;
            }

            //내가 틀린 부분
            //여기서 lc 꼬리인 q에 newNode 연결 시키기
            //q-> newNode -> header로 만든 다음 q를 다시 newNode로 갱신시켜 주면 된다
            //꼭 newNode로 갱신시켜야 함 newNode가 새로운 last이기 때문
            q->link = newNode;
            newNode->link = headerC;
            q = newNode;
        }

        //내가 틀린 부분
        //나머지 a 삽입 방법
        //pA != headerA동안 GetNode로 새로운 노드 만든 다음에 newData에 넣고 다음넘어간 후 위처럼 꼬리에 저장
        while(pA != headerA){
            Node* newNode = GetNode();
            newNode->data = pA->data;
            pA = pA->link;

            //q->newNode->headerC 만들기
            q->link = newNode;
            newNode->link = headerC;
            q = newNode;
        }

        while(pB != headerB){
            Node* newNode = GetNode();
            newNode->data = pB->data;
            pB = pB->link;

            //q->newNode->headerC 만들기
            q->link = newNode;
            newNode->link = headerC;
            q = newNode;
        }

        //제일 마지막에 최종 값 반환
    return lc;
    }

    int solveJosephus(vector<int> testData,int K){
        //내가 틀린 부분
        //여기 꼭 외워서 가라

        //먼저 초기화
        this->Erase();

        //testData 받아서 바로 리스트에 집어 넣기
        for(int i=0; i<testData.size(); i++){
            this->Add(testData[i]);
        }

        this->Show();


        //여기는 header=last랑 p=header가 필요
        Node* header = last;
        Node* p = header;

        //총 N명중 N-1을 삭제 하면 된다
        for(int i=0; i<testData.size()-1; i++){
            //p는 삭제할 대상인 k-1까지만 도착하면 되고
            //실제로 삭제할 대상은 p->link인 것으로 만들기
            for(int j=0; j<k-1; j++){
                p =p->link;
                //내가 틀린 부분
                //예외처리 p==header을 지나가는 경우는 한칸 더 올려라
                if(p == header){
                    p = p->link;
                }
            }

            Node* q = p->link;
            //실제로 삭제할 데이터인 q를 지정함

            //예외처리
            //q가 header라면 마찬가지고 한칸 더 올리기
            //대신 여기선 p도 함께 올려야 한다는 것 잊지말기
            if(q==header){
                q = q->link;
                p = p->link;
            }

            //삭제 실행
            p->link = q->link;
            RetNode(q);
        }

        Node* survivor = header->link;
        //최종 답은 마지막 link;
        cout << survivor->data << "\n";

        return survivor->data;
    }


    enum Menu{
        make_listA,  // 0 //이거 la에 바로 추가 될 수 있도록 하기
        make_listB, //1 //이거 lb에 바로 추가 될 수 있도록 하기
        Delete,   // 2
        Show,     // 3
        Search,   // 4
        Merge,    // 5
        Josephus, // 6
        Exit
    }

    Node* Circularlist::av = nullptr;

    int main(){
        int selectMenu;
        int num = 0;
        bool result = false;
        //이 버전은 testData 안쓰고 그냥 la, lb로 그냥 하는 것
        //메모리 더 빡빡하게 주어지면 길이 설정하고 clear()로 하나만 쓰셈

        CircularList la, lb, lc;
        int data = 0;

        //do while로 설정하기
        do{
            cout << "\n0.make_listA, 1.make_listB, 2.Delete, 3.Show, 4.Search, 5.Merge, 6.Josephus, 7.Exit 선택::";
            cin >> selectMenu;

            switch(static_cast<Menu>(selectMenu)){
                case make_listA:
                    cout << "데이터 입력A :\n";
                    cin.ignore();

                    string line;
                    getline(cin,line);
                    stringstream ss(line);

                    int number=0;
                    while(ss >> number){
                        la.Add(number);
                    }
                    break;
                case make_listB:
                    cout << "데이터 입력B :\n";
                    cin.ignore();

                    string line;
                    getline(cin,line);
                    stringstream ss(line);

                    int number=0;
                    while(ss >> number){
                        la.Add(number);
                    }
                    break;

                case Merge: // 5. 병합
                    lc = la + lb;
                    cout << "  리스트 lc = ";
                    lc.Show();
                    break;
                case Josephus:
                    int n, k;
                    n = testData.size();
                    cout << "  제거 간격 (K): ";
                    cin >> k;
                    if (n > 0 && k > 0) {
                        la.SolveJosephus(testData, k); //이거 돌리면 알아서 la가 나오게 된다
                        //아님 여기서 출력 시키던가
                    } else {
                        cout << " N과 K는 0보다 커야 합니다." << endl;
                    }
                    break;
            }



        }while

    }




