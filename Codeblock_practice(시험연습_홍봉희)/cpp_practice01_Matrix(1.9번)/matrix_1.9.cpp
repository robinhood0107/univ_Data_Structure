#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// implement the functions : add, sub, mult, transpose
class Matrix {
public:
    Matrix(int row = 0, int col = 0);
    Matrix(const Matrix&);                 // 복사 생성자
    ~Matrix();                             // Rule of Three: 소멸자
    int GetData(int maxrand = 9);          // 0~maxrand 난수 채우기
    Matrix Transpose() const;              // 전치
    Matrix Multiply(const Matrix& b) const;// 일반 곱
    Matrix Add(const Matrix& b) const;     // 덧셈
    Matrix Sub(const Matrix& b) const;     // 뺄셈
    Matrix Multiply2(const Matrix& b) const; // b를 내부에서 전치하여 곱(캐시 친화)
    int CompareRowCol(const Matrix& b) const; // (this->cols != b.rows) ? 1 : 0
    void operator=(const Matrix&);         // 대입 연산자(메모리 안전)

    friend ostream& operator << (ostream& stream, const Matrix& m);
    inline int Rows() const { return rows; }
    inline int Cols() const { return cols; }

private:
    int rows, cols;
    int* Term;
};




//Term[i * cols + j] (i,j)원소 이거 꼭 기억하자 이것만 기억해도 반은 간다.ㄴ


// ---- 구현부 ----
Matrix::Matrix(int row, int col) : rows(row), cols(col), Term(nullptr) {
    if (rows > 0 && cols > 0) Term = new int[rows * cols]{ 0 };
}

Matrix::Matrix(const Matrix& m) : rows(m.rows), cols(m.cols), Term(nullptr) {
	Term = new int[rows * cols];
    copy(m.Term, m.Term + rows * cols, Term);
}

Matrix::~Matrix() {
		delete [] Term;
}

void Matrix::operator=(const Matrix& m) {
    if (this == &m) { //자기 자신을 가리키는 포인터인지 확인
        return;
    }
	delete[] Term; //기존 메모리 꼭 해체하기
	rows = m.rows;
	cols = m.cols;
	Term = new int[rows * cols];
	std::copy(m.Term, m.Term + rows * cols, Term);
}

int Matrix::GetData(int maxrand) {
    if (!Term) return -1;
    for (int j = 0; j < rows * cols; j++) {
        Term[j] = rand() % (maxrand + 1);
    }
    return 0;
}

Matrix Matrix::Transpose() const {
	Matrix my(cols,rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // 원본의 (i, j) 요소를 목적지의 (j, i) 위치로 복사
            my.Term[j * my.cols + i] = Term[i * cols + j];
        }
    }
	return my;
}

Matrix Matrix::Multiply(const Matrix& b) const {
	if(!CompareRowCol(b)){
			Matrix temp(rows, b.cols);
			for(int i=0;i<rows;i++){
				for(int j=0;j<b.cols;j++){
					temp.Term[i * temp.cols + j] = 0;
					for(int k = 0; k < cols; ++k) {
						// 현재 행렬의 (i, k) 요소 * 인자 행렬의 (k, j) 요소
						temp.Term[i * temp.cols + j] += Term[i * cols + k] * b.Term[k * b.cols + j];
					}
				}
			}
            return temp;
		}
		else{
			return Matrix();
			//return this;
		}
}

Matrix Matrix::Add(const Matrix& b) const {
	Matrix temp(rows, cols);
	for (int i = 0; i < rows * cols; ++i){
        temp.Term[i] = Term[i] + b.Term[i]; //그냥 1차원 배열이라 같은 인덱스 번호끼리 더하기
    }
    return temp;
}

Matrix Matrix::Sub(const Matrix& b) const {
	Matrix temp(rows, cols);
	for (int i = 0; i < rows * cols; ++i){
        temp.Term[i] = Term[i] - b.Term[i]; //그냥 1차원 배열이라 같은 인덱스 번호끼리 빼기
    }
    return temp;
}


//나 이거 처음에 뭔소리인지 몰랐음
//지금 여기 있는 모든 멤버함수 전부 다 짤 줄 알면 된다.


// Multiply2: b를 내부에서 전치해 두고 (행 x 행) 내적 형태로 계산
Matrix Matrix::Multiply2(const Matrix& b) const {
	Matrix b_Transpose = b.Transpose();
	Matrix temp(rows, b.cols);
	//(A의 i번째 행)과 (B?의 j번째 행)의 내적 계산 (행X행 내적)
    for (int i = 0; i < this->rows; i++) {       // 결과 행렬의 행 (A의 행)
        for (int j = 0; j < b.cols; j++) {       // 결과 행렬의 열 (B?의 행)
            double sum = 0.0;
            for (int k = 0; k < this->cols; k++) { // 내적을 위한 반복 (A의 열)
                // A의 (i, k) 요소 * B?의 (j, k) 요소
                sum += this->Term[i * this->cols + k] * b_Transpose.Term[j * b_Transpose.cols + k];
            }
            temp.Term[i * temp.cols + j] = sum;
        }
    }
    return temp;
}

int Matrix::CompareRowCol(const Matrix& b) const {
    return (cols != b.rows) ? 1 : 0;
}


//특히 이 ostream 잘 짤 수 있어야 한다. 이중 for문 돌려서 행렬 출력하는거 특히!!!! 마지막 return까지

//Term[i * cols + j] (i,j)원소 이거 꼭 기억하자 이것만 기억해도 반은 간다.

ostream& operator << (ostream& stream, const Matrix& m){
    stream << "\n";
    for (size_t i = 0; i < m.rows; ++i) {
        for (size_t j = 0; j < m.cols; ++j) {
            stream << " " << m.Term[i * m.cols + j] ;
        }
        stream << std::endl;
    }
    return stream;
}




// ---- 메뉴 관련 ----
enum Menu { INPUT = 1, SHOW_A, SHOW_B, TRNSPOSE, ADD, SUBTRACT, MULTIPLY };

static void printMenu() {
    cout << "\n===== Matrix Menu =====\n";
    cout << "1) INPUT       : A, B 크기 설정 및 랜덤 채우기\n";
    cout << "2) SHOW_A      : 행렬 A 출력\n";
    cout << "3) SHOW_B      : 행렬 B 출력\n";
    cout << "4) TRNSPOSE    : B^T 출력\n";
    cout << "5) ADD         : C = C + D (동형 필요)\n";
    cout << "6) SUBTRACT    : D = C - D (동형 필요)\n";
    cout << "7) MULTIPLY    : C = A * B (또는 Multiply2 사용)\n";
    cout << "기타 입력      : 종료\n";
    cout << "선택> ";
}

int main() {
    srand(49);

    // 기본 초기 크기
    Matrix a(3, 4);
    Matrix b(4, 5);
    Matrix c(3, 5); // A*B 결과 크기에 맞춤
    Matrix d(3, 5); // Add/Sub 테스트용 동형 행렬
    Matrix t(5, 4); // B^T 크기

    // 초기 데이터
    a.GetData(); b.GetData(); c.GetData(); d.GetData();

    while (true) {
        printMenu();
        int sel;
        if (!(cin >> sel)) break; // 숫자 아닌 입력 시 종료
        if (sel < 1 || sel > 7) break;

        switch (static_cast<Menu>(sel)) {
        case INPUT: {
            int ar, ac, br, bc;
            cout << "Enter rows, cols for A (e.g., 3 4): ";
            cin >> ar >> ac;
            cout << "Enter rows, cols for B (e.g., 4 5): ";
            cin >> br >> bc;

            if (ar <= 0 || ac <= 0 || br <= 0 || bc <= 0) {
                cout << "양수 크기만 허용됩니다.\n";
                break;
            }
            a = Matrix(ar, ac);
            break;

        case TRNSPOSE: {
            if (b.Rows() == 0) { cout << "B가 비어 있습니다.\n"; break; }
            t = b.Transpose();
            cout << "Transpose(B) = B^T (" << t.Rows() << "x" << t.Cols() << ")\n";
            cout << t;
            break;
        }

        case ADD: {
            // C = A + D  (동형 필요)
            if (a.Rows() == 0 || d.Rows() == 0) { cout << "A 또는 D가 비어 있습니다.\n"; break; }
            if (c.Rows() != d.Rows() || c.Cols() != d.Cols()) {
                cout << "Add 불가: A와 D의 크기가 다릅니다.\n";
                break;
            }
            c = c.Add(d);
            cout << c;
            break;
        }

        case SUBTRACT: {
            // D = C - D (동형 필요)
            if (c.Rows() == 0 || d.Rows() == 0) { cout << "C 또는 D가 비어 있습니다.\n"; break; }
            if (c.Rows() != d.Rows() || c.Cols() != d.Cols()) {
                cout << "Sub 불가: C와 D의 크기가 다릅니다.\n";
                break;
            }
            d = c.Sub(d);
            cout << d;
            break;
        }

        case MULTIPLY: {
            if (a.Rows() == 0 || b.Rows() == 0) { cout << "A 또는 B가 비어 있습니다.\n"; break; }
            if (a.Cols() != b.Rows()) {
                cout << "곱셈 불가: A.cols != B.rows\n";
                break;
            }
            // 일반 곱
            c = a.Multiply(b);
            cout << "C = A * B (기본 곱) (" << c.Rows() << "x" << c.Cols() << ")\n";
            cout << c;

            // 전치 활용 곱
            Matrix c2 = a.Multiply2(b);
            cout << "C2 = A * B (Transpose 활용 Multiply2) (" << c2.Rows() << "x" << c2.Cols() << ")\n";
            cout << c2;
            break;
        }

        default:
            // 도달하지 않음
            break;
        }
    }

    cout << "프로그램을 종료합니다.\n";
    return 0;
}
}