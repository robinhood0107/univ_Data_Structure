#include <iostream>
#include <stack>
#include <deque> // std::deque 사용
#include <vector>
#include <queue>

int main() {
    // int 타입을 저장할 스택 생성 - ADAPTER
    std::stack<int, std::deque<int>> int_stack;

    // 스택에 원소 추가
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);

    // 스택에서 원소 삭제 및 출력
    std::cout << "Stack elements:" << std::endl;
    while (!int_stack.empty()) {
        std::cout << int_stack.top() << " "; // 스택의 가장 위에 있는 원소 출력
        int_stack.pop(); // 스택에서 원소 삭제
    }
    std::cout << std::endl;

    // std::vector를 사용하는 스택 예제
    std::stack<std::string, std::vector<std::string>> string_stack;

    // 스택에 문자열 추가
    string_stack.push("Hello");
    string_stack.push("World");

    // 스택에서 문자열 삭제 및 출력
    std::cout << "String stack elements:" << std::endl;
    while (!string_stack.empty()) {
        std::cout << string_stack.top() << " "; // 스택의 가장 위에 있는 원소 출력
        string_stack.pop(); // 스택에서 원소 삭제
    }
    std::cout << std::endl;
    //
    // 1. 기본적으로 최대 힙을 사용하는 priority_queue
    std::priority_queue<int> max_heap;

    // 요소 추가 (push)
    max_heap.push(10);
    max_heap.push(20);
    max_heap.push(5);

    // 최대 힙에서의 출력: 큰 순서대로 출력 (20, 10, 5)
    std::cout << "Max Heap (Priority Queue):" << std::endl;
    while (!max_heap.empty()) {
        std::cout << max_heap.top() << " "; // 가장 큰 값을 출력
        max_heap.pop(); // 가장 큰 값을 제거
    }
    std::cout << std::endl;

    // 2. 최소 힙을 사용하려면 std::greater<T>를 사용
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

    // 요소 추가 (push)
    min_heap.push(10);
    min_heap.push(20);
    min_heap.push(5);

    // 최소 힙에서의 출력: 작은 순서대로 출력 (5, 10, 20)
    std::cout << "Min Heap (Priority Queue):" << std::endl;
    while (!min_heap.empty()) {
        std::cout << min_heap.top() << " "; // 가장 작은 값을 출력
        min_heap.pop(); // 가장 작은 값을 제거
    }
    std::cout << std::endl;

    return 0;
}