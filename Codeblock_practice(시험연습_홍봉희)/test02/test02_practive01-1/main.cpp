#include <iostream>
#include <list>
#include <memory>
template <typename T>
struct MyAllocator {
    using value_type = T;

    MyAllocator() = default;

    // 메모리 할당
    T* allocate(std::size_t n) {
    }

    // 메모리 해제
    void deallocate(T* p, std::size_t n) {
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
