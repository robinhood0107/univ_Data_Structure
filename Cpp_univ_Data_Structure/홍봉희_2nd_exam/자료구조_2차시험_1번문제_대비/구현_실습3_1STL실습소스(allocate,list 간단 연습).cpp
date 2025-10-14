#include <iostream>
#include <list>
#include <memory>
template <typename T>
struct MyAllocator {
    using value_type = T;

    MyAllocator() = default;

    // 메모리 할당

    //allocate 쓰는 이유
    //컨테이너 stl을 사용할 때 allocate를 이용하면 내 맘대로 메모리 할당/해제를 조작해서 나만의 new, delete를 만들어 줄 수 있음.
    T* allocate(std::size_t n) {
        //걍 내 스스로 공부하는 거니까 한글출력은 내가 창작해서 조정
        std::cout << "Allocating: 총 " << n << "개의 원소를 allocate 합니다(동적할당)" << "\n";

        return static_cast<T*>(::operator new(n * sizeof(T)));
        //global scope의 new를 연산자 오버로딩
        //원래 ::operator new()로 선언하면 void*라는 포인터 형식으로 반환됨. 이걸 강제로 형식 지정해서 바꿔주는 것.
    }

    //::operator delete, ::operator new에 대한 설명
    /*
    일단 하나하나 보자면
    :: (전역 범위 지정 연산자, Global Scope Resolution Operator)
    
    원래 ::는 네임스페이스나 클래스의 멤버를 호출할 때 지정하기 위해서 사용함
    근데 앞에 아무것도 없이 ::~ 이런식으로 작성하면 전역(Global) 네임스페이스를 의미함.
    뭔 말이냐면 가장 바깥 scope, c++의 가장 밖인 Global에 있는 함수를 지정하기 위해서 사용됨
    (예를 들어서 여기서 나온 operator가 global이라는 가장 외곽의 네임스페이스에 멤버함수로 있음)

    operator new, operator delete

    왜 ::(Global)에서 operator라는 키워드를 붙이는 거임? 
    -> 답변: 걍 연산자 오버로딩 문법 그 자체. 이게 오버로딩이라면 operator이라 붙여야 오버로딩 됨.
    설명 : 
    컴파일러가 이게 "연산자 오버로딩"임을 알아듣게 해야함. 
    클래스 안에서 operator+ 하던거랑 같은 것임. 단지 new/delete는 이런방식으로 적을 뿐.(operator new(), operator delete())
    클래스 안에서 연산자오버로딩 할때도 //Vector2D operator+(const Vector2D& other) const { return ~~ }// 이런 방식으로 하잖아.
    이걸 단지 ::operator로 Global단위로 적용하겠다는 거임.
    만약 전역인데 해당 클래스 내에서 <<를 전부 다 재정의 한다면(stl 다 영향받아서 조심히 사용해야 하는데)
    //::operator <<(~~~)// 이런 방식으로 적어 줄 수 있겠음.
    


    (이게 중요함. 나만의 allocate 쓰는 이유)
    delete와 ::operator delete, new와 ::operator new의 차이점
    
    이게 new나 delete라는 함수를 호출하게 되면 c++ 내부에서는 총 2가지 일이 발생함.
    
    만약 delete p;라는 명령어가 실행되면,
    1.객체의 소멸자를 호출함.
    delete p; 표현식에서 delete는 포인터 p가 가리키는 바로 그 객체의 소멸자를 호출함.
    컴파일러는 포인터 p의 "타입(type)"을 보고 어떤 클래스의 소멸자를 호출해야 할지 정확히 알 수 있기 때문.
    먼저 p라는 포인터로 가서 그 객체의 타입을 보고 해당 타입에 맞는 c++의 타입객체(int,string 같이 global단위같은 곳에서 미리 정의된거)의 소멸자를 호출
    (소멸자 호출되면 해당 객체는 당연 삭제되겠지?)


    2.불러온 객체의 메모리 해제
    (1에서 소멸자로 객체삭제는 했는데 아직 포인터에는 메모리 할당되있잖아)
    (이거 삭제해줘야 되는데 c++에선 정적이면 삭제하면 안되잖아(계속 쓸거니까))
    (그래서 너가 수동으로 해당 포인터를 delete 실행하서 삭제하는 것.)
    (정적할당이 애초에 기본이니까 동적할당해제(delete)는 너가 하라고)
    해당 타입 객체의 포인터에서 operator delete를 실행해버림.

    new도 마찬가지로 
    1.메모리 할당: 객체를 저장할 만큼의 메모리 공간을 확보.
    2.생성자 호출: 확보된 메모리 공간에 객체를 생성하고 생성자를 실행하여 초기화.

    이런식으로 객체호출이랑 메모리관리 이렇게 2가지 작업을 함

    근데 이게 vector에서는 내부에서 그냥 쓰고 마는건데 객체가 없는데 뭘 부른다는 거임. 
    temp용으로 잠깐 객체 만들었다가 지워버리는 것은 매우 비효율적임.

    난 2가지중 1개인 메모리 관리인 operator delete, operator new를 쓰고 싶은 것이니까

    이래서 vector,list... 이런거 쓸 때 delete 걍 안쓰고 allocate를 재정의해서 쓰는 것.
    (객체호출 필요없고 메모리관리만 할꺼니까)
    그래서 이것만 1가지만 쓰기 위해서 allocate stl 쓰고 ::operator new이런식으로 쓰는것.
    */


    // 메모리 해제
    void deallocate(T* p, std::size_t n) {
        std::cout << "Deallocateing: 총 " << n << "개의 원소를 deallocate(메모리 해제)" << "\n";
        ::operator delete(p);
        //global scope의 delete를 연산자 오버로딩
    }
};

int main() {
    // std::allocator<int>를 사용하는 std::list
    std::list<int, std::allocator<int>> my_list;
    //이거 명시적으로 allocator사용하겠다고 선언해줌.

    // list에 값 추가
    my_list.push_back(10);
    my_list.push_back(20);

    // 리스트 출력
    for (const int& val : my_list) {
        std::cout << val << " ";
    }

    // MyAllocator<int>를 사용하는 list
    std::list<int, MyAllocator<int>> my_list_custom_allocator;

    my_list_custom_allocator.push_back(1);
    my_list_custom_allocator.push_back(2);
    //이것처럼 MyAllocator라는 내 특제 allocate를 사용해도 잘 작동함

    for (const int& val : my_list_custom_allocator) {
        std::cout << val << " ";
    }
    return 0;
}