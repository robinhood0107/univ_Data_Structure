#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>


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
	void AddTerm(int coef, int exp);
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
    if(terms == capacity){
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray,termArray+free,temp);
        delete [] termArray;
        termArray = temp;
    //copy에서 시작, 시작+free 인거 기억
    }
    termArray[free].coef = theCoeff; //이거 스펠링 조심해라 항상 함수 1개 완성하면 스펠링 문제 없는지 확인
    termArray[free].exp = theExp;
    free++;
}

Polynomial::Polynomial():start{-1},finish{-1},terms{0}{}

int Polynomial::GetData() {
    int i,degree;
    float coef;
    int exp,newexp;

    cout << "Degree : ";
    cin >> degree;

    //항상 start,finish(젤 마지막에)
    start = free;
    exp = degree;

    //do while
    for(i=degree;i>0;i--){//이거 기억해라
        do{
            coef = rand()%degree;
        }while(coef==0);
        do{
            newexp = static_cast<int>(rand()%degree);
        }while(newexp >= exp);
        exp=newexp;
        NewTerm(coef,exp);

        if(exp == 0){
            break;
        }
    }

    finish = free -1;
    terms = finish - start +1;
    return 0;
}

ostream& operator <<(ostream& stream, Polynomial& p) {
    //빈다항식
    //+ 출력 특수조건 aPos-p.finish!=0
    int aPos = p.start;

    if(aPos == -1){
        stream << "빈 다항식\n";
        return stream;
    }
    for(;aPos<=p.finish;aPos++){
            //진짜 이거 계속 까먹네.. 무조건 getCoef랑 getExp 로만 출력!!!!!
        stream << Polynomial::termArray[aPos].getCoef() << "x^" << Polynomial::termArray[aPos].getExp();

        if((aPos-p.finish)!=0){
            cout << " + ";
        }
    }
    stream << "\n";
    return stream;
}

Polynomial Polynomial::Add(Polynomial& b){
    int aPos = start;
    int bPos =b.start;

    Polynomial c;
    c.start = free;

    while((aPos<=finish)&&(bPos<=b.finish)){ //add는 큰 while 크게 있는거 기억!!!!!
        if(termArray[aPos].exp == b.termArray[bPos].exp){
            float t = termArray[aPos].coef + b.termArray[bPos].coef;

            if(t){//if(t!=0) 이거 하는거 꼭 기억! 0 제거해야 함!!!
                c.NewTerm(t,termArray[aPos].exp);
            }
            //aPos,bPos 더하는거도 꼭 기억!!!!
            aPos++;
            bPos++;
        }else if(termArray[aPos].exp > b.termArray[bPos].exp){
            c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
            aPos++;
        }else{
            c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
            bPos++;
        }
    }
    //반드시 나머지 aPos들도 출력
    for(;aPos<=finish;aPos++){
        c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
    }
    //b.finish인거 제발 잊지마라
    for(;bPos<=b.finish;bPos++){
        c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
    }

    //무조건 제일 마지막에 c.finish = free -1; //그리고 내가 방금 틀린건데 c.꼭 붙여야 함!!!!!
    c.finish = free -1;
    c.terms = c.finish - c.start +1;
    return c;
}

Polynomial Polynomial::Sub(Polynomial& b){

// -는 무조건 coef만 붙임 !!!!
    int aPos = start;
    int bPos = b.start;

    Polynomial c;
    c.start = free;

    while((aPos<=finish)&&(bPos<=b.finish)){ //add는 큰 while 크게 있는거 기억!!!!!
        if(termArray[aPos].exp == b.termArray[bPos].exp){
            float t = termArray[aPos].coef - b.termArray[bPos].coef;

            if(t){//if(t!=0) 이거 하는거 꼭 기억! 0 제거해야 함!!!
                c.NewTerm(t,termArray[aPos].exp);
            }
            //aPos,bPos 더하는거도 꼭 기억!!!!
            aPos++;
            bPos++;
        }else if(termArray[aPos].exp > b.termArray[bPos].exp){
            c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
            aPos++;
        }else{
            c.NewTerm(-b.termArray[bPos].coef,b.termArray[bPos].exp);
            bPos++;
        }
    }
    //반드시 나머지 aPos들도 출력
    for(;aPos<=finish;aPos++){
        c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
    }
    //b.finish인거 제발 잊지마라
    for(;bPos<=b.finish;bPos++){
        c.NewTerm(-b.termArray[bPos].coef,b.termArray[bPos].exp);
    }

    //무조건 제일 마지막에 finish = free -1;
    c.finish = free -1;
    c.terms = c.finish - c.start +1;
    return c;
}

void Polynomial::AddTerm(int coef, int exp) {
    int indx = finish;
    int indx2 = indx;
		//exp가 같은 경우 처리
		for(int aPos=start;aPos<=finish;aPos++){
			if(termArray[aPos].exp == exp){
				termArray[aPos].coef += coef;
				if(termArray[aPos].coef == 0){
					//shift left [i]=[i+1]
					for(int i=aPos;i<indx2;i++){
						termArray[i] = termArray[i+1];
					}
					finish--;
					free--;
					terms--;
					indx2 = finish;
				}
				return;
			}
		}
		//exp가 같은 것이 없는 경우
		int import_pos = start;
		while((import_pos<=indx)&&(termArray[import_pos].exp > exp)){
			import_pos++;
		}
		//shift right //요소 추가 [i]=[i-1]
		for(int i=indx+1;i>0;i--){
			termArray[i] = termArray[i-1];
		}
		finish++;
		free++;
		terms++;
		indx = finish;
		termArray[import_pos].coef = coef;
		termArray[import_pos].exp = exp;
		return;

    return;
}

Polynomial Polynomial::Mult(Polynomial& b){
//mult에서만 무조건 먼저 finish까지 전부 추가해야 함
    Polynomial c;
    c.start = free;
    c.finish = free-1;
    c.terms = c.finish - c.start +1;

    //for문 중첩문인거 꼭 기억 및 b.start랑 b.finish다... //그리고 지수는 더하는 거다
    for(int aPos=start;aPos<=finish;aPos++){
        for(int bPos=b.start;bPos<=b.finish;bPos++){
            float multcoef = termArray[aPos].coef * b.termArray[bPos].coef;
            int multexp = termArray[aPos].exp + b.termArray[bPos].exp;
            c.AddTerm(multcoef,multexp);
        }
    }

    return c;
}



double Polynomial::Eval(int num) {
    double result=0;

    for(int aPos=start;aPos<=finish;aPos++){
        result += termArray[aPos].coef * pow(num,termArray[aPos].exp);
    }

    return result;
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
