/*
C++에서 {12, 13, 345, ...}와 같이 중괄호로 감싸진 형태의 목록을 **Initializer List (초기화 리스트)**라고 부릅니다.

이것을 함수의 파라미터로 직접 받으려면 std::initializer_list<T> 라는 타입을 사용하거나, C++의 자동 형 변환을 이용해 
**std::vector<T>**로 받을 수 있습니다.

가장 편하고 직관적인 두 가지 방법을 알려드리겠습니다.

방법 1. std::initializer_list 사용 (가장 가벼운 방법)
이 방법은 벡터로 변환하는 과정 없이, {...} 목록 그 자체를 가볍게 받아옵니다. #include <initializer_list>가 필요합니다.

클래스 내부 함수 추가:

C++

#include <initializer_list> // 상단에 추가

// ... BST 클래스 내부 ...

// 다중 값 삽입 (Initializer List)
void Insert(std::initializer_list<int> list) {
    for (int x : list) {
        Insert(x); // 기존의 단일 삽입 함수 반복 호출
    }
}
사용법 (main 함수):

C++

tree.Insert({10, 20, 30, 40, 50}); // 변수 선언 없이 바로 넣기 가능
방법 2. std::vector 사용 (가장 범용적인 방법)
앞서 설명드린 것처럼 벡터를 인자로 받도록 만들어두면, {...} 형태도 자동으로 벡터로 변환되어 전달됩니다.

클래스 내부 함수 추가:

C++

#include <vector> // 상단에 추가

// ... BST 클래스 내부 ...

// 다중 값 삽입 (Vector)
void Insert(const std::vector<int>& list) {
    for (int x : list) {
        Insert(x);
    }
}
사용법 (main 함수):

C++

// 1. 변수에 담아서 넣기
vector<int> v = {12, 13, 345, 324};
tree.Insert(v);

// 2. 직접 넣기 (이것도 됩니다!)
tree.Insert({12, 13, 345, 324}); 
결론: 무엇을 써야 할까?
작성하신 코드(BST)의 목적을 고려할 때, **방법 2 (std::vector)**를 추천합니다. 이유:

{1, 2, 3} 처럼 직접 넣는 것도 되고,

main에서 rand()로 생성한 vector 변수를 넘기는 것도 되기 때문입니다. (범용성 최고)
*/