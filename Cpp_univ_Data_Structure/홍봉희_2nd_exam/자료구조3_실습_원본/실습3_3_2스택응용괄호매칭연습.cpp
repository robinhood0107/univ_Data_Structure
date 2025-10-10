#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
문제 설명:
 - 문자열에서 괄호(<>, (), {}, [])의 짝과 중첩이 올바른지 검사
 - 괄호 외 문자는 모두 무시
출력:
 - 유효: "Valid", 아니면: "Invalid"
*/
/*
unordered_set<char> 와 unordered_map<char, char> 는 둘 다 C++ STL의 해시 기반 컨테이너

unordered_set의 메소드:
insert(val) : 값 삽입
erase(val) : 값 삭제
count(val) : 값 존재 여부 (0 또는 1 반환)
find(val) : 값 위치 반환 (없으면 end())

unordered_map의 메소드
operator[] : 키에 해당하는 값 접근/삽입
insert({key, value}) : 키-값 쌍 삽입
erase(key) : 키 삭제
count(key) : 키 존재 여부 (0 또는 1)
find(key) : 이터레이터 반환 (it->first, it->second)
at(key) : 값 접근 (없으면 예외 발생, []는 새 키 생성 위험 있음)

stack의 메소드
push(value), pop(), top(),size(),empty()

*/
bool isValid(const string& s) {
    // 닫는 괄호 -> 여는 괄호 매핑
    static const unordered_map<char, char> close2open = {
        {')', '('}, {'}', '{'}, {']', '['}, {'>', '<'}
    };
    static const unordered_set<char> openings = { '(', '{', '[', '<' };
    static const unordered_set<char> closings = { ')', '}', ']', '>' };

    stack<char> st;

    for (char ch : s) {
        
        // 괄호 외 문자는 무시
    }
    return st.empty();                               // 모두 닫혔는지 확인
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> cases1 = {
        "(12{as[33<1q2w3e>90]kkk}4r)fg",
        "<111{ddd[4r(1q2w3e)44]77}jj>kk",
        "zz{w(a+b)*[c/d]-<q-e>1+2}w*t",
        "dd[a+b+c(y*u[abstract]go{234}2w3e)444]ttt",
        "a+b<c-d<e%r{123{waste[go[stop(a+b+c(?)$)@]!]*}12}33>c-d>drop"
    };

    vector<string> cases2 = {
        "a-b-c{1234[3.14(hello)kkk]1>d-w",
        "a*b*c(121<good[days)gostop>q-w]t-1",
        "123{hello[a-w-e(w/e/r]\n)\t}qq",
        "q*t&w{12-34[a+b]*(c/d]-e}123",
        "12<a/b/c/d{q-t-t[a=c(78::]23;)'8}sss>x+y+w"
    };

    cout << "예제1:\n";
    for (const auto& s : cases1) {
        cout << s << " \u2192 " << (isValid(s) ? "Valid" : "Invalid") << '\n';
    }

    cout << "\n예제2:\n";
    for (const auto& s : cases2) {
        cout << s << " \u2192 " << (isValid(s) ? "Valid" : "Invalid") << '\n';
    }

    return 0;
}
