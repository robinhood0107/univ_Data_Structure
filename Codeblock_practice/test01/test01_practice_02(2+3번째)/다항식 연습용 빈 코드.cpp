#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>


using namespace std;
class Polynomial;

class Term
{
	friend Polynomial;
private:
	double coef;
	int exp;
public:
	double getCoef() { return coef; }
	int getExp() { return exp; }
};

class Polynomial {
public:
	Polynomial();
	Polynomial Add(Polynomial& b);
	Polynomial Sub(Polynomial& b);
	Polynomial Mult(Polynomial& b);
	void AddTerm(const float theCoeff, const int theExp);
	void NewTerm(const float theCoeff, const int theExp);
	int GetData();
	double Eval(int);
	friend ostream& operator <<(ostream&, Polynomial &);
private:
	static Term* termArray;
	static int capacity;
	static int free;
	int start, finish;
	int terms;
};

void Polynomial::NewTerm(const float theCoeff, const int theExp){

}

Polynomial::Polynomial():start{-1},finish{-1},terms{0}{}

int Polynomial::GetData() {

}

ostream& operator <<(ostream& stream, Polynomial& p) {

}

Polynomial Polynomial::Add(Polynomial& b){

}

Polynomial Polynomial::Sub(Polynomial& b){

}

void Polynomial::AddTerm(const float theCoeff, const int theExp){

}

Polynomial Polynomial::Mult(Polynomial& b){

}



double Polynomial::Eval(int num) {
    
}

// enum 선언
enum MenuChoice { ADDITION = 1, SUBTRACTION, MULTIPLICATION, EVALUATION, EXIT, ADDTERM };


//static 정적멤버 선언부 //static은 이걸 무조건 해줘야 선언되는 거임.
int Polynomial::capacity = 100;
Term* Polynomial::termArray = new Term[100];
int Polynomial::free = 0;

int main(void) {
	srand(time(NULL));
	int choice;
        float mycoef=0;
        int myexp=0;
	Polynomial P1, P2, P3;
	//cout << "입력 예제: \nP(x)=5x^3+3x^1\n";
	cout << "입력 다항식 P1:-" << endl;
	P1.GetData();
	cout << P1;
	cout << "입력 다항식 P2:-" << endl;
	P2.GetData();
	cout << P2;
	cout << "****" << P2;
	while (1) {
		cout << "\n****** Menu Selection ******" << endl;
		cout << "1: Addition\n2: Subtraction\n3: Multiplication\n4: Evaluation\n5: Exit\n6: AddTerm" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		//static_cast, dynamic_cast, const_cast 공부 필요>>정수를 열거형 변환시에 많이 사용
		// switch 문에서 enum 사용
		switch (static_cast<MenuChoice>(choice)) {
		case ADDITION:
			cout << "\n--------------- Addition ---------------\n";
			cout << "Polynomial1: ";
			cout << P1;
			cout << "Polynomial2: ";
			cout << P2;
			P3 = P1.Add(P2);
			cout << "덧셈 결과: ";
			cout << P3;
			cout << "----------------------------------------\n";
			break;

		case SUBTRACTION:
			cout << "\n------------- Subtraction -------------\n";
			cout << "Polynomial1: ";
			cout << P1;
			cout << "Polynomial2: ";
			cout << P2;
			P3 = P1.Sub(P2);
			cout << "Resultant Polynomial: ";
			cout << P3;
			cout << "----------------------------------------\n";
			break;

		case MULTIPLICATION:
			cout << "\n----------- Multiplication -------------\n";
			cout << "Polynomial1: ";
			cout << P1;
			cout << "Polynomial2: ";
			cout << P2;
			P3 = P1.Mult(P2);
			cout << "Resultant Polynomial: ";
			cout << P3;
			cout << "----------------------------------------\n";
			break;

		case EVALUATION:
			cout << "\n------------- Evaluation -------------\n";
			int evalValue;
			cout << "Enter the value to evaluate Polynomial2: ";
			cin >> evalValue;
            cout << P2;
			cout << P2.Eval(evalValue) << "\n";
			cout << "----------------------------------------\n";
			break;

		case EXIT:
			cout << "Good Bye...!!!" << endl;
			exit(0);

        case ADDTERM:
            cout << "\n----------- ADDTERM -------------\n";
			cout << "Polynomial1: ";
			cout << P1;
			cout << "삽입할 coef exp";
			cin >> mycoef >> myexp;
			P1.AddTerm(mycoef,myexp);
			cout << "Resultant Polynomial: ";
			cout << P1;
			cout << "----------------------------------------\n";
			break;

		default:
			cout << "Invalid choice! Please select again." << endl;
		}
	}

	system("pause");
	return 0;
}
