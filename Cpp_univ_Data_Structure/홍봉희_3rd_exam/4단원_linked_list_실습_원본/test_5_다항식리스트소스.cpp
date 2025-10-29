/*다항식 리스트: Polynomial Linked List
//지수는 정수 0<= 지수 <= 5, 난수로 생성한다
//계수는 double로 난수 생성한다.  -9.0 < 계수 < 9.0
- 지수 내림 차순으로 정렬한다.
- c = a.Add(b) 구현한다.
- singly linked list, circular linked list, circular linked list with head node
*/
#include <iostream>
#include<string>
#include <assert.h>
using namespace std;

template<class T> class Term {
public:
	//All members of Term are public by default
	T coef; //coefficient
	int exp; //exponent
	Term() { coef = 0; exp = 0; }
	Term(T c, T e) :coef(c), exp(e) { }
	Term Set(int c, int e) { coef = c; exp = e; return *this; };
};

template<class T> class Chain; //forward declaration
template<class T> class ChainIterator;

template<class T>
class ChainNode {
	friend class Chain<T>;
	friend class ChainIterator<T>;
public:
	ChainNode() { }
	ChainNode(const T&);
private:
	T data;
	ChainNode<T>* link;
};

template<class T> class Chain {
public:
	Chain() { first = 0; };
	void Delete(void); //delete the first element after first
	int Length();
	void Add(const T& element); //add a new node after first
	void Invert();
	void Concatenate(Chain<T> b);
	void InsertBack(const T& element);
	void displayAll();

	ChainIterator<T> begin() const { return ChainIterator<T>(first); }
	ChainIterator<T> end() const { return ChainIterator<T>(nullptr); }
private:
	ChainNode<T>* first;
};

template<class T> class ChainIterator {
private:
	//const Chain<T>* list; //refers to an existing list
	ChainNode<T>* current; //points to a node in list
public:
	//ChainIterator<T>(const Chain<T> &l) :Chain(l), current(l.first) { };
	ChainIterator() { }
	ChainIterator(ChainNode<T>* node) :current(node) { }
	//dereferencing operators
	T& operator *() const { return current->data; }
	T* operator->()const { return &current->data; }
	bool operator && (ChainIterator<T> iter)const {
		return current != NULL && iter.current != NULL;
	}
	bool isEmpty() const { return current == NULL; }
	//increment
	ChainIterator& operator ++(); //preincrement
	ChainIterator<T> operator ++(int); //post increment
	bool NotNull(); //check the current element in list is non-null
	bool NextNotNull(); //check the next element in list is non-null
	//T* First( ) { //return a pointer to the first element of list
	//	if (list->first) return &list->first->data;
	//	else return 0;
	//}
	T* Next();//return a pointer to the next element of list
};

/*
class Polynomial
*/
template<class T> class Polynomial {
public:
	Polynomial() { }
	Polynomial(Chain<Term<T> >* terms) :poly(terms) { }
	Polynomial<T> operator+(const Polynomial<T>& b) const;
	void add(T coef, T exponent);
	void addAll(Polynomial<T>* poly);
	void display();
	/*
	T Evaluate(T&) const;//f(x)에 대하여 x에 대한 값을 구한다
	polynomial<T> Multiply(Polynomial<T>&); //f(x) * g(x)
	Polynomial(const Polynomial& p); //copy constructor
	friend istream& operator>>(istream&, Polynomial&);//polynomial 입력
	friend ostream& operator<<(ostream&, Polynomial&);//polynomial 출력
	const Polynomial& operator=(const Polynomial&) const;
	~Polynomial( );
	Polynomial operator-(const Polynomial&)const;
	*/
private:
	Chain<Term<T> > poly;
};

template <typename valType>
inline ostream& operator<< (ostream& os, const Term<valType>& term) {

}

template <class T>
ChainNode<T>::ChainNode(const T& element) {

}

template <class T>
void Chain<T>::Delete(void) //delete the first element after first
{

}

template <class T>
void Chain<T>::Add(const T& element) //add a new node after first
{

}

template <class T>
void Chain<T>::Invert() {
	ChainNode<T>* p = first, * q = 0; //q trails p
	while (p) {
		ChainNode<T>* r = q; q = p; //r trails q
		p = p->link; //p moves to next node
		q->link = r; //link q to preceding node
	}
	first = q;
}

template <class T>
void Chain<T>::Concatenate(Chain<T> b) {
	if (!first) { first = b.first; return; }
	if (b.first) {
		for (ChainNode<T>* p = first; p->link; p = p->link) {
			p->link = b.first;
		}
	}
}

template <class T>
void Chain<T>::InsertBack(const T& element) {
	ChainNode<T>* newnode = new ChainNode<T>(element);
	if (!first) //insert into empty list
	{
		first = newnode;
		return;
	}
	ChainNode<T>* curr = first;
	while (curr->link != NULL) {
		curr = curr->link;
	}
	curr->link = newnode;
}

template <class T>
void Chain<T>::displayAll() {

}

template <class T>
ChainIterator<T>& ChainIterator<T>::operator ++() //preincrement
{

}

template <class T>
ChainIterator<T> ChainIterator<T>::operator ++(int) //post increment
{

}

template <class T>
bool ChainIterator<T>::NotNull() { //check the current element in list is non-null

}

template <class T>
bool ChainIterator<T>::NextNotNull() { //check the next element in list is non-null

}

template <class T>
T* ChainIterator<T>::Next() {//return a pointer to the next element of list

}

template<class T>
void Polynomial<T>::add(T coef, T exponent) {
	Term<T>* newTerm = new Term<T>(coef, exponent);
	this->poly.Add(*newTerm);
}

template<class T> void Polynomial<T>::addAll(Polynomial<T>* b) {
	ChainIterator<Term<T>> iterB = b->poly.begin();

	while (iterB.NotNull()) {
		Term<T> dataB = *iterB;
		add(dataB.coef, dataB.exp);
		iterB.Next();
	}
}

template<class T> void Polynomial<T>::display() {
	poly.displayAll();
	cout << endl;
}

template<class T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& b) const {
	Term<T> temp;
	ChainIterator<Term<T>> ai = poly.begin(), bi = b.poly.begin();
	Polynomial<T> c;


}


int main(void) {

	Polynomial<int> a, b, sum;

	char select;
	Term<int>* tempTerm;
	ChainNode<Term<int>> cn;
	Chain<Term<int>> ca, cb;
	ChainIterator<Term<int>> iter;
	int c, e;

	cout << endl << "명령 선택: a: Add_a, b: Add_b, p: a + b, d: DisplayAll, q: exit" << endl;
	cin >> select;
	while (select != 'q')
	{
		switch (select)
		{
		case 'a':
			cout << "리스트 a의 항 입력 : " << endl;
			cout << "정수 coef: ";
			cin >> c;
			cout << "정수(내림차순) exp: ";
			cin >> e;
			a.add(c, e);//지수를 임의 숫자로 입력하여도 지수 내림 차순으로 정렬
			break;
		case 'b':
			cout << "리스트 b의 항 입력: " << endl;
			cout << "정수 coef: ";
			cin >> c;
			cout << "정수(내림차순) exp: ";
			cin >> e;
			b.add(c, e);
			break;
		case 'p': //a+b
			cout << "a+b: ";
			//a.addAll(&b);
			a.display();
			b.display();
			sum = a + b;
			sum.display();
			//cout << sum;
			break;
		case 'd':
			cout << "display all: " << endl;
			a.display();
			b.display();
			break;
		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
		}
		cout << endl << "Select command: a: Add_a, b: Add_b, p: Plus, d: DisplayAll, q: exit" << endl;
		cin >> select;
	}
	system("pause");
	return 0;
}