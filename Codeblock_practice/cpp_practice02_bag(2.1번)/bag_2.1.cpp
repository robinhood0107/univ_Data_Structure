
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <vector>
using namespace std;

template <class T> class Bag;
template <class T> std::ostream& operator<<(std::ostream&, const Bag<T>&); // 출력 연산자 전방 선언

template <class T>
class Bag {
public:
    Bag(int bagCapacity = 10);
    ~Bag();

    bool IsFull() const;
    int Size() const;              // HowMany()
    bool IsEmpty() const;

    void Push(const T& x);         // 삽입 (필요 시 자동 리사이즈)
    T Pop();                       // 삭제 후 반환 (값으로 반환)
    const T& Peek() const;         // 맨 위(최근) 원소 조회 (비삭제)

    void Dump() const;             // 모든 원소 출력 (0..top)
    friend ostream& operator<< <>(ostream& os, const Bag<T>& b);


private:
    T* array;
    int capacity; // 배열 용량
    int top;      // 마지막 원소의 인덱스 (비어있으면 -1)
};

template <class T>
Bag<T>::Bag(int bagCapacity = 10):capacity{0},top{-1} {
    array = new T[0];
}


template <class T>
Bag<T>::~Bag() { delete[] array; }

template <class T>
int Bag<T>::Size() const { return top + 1; }

template <class T>
bool Bag<T>::IsEmpty() const { return top < 0; }

template <class T>
bool Bag<T>::IsFull() const { return top == capacity - 1; }


//////////////////////


template <class T>
void Bag<T>::Push(const T& x){
    arrr
}       // 삽입 (필요 시 자동 리사이즈)

template <class T>
T Bag<T>::Pop(){

}                     // 삭제 후 반환 (값으로 반환)

template <class T>
const T& Bag<T>::Peek() const{

}         // 맨 위(최근) 원소 조회 (비삭제)


template <class T>
void Bag<T>::Dump() const{

}           // 모든 원소 출력 (0..top)

template <class T>
friend ostream& operator<< <>(ostream& os, const Bag<T>& b){




    return os;
}


// ---- 예제용 Employee 클래스 ----
class Employee {
    string eno;
    string ename;
    int age{};
public:

};




// ---- 메뉴 관련 ----
enum Menu { PUSH = 1, POP, PEEK, DUMP, EXIT };
/*
    "1. PUSH (샘플 5명 일괄 삽입)\n";
    "2. POP  (하나 꺼내기: 가운데에서 꺼내고 마지막으로 대체)\n";
    "3. PEEK (맨 위 조회)\n";
    "4. DUMP (전체 출력)\n";
    "5. EXIT\n";
*/
static void printMenu() {
    cout << "\n===== 메뉴 =====\n";
    cout << "1. PUSH\n";
    cout << "2. POP\n";
    cout << "3. PEEK\n";
    cout << "4. DUMP\n";
    cout << "5. EXIT\n";
    cout << "선택 >> ";
}

int main() {
    Bag<Employee> b(4);

    // 샘플 데이터(값 타입)
    vector<Employee> data = {
        {"E001", "John", 30},
        {"E002", "Jane", 25},
        {"E003", "Mike", 28},
        {"E004", "Anna", 35},
        {"E005", "Tom", 40}
    };



int main() {
    Bag<Employee> b(4);

    // 샘플 데이터(값 타입)
    vector<Employee> data = {
        {"E001", "John", 30},
        {"E002", "Jane", 25},
        {"E003", "Mike", 28},
        {"E004", "Anna", 35},
        {"E005", "Tom", 40}
    };

    while (true) {
        printMenu();
        int choice;
        if (!(cin >> choice)) {
            cout << "\n입력이 종료되어 프로그램을 종료합니다.\n";
            break;
        }
        if (choice < 1 || choice > 5) {
            cout << "메뉴 번호(1~5)를 선택하세요.\n";
            continue;
        }

        try {
            switch (static_cast<Menu>(choice)) {
            case PUSH: {
                for (const auto& e : data) b.Push(e);
                cout << "PUSH 완료. Size=" << b.Size() << '\n';
                break;
            }
        case POP: {
                if (b.IsEmpty()) {
                    cout << "Bag이 비어 있습니다.\n";
                }
                else {
                    Employee out = b.Pop();
                    cout << "POP: " << out << " (Size=" << b.Size() << ")\n";
                }
                break;
            }
            case PEEK: {
                if (b.IsEmpty()) {
                    cout << "Bag이 비어 있습니다.\n";
                }
                else {
                    const Employee& t = b.Peek();
                    cout << "PEEK: " << t << " (Size=" << b.Size() << ")\n";
                }
                break;
            }
            case DUMP: {
                cout << "DUMP: ";
                b.Dump();
                break;
            }
            case EXIT:
                cout << "프로그램을 종료합니다.\n";
                return 0;
            default:
                break;
            }
        }
        catch (const exception& ex) {
            cout << "오류: " << ex.what() << '\n';
        }
        catch (const char* msg) {
            cout << "오류: " << msg << '\n';
        }
    }

    cout << "프로그램을 종료합니다.\n";
    return 0;
}
