#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N=0;
    vector<pair<string,int>> vec;
    string s;
    int price;
    
    
    cin >> N;
    for(int i; i<N; i++){
        cin >> s >> price;
        vec.push_back({s,price});
    }

    sort(vec.begin(),vec.end(),[](auto x,auto y){ return x.second > y.second; });
    //오름차순

    int i = 0;
    bool result = false; //유찰되면 false

    while (i < N) {
        int cnt = 0; //cnt는 동일가격 개수
        for (int j = i; j < N && vec[j].second == vec[i].second; j++) {
            cnt++;
        }

        if (cnt == 1) {
            cout << vec[i].first;
            result = true;
            break; // while문 종료
        }
        else {
            i += cnt; //동일가격만큼 전부 건너뜀
        }
    }

    if (!result) {
        cout << "NONE";
    }
}