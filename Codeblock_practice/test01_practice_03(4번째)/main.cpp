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
    //항상 기억
    //(배열이 작으면 크게 재설정)
    //각종 조건들 꼭 기억 (기억할 조건들 주석 살짝 적어둠)
    //원소 넣고 free++

    if(terms == capacity){//무조건 terms랑 비교!!! capacity와 terms 비교한다!!
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray,termArray+free,temp);//copy할때 무조건 시작,시작+free까지
        delete [] termArray;
        termArray = temp;
        //새로 만들고
        //복사한 뒤에
        //기존것 해제하고
        //연결
    }
    termArray[free].coef = theCoeff;
    termArray[free].exp = theExp;
    free++; //이거 꼭 기억!!!!
}

Polynomial::Polynomial():start{-1},finish{-1},terms{0}{}

int Polynomial::GetData() {
    //GetData가 젤 중요함!!!
    //GetData에서 맨처음에 exp=degree로 설정하는 것 꼭 기억!!
    //그리고 처음에 start 설정하고 함수 끝날때 finish!!!!!!(반드시 함수 끝날 때)

    //큰 for문의 경우 degree부터 >0까지 내려가는 것!!!! i--인거 반드시 기억 (degree번 반복)

    //coef==0 newexp>=exp while 조건문 반드시 기억!!!
    //do while 전부 끝나고 exp=newexp로 갱신 후 NewTerm 전부 한 다음에는 if문!!! exp==0이면 바로 빠져나오기!!!
    int i,degree;
    float coef;
    int exp, newexp;

    //제발 이 2개는 반드시 먼저 해라!!!!!!!!
    //꼭 기억// 시험치기 전에도 이건 먼저 한다고 기억
    start = free;
    exp = degree;

    cout << "Degree 입력 : ";
    cin >> degree;

    for(i=degree;i>0;i--){
        do{
            coef = rand() % degree;
        }while(coef == 0); //0이면 안된다는 것

        do{
            newexp = static_cast<int>(rand() % degree);
        }while(newexp>=exp);//exp보다 크거나 같으면 쓸모없는 값이랑 다시 while문
        exp=newexp; //값 갱신

        NewTerm(coef,exp);
        if(exp == 0){
            break;
        }
    }

    ///반드시 기억(mult 빼고는 전부 finish는 함수 제일 뒤에 적는다!!)

    finish = free-1;
    terms = finish - start + 1;
    return 0;
}

ostream& operator <<(ostream& stream, Polynomial& p) {
        //여기서 중요한 것!!!
        //시험때 기억안나면 이렇게 빠르게 할 일 주석으로 적어버리자 그러면 바로 기억남

        // aPos == -1이면 빈 다항식
        //p.finish처럼 꼭 앞에 p. 붙일 것!!
        // 반드시 출력할때 getCoef, getExp 사용할 것!!! (이거 꼭 기억)

        //+ 출력할 때 반드시 조건(암기) => aPos-p.finish!=0 일때만 + 출력!!!!


        int aPos = p.start;

        if(aPos == -1){
            stream << "빈 다항식 \n";
            return stream;
        }
        for(;aPos<=p.finish;aPos++){
            //제발!!! Polynomial::termArray 이렇게 출력 해야 되고, 반드시 getCoef 써야 한다고 머리에 암시해둬!!!!
            stream << Polynomial::termArray[aPos].getCoef() << "x^" << Polynomial::termArray[aPos].getExp();
            if((aPos-p.finish)!=0){                                                                             //주의!!! 스펠링 주의!!! aPos-p.finish다 !!!
                stream << " + "; //특정 조건에서만 + 출력 하도록 하기!!
            }
        }

        stream << "\n";
        return stream;
}

Polynomial Polynomial::Add(Polynomial& b){
    //start는 젤 먼저                               start=free
    //finish,terms는 반드시 제일 마지막에             finish=free-1
    //if(t)나 if(t!=0)으로 coef==0인 경우를 걸러내기!!!
    //exp같은 경우 다른경우 2개, 마지막에 for문 2개로 나머지들 출력
    //while에 ()&&()로 aPos<=finish 들어가는거 기억!

    //항상 기억!!!
    //c.NewTerm으로 넣은 다음에는 반드시 aPos++ bPos++로 갱신!!

    int aPos = start;
    int bPos = b.start;

    Polynomial c;
    c.start = free;

    while((aPos<=finish)&&(bPos<=b.finish)){
        if(termArray[aPos].exp == b.termArray[bPos].exp){
            float t = termArray[aPos].coef + b.termArray[bPos].coef;

            //if(t!=0)으로 coef 0 판별한다고 꼭 기억!!!
            if(t){//if(t!=0)이거랑 똑같음
                c.NewTerm(t,termArray[aPos].exp);
            }
            aPos++;
            bPos++;
        }
        else if(termArray[aPos].exp > b.termArray[bPos].exp){
            //큰거인 a만 넣기
            c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
            aPos++;
        }
        else{
            c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
            bPos++;
        }
    }
    //나머지 apos,bpos로 전부 출력
    for(;aPos<=finish;aPos++){
        c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
    }
    for(;bPos<=b.finish;bPos++){//b.무조건 붙이기!!!!!!! 꼭 기억!!
        c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
    }

    //항상 마지막에 finish!!!
    //이거 안하면 아예 출력이 안되기 때문에 반드시 출력!!!!!

    c.finish = free -1;
    c.terms = c.finish - c.start +1;
    return c;
}

Polynomial Polynomial::Sub(Polynomial& b){
    //b 앞에는 -를 붙여라!!!

    // - 붙이기 !!!! //exp 지수는 붙이지 마라!!!!! coef만!!!!!

    int aPos = start;
    int bPos = b.start;

    Polynomial c;
    c.start = free;

    while((aPos<=finish)&&(bPos<=b.finish)){
        if(termArray[aPos].exp == b.termArray[bPos].exp){
            float t = termArray[aPos].coef - b.termArray[bPos].coef; // - 붙이기 !!!!
            if(t){
                c.NewTerm(t,termArray[aPos].exp);
            }
            aPos++;
            bPos++;
        }
        else if(termArray[aPos].exp > b.termArray[bPos].exp){
            c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
            aPos++;
        }
        else{
            c.NewTerm(-b.termArray[bPos].coef,b.termArray[bPos].exp); // - 붙이기 !!!! //exp 지수는 붙이지 마라!!!!! coef만!!!!!
            bPos++;
        }
    }
    //나머지 apos,bpos로 전부 출력
    for(;aPos<=finish;aPos++){
        c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
    }
    for(;bPos<=b.finish;bPos++){
        c.NewTerm(-b.termArray[bPos].coef,b.termArray[bPos].exp); // - 붙이기 !!!! coef만!!!!!
    }

    //항상 마지막에 finish!!!
    //이거 안하면 아예 출력이 안되기 때문에 반드시 출력!!!!!

    c.finish = free -1;
    c.terms = c.finish - c.start +1;
    return c;
}

void Polynomial::AddTerm(const float theCoeff, const int theExp){
    //항상 이미 구했으면 return으로 바로 빠져 나오기
    //theCoeff==0이면 바로 빠져 나오기
    //if 중첩 exp 같으면 기본 coef에 더하기 그리고 이 coef 값이 같으면 배열 요소 제거 = shift left --> 올라가면서 <finish [i] = [i+1]로 덮어쓰기 !!
    //shift left(당기기) <finish [i] = [i+1] 이거 꼭 기억!!!\
    //끝에서 당겼으니까 finish,free,terms 전부 --;

    //그리고 나선 import_pos=start 설정 후에  ()&&()로 찾는데 import_pos].exp > theExp (나 자신보다 클때만 import_pos++해서 작아지기 전 위치 찾기)
    //그 후 shift right //이건 free부터 시작한다!!! 내려가면서 i--!!! shift right은 free부터라고 기억 (벌리기 이므로) (작은것을 큰것에 덮기) [i] = [i-1]
    //끝에서 벌렸으니까 finish,free,terms 전부 ++;

    if(theCoeff == 0) return;                                                   //주의 !!! theCoeff로 해야 한다!!!
    for(int aPos=start;aPos<=finish;aPos++){
        if(termArray[aPos].exp == theExp){
            termArray[aPos].coef += theCoeff;

            if(termArray[aPos].coef == 0){
                for(int i=aPos;i<finish;i++){
                //shift left //중간 제거 //큰거로 작은거 덮음
                    termArray[i] = termArray[i+1];
                }

                finish--;
                terms--;
                free--;
            }
            //다른 반복 돌기 전에 빨리 return;
            //if중첩중 return 큰 if 안에 하면 됨!
            return;
        }
    }


    int import_pos = start;
    while((import_pos<=finish)&&(termArray[import_pos].exp > theExp)){ //termArray[import_pos].exp > theExp 이거 인 것 꼭 기억!!!
        import_pos++;
    }

    //내려가면서 !!!! //free 시작!!
    for(int i=free;i>import_pos;i--){
    //요소 넣기 //벌리기 //작은거로 큰거 덮기
        termArray[i] = termArray[i-1];
    }


                                                                    //아 참 이걸 빼먹었다!!!!!!!!!!!
                                                                    //생각을 해!! 이렇게 벌렸으면 새로 넣어야 될 거 아냐!!! 새로 넣어야 한다고 꼭 기억!!!

    termArray[import_pos].coef= theCoeff;
    termArray[import_pos].exp= theExp;

    finish++;
    terms++;
    free++;

    return;
}

Polynomial Polynomial::Mult(Polynomial& b){
    //mult에서만 특이하게 Polynomial c; 선언시에 반드시 start, finish 먼저 선언해야 함!!!!!
    //중첩 for문인거 기억!!!

    //중요//내가 자주 틀리는 부분
    //내가 틀린 부분!!!! for문 b.start b.finish여야 한다!!!!

    Polynomial c;
    //꼭 mult만 먼저 start finish까지(나머지 다른 함수는 함수끝날때 finish임)
    c.start = free;
    c.finish = free-1;
    c.terms = c.finish - c.start + 1;

    for(int aPos=start;aPos<=finish;aPos++){
        for(int bPos=b.start;bPos<=b.finish;bPos++){                                    //내가 틀린 부분!!!! b.start b.finish여야 한다!!!!
            float multcoef = termArray[aPos].coef * b.termArray[bPos].coef;
            int multexp = termArray[aPos].exp + b.termArray[bPos].exp; //지수는 더한다!!
            c.AddTerm(multcoef,multexp);
        }
    }

    return c;
}



double Polynomial::Eval(int num) {
//pow(진수,지수) 써라 <cmath>
    double result = 0;

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
