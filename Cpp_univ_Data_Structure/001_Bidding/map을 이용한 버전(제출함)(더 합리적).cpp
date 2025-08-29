#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie();

    int N;
    std::cin >> N;

    // 가격을 키로 할 경우 같은 가격의 사람을 묶어버릴 수 있음
    map<int, vector<string>, greater<int>> mymap;
    //map의 default값은 key 값 기준 오름차순
    //내림차순으로 하고 싶을 경우 3번째 인자에 greater<int>
    for (int i=0; i<N; i++) {
        string n;
        int price=0;
        cin >> n >> price;
        mymap[price].push_back(n);
    }

    for (auto& lt : mymap) {
        if (lt.second.size() == 1) {
            cout << lt.second[0];
            return 0; // 출력하고 바로 프로그램 종료해야 함
        }
    }

    // 위에서 종료 안되었을 경우 유찰이므로 NONE
    cout << "NONE";
    return 0;
}