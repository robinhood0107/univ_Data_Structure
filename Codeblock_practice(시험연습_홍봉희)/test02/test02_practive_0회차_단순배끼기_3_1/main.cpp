#include <iostream>
#include <list>
#include <memory>
template <typename T>
struct MyAllocator {
    using value_type = T;

    MyAllocator() = default;

    // 메모리 할당
    T* allocate(std::size_t n) {
        std::cout << "Allocating: 총 " << n << "개의 원소를 allocate 합니다(동적할당)" << "\n";
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    // 메모리 해제
    void deallocate(T* p, std::size_t n) {
        std::cout << "Deallocating: 총 " << n << "개의 원소를 deallocate 합니다(메모리 해제)" << "\n";
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
    std::list<int, MyAllocator<int>> my_list_custom_allocator;

    my_list_custom_allocator.push_back(1);
    my_list_custom_allocator.push_back(2);

    for (const int& val : my_list_custom_allocator) {
        std::cout << val << " ";
    }
    return 0;
}
