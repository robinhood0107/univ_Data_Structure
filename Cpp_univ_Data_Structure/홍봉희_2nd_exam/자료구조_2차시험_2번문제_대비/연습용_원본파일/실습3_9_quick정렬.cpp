#include <iostream>
using namespace std;
/*
int partition(vector<int>& a, int l, int r) {
    int pivot = a[(l + r) / 2]; // 중앙값 피벗
    int i = l, j = r;

    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) {
            swap_elem(a, i, j);
            i++; j--;
        }
    }
    return i; // 분할 기준점 반환
}

// --- Quick Sort (재귀) ---
void quickSort(vector<int>& a, int l, int r) {
    if (l >= r) return; // 원소 1개 이하 → 종료

    int index = partition(a, l, r);

    // 왼쪽 부분 배열 정렬
    quickSort(a, l, index - 1);

    // 오른쪽 부분 배열 정렬
    quickSort(a, index, r);
}

*/
struct Point {
    int x, y;
    Point(int a = 0, int b = 0) : x(a), y(b) {}
};

void swap_elem(vector<int>& a, int i, int j) {
    int t = a[i]; a[i] = a[j]; a[j] = t;
}

void print_range(const vector<int>& a, int l, int r) {
    cout << "left = " << l << " right = " << r << '\n';
    for (int i = l; i <= r; ++i) cout << " " << a[i];
    cout << '\n';
}

void quickSort(vector<int>& a, int left, int right) {
    stack<Point> st;
    st.emplace(left, right);

    while (!st.empty()) {
        Point rt = st.top(); st.pop();
        int l = rt.x;
        int r = rt.y;

        int pl = l;
        int pr = r;
        int mp = a[(pl + pr) / 2];

        do {
            while (a[pl] < mp) ++pl;
            while (a[pr] > mp) --pr;
            if (pl <= pr) swap_elem(a, pl++, pr--);
        } while (pl <= pr);

        print_range(a, l, r);

        if (l < pr)  st.emplace(l, pr);
        if (pl < r)  st.emplace(pl, r);
    }
}

void showData(const vector<int>& d) {
    cout << '\n';
    for (int v : d) cout << v << ' ';
    cout << '\n';
}

int main() {
    int nx = 10;
    vector<int> x(nx);

    // 난수 생성: srand 고정 시드 + rand()%999
    srand(41);
    for (int i = 0; i < nx; ++i) {
        x[i] = rand() % 999;   // 0 ~ 998 사이 정수
    }

    showData(x);
    quickSort(x, 0, nx - 1);
    cout << "오름차순으로 정렬했습니다.\n";
    showData(x);
    return 0;
}
