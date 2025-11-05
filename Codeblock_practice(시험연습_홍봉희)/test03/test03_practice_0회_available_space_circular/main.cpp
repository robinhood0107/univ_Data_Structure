#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <time.h>

using namespace std;

class Node{
    friend class CircularList;
    int data;
    Node* link;
public:
    Node(){}
    Node(int element){
        data = element;
        link = nullptr;
    }
};

class CircularList{
private:
    Node* last; //last가 리스트의 header 노드를 가킨다고 생각해라 //데이터 비어있으면 last->link = last
    static Node* av;
public:
    CircularList(){
        last = new Node();
        last -> link = last;
    }
    void Add(int element);
    bool Delete(int element);
    void Show();
    bool Search(int element);
    CircularList operator+(const CircularList& lb);

    int SolveJosephus(vector<int> &testData, int K);

    Node* GetNode(); //새 노드 할당(av에서 가져오거나 new Node)
    void RetNode(Node* x);
    void Erase();
};


    Node* CircularList::GetNode(){
        //새 노드 할당(av에서 가져오거나 new Node)
        //항상 먼저 생각할 것
        //1.일단 새로운 노드포인터를 일단 1개 만듦
        //if 판단 기준은 av다
        //2. av면 x는 av 포인터로 옮기고, (중요) av는 av->link로 다음 노드로 이동한다.
        //(계속 이런식으로 노드를 다음 노드(->link)로 옮기고 옮기고.. 이런 방식이다!!!
        //아니면 그냥 노드를 새로 부여
        //3. 꼭 return x;

        Node* x;
        if(av){
            x = av;
            av = av->link;
            //내가 틀린 지점!!!
        }else{
            x = new Node;
        }
        return x;
    }
    void CircularList::RetNode(Node* x){
        //동적 할당 된 것을 av로 버린다!!! 이것만 꼭 기억하셈
        //버리는 방법 -> av를 현재 x로 지정해주고
        //x->link로 다음 노드는 av를 가리키게 하면 된다
        //이정도는 암기해주기
        x->link = av;
        av = x;
        //x가 av의 last가 되도록
    }
    void CircularList::Show(){
        //출력함수
        //head에는 아무 데이터도 안가지고 있음을 무조건 기억하기
        //last는 결국 header임을 반드시 기억하고, current는 header->link(첫번째 데이터)를 가리킨 다는 사실 기억

        Node* header = last;
        Node* current = header->link;
        //이 2개는 확실하게 암기하고 있기

        //current == header(리스트 빔,if) current != header(리스트 있음,while)으로 구별하는 것 기억하고 있기

        //current == header로 리스트가 비어있는지 반드시 확인
        if(current == header){
            cout << "[리스트 비어있음]" << "\n";
            return;
            //비어있으면 아무것도 출력 안함
        }

        //current가 header로 다시 돌아올때까지 순회!!!!!!
        //현재 노드 출력하고 다음 노드로 current 이동시키기
        //현재가 header가 아니라면 "->" 도 출력
        cout << "[";
        while(current != header){
            cout << current->data; //출력
            current = current->link;//다음노드로 이동
            if(current != header){
                cout << "->";
            }
        }
        cout << "]" << "\n";
    }

    void CircularList::Add(int element){
        //add 이거 구현할 때는 딱 3가지 필요하다고 알고 있기
        //일단 GetNode를 통해 비어있는 새로운 Node* 노드(newNode)로 만들고, 거기에 int element를 집어넣기(새로운 element 노드)

        //header = last인건 당연하고, q(이전노드) = header, p(다음노드) = header->link;를 이용해서
        //삽입위치는 반드시 p가 header가 아니면서(아직 순회 안끝나면서)
        //&& (p->data > element(역전)가 되는 지점인) p->data < element가 만족하지 않는 지점 이 지점까지 while로 이동만 함
        //이 whlie문을 제대로 외워주면 됨
        Node* newnode = GetNode();
        newnode->data = element; //값 집어넣기는 이렇게 data에 넣어주면 된다

        Node* header = last;
        Node* q = header;
        Node* p = header->link;



        while(p!=header && p->data < element){ //이 조건식 반드시 암기 //딱 경계선 불만족 할때만 while
            q=p; //q는 p로 오른쪽 한칸 이동
            p = p->link; //p는 p->link로 오른쪽 한칸 이동
        }

        //이동 다 했으면 삽입
        //q의 다음노드로 newnode를 설정하고 newnode의 다음노드를 p로 설정해서 중간에 끼워 넣는다고 생각해라!!!!
        q->link = newnode;
        newnode->link = p;
    }


    bool CircularList::Delete(int element){
        //준비는 add와 똑같이 3가지
        //header = last, q = header, p= header->link

        //p!=header로 전체 순회하면서
        //p->data == element일 때 (찾았을 경우) p를 건너뛰도록 q를 수정하고 해당 p는 RetNode에 넣어서 av로 편입시킴.
        //q -> p -> (p->link)  ==>  q -> (p->link) 하려면 q->link = p->link가 되도록 p를 건너뛰고
        //그 다음 RetNode(p);

        //못찾을 경우는 각각 q랑 p 오른쪽으로 한칸 이동시키기

        Node* header = last;
        Node* q = header;
        Node* p = header->link;

        while(p!=header){
            if(p->data == element){
                q->link = p->link;
                RetNode(p);
                return true;
            }
            else{
                q = p;
                p = p->link;
            }
        }
    return false;
    }

    bool CircularList::Search(int element){
        //오름차순 search
        //Show처럼 header = last랑 current = header->link를 준비

        //조건식 암기
        // current가 header으로 돌아오지 않은 상태에서(순회 중)
        // current의 데이터가 element보다 "작거나 같은" 상태에서만 whlie 지속시키기
        //element가 current->data보다 크면 지나친 상태인 것임
        // 암튼 조건식 이정도는 외워줘라
        //element가 크면 안된다!!!! while동안 element가 작거나 같아야 한다!!!!

        Node* header = last;
        Node* current = header->link; //current는 첫번째 데이터 노드!!! 이거 꼭 기억해라!!!


        while(current != header && current->data <= element){
            if(current->data == element){
                //찾았을 경우 바로 true
                return true;
            }
            //아니면 다음 노드로 넘어가기
            current = current->link;
        }
    //루프 종료되었으면 없다는 것
    return false;
    }

    void CircularList::Erase(){
        //Show랑 Search랑 비슷한데 살짝 다르다
        //firstData = header->link로 설정한 다음에
        //비어있는지 아닌지 firstData == header(if) firstData != header(while)로 확인
        //current = firstData 이후 current는 리스트의 마지막 직전 노드(current->link != header인 것)으로 쭉 이동하고
        //firstData 그대로 있으면서
        //current->link인 last(header)를 av에 연결한다(즉 현재 연결리스트의 last랑 av포인터랑 그대로 연결시킨다고 생각하면 된다)
        //그리고 av의 새로운 시작 포인터는 firstData로 설정시켜줌

        //그리고 필수적으로 반드시 header->link = header로 header가 자기 자신을 가리키게 해서 초기 리스트 상태로 되돌려 주면 된다

        Node* header = last;
        Node* firstData = header->link;


        if(firstData == header){
            return;
        }

        Node* current = firstData;
        while (current->link != header){
            current = current->link;
            //current를 마지막 데이터 노드까지 이동시키는 작업
        }

        current->link = av;

        av = firstData;

        header->link = header;
    }

    CircularList CircularList::operator+(const CircularList& lb){
    //merge 함수
    //새로운 CircularList를 생성한 다음에
    CircularList lc;

    //각 리스트의 헤더를 전부 정의 headerA = this->last; headerB = lb.last; 이런 방식
    //그리고 A를 순회할 포인터 pA = headerA->link;, B를 순회할 포인터 pB = headerB->link; 설정
    Node* headerA = this->last; // 나의 헤더
    Node* headerB = lb.last;    // lb의 헤더
    Node* headerC = lc.last;    // lc의 헤더

    Node* pA = headerA->link; // 'A' 리스트를 순회할 포인터
    Node* pB = headerB->link; // 'B' 리스트를 순회할 포인터

    Node* q = headerC;
    //q는 무조건 항상 lc의 마지막 데이터 노드를 가리킨다고 고정시켜두기
    //일단 시작은 headerC

    //pA랑 pB가 둘다 동시에 비어있지 않은 경우(둘 다 헤더 안만난 경우를 탐색)
    //둘 죽 더 작은 값을 먼저 넣는 것!!!!! 그래서 if도 작은 값일 경우 넣는 거다
    while (pA != headerA && pB != headerB) {
        Node* newNode = GetNode();  //새로운 노드 부르기

        if (pA->data < pB->data) { //A가 작은 경우
            newNode->data = pA->data;
            pA = pA->link; // A만 집어 넣은 다음에 A만 다음 칸으로
        }
        else if (pA->data > pB->data) {//B가 작은 경우
            newNode->data = pB->data;
            pB = pB->link; // B만 다음 칸으로
        }
        else{ //서로 같은 경우에는 a만 추가하고 반드시 a,b 둘 다 다음칸으로 옮겨줘야 함!!!!
            newNode->data = pA->data;
            pA = pA->link;
            pB = pB->link;
        }

        //'lc'의 꼬리(q)에 새 노드를 직접 연결
        //최종적으로 (q -> newNode -> headerC) 만든다고 기억하면 된다!!!!

        newNode->link = headerC; //새 노드는 헤더를 가리킨다
        q->link = newNode; //이전의 last였던 q가 newNode를 가리킨다
        q = newNode; // newNode가 꼬리가 된다
    }

    //나머지 A삽입
    while(pA != headerA){
        Node* newNode = GetNode(); //새로운 노드 가져와서
        newNode->data = pA->data; //데이터 복사
        pA = pA->link; //pA 다음으로 이동시키기

        //마찬가지로 lc에 꼬리 삽입
        //(q -> newNode -> headerC) 만든다고 기억하면 된다!!!!
        newNode->link = headerC;
        q->link = newNode;
        q = newNode; //q위치 갱신 이거 꼭 해야지 newNode와 q가 꼬리가 된다!!!
    }
    //나머지 B삽입
    while(pB != headerB){
        Node* newNode = GetNode(); //새로운 노드 가져와서
        newNode->data = pB->data; //데이터 복사
        pB = pB->link; //다음 노드로 이동

        //마찬가지로 lc에 꼬리 삽입
        //(q -> newNode -> headerC) 만든다고 기억하면 된다!!!!
        newNode->link = headerC;
        q->link = newNode;
        q = newNode; //q위치 갱신 이거 꼭 해야지 newNode와 q가 꼬리가 된다!!!
    }


    //마지막에 최종 lc 꼭 반환해라
    return lc;
    }



    int CircularList::SolveJosephus(vector<int> &testData, int K){
    //일단 리스트를 깨끗하게 Erase()를 통해서 비움
    this->Erase();

    //2. vector 받아서 리스트 삽입(배열일수도 있고 백터일수도 있고 암튼 입력을 받아야 한다)
    //아마 getline으로 받을 것 같아
    for (int i = 0; i < testData.size(); i++) {
        this->Add(testData[i]);
    }

    cout << "\n[요세푸스 시작 리스트]: ";
    this->Show();

    //그리고 header = last, p = header로 설정하기
    Node* header = last;
    Node* p = header;

    //총 N명중에서 N-1명을 제거해서 마지막 1명을 남겨야 한다
    for(int i=0; i< testData.size()-1; i++){ //N-1번 반복

        //삭제할 노드 직전까지 포인터 p를 이동시키면 된다
        //p는 header에서 시작하므로 만약 k번째를 삭제시켜야 한다고 하면
        //삭제할 대상은 p의 다음 노드인 k번 째
        //즉 p의 경우엔 k-1번 이동하면 된다!!!!
        for (int j = 0; j < K - 1; j++) { //그래서 k-1 반복
            //p를 다음 노드로 이동
            p = p->link;

            //예외처리1) p가 header를 밟은 경우 (예: ... -> 7번 -> header -> 1번 ...) 이렇게 지나가야 하는 경우
            //header를 밟은 것은 카운트에서 제외!!! 한칸 더 이동한다!
            //한칸 더 이동해야 함!
            if (p == header) {
                    p = p->link;
                }
        } //이렇게 이동하면 p는 k-1번째 이고 p->link(p의 다음노드) k번째가 삭제할 대상


        Node* q = p->link; //삭제할 노드인 p->link를 q로 지정


        // [예외 처리 2: 'q'가 헤더를 가리키는 경우] //한칸 더 이동한다!!!
        //만약에 p가 마지막 데이터 노드에서 멈출 경우
        //q(p->link)는 last 즉 header라는 것
        //여기서 header를 지울수는 없고 원래 삭제 대상은 첫번째 데이터
        //즉 q->link를 지워야 함.
        //즉 이 경우도 한칸 더 이동해야 함
        if (q == header) {
            q = q->link;

            //여기서 절대 잊으면 안되는건데 반드시 그 이전 노드인 p도 함께 이동해 줘야 함
            //q움직이면 p도 함께 움직여야 한다는 것 기억
            p = p->link;
        }


        //실제로 q를 삭제하는 코드
        //이전처럼 [p] -> [q] -> [q의 다음 노드] 를 [p] --------> [q의 다음 노드]로 번경 시켜 주면 됨
        //즉 p->link = q->link 로 변경해주면 바로 해결
        //그리고 삭제한 대상 q는 RetNode로 보내기
        p->link = q->link;
        RetNode(q);
    }


    //while문 전부 끝내고 마지막으로 남은 것은 리스트의 데이터 첫번째에 1개로 남아있을 것
    //header 바로 다음 노드
    //이걸 return 해주면 된다.
    Node* survivor = header->link;
    cout << "[최종 생존자]: " << survivor->data << endl;

    return survivor->data;
    }



    //main 작성 할 때 Node* CircularList::av = nullptr; 이거 무조건 해줘야 함

    //static은 무조건 밖에서 초기화!!!!!!!

    enum Menu {
    Add1,     // 0
    Add2,     // 1
    Delete,   // 2
    Show,     // 3
    Search,   // 4
    Merge,    // 5
    Josephus, // 6
    make_list,  // 7
    Exit      // 8
};

    Node* CircularList::av = nullptr;

    int main() {
    int selectMenu;
    int num = 0; bool result = false;
    vector<int> testData;

    // rand()를 위한 시드 초기화
    srand(time(NULL));

    CircularList la, lb, lc; // CircularList 사용 (이름만 la, lb, lc로 변경)
    int data = 0;

    do {
        cout << "\n0.Add1, 1.Add2, 2.Delete, 3.Show, 4.Search, 5.Merge, 6.Josephus, 7.make_list, 8.Exit 선택::";
        cin >> selectMenu;

        switch (static_cast<Menu>(selectMenu)) {

            case Add1: // 0. A에 랜덤 데이터 추가
                data = rand() % 49 + 1; // 1~49 사이의 랜덤 숫자
                la.Add(data);
                cout << "  리스트 la에 " << data << " 추가됨." << endl;
                break;

            case Add2: // 1. B에 랜덤 데이터 추가
                data = rand() % 49 + 1; // 1~49 사이의 랜덤 숫자
                lb.Add(data);
                cout << "  리스트 lb에 " << data << " 추가됨." << endl;
                break;

            case Delete: // 2. A에서 삭제
                cout << "  삭제할 데이터 입력: ";
                cin >> data;
                result = la.Delete(data);
                if (result)
                    cout << "  " << data << " 삭제 완료.";
                else
                    cout << "  " << data << "를 찾지 못했습니다.";
                break;

            case Show: // 3. 모든 리스트 보기
                cout << "  리스트 la = "; la.Show();
                cout << "  리스트 lb = "; lb.Show();
                cout << "  리스트 lc = "; lc.Show();
                break;

            case Search: // 4. A에서 검색
                cout << "  검색할 데이터 입력: ";
                cin >> data; // data 변수 재활용
                result = la.Search(data);
                if (!result)
                    cout << "  검색 값 = " << data << " 데이터가 없습니다.";
                else
                    cout << "  검색 값 = " << data << " 데이터가 존재합니다.";
                break;

            case Merge: // 5. 병합
                lc = la + lb;
                cout << "  리스트 lc = ";
                lc.Show();
                break;

            case Josephus: { // 6. 요세푸스 문제 ({}로 지역변수 범위 생성)
                int n, k;
                n = testData.size();
                cout << "  요세푸스 문제. 총 인원 (N): " << n;
                cout << "  제거 간격 (K): ";
                cin >> k;
                if (n > 0 && k > 0) {
                    la.SolveJosephus(testData, k);
                } else {
                    cout << " N과 K는 0보다 커야 합니다." << endl;
                }
                break;
            }

            case make_list: { // 7. 한 줄의 입력을 받아 vector로 추가
                cout << " testData vector에 추가할 숫자들을 한 줄로 입력하세요 (예: 20 10 50 40 5):" << endl;
                cin.ignore();

                string line;
                getline(cin, line);
                stringstream ss(line);

                int number;
                while (ss >> number) {
                    testData.push_back(number); // 뽑아낸 숫자를 testData에 추가
                }

                cout << "[";
                for(int i=0; i<testData.size();i++){
                    cout << testData[i];
                    if(i!=testData.size()-1){
                        cout << " -> ";
                    }
                }
                cout << "]";
                break;
            }

            //쉼표로 파싱해야 할 경우 다음 코드 사용
            // case make_list: { // 7-1. 쉼표로 구분한 것 파싱, 한 줄의 입력을 받아 vector로 추가
            //     cout << "testData vector에 추가할 숫자들을 쉼표(,)로 구분해 입력하세요 (예: 20, 10, 50, 40, 5):" << endl;
            //     string line;
            //     getline(cin, line);

            //     stringstream ss(line);
            //     string token;
            //     int count = 0;

            //     while (getline(ss, token, ',')) {
            //         // 'token' (string)을 'num' (int)로 변환 (stoi 사용)
            //         int num = std::stoi(token);
            //         testData.push_back(num); // 정수로 변환된 숫자를 la에 추가
            //         count++;
            //     }

            //     for(auto lt: testData){
            //         cout << lt;
            //     }
            //     break;
            // }

            case Exit: // 8. 종료
                cout << "프로그램을 종료합니다." << endl;
                break;

            default:
                cout << "잘못된 선택입니다. (0~7 사이 숫자)" << endl;
                break;
        } // end of switch
    } while (static_cast<Menu>(selectMenu) != Exit); // end of do-while

    cin >> num; // 프로그램 종료 전 입력 대기 (참고 코드 반영)
    return 0;
}


