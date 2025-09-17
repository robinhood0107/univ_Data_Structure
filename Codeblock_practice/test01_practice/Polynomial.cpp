//소스 코드2.5: Polynomial 클래스
/*
* +, -, *, << , >> operator를 사용한 버젼으로 구현한다.
* template 버젼으로 구현: T coef;
* sub와 Mult(), Eval()를 구현한다
*/


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
	//construct the polynomial p(x) = 0;
	Polynomial Add(Polynomial& b);
	Polynomial Sub(Polynomial& b);
	//Polynomial& operator + (Polynomial&);
	//Polynomial& operator - (Polynomial&);
	//Polynomial& operator * (Polynomial&);
	//return the sum of the polynomials *this and b
	Polynomial Mult(Polynomial& b);
	void AddTerm(const float theCoeff, const int theExp);
	//return the product of the polynomials *this and b
	//float Eval(float f);
	//evaluate the polynomial *this at f and return the result
	void NewTerm(const float theCoeff, const int theExp);
	//int Display();
	int GetData();
	double Eval(int);
	friend ostream& operator <<(ostream&, Polynomial &);
	//friend istream& operator >>(istream&, Polynomial&);
private:
	static Term* termArray;
	static int capacity;
	static int free;
	int start, finish;
	int terms;
};
/*
std::ostream 클래스에는 기본 타입(예: int, double, std::string)에 대한 operator<< 오버로딩이 정의되어 있습니다.
예를 들어, std::cout << 5; 와 같은 구문은 std::ostream에 이미 정의된 operator<<를 사용하여 정수 5를 출력합니다.
사용자 정의 타입에 대한 operator<< 오버로딩
std::ostream 클래스 내부에 operator<<를 정의하면, 특정 클래스에 대한 출력 방식이 직접적으로 ostream 클래스에 포함되어야 한다
 클래스가 다수일 경우 유지보수가 어렵습니다. 따라서 사용자 정의 타입에 대한 operator<<는 외부 함수로 구현하여 코드의 모듈성과 유지보수성을 높인다
*/














//구현 순서대로 정렬 함(이 순서대로 알고 있어야 시험때 빠르게 이 순서대로 올라간다.)

//이 NewTerm도 안 줄 수 있으니까 알고 있어야 함.
void Polynomial::NewTerm(const float theCoeff, const int theExp){
    //1.static Term* termArray에 새로 저장하고, 2.static int free;와 static int capacity;을 설정한다.


    //termArray 동적배열 크기 늘리는 if문(static Polynomial::capacity이 100인데 만약 다항식 저장한것들이 100이 되면 더 저장할 곳이 없으니까 새로 만들기
    if(terms == capacity){
        capacity *= 2;//늘릴 크기만큼 capacity 설정 (동적배열 크기 얼마나 늘릴지는 보통 지금의 2배 정도 늘리는게 관습인듯)
        Term* temp = new Term[capacity]; //이 동적할당 외워라....
        copy(termArray,termArray+free,temp); //이거 copy 주의 할 것이 free까지만 복사해서 붙여넣는거다. 이거 꼭 외우고 있으셈
        delete[] termArray;
        termArray = temp;
        //static은 this 못쓴다. 명심해라.

        //항상 1.temp만들고
        //2.복사한 다음
        //3.삭제 후
        //4. termArray에 다시 할당
        //동적배열은 vector아니라서 시작,끝은 항상 (termArray,termArray+5) 이런방식으로 크기 지정하는 거임
        //그리고 동적할당 해제 배열은 delete 바로뒤에 [] 이거 붙는거 잊지말기. 항상 ~delete[] "배열이름"~ 이거다
    }
    termArray[free].coef = theCoeff;
    termArray[free++].exp = theExp;
    //배열 크기 충분하면 if건너뛰고 바로 인덱스free의 Term인스턴스의 coef, exp저장(배열 1칸에 객체 1개 저장되어있잖아, 애초에 객체 1개, 같은 인덱스에 저장되는 것)
    //(여기서 free++라 연산 후 증가됨)(free인덱스 1칸에 coef exp 다 넣은 다음에 free++되는 것)
}

Polynomial::Polynomial():start{-1},finish{-1},terms{0}{}





//1.GetData, 연산자 오버로딩 << 구현이 1점(이거 구현 못하면 걍 0점)
int Polynomial::GetData() {
    int i, degree; //degree는 차수
    float coef; //coef는 계수
    int exp, newexp; //expo는 지수 이다
    cout << "Enter Degree Of Polynomial:";
    cin >> degree; //degree는 입력으로 주어진다.
    start = free; //free = 다항식을 저장할 배열의 다음 새로운 항을 추가할 수 있는 시작 인덱스
    exp = degree; //일단 시작은 내가 설정한 차수로
    for(i=degree;i>0;i--){
        do{
        //coef에 난수를 입력받는 do while
            coef = rand() % degree;
        }while(coef == 0);//coef == 0나온다면 다시 while문 돎 => 즉, coef는 degree-1보다 작은 0이 아닌 양수가 나옴
        do{
        //newexp에 난수를 입력받는 do while
            newexp = static_cast<int>(rand()%degree);
        }while(newexp >= exp); //새로운 지수가 exp보다 크거나 같으면 다시 while문 => 즉, newexpo는 무조건 exp보다 작다
        exp = newexp;
        NewTerm(coef,exp); //새로운 클래스 동적배열객체 생성(저장은 static Term* termArray에 저장됨) //여기에서 모두 하나의 static배열을 쪼개 공유해서 사용함
        if(exp==0){ //exp가 0일 경우 자연수란 거니까 0 되면 바로 for문 종료
            break;
        }
    }
    finish = free - 1; //free는 static이라서 NewTerm호출할때마다 NewTerm에 의해 계속 free값 변함
    terms = finish - start + 1; //총 다항식 개수가 terms임. finish - start + 1 이라고 걍 알고 있자
    return 0;
}

ostream& operator <<(ostream& stream, Polynomial& p) {
    //출력형태는 항상 x^6+....+7 이런 방식
    //아예 없으면 빈 다항식이라 출력
    //교수님이 마지막 뒤에 + 출력 안되도록 for문 안에 (aPos-p.finish)!=0일때만 "+"출력하도록 if문 꼭 넣기
    //+출력을 하는 조건은 (aPos-p.finish)!=0 (하나의 개별 다항식만 출력할꺼니까)

    int aPos = p.start; //aPos변수 만들어서 이걸로 for문
    if(aPos == -1){
        stream << "빈 다항식" << "\n";
        return stream;
    }
    //for문 p.finish보다 같거나 작을때만 돌아감
    for(;aPos <= p.finish;aPos++){//앞에서 aPos초기화 해놓아서 여기는 필요없어서 안적음
        //기억) friend나 밖에서 static을 부를 때는 Polynomial::termArray 이런식으로 부른다 //암튼 연산자 오버로딩에선 이렇게 꼭 부른다 암기
        //그리고 public에 있는 함수만 접근 가능하니까 getCoef,getExp
        stream << Polynomial::termArray[aPos].getCoef() << "x^" << Polynomial::termArray[aPos].getExp();

        if((aPos-p.finish)!=0){//이렇게 꼭 + 나오는 조건 설정해줘야 함.
            cout << " + ";
        }
    }
    stream << "\n";
    return stream;
}
//여기는 아주 기본. 이거를 해야 0점은 면할 수 있음


//2.그리고 Add() 구현하기 ==> 다항식 더하기 한후 p3=p1.sub(p2) 이렇게 해서 출력 cout << p3;하면 나오게끔
Polynomial Polynomial::Add(Polynomial& b){
    //a 다항식은 this!!! b 다항식은 b.start,b.finish!!!!
    int aPos = start; //1번째 다항식은 this 당연 지금 현재 클래스니까 this
    int bPos = b.start; //2번째 다항식은 b.finish부터 시작

    //출력용 객체 c
    Polynomial c; //더한 다항식 저장할 새로운 객체
    c.start = free; //c.start는 남아있는 저장공간시작점 static free로 위치 설정!!!
    //(중요!!!!!) 잊지마라 c.start랑c.finish, c.terms꼭 설정해줘야 함!!!! - 제일 밑에 NewTerm다 수행하고 finish 저장해야 함. 잊지말기


    //while문 1개(내부 exp비교 if문) for문 2개(aPos랑 bPos로 남아있는 항 출력)
    //while안의 if문은 총 3가지(exp 서로 같을때)(a의 exp가 더 클때)(b의 exp가 더 클때)
    while((aPos <= finish) && (bPos <= b.finish)){ //각각 pos값이 finish값보다 같거나 작을때까지만
        if(termArray[aPos].exp == b.termArray[bPos].exp){//b.termArray[bPos].exp에 앞에 b. 붙이는거 잊지마라
            //새로운 계수 coef 계산 //당연히 float
            float t = termArray[aPos].coef + b.termArray[bPos].coef;

            if(t!=0){//t가 0이 아니라면...if(t)라고 해도 됨
                c.NewTerm(t,termArray[aPos].exp); //c객체에 NewTerm으로 static termArray에 저장
            }
            aPos++;
            bPos++;
        }
        else if(termArray[aPos].exp > b.termArray[bPos].exp){
            //더 크니까 c에다가 a의 다항식 항 1개를 넣으면 됨 //마찬가지로 바로 c.NewTerm
            c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
            aPos++; //a만 넣었으니 aPos만 증가
        }
        else{
            c.NewTerm(b.termArray[bPos].exp,b.termArray[bPos].exp);
            aPos++; //a만 넣었으니 aPos만 증가
        }
    }
    //for문 1개 반드시 더 필요함
    //aPos나 bPos에서 위에서 while 비교후 서로 같은 차수 보다 더 작은 항들을 전부 넣어주어야 함(이게 누락됨)(서로 안겹치는 제일 작은 항들을)
    //어쩌피 aPos랑 bPos는 위에서 계산되고 남는 위치가 있으니 그걸로 사용해야 함.(그리고 aPos,bPos둘다 어쩌피 선언되어 있음)
    for(;aPos<=finish;aPos++){//a에서 남은 aPos부터 finish까지 전부
        c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
    }
    for(;bPos<=b.finish;bPos++){//b에서 남은 bPos부터 b.finish까지 전부
        c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
    }


    //(중요!!!!!) 잊지마라 c.start랑c.finish, c.terms꼭 설정해줘야 함!!!!
    //아직 c.finish 초기화 안했음!!!
    c.finish = free - 1;
    c.terms = c.finish - c.start + 1;

    return c;
}


//3.그리고 Sub()구현하기 ==> ADD에서 -로 변형만!!
//Add만 제대로 할줄 알면 이건 쉬움
//if(t!=0) 이거 꼭 기억해라
Polynomial Polynomial::Sub(Polynomial& b){
    int aPos = start;
    int bPos = b.start;

    Polynomial c;
    c.start = free;
    while((aPos<=finish)&&(bPos<=b.finish)){ //내가 틀린 부분.... "(aPos <= finish) && (bPos <= b.finish)" <= 이거여야 Pos가 finish보다 같거나 작은 곳(내 다항식)만 탐색함!!!
        if(termArray[aPos].exp == b.termArray[bPos].exp){
            float t = termArray[aPos].coef - b.termArray[bPos].coef;
            if(t!=0){
                c.NewTerm(t,termArray[aPos].exp);
            }
            //틀릴 뻔)aPos,bPos 더해주는 거 잊지마라
            aPos++;
            bPos++;
        }
        else if(termArray[aPos].exp > b.termArray[bPos].exp){
        //(중요)(Add와 다른 점)주의!!!!!!! a-b 상태이기 때문에 a는 부호 그대로 들어감
            c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
            aPos++;
        }
        else{
        //(중요)(Add와 다른 점)주의!!!!!!! a-b 상태이기 때문에 b는 부호 반대!!!!!!! - 꼭 붙여라!!!
            c.NewTerm(-termArray[aPos].coef,termArray[aPos].exp);
            bPos++;
        }
    }
    for(;aPos<=finish;aPos++){//a-b니까 a는 부호 그대로
        c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
    }

    for(;bPos<=b.finish;bPos++){//(중요)(Add와 다른 점)주의!!!!!!! a-b니까 b는 부호 반대!!! -붙여라!!
        c.NewTerm(-termArray[aPos].coef,termArray[aPos].exp);
    }

    c.finish = free - 1;
    c.terms = finish - start + 1;

    return c;
}

//4.AddTerm 구현(곱셈은 AddTerm 구현한 후에 구현하는게 더 효율적임)
//그러니까 나도 AddTerm 먼저 구현하는게 시간적으로 유리하다
//AddTerm()의 사용조건 = 무조건 마지막으로 만들어진, 가장 static termArray의 오른쪽에 있는 객체만 사용 가능한 함수
void Polynomial::AddTerm(const float theCoeff, const int theExp){
    //따져야 하는 상황
    //coef가 0일 경우
    //exp가 서로 같은 차수 검색해서 있으면 계수 더하고 종료
    //같은 차수가 없다면 배열의 정렬 진행(자기 위치에 똑바로 넣기)



    if (theCoeff == 0) return;

    for(int aPos = start;aPos<=finish;aPos++){//exp가 같은것 찾아서 계수 더하고 종료
        if(termArray[aPos].exp == theExp){
            termArray[aPos].coef += theCoeff; //같은 지수면 바로 더함
            if (termArray[aPos].coef == 0) {
                for (int i = aPos; i < finish; i++) {
                    termArray[i] = termArray[i + 1]; //shift-left로 지워버리면 된다!!!
                }
                finish--;
                terms--;
                free--;
            }
        return;//처리했으면 바로 종료해야 됨. 이게 젤 중요함. //위치 제대로 기억
        }
    }

    //삽입 위치 결정 및 삽입
    //이 코드 꼭 외워라
    int insert_pos = start;
    while((insert_pos<= finish)&&(termArray[insert_pos].exp > theExp)){//나 자신보다 작아지는 처음 차수를 찾으면 됨(거기부터 1칸씩 이동하면 됨)
        insert_pos++;
    }

    //전체 항 이동 (Shift) - 반드시 뒤에서부터!
    //free 위치부터 insert_pos 다음 위치까지의 항들을 한 칸씩 뒤로 민다.
    // 'Shift-Right'로 삽입할 공간 확보 (반드시 뒤에서부터)
    for (int i = free; i > insert_pos; i--) {
        termArray[i] = termArray[i - 1];
    }

    termArray[insert_pos].coef = theCoeff;
    termArray[insert_pos].exp = theExp;

    finish++;
    terms++;
    free++;
    return;
    //배열에서 한칸씩 미는 행동은 O(n)의 시간복잡도, 무조건 뒤에서부터 하나씩 오른쪽으로 이동시켜야만 한다!!!!!!!(뒤에서부터 기억)

}
//------------------------------------------------------------------------------------------------------------------------------------//
//4. AddTerm관련 여담...

//솔직히 교수님이 배열 사이에 항을 끼워 넣는 코드를 넣으라고 하셨는데 이러면 객체 맴버변수 start,finish가 완전 개판인 쓰레기값이 들어가는 치명적 문제 발생
//이 함수 치명적인 문제점 : AddTerm 함수는 객체를 만들 당시 무조건 제일 마지막에 저장한 객체를 조작할때만 쓸 수 있음

/*
전역 상태 관리의 복잡성

가장 치명적인 문제. AddTermWithShift 함수는 *this 객체만 알고 있기 때문에 항을 밀어내는 순간, insert_pos보다 뒤에 start 인덱스를 가진 다른 모든 Polynomial 객체들의 정보가 망가짐.
이 문제를 해결하려면, 생성된 모든 Polynomial 객체를 관리하는 전역 리스트 같은 것이 필요하며, 항을 밀 때마다 이 리스트를 전부 순회하며 각 객체의 start와 finish 값을 일일이 수정해줘야 함.
이는 엄청나게 복잡하고 오류가 발생하기 쉬운 설계.
결론적으로, 기술적으로 구현은 가능하지만, 그 대가로 성능, 단순성, 안정성을 모두 잃게 됨.
이 때문에 이러한 공유 풀 구조에서는 정렬을 유지하지 않고 끝에 추가하는 방식을 사용하는 것.
*/


//다시 말하면 제일 마지막에(최근에) 만들어진 Polynomial객체는 상관 없음.
//근데 중간이나 처음에 저장되어있는 다항식 객체에 AddTerm을 하는 순간 객체값이랑 static termArray가 불일치하는 대참사가 발생
//(완전 못써먹을 치명적 오류의 자료구조가 만들어지는 것)

//(위에서 장황하게 문제점 써놓은 그 코드)(정렬을 여기서 꼭! 해야 겠다면 제일 마지막 객체에만 쓴다는 가정하에만 쓸 수 있음)
//AddTerm()의 사용조건 기억 못하면 개박살 나는거지 ㅋㅋㅋㅋ 이런 코드는 실전에선 절대 쓰면 안됨

//근데 생각해보니까 위에서처럼 정렬하지 말고 그냥 NewTerm()으로 해도 마지막으로 만들어진 객체 아니면 어쩌피 못쓰네?

//아! 그냥 공유 메모리 풀의 최악의 단점 아님? 이게?
//해결책은 => static Term* termArray(공유 메모리 풀)대신 객체 자신만의 private멤버변수로 동적배열이나 vector 가지고 있으면 되잖아...
//그러면 AddTerm 어쩌피 각자 따로 들어가서 아무 상관 없어지게 됨...



//생각해보니까 static Term* termArray의 한계니까 교수님 말대로 정렬까지 구현하는 걸로.... 어쩌피 시험 나올듯.


//결론) AddTerm()의 사용조건 = 무조건 마지막으로 만들어진, 가장 static termArray의 오른쪽에 있는(인덱스가 제일 높은)객체만 사용 가능한 함수
//--------------------------------------------------------------------------------------------------------------//





//5.곱셈 !!!! Mult()
//Add()이용하는 방법은 매우 비효율적, AddTerm(coef,exp) 방식을 사용해야 효율적임

//AddTerm을 이용한다
Polynomial Polynomial::Mult(Polynomial& b){
    Polynomial c; //for문 내에서 계속 갱신될 것
    c.start = free;
    //(매우 중요!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
    //내가 여기때문에 시간 많이 씀
    //지금 생성자에서 start랑 finish, terms를 p(0)로 초기화한 상태라서
    //무조건!!! c.start와 c.finish를 c생성할때 무조건 먼저 만들어주고 시작해야만 한다.
    c.finish = free - 1;
    c.terms = 0;
    //잊지마라 for문 쓰기 전에 c.start랑 c.finish, c.terms꼭 설정해줘야 함!

    //기본 전략 = 각 항별로 곱한 다음 다항식 2개를 만들어서 서로 더한다.
    for(int aPos = start;aPos<=finish;aPos++){
        for(int bPos = b.start;bPos<=b.finish;bPos++){

            //이게 지금 첫번째 bPos랑 a의 모든 항과 곱한 다항식

            //주의!!!!!!! multexp 지수는 더하는거다!!!!
            float multcoef = termArray[aPos].coef * b.termArray[bPos].coef;
            int multexp = termArray[aPos].exp + b.termArray[bPos].exp;//주의!!!!
            c.AddTerm(multcoef, multexp);
        }
    }
    return c;
}
//참고)댕글링 참조 때문에 반환값은 참조형이면 안된다. 반환값은 참조형이 아닌 것이 좋다.



double Polynomial::Eval(int num) {
    double result = 0;

    for (int i = start; i <= finish; i++) {//start부터 finish까지 전부 가져옴
        double current_coef = termArray[i].coef; //현재 coef
        int current_exp = termArray[i].exp; //현재 exp

        //#include <cmath> 으로 pow(진수,지수) 사용하기
        //'계수 * (num ^ 차수)'
        result += current_coef * pow(num, current_exp);
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
