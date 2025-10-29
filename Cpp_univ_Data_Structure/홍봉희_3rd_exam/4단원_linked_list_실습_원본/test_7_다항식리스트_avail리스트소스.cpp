/*
* 단계7 : 다항식 연결리스트: Available Linked List
* circular list를 사용한 version, available list를 사용한 구현
* template 버전 구현 
*/

#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

class CircularList;
class CircularListIterator;

class Term {
public:
	//All members of Term are public by default
	int coef; //coefficient
	int exp; //exponent
	Term() { coef = 0; exp = 0; }
	Term(int c, int e) :coef(c), exp(e) { }

	void NewTerm(float coef, int exp) {
		this->coef = coef; this->exp = exp;
	}
	template <class T>
	friend ostream& operator<<(ostream& os, Term& e);
};

template<class T>
ostream& operator<<(ostream& os, Term& e)
{
	os << e.coef << "X**" << e.exp;
	return os;
}

template 
class ListNode {
	friend class CircularList<Type>;
	friend class CircularListIterator<Type>;
private:
	Type data;
	ListNode<Type>* link;
public:
	ListNode(Type);
	ListNode();
	template 
	friend ostream& operator<<(ostream&, ListNode<Type>&);
};
template 
ostream& operator<<(ostream& os, ListNode<Type>& ln) {
	os << ln.data
		return os;;
}
template 
ListNode<Type>::ListNode(Type Default)
{
	data = Default;
	link = 0;
}
template 
ListNode<Type>::ListNode()
{
	data = *new Type;
	link = 0;
}

template 
class CircularList {
	friend class CircularListIterator<Type>;
public:
	CircularList() { last = new ListNode<Type>; last->link = last; };
	CircularList(const CircularList&);
	~CircularList();
	void Attach(Type);
	ListNode<Type>* GetNode();
	void RetNode(ListNode<Type>*);
	void Erase();
	template 
	friend ostream& operator<<(ostream& os, CircularList<Type>& cl);
private:
	ListNode<Type>* last;
	static ListNode<Type>* av;
};

template 
ListNode<Type>* CircularList<Type>::av = 0;//static 사용시 초기화 방법
//ListNode<Term> CircularList<Term>::av = 0;//오류 발생

template 
class CircularListIterator {
public:
	CircularListIterator(const CircularList<Type>& l) : list(l) { current = l.last->link; }
	Type* Next();
	Type* First();
	bool NotNull();
	bool NextNotNull();
private:
	const CircularList<Type>& list;
	ListNode<Type>* current;
};

template 
Type* CircularListIterator<Type>::First() {
	if (current->link != list.last->link) {
		current = current->link;
		return &current->data;
	}
	else return 0;
}

template 
Type* CircularListIterator<Type>::Next() {
	current = current->link;
	if (current != list.last->link) return &current->data;
	else return 0;
}

template 
bool CircularListIterator<Type>::NotNull()
{
	//if (current == nullptr)
	//	return false;
	if (current->link != list.last->link) return true;
	else return false;
}

template 
bool CircularListIterator<Type>::NextNotNull()
{
	if (current != list.last->link) return true;
	else return false;
}


template 
CircularList<Type>::CircularList(const CircularList<Type>& l)
{
	if (l.last->link == l.last) { last = new ListNode<Type>; return; }
	ListNode<Type>* first = l.last->link;

	ListNode<Type>* p = new ListNode<Type>;//head node
	p->link = p;
	last = p;
	for (ListNode<Type>* current = first->link; current != first; current = current->link)
	{
		ListNode<Tye>* temp = new ListNode<Type>(current->data);
		p->link = temp; p = temp;
	}
	p->link = last;
	last = p;
}

template 
CircularList<Type>::~CircularList()
{
	if (last)
	{
		ListNode<Type>* tmp = last->link;
		last->link = av;
		av = tmp;
	}
}
template 
ostream& operator<<(ostream& os, CircularList<Type>& l)
{
	cout << "원형 리스트 출력  " << endl;
	CircularListIterator<Type> li(l);
	if (!li.NotNull()) return os;
	os << *li.First();
	while (li.NotNull())
		os << " + " << *li.Next();
	os << endl;
	return os;
}

template 
void CircularList<Type>::Attach(Type k)
{
	ListNode<Type>* p = last;
	ListNode<Type>* newnode = new ListNode<Type>(k);
	if (p->link == last) {
		p->link = newnode;
		newnode->link = last;
		last = newnode;
	}
	else {
		newnode->link = last->link;
		last->link = newnode;
		last = newnode;
	}
}
template 
ListNode<Type>* CircularList<Type>::GetNode()
{ //provide a node for use
	ListNode<Type>* x;
	if (av) { x = av, av = av->link; }
	else x = new ListNode<Type>;
	return x;
}
template 
void CircularList<Type>::RetNode(ListNode<Type>* x)
{ //free the node pointed to by x
	x->link = av;
	av = x;
}
template 
void CircularList<Type>::Erase() {
	ListNode<Type>* temp = last->link;
	last->link = av;
	av = temp;
	last = NULL;

}
//////////////Polynomial////////////////
template 
class Polynomial
{
private:
	CircularList<Term<Type>> poly;
public:
	Polynomial(CircularList<Term<Type> >* terms) :poly(terms) { }
	template 
	friend ostream& operator<<(ostream&, Polynomial<Type>&);//polynomial 출력
	/*
	template 
	friend istream& operator>>(istream&, Polynomial&);//polynomial 출력
	*/
	Polynomial<Type>* operator+(const Polynomial<Type>&)const;//polynomial ADD( )
	Polynomial();//생성자 정의 필요-head node를 갖는 경우
	void Add(Term<Type> e);
	int GetData();
	void Erase();
	/*
	int Evaluate(T&) const;//f(x)에 대하여 x에 대한 값을 구한다
	Polynomial Multiply(Polynomial&); //f(x) * g(x)
	Polynomial(const Polynomial& p); //copy constructor
	friend istream& operator>>(istream&, Polynomial&);//polynomial 입력
	friend ostream& operator<<(ostream&, Polynomial&);//polynomial 출력
	const Polynomial& operator=(const Polynomial&) const;
	~Polynomial( );
	Polynomial operator-(const Polynomial&)const;
	*/
};
template 
Polynomial<Type>::Polynomial()
{
	poly = *new CircularList<Term<Type>>;
}
template 
int Polynomial<Type>::GetData() {
	int i, degree;
	float coef;
	int expo;
	int maxExp = 999;

	do {
		Term<float> m;
		i = rand() % 10;
		if (i == 0)
			continue;
		coef = (float)i / 10.0;
		expo = rand() % 9;
		if (expo >= maxExp)
			continue;
		maxExp = expo;
		m.NewTerm(coef, expo);
		poly.Attach(m);
	} while (maxExp > 0);
	return 0;
}

template 
void Polynomial<Type>::Add(Term<Type> e)
{
	poly.Attach(e);
}
template 
void Polynomial<Type>::Erase() {
	poly.Erase();
}

template 
ostream& operator<<(ostream& os, Polynomial<Type>& p)
{
	os << p.poly;
	return os;
}

char compare(int a, int b)
{
	if (a == b) return '=';
	if (a < b) return '<';
	return '>';
}
/*
CircularListIterator<Type> li(l);
if (!li.NotNull()) return os;
os << *li.First();
while (li.NextNotNull())
os << " + " << *li.Next();
*/
template 
Polynomial<Type>* Polynomial<Type>::operator+(const Polynomial<Type>& b)const
{
	Term<Type>* p, * q, * temp;
	CircularListIterator<Term<Type>> Aiter(poly);
	CircularListIterator<Term<Type>> Biter(b.poly);
	Polynomial<Type>* c = new Polynomial<Type>;

	p = Aiter.First();
	q = Biter.First();
	float x = 0.0;
	while (Aiter.NextNotNull() && Biter.NextNotNull()) {
		Term<float> m;
		switch (compare(p->exp, q->exp)) {
		case '=':
			x = p->coef + q->coef;
			m.NewTerm(x, q->exp);
			if (x) c->poly.Attach(m);
			p = Aiter.Next();
			q = Biter.Next();
			break;
		case '<':
			m.NewTerm(q->coef, q->exp);
			c->poly.Attach(m);
			q = Biter.Next();
			break;
		case '>':
			m.NewTerm(p->coef, p->exp);
			c->poly.Attach(m);
			p = Aiter.Next();
		}
	}
	while (Aiter.NextNotNull()) {
		Term<float> m;
		m.NewTerm(p->coef, p->exp);
		c->poly.Attach(m);
		p = Aiter.Next();
	}
	while (Biter.NextNotNull()) {
		Term<float> m;
		m.NewTerm(q->coef, q->exp);
		c->poly.Attach(m);
		q = Biter.Next();
	}
	return c;
}
//adding two polynomials as circular lists with head nodes=> 수정하는 것을 실습

int main()
{
	srand(time(NULL));

	Polynomial<float> p, q, r, * s, * t;
	char select;
	Term<float> e;
	cout << endl << "Select command: a: 다항식 입력, b: p+q, c: (p+q)+r, q: exit" << endl;
	cin >> select;
	while (select != 'q')
	{
		switch (select)
		{
		case 'a':
			p.GetData();
			q.GetData();
			r.GetData();
			cout << "다항식 p, q, r 입력 결과::";
			cout << p;
			cout << q;
			cout << r;
			break;
		case 'b': //a+b
			s = p + q;
			cout << "a = p + q 실행결과::";
			cout << p;
			cout << q;
			cout << *s;
			cout << "다항식 p, q를 삭제";
			p.Erase(); q.Erase();
			break;
		case 'c':
			t = *s + r;
			cout << "t = s + r 실행결과::";
			cout << *s;
			cout << r;
			cout << *t;
			cout << "다항식 s, r를 삭제";
			s->Erase(); r.Erase();
			break;
		default:
			cout << "WRONG INPUint  " << endl;
			cout << "Re-Enter" << endl;
		}
		cout << endl << "Select command: a: 다항식 입력, b: p+q, c: (p+q)+r, q: exit" << endl;
		cin >> select;
	}
	system("pause");
	return 0;
}