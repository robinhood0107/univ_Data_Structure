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


//혹시 스펠 틀렸으면 b. 랑 free++이런거 제대로 되어 있는지 확인
//그리고 함수 하나하나 완성하고 테스트 해서 점수 받은다음에 다음꺼 하는거다

//기억 안나면 먼저 getData부터 만들어 int i,degree... 하다보면 NewTerm은 배열 작으면 생성, 넣기 및 free++ 이거 기억날테니까

void Polynomial::NewTerm(const float theCoeff, const int theExp){
    //아 기억났다

    //항상 기억
    //먼저 배열의 크기가 부족하면 늘리는 if문
    //반드시 기억해야 하는 것은 terms == capacity일 때 배열 늘린다는 점만 암기하고 있기(terms를 여기서 사용한다고 반드시 알고 있기)
    //copy 배열할때 반드시 시작,시작+free로 해주기
    //그리고 바로 넣고
    //free++

    if( terms == capacity ){
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray,termArray+free,temp);
        delete [] termArray;
        termArray = temp;
    }
    termArray[free].coef = theCoeff;
    termArray[free++].exp = theExp;
    //free++;
}

Polynomial::Polynomial():start{-1},finish{-1},terms{0}{}




///아주아주아주아주 중요!!!!! ---> getdata에서 finish랑 terms는 for문 돌고 제일 마지막에 넣어야 함!!!!
// 내 GetData()가 작동이 안된 이유 => finish = free -1; 이랑 terms = finish - start + 1;은 반드시 getData로 전부 집어 넣은 다음에 결정해줘야 문제가 안생긴다.
//이게 이유가 GetData()는 객체 생성자가 아니라 멤버 함수라서 이 순서가 매우매우 매우 중요함

//Polynomial c;랑은 다르다 !!!!!!!!!!
int Polynomial::GetData() {
    int i,degree;
    float coef;
    int exp, newexp;
    cout << "degree입력";
    cin >> degree;

    //항상 기억(이 주석을 아무것도 없을 때 생각 해 낼 수 있어야 함)
    //반드시 기억) 여기는 이거만 암기하면 됨) exp = degree로 해두기!!!!  (오버로딩이랑 헷깔리지 마라)
    //for문에서 int=degree로 시작해서 0으로 끝나는 degree에서 줄어드는 for문
    //do while문인데 각각 while문에는 네거티브적으로 생각해라(이건 들어가면 안된다면 그걸 while문 돌리기)
    //coef ==0
    //newexp>=exp
    //이 2개는 꼭 기억 , 그리고 newexp는 while끝났으면 꼭 저장

    //추가 기억
    //for문에서 반드시 if(exp==0면 바로 연산 멈추고 for문 빠져나와야 함)
    //아 맞다. 반드시 start, finish, terms 꼭 free, free-1, finish-start+1로 저장하고 시작해야 함!!!



    //내가 mult에서 이거 for문 돌리기 전에 젤 처음 finish = free -1;을 안해서 개박살 난거를 주의해야함 //그리고 mult에서 for문 반복자 2개 전부 반드시 for스코프 안에서 선언
    start = free; //(안 틀리기위한 중요한 팁)start,finish는 항상 처음에 free로 초기화해야 함. 걍 이렇게 기억하자  //진짜 복잡하면 걍 생성자에 때려 넣으셈 그럼 이런짓 안해도 됨.
    exp=degree;


    for(i=degree;i>0;i--){
        do{
            coef = rand() % degree;
        }while(coef == 0); // 0이면 다시 돌려라
        do{
            newexp = static_cast<int>(rand()% degree);
        }while(newexp>=exp); //newexp>=exp면 안되므로 다시 돌려라 <--(이 마인드가 중요한 듯 조건 세울때는 이렇게 생각 할 줄 알아야 됨)
        exp = newexp;
        NewTerm(coef,exp);
        if(exp==0){
            break;
        }
    }

    //내가 틀린부분!!!!!!!!!!!!                                       //여기 위험하다!!!!
    finish = free -1;                                               //getData()에서는 finish랑 terms는 제일 마지막에 결정해야 한다!!!
    terms = finish - start + 1;                                     //다른 것들도 반드시 제일 마지막에 전부 다 계산 한 후에 finish를 결정해 줘야 한다.
    return 0;
}

ostream& operator <<(ostream& stream, Polynomial& p) {

                                                                    //여기 위험하다!!!!
                                                                    //Polynomial::termArray[aPos] 이거 출력할때 반드시 함수 써야 한다는 것 기억!!!! getcoef써야 한다는 것 기억!!!

    //항상 기억
    //aPos == -1은 빈 다항식
    //특정 상황에서만 + 출력 되도록 for문 내부에 if문 만들기

    //하면서 기억난 것
    //for내부 if문의 경우 aPos와 finish를 빼서 비교한다!!!!!(aPos-finish)!=0
    //무조건 기억해야 하는 것//static termArray를 참조하려면 여기서는 Polynomial::termArray라고 꼭 해야 한다.
    int aPos = p.start;

    if(aPos == -1){                                                                                             //내가 틀린 부분
        stream << "빈 다항식" << "\n";
        return stream;
    }

    for(;aPos<=p.finish;aPos++){//아주위험하다!!!! <= 이거 부등호 틀렸다고 + 인쇄가 되는 참사가 벌어짐!!! 이러면 절대 안된다. 부등호까지 완벽해야 함 //반드시 이것도 p.finish라고 적어줘라!!!!!
        stream << Polynomial::termArray[aPos].getCoef() << "x^" << Polynomial::termArray[aPos].getExp();
        if((aPos-p.finish)!=0){//이때만 출력한다                                                                 //내가 틀린 부분 //반드시 이것도 p.finish라고 적어줘라!!!!!
            cout << " + ";
        }
    }
    stream << "\n";
    return stream;
}

Polynomial Polynomial::Add(Polynomial& b){
    //항상 기억
    //while(둘다 finish전까지)
    //exp 같은것 다른것2개
    //float t!!!
    //반드시 if(t) 이거로 coef 0인지 아닌지 판별
    //출력안된 나머지들 for문 2개로 각각 전부 출력하기

    //하면서 기억할 것
    //중간에 aPos++ bPos++로 갱신해야 함!!!!

    int aPos = start;
    int bPos = b.start;

    Polynomial c;
    c.start = free;

    while((aPos<=finish)&&(bPos<=b.finish)){
        if(termArray[aPos].exp == b.termArray[bPos].exp){
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if(t!=0){
                c.NewTerm(t,b.termArray[bPos].exp);
            }
            aPos++;
            bPos++;
        }
        else if(termArray[aPos].exp > b.termArray[bPos].exp){
            //큰거 coef,exp만 추가!!
            c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
            aPos++;
        }
        else{
            c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
            bPos++;
        }
    }
    for(;aPos<=finish;aPos++){
        c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
    }
    for(;bPos<=b.finish;bPos++){
        c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
    }

    c.finish = free-1;
    c.terms = c.finish-c.start+1;
    return c;
}

Polynomial Polynomial::Sub(Polynomial& b){
    //add랑 똑같은데 bexp가 클때 b.termArray[bPos]앞에 -만 붙여주면 됨
    //기억할 것 bexp가 클때(else) 앞에 "-" 붙이자!!!!

    int aPos = start;
    int bPos = b.start;

    Polynomial c;
    c.start = free;


    while((aPos<=finish)&&(bPos<=b.finish)){
        if(termArray[aPos].exp == b.termArray[bPos].exp){
            float t = termArray[aPos].coef - b.termArray[bPos].coef;
            if(t!=0){
                c.NewTerm(t,b.termArray[bPos].exp);
            }
            aPos++;
            bPos++;
        }
        else if(termArray[aPos].exp > b.termArray[bPos].exp){
            c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
            aPos++;
        }
        else{
        //여기에 - 붙이라는 것!!!!!!!!!
            c.NewTerm(-b.termArray[bPos].coef,-b.termArray[bPos].exp);
            bPos++;
        }
    }
    for(;aPos<=finish;aPos++){
        c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
    }
    for(;bPos<=b.finish;bPos++){
        c.NewTerm(-b.termArray[bPos].coef,-b.termArray[bPos].exp);
    }

    //내가 틀린부분!!!!!!!!!!!!                                       //여기 위험하다!!!!
    c.finish = free-1;
    c.terms = c.finish-c.start+1;                                    //무조건 여기 위치여야만 함!!!
    return c;
}

void Polynomial::AddTerm(const float theCoeff, const int theExp){
    //알고리즘 기억(이건 나중에 피가되고 살이 되니까 이 밑에 있는 주석을 내가 안보고 적어낼 수 있을 정도로 이해하고 암기하고 있어야 함)
    //배열의 shift left
    //주로 배열 중간에 있는것 지워버릴 때 사용한다고 생각
    //즉, 배열 요소 삭제 == shift left
    //삭제부위부터 i++로 올라가면서 arr[i-1] = arr[i] //인덱스 작은 거 큰거로 덮어쓰기

    //배열의 shift right
    //주로 배열 중간에 "삽입" 할때 사용한다
    //즉, 배열 요소 "삽입" == shift right
    //중요) right는 left 정확하게 모든걸 반대로 한다 생각하셈
    //요소 젤 끝부터 "거꾸로" i--로 내려가면서 arr[i] = arr[i-1] //작은거로 큰쪽 덮어쓰기 //벌려!!


    //항상 기억
    //이 addTerm에서 반복문이던지 어디던지 답 구했으면 바로 return으로 종료해야 다른 문제 안생긴다는 거 기억
    //theCoeff ==0 이면 바로 종료
    //if 중첩) 탐색하면서 exp 같으면 coef 더하고, 만약 연산후 coef가 0이면 배열 요소 삭제(즉, 없애야 함 = shift left)(올라가면서 덮어쓰기)

    //하면서 기억
    //shift 다하고 나면 반드시 aPos 뒤에 있는 finish, free, term은 갱신 해줘야 한다( 둘 다 )
    if(theCoeff ==0){
        return;
    }
    for(int aPos=start;aPos<=finish;aPos++){
        if(termArray[aPos].exp == theExp){
            termArray[aPos].coef += theCoeff;

            if(termArray[aPos].coef == 0){
                for(int i=aPos;i<finish;i++){                       //내가 틀린 부분!!!!!!
                    termArray[i] = termArray[i+1];                  // < finish이고 큰거로 작은거 덮는데 [i] = [i+1]이다!!!!!
                }
                finish--;
                free--;
                terms--;
            }
            return;//if문 큰게 완료되었다는 것은 찾아서 바꾸었다는 것이니까 바로 빠져와야 한다
        }
    }



    //이거 인덱스 찾는게 살짝 기억이 안난다
    //[import_pos].exp > theExp라는 거 꼭 기억 , 나보다 크면 계속 while문 돌리기!!(나보다 작은 exp값 찾는 것)
    //aPos<=finish같은 방법으로 돌면서 &&로 [import_pos].exp > theExp(자신(theExp)보다 작기 전까지는(즉, 나보다 큰 상태면) 계속 while문 돌려라)로 자신(theExp)보다 딱 작아지는 시점 직전에서 멈춤 (그 이후를 벌리면 되니까) (내림차순 정렬되어 있어서 start가 가장 큰 exp)
    //while에 들어가는 건 항상 네거티브(반대로) 생각해보자
    int import_pos = start;
    while((import_pos<=finish)&&(termArray[import_pos].exp > theExp)){
        import_pos++; //이건 걍 외우고 있자.
    }

    //shift_right //거꾸로! //작은거로 큰거 덮어
    for(int i=free;i>import_pos;i--){
        termArray[i] = termArray[i-1];
    }

    //이제 그 위치에 저장
    termArray[import_pos].coef = theCoeff;
    termArray[import_pos].exp = theExp;

    finish++;
    free++;
    terms++;

    return;
}



Polynomial Polynomial::Mult(Polynomial& b){
    //for문 중첩으로 돌리면 되고
    //곱한다음에 계속 addTerm으로 던지면 됨;
    //암튼 중첩for문이라고 알고 있어

    //mult에서 가장 중요한것
    //내가 시간 개박살난 그것!!
    //무조건 for문 전에!! 바로 Polynomial c; 선언한뒤에 반드시 반사적으로 start,finish,terms를 free,free-1,finish-start+1로 초기화!!!
    //무조건 for문 전에!!


    //내가 틀린부분!!!!!!!!!!!!                                       //여기 위험하다!!!!
    Polynomial c;
    c.start = free;
    c.finish = free-1;
    c.terms = c.finish-c.start+1;                                                //신기하게도 오직 mult만 for문 앞에 맨 처음 c.finish = free-1;가 있어야 되고
                                            //나머지는 반드시 전부 함수 제일 마지막에 있어야 한다.
    //신기하게도 오직 mult만 for문 앞에 맨 처음 c.finish = free-1;가 있어야 되고
    //나머지는 반드시 전부 함수 제일 마지막에 있어야 한다.
    //즉!!!! 그냥 mult 빼고는 전부 함수 제일 마지막에 있어야 함!!!!!


    //지수는 더하는거다!!!
    for(int aPos=start;aPos<=finish;aPos++){
        for(int bPos=b.start;bPos<=b.finish;bPos++){
            float multcoef = termArray[aPos].coef * b.termArray[bPos].coef;
            int multexp = termArray[aPos].exp + b.termArray[bPos].exp;

            c.AddTerm(multcoef,multexp);
        }
    }


    return c;
}


//pow(진수,지수)인거 기억하셈 //그리고 쓰려면 #include <cmath>
double Polynomial::Eval(int num) {
    double result = 0;

    for(int aPos=start;aPos<=finish;aPos++){
        //계수 * pow(진수,지수)를 계속 더함
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
