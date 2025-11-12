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

//RetNode
// x->link = av
// av = x;

//이건 외우기

class Circularlist{
private:
    Node* last;
    static Node* av;
public:
    void Add(int element);
    bool Delete(int element)
    void Show()
    bool Search(int element);
    Circularlist operator+(const Circularlist& lb);

    int solvejosephus(vector<int> testData,int k);

    Node* GetNode();
    void RetNode(Node* x);
    void Erase();
};

    void Add(int element){
        Node* newNode = GetNode();
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
                p = p->link;
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

        cout<< "[";
        while(current != header){
            cout << current->data;
            current = current->link;
            if(current != header){
                cout << "->";
            }
        }
        cout<< "]"
    }

    bool Search(int element){
        Node* header = last;
        Node* current = header->link;

        while(current != header && current->data <= element){
            if(current == header){
                return true;
            }
            current = current->link;
        }

        return false;
    }

    Circularlist operator+(const Circularlist& lb){

    }

    int solvejosephus(vector<int> testData,int k){
        Node* header = last;
        Node* p = header;

        for(int i=0; i<testData.size(); i++){
            for(iint j=0; j<k-1; j++){
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

            //삭제 진행
            //p-> newNode -> q 구조인 상태임
            p->link = q->link;
            RetNode(q);
        }


    }

    Node* GetNode(){
        Node* x;
        if(av){
            x =av;
            av = av->link;
            //x에게 av를 주고 av는 오른쪽으로 한칸 이동
        }else{
            x = new Node;
        }
        return x;
    }
    void RetNode(Node* x){
        //이건 외워
        //av = x를 통해 x가 av의 last가 되게 한다 그리고 x->link는 av에 연결
        x->link = av;
        av = x;
    }
    void Erase();



    enum Menu{



    }

    Node* Circularlist::av = nullptr;

    int main(){
        int selectMenu;

        cin << selectMenu;
        do{
            switch(static_cast<Menu>(selectMenu)){
                case asdf:

                    break;


            }

        }while(static_cast<Menu>(selectMenu) != Exit);


    }
