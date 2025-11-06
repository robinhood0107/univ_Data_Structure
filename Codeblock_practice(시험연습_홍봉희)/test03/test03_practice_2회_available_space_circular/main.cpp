#include <iostream>


using namespace std;



class Node{
private:
    friend class Circularlist;
    int data;
    Node* link;
public:
    Node(){}
    Node(int element){
        data = element;
        link = nullptr;
    }
};

class Circularlist{
private:
    Node* last;
    static Node* av;
public:
    void Add(int element);
    bool Delete(int element);
    void Show();
    bool Search(int element);
    Circularlist operator+(const Circularlist& lb);

    int SolveJosephus(vector<int> testData,int k);

    Node* GetNode();
    void RetNode(Node* x);
    void Erase();
};

//빈 리스트 return;은 순회하는 것들만 해주면 됨



    Node* Circularlist::GetNode(){
        Node* x;
        if(av){
            //x를 av로 설정하고 한칸씩 이동
            x = av
            av = av->link;
        }else{
            x = new Node;
        }
        return x;
    }
    void Circularlist::RetNode(Node* x){
        av = x;
        x->link = av;
        //av = x; x->link=av 이건 외워주자!!
    }



    void Circularlist::Add(int element){
        Node* newNode = GetNode();
        newNode->data = element;

        Node* header = last;
        Node* q = header;
        Node* p = header->link;

        while(p != header && p->data < element){
            q = p;
            p = p->link;
        }

        //q-> newNode -> p
        q->link = newNode;
        newNode->link = p;
    }
    bool Circularlist::Delete(int element){
        //delete도 마찬가지로 add처럼 header,q,p 준비한다
        Node* header = last;
        //내가 틀린 부분
        Node* q = header;
        Node* p = header->link;

        while(p != header){
            if(p->data == element){
            //내가 틀린 부분
                q->link = p->link;
                RetNode(p);
                return true;
            }else{
                q = p;
                p = p->link;
                //각각 한칸씩 이동시키기
            }
        }
    return false;
    }
    void Circularlist::Show(){
        Node* header = last;
        Node* current = header->link;

        if(current == header){
            return;
        }

        cout << "[";
        while(current != header){
            cout << current->data;
            //내가 잊어먹은 부분 //꼭 다음으로 넘어가야지!!!!
            current = current->link;
            if(current != header){
                cout << "->";
            }
        }
        cout << "]";
    }
    bool Circularlist::Search(int element){
        Node* header = last;
        Node* current = header->link;

        //search는 if 필요없음
        while(current != header && current->data <= element){
            if(current->data == element){
                return true;
            }
            current = current->data;
        }
    return false;
    }

    Circularlist Circularlist::operator+(const Circularlist& lb){
        Circularlist lc;

        Node* headerA = this->last;
        Node* headerB = la.last;
        Node* headerC = lb.last;

        Node* pA = headerA->link;
        Node* pB = headerB->link;

        Node* q = headerC;

        while(pA != headerA && pB != headerB){
            Node* newNode = GetNode();

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

            //내가 잊어 먹은 것
            //꼬리에 무조건 추가 해줘야지
            //q-> newNode -> headerC 해준 다음에 q=newNode로 초기화
            q->link = newNode;
            newNode->link = headerC;
            q = newNode;
            }

        while(pA != header){
        //내가 잊어먹은 부분!!!
        //반드시 여기서 newNode 새로운 노드를 하나 만들어야함!!!
            Node* newNode = GetNode();
            newNode->data = pA->data
            pA = pA->link;

            q->link = newNode;
            newNode->link = headerC;
            q = newNode;
        }

        while(pB!= header){
        //내가 잊어먹은 부분!!!
        //반드시 여기서 newNode 새로운 노드를 하나 만들어야함!!!
            Node* newNode = GetNode();
            newNode->data = pB>data
            pB= pB>link;

            q->link = newNode;
            newNode->link = headerC;
            q = newNode;
        }

    return lc;
    }

    int SolveJosephus(vector<int> testData,int k){
        this->Erase();

        for (int i = 0; i < testData.size(); i++) {
            this->Add(testData[i]);
        }

        //요세푸스는 header = last p=header로 설정
        Node* header = last;
        Node* p = header;

        for(int i=0; i<testData.size()-1; i++){
            for(int i=0; i<k-1; i++){
                p = p->link;

                if(p==header){
                    p = p->link;
                }
            }

            Node* q = p->link;

            if(q==header){
                q = q->link;
                p = p->link;
            }

            //q를 삭제하는 코드
            p->link = q->link;
            RetNode(q);
        }

    Node* survivior = header->link;
    return survivior->data;
    }

    //Erase 없어도 문제 없으므로 마지막에 필요하면 구현하기
    void Circularlist::Erase(){
        Node* header = last;
        Node* firstData = header->link;

        if(firstData == header){
            return;
        }

        Node* current = firstData;
        //current를 last까지만 이동시킴
        while(current != header){
            current = current->link;
        }

        //내가 잊어먹은 부분
        //현재 header이자 last인 current->link를 전부 av로 붙여넣어 주기
        current->link = av;
        av = firstData;


        //초기화
        header->link = header;
    }

