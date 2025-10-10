#include <iostream>
#include <stack>
#include <deque> // std::deque 사용
#include <vector>
#include <queue>

int main() {
    // int 타입을 저장할 스택 생성 - ADAPTER
    std::stack<int, std::deque<int>> int_stack;
    //stack stl에 대한 설명:
    //stack은 선언할 때 stack<타입,컨테이너>로 이루어져 있는데,
    //기본은 컨테이너로 deque를 사용함
    //하지만 대신에 vector나 list같이 다른 컨테이너 넣어도 됨!!(커스텀 가능)
    
    //deque(덱)은 앞 뒤가 전부 뚫린 터널같은 것
    //데이터 중복 허용되는 양방향 입출력 가능한 array라고 생각하셈
    //덱 특징:
        //1.양방향 삽입/삭제: 앞(front)과 뒤(rear) 양쪽에서 모두 데이터를 넣고(push) 뺄(pop) 수 있습니다.
        //2.인덱싱 가능: 리스트(list)처럼 인덱스를 통해 특정 위치의 데이터에 바로 접근할 수 있습니다.
        //3.순서 유지: 데이터는 입력된 순서대로 저장됩니다.
    //아무튼 간에 기본은 stack은 <int,deque>로 이루어져 있다.
    //원래는 평상시 사용할때 stack<int>라고 선언하는게 일반적인 방법임!    


    //근데 이걸 왜 설명하냐? 
    //--> 밑에서 deque 대신에 vector랑 heap을 사용할꺼임
    
    //근데 왜 stack은 deque를 기본으로 사용함?
    //stack은 어쩌피 LIFO니까 한쪽 끝만 빼고 넣는 기능만 있으면 되서 
    //pop_back이랑 push_back만 효율적이면 된다.

    //3개 주요 컨테이너중에선 deque가 효율적임.
    //컨테이너	장점	단점
    /*
    std::deque	
        장점✅ 양쪽 끝에서의 삽입/삭제가 빠름.	
        단점❌ vector보다 약간의 메모리 오버헤드가 있음.

    std::vector	
        장점✅ 메모리가 연속적이어서 캐시 효율이 좋음.(근데 이건 다른 배열도 다 똑같음)
        단점⚠️ 용량이 꽉 찼을 때 재할당 비용이 발생할 수 있음. (모든 원소를 복사해야 함)
    //vector는 메모리 찼을때 죄다 복사해서 새로 할당하는 과정이 넘 비효율적임!!!
    
    std::list	
        장점✅ 삽입/삭제 시 원소 재배치가 없음.	
        단점❌ 각 원소마다 포인터를 위한 메모리 오버헤드가 크고, 캐시 효율이 떨어짐.
    */

    //메모리 오버헤드?
    //데이터를 위한 데이터로,포인터 같은걸 메모리 오버헤드라고 생각하면 됨.

    //메모리 오버헤드 AI 설명
    /*메모리 오버헤드란 실제 데이터 외에, 그 데이터를 관리하기 위해 추가로 드는 메모리입니다.
    간단히 말해, 물건을 포장할 때 쓰는 **'택배 상자'**나 '뽁뽁이' 같은 개념이죠.
    물건(데이터)을 관리하려면 포장(추가 메모리)이 꼭 필요한 것처럼, 프로그래밍에서도 데이터를 관리하기 위한 부가 정보 때문에 메모리 오버헤드가 발생합니다.
    예를 들어, 연결 리스트에서는 실제 데이터와 함께 다음 데이터를 가리키는 **주소값(포인터)**이 필요한데, 바로 이 '주소값'이 메모리 오버헤드입니다.*/

    // 스택에 원소 추가
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);
    //stack stl은 push로 넣는다.

    // 스택에서 원소 삭제 및 출력
    std::cout << "Stack elements:" << std::endl;
    while (!int_stack.empty()) {
        std::cout << int_stack.top() << " "; // 스택의 가장 위에 있는 원소 출력
        int_stack.pop(); // 스택에서 원소 삭제
    }
    std::cout << std::endl;

    //pop,push,top,size,empty라는 멤버함수가 있고
    //swap(stack1,stack2)으로 두 스택 내용 바꿀 수 있음.
    //empty메서드는 비어있으면 1(true)

    //​pop의 반환값은 void이며 마지막 원소가 아닙니다. (파이썬 list의 pop()과 다릅니다)
    //push,top은 당연히 void인데 c++은 pop도 void임!!!!(파이썬이랑 다름)
    
    //stack을 완전히 비우고 싶으면 while (S.size()) S.pop();으로 비워야 함.(clear 없음) 
    //(파이썬이랑 다름)std::stack에는 clear 멤버 함수가 없습니다. 만약 stack의 모든 원소를 pop하고싶다면 while (S.size()) S.pop()으로 처리해줘야 합니다.

    //주의:비어있는 stack에서 pop, top을 호출하는 것은 UB이며 보통 런타임 에러를 발생시킵니다.
    //비어있는데 pop이나 top하면 런타임 오류 발생하니까(문법오류), 무조건 empty()메서드로 확인 해줘야 함.
    
    //그리고 std::stack은 이터레이터 없음. top만 접근 가능.
    //std::deque와 달리 [] 연산자나 iterator가 없기 때문에 top() 이외의 원소에는 접근할 수 없습니다.
    


    //push는 emplace로 대체할 수 있다. 
    //push를 쓰던지, emplace를 쓰던지 각각 장단점이 있으니 자신에게 맞는 함수를 사용하면 됩니다.
    //emplace함수란?(영어로 "배치한다"란 뜻임)
    /*
    emplace를 사용하는 컨테이너들은 vector, queue, map, list가 있음
    특징)(공식 레퍼)
    0.임시객체를 생성하지 않고 복사를 안해서 효율적인 삽입을 추구하는 함수임

    1.컨테이너에 키가 있는 요소가 없는 경우 지정된 인수로 구성된 컨테이너에 새 요소를 삽입한다.
    //map이 아니라면 그냥 원소를 새로 삽입하고, 
    //map의 경우는 이미 있는 key 값의 원소를 갱신하고 싶지 않고 새로 추가하고 싶을 때 유용함. 
        (map 내부의 empalce 원리: 원소를 생성자에 매개변수로 전달하는 방식으로 추가한다. 따라서 std::map 내부에서 직접 생성하게 된다.)
    
    2.불필요한 복사 또는 이동 작업을 피하면서 새로운 요소를 구성할 수 있다.
    //emplace를 사용하면 사용자가 요소만 넣어줘도 사용자가 원하는 컨테이너를 찾고 넣어준다.
    
    3.반복자 및 참조자가 무효화되지 않는다.
    //push_back과 비교해보면 쉬움.
    예를 들어 원소가 여러 개 담긴 vector가 있다고 가정해보자.
    우선, iterator로 vector의 시작 원소를 가리키게 하고
    이후 여러 원소들을 다시 push_back해준 후
    반복자(iter)를 통해 vector의 모든 원소들을 출력하게 하면 모두 출력되지 않는다.

    왜냐하면 vector의 push_back은 단지 원소를 넣을 뿐, 
    용량을 늘리지 않는 삽입 작업이고, 
    그렇기 때문에 그 위치를 지나가는 요소를 가리키는 반복자 및 포인터 (iterator)를 무효화하기 때문이다. 

    하지만, emplace 함수는 생성에 필요한 인자를 받아 내부에서 생성 및 삽입이 이루어지기 때문에 반복자 및 참조자가 무효화되지 않는다는 것이다.

    //ai에게 emplace의 "반복자 및 참조자가 무효화되지 않는다."에 대한 설명을 비유 시켜봄
    도서관 책장에 꽂힌 책들을 상상해 보세요.

    컨테이너 (ex: std::vector, std::list): 책장 전체
    요소 (element): 책 한 권 한 권
    반복자(iterator) / 참조자(reference): 특정 책을 가리키는 '책갈피'

    //"무효화된다"는 것은 무슨 뜻일까요?
        책장에 책을 추가하거나 정리할 때를 생각해 보세요.

        상황 1: 책장이 꽉 차서 더 큰 책장으로 이사하는 경우 (vector에서 주로 발생)
        지금 std::vector라는 빽빽한 책장에 책을 한 권 더 꽂으려고 하는데, 공간이 없습니다. 그럼 어쩔 수 없이 더 큰 새 책장을 가져와 모든 책을 그대로 옮겨야 합니다.
        이때, 원래 책장에 꽂아뒀던 '책갈피'는 어떻게 될까요?
        당연히 이사 간 새 책장에서는 아무 쓸모가 없어집니다. 책은 이미 다른 곳에 있으니까요. 이것이 바로 책갈피, 즉 반복자/참조자가 '무효화(invalidated)'되었다고 말하는 상황입니다.

    //"무효화되지 않는다"는 것은 무슨 뜻일까요?
        이 말은 주로 std::list나 std::map 같은 자료구조에 해당하는 중요한 특징입니다.

        상황 2: 책마다 고유 공간이 있고, 새 책은 빈 곳에 넣는 경우 (list에서 주로 발생)
        std::list는 vector처럼 책들이 딱 붙어있는 책장이 아니라, **각 책이 자기만의 독립된 공간(칸)**을 가지고 있고, 각 칸이 '다음 책은 저기 있어'라고 서로 연결된 방식입니다.
        여기에 새 책을 emplace로 추가하면 어떻게 될까요?
        그냥 빈 공간에 새 칸을 만들고 기존 책들과 연결만 시켜주면 끝입니다. 기존에 있던 다른 책들은 전혀 자리를 옮길 필요가 없습니다.
        따라서 내가 다른 책에 꽂아뒀던 '책갈피'는 전혀 영향을 받지 않고 계속 그 책을 올바르게 가리킵니다. 이것이 바로 **반복자/참조자가 '무효화되지 않는다'**는 의미입니다.

    //결론
        **"emplace의 반복자 및 참조자가 무효화되지 않는다"**는 말은,
        std::list나 std::map 같은 자료구조에 emplace로 새 데이터를 추가해도, 기존에 있던 다른 데이터들을 가리키던 '책갈피(반복자/참조자)'들은 전혀 영향을 받지 않고 계속 유효하다는 뜻입니다.
        이는 데이터를 중간에 자주 추가하거나 삭제하면서도 기존 데이터의 위치를 계속 추적해야 할 때 매우 중요한 장점이 됩니다.
    */
    
    //emplace의 단점....
    //emplace는 혼자 알고리즘 공부할 때 사용해라!!!
    //emplace는 호환성이 떨어짐.
    //Microsoft Visual C++ 표준 라이브러리 구현 공식 관리자가 버그가 있는데 고치진 않았다라고 함...
    //암튼 혼자 하는 알고리즘 또는 개인 프로젝트에서는 유용하나, 
    //다른 사람과 같이 할 때는 웬만하면 push_back, insert를 사용하는 것을 추천


    //좋은 레퍼: https://blog.naver.com/jinhan814/222446815488








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
    //deque랑 크게 다른건 없지만 바꿔 쓸 수 있다.



    //std::priority_queue<int> max_heap; 에 대한 설명
    /*
    //queue는 그냥 FIFO인데 priority_queue는 우선순위가 큰 것을 FIFO(큰값을 우선순위가 높다고 봄)
    //내부적으로 heap구조를 사용함.
    
    pq.push(10); // pq: [10]
    pq.push(30); // 30이 더 크므로 top으로 -> [30, 10]
    pq.push(20); // 30이 여전히 가장 큼 -> [30, 20, 10] (내부적으로 heap 구조)

    // 우선순위가 가장 높은(가장 큰) 30을 확인(top)하고 제거(pop)
    std::cout << pq.top() << std::endl; // 30 출력
    pq.pop();

    // 남은 원소 중 가장 큰 20을 확인하고 제거
    std::cout << pq.top() << std::endl; // 20 출력
    pq.pop();

    이런 방식임.

    //중요: 내림차순, 오름차순 결정
    priority_queue은 내림차순(가장 큰값이 top)기본이고 <T,std::vector<T>,std::less<T>>가 기본값임 (백터로 완전 이진트리 heap을 구현함, tree 배울때 배운다)

    가장 작은 수가 맨 앞(top)으로 오름차순 하고 싶으면 std::greater<T> 넣어주면 된다.

    쉽게 외우는 법
    priority_queue는 기본이 가장 큰 값이 우선순위가 높은 것이고 std::less이다
    */

    //그리고 잊지 말아야 되는게 queue는 기본적으로 tail로 들어가서 top으로 나온다는 것이다 (FIFO니까 가장 오래된게 top)

    // 1. 기본적으로 최대 힙을 사용하는 priority_queue
    //가장 큰 값이 우선순위가 높은 heap을 이용
    std::priority_queue<int> max_heap;

    // 요소 추가 (push)
    max_heap.push(10); //[10]
    max_heap.push(20); //[20,10] //20을 top으로 함
    max_heap.push(5);  //[20,10,5]

    // 최대 힙에서의 출력: 큰 순서대로 출력 (20, 10, 5)
    std::cout << "Max Heap (Priority Queue):" << std::endl;

    // 2. 최소 힙을 사용하려면 std::greater<T>를 사용
    std::priority_queue<int,std::vector<int>,std::greater<int>> min_heap;
    // 요소 추가 (push)
    min_heap.push(10); //[10]
    min_heap.push(20); //[10,20]
    min_heap.push(5);  //[5,10,20] //5가 10보다 작으니까 //완전 이진 tree:부모가 자식노드보다 작음

    // 최소 힙에서의 출력: 작은 순서대로 출력 (5, 10, 20)
    std::cout << "Min Heap (Priority Queue):" << std::endl;
    while (!min_heap.empty()) {
        std::cout << min_heap.top() << " "; // 가장 작은 값을 출력
        min_heap.pop(); // 가장 작은 값을 제거
    }
    std::cout << std::endl;

    return 0;
}