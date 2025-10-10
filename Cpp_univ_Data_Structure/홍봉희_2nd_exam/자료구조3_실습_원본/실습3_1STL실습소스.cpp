//3.1절 STL
#include <iostream>
#include <list>
#include <memory> // std::allocator
template <typename T>
struct MyAllocator {
    using value_type = T;

    MyAllocator() = default;

    // 메모리 할당
    T* allocate(std::size_t n) {
        std::cout << "Allocating " << n << " elements" << std::endl;
        //:: scope resolution operator이고 전역 범위 연산자이다 
        return static_cast<T*>(::operator new(n * sizeof(T)));//**static_cast<T*>**는 타입 변환 연산자. 할당된 메모리는 일반적인 void* 포인터로 반환되므로, 이를 T* 타입으로 변환
    }

    // 메모리 해제
    void deallocate(T* p, std::size_t n) {
        std::cout << "Deallocating " << n << " elements" << std::endl;
        ::operator delete(p);
    }
};

int main() {
    // std::allocator<int>를 사용하는 std::list
    std::list<int, std::allocator<int>> my_list;

    // list에 값 추가
    my_list.push_back(10);
    my_list.push_back(20);

    // 리스트 출력
    for (const int& val : my_list) {
        std::cout << val << " ";
    }
    //
    // MyAllocator<int>를 사용하는 list
    std::list<int, MyAllocator<int>> my_list;

    my_list.push_back(1);
    my_list.push_back(2);

    for (const int& val : my_list) {
        std::cout << val << " ";
    }
    return 0;
}