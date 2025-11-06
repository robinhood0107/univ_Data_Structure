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

    int solvejosephus(vector<int> testData,int k);

    Node* GetNode();
    void RetNode(Node* x);
    void Erase();
};

    void Add(int element){
        Node* newNode = GetNode;
        //내가 빼먹은 부분!!!!
        newNode->data = element;

        Node* header = last;
        Node* q = header;
        Node* p = header->link;

        while(p != header && p->data < element){
            q = p;
            p = p->link;
        }
        //q->newNode->p
        q->link = newNode;
        newNode->link = p;
    }
    bool Delete(int element){
        Node* header = last;
        Node* q = header;
        Node* p = header->link;

        while(p != header){
            if(p->data == element){
                q->link = p->link;
                RetNode(p);
                return true;
            }else{
                q = p;
                p  = p->link;
            }
        }
    return false;
    }
    void Show(){
        Node* header = last;
        Node* current = header->link;

        if(current == header){
            return;
        }

        cout << "[";
        while(current != header){
            cout << current->data;
            current = current->link;
            if(current != header){
                cout << "->";
            }
        }
        cout << "]" << "\n";
    }
    bool Search(int element){
        Node* header = last;
        Node* current = header->link;

        while(current != header && current->data <= element){
            //내가 까먹은 부분
            //그냥 if로 같은거 찾으면 true만 출력해주면 됨
            if(current->data == element){
                return true;
            }
            current = current->link;
        }
    return false;
    }
    Circularlist operator+(const Circularlist& lb){
        Circularlist lc;

        Node* headerA = this->last;
        Node* headerB = lb->last;
        Node* headerC = lc->last;

        Node* pA = headerA->link;
        Node* pB = headerB->link;

        Node* q = headerC;

        while(pA != headerA && pB != headerB){
            Node* newNode = GetNode;

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

            //q->newNode->headerC로 만든 후에 q=newNode로 초기화
            q->link = newNode;
            newNode->link = headerC;
            q = newNode;
        }

        while(pA != headerA){
            Node* newNode = GetNode();
            newNode->data = pA->data;
            pA = pA->link;

            q->link = newNode;
            newNode->link = headerC;
            q = newNode;
        }

        while(pB != headerB){
            Node* newNode = GetNode();
            newNode->data = pB->data;
            pB = pB->link;

            q->link = newNode;
            newNode->link = headerC;
            q = newNode;
        }

    return lc;
    }

    int solvejosephus(vector<int> testData,int k){

        Node* header = last;
        Node* p = header;

        for(int i=0; i<testData.size()-1; i++){
            //p를 k-1까지 이동시킴
            for(int j=0; j<k-1; j++){
                p = p->link;

                if(p == header){
                    p = p->link;
                }
            }

            Node* q = p->link;

            if(q == header){
                p = p->link;
                q = q->link;
            }

            //삭제 수행
            // p-> q삭제 -> q->link
            p->link = q->link;
            RetNode(q);
        }

        Node* survivor = header->link;
        return survivor->data;
    }

    Node* GetNode(){Nd
        Node* x;
        if(av){
            x=av;
            av=av->link;
        }else{
            x = new Node;
        }
        return x;
    }
    void RetNode(Node* x){
        av=x;
        x->link=av;
        //x가 av의 last가 되도록
    }
    void Erase(){
        Node* header = last;
        Node* firstData = header->link;

        if(firstData == header){
            return;
        }

        Node* current = firstData;
        while(current != header){
            current = current->link;
        }

        current->link = av;
        av = firstData;

        header->link = header;
    }

    enum Menu{
        make_list,
        josephus,
        Exit
    };

    int main(){
        int selectMenu;

        do{
            switch(static_cast<Menu>(selectMenu)){
                case hello:

                case Exit:


            }

        }while(static_cast<Menu>()!= Exit);
        return 0;
    }
