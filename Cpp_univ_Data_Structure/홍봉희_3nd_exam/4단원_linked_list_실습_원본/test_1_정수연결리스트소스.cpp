/*
* 1단계-정수 연결 리스트: 단순한 linked list에서 add, delete하는 알고리즘을 코딩
* template 버전으로 만들기 
*/
#include <iostream>
#include <time.h>
using namespace std;

class Node {
	friend class LinkedList;
	int data;
	Node* link;
public:
	Node(int element) {
		data = element;
		link = 0;
	}
};

class LinkedList {
	Node* first;
public:
	LinkedList() {
		first = 0;
	}
	bool Delete(int);
	void Show();
	void Add(int element);//정렬되도록 구현
	bool Search(int data);
	LinkedList& operator+(LinkedList&);
};
void LinkedList::Show() { // 전체 리스트를 순서대로 출력한다.
	Node* p = first;

}
void LinkedList::Add(int element) // 임의 값을 삽입할 때 리스트가 오름차순으로 정렬이 되도록 한다
{
	Node* newNode = new Node(element);

}
bool LinkedList::Search(int data) { // 전체 리스트를 순서대로 출력한다.
	Node* ptr = first;

}
bool LinkedList::Delete(int element) // delete the element
{
	Node* q, * current = first;
	q = current;

}
LinkedList& LinkedList::operator+(LinkedList& lb) {
	LinkedList lc;
	Node* a = first, * b = lb.first;

}
enum Enum {
	Add1, Add2, Delete, Show, Search, Merge, Exit
};
void main() {
	Enum menu; // 메뉴
	int selectMenu;
	int num = 0; bool result = false;
	srand(time(NULL));
	LinkedList la, lb, lc;
	int data = 0;
	do {
		cout << "0.ADD0, 1. Add1, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit 선택::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add1:
			data = rand() % 49;
			la.Add(data);
			break;
		case Add2:
			data = rand() % 49;
			lb.Add(data);
			break;
		case Delete:
			cin >> data;
			result = la.Delete(data);
			if (result)
				cout << "삭제 완료";
			break;
		case Show:
			cout << "리스트 la = ";
			la.Show();
			cout << "리스트 lb = ";
			lb.Show();
			break;
		case Search: // 회원 번호 검색
			int n; cin >> n;
			result = la.Search(n);
			if (!result)
				cout << "검색 값 = " << n << " 데이터가 없습니다.";
			else
				cout << "검색 값 = " << n << " 데이터가 존재합니다.";
			break;
		case Merge:
			lc = la + lb;
			cout << "리스트 lc = ";
			lc.Show();
			break;
		case Exit:
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}

