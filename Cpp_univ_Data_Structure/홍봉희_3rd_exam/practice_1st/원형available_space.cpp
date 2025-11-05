#include <iostream>
#include <vector>
using namespace std;

class Node{
    friend class CircularList;
    int data;
    Node* link;
public:
    Node(){}
    Node(int element){
        data = element;
        link = nullptr;
    }
};

class CircularList{
private:
    Node* last; //last가 리스트의 header 노드를 가킨다고 생각해라 //데이터 비어있으면 last->link = last
    static Node* av;
public:
    CircularList(){
        last = new Node();
        last -> link = last;
    }
    void Add(int element);
    bool Delete(int element);
    void Show();
    bool Search(int element);
    CircularList operator+(const CircularList& lb);

    int SolveJosephus(vector<int> &testData, int K);

    Node* GetNode(); //새 노드 할당(av에서 가져오거나 new Node)
    void RetNode(Node*);
    void Erase();
};