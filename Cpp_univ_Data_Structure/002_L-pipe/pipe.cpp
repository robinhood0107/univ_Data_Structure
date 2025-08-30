#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(){
    int N; //개수
    int x,y,d,h,w; //함수값
    const double power_d = pow(d,2);

    vector<pair<int,int>> vec; //좌표 저장

    vector<string> result; //출력벡터

    ios_base::sync_with_stdio(0);
    cin.tie();

    cin >> x >> y >> d >> h >> w;
    cin >> N;

    for(int i=0;i<N;i++){
        int my_x;
        int my_y;
        cin >> my_x >> my_y;
        vec.push_back({my_x,my_y});
    }

    
    for(auto& lt : vec){
        long long circle = (lt.first - x) * (lt.first - x) + (lt.second - y) * (lt.second - y);
        
        if(
            (lt.first == 0 && lt.second >= 0 && lt.second <= h) ||
            (lt.second == 0 && lt.first >= 0 && lt.first <= w) ||
            (lt.second == h && lt.first >= 0 && lt.first <= x - d) ||
            (lt.first == x - d && lt.second >= y && lt.second <= h) ||
            (lt.second == y - d && lt.first >= x && lt.first <= w) ||
            (lt.first == w && lt.second >= 0 && lt.second <= y - d) ||
            (circle == (d*d) && lt.first >= x - d && lt.first <= x && lt.second >= y - d && lt.second <= y))
            {
            result.push_back("ON");
        }
        else if (
            (lt.first > 0 && lt.first < x - d && lt.second > 0 && lt.second < h) ||
            (lt.first > 0 && lt.first < w && lt.second > 0 && lt.second < y - d) ||
            (circle < (d*d) && lt.first >= x - d && lt.first <= x && lt.second >= y - d && lt.second <= y)
        ){
            result.push_back("IN");
        }
        else {
            result.push_back("OUT");
        }
    }


    for(auto& lt : result){
        cout << lt << "\n";
    }
}