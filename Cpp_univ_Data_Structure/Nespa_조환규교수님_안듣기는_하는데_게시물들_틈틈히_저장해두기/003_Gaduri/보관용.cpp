#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    double x1,y1,r1 = 0;
    double x2,y2,r2 = 0;
    const double PI = 3.14159265358979;

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> x1 >> y1 >> r1;
    cin >> x2 >> y2 >> r2;

    double r_max = max(r1,r2);
    double r_min = min(r1,r2);
    double m_distance = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    double L = sqrt(m_distance*m_distance-(r_max-r_min)*(r_max-r_min));

    cout << r_max << r_min << m_distance << L;

    double radian = acos((r_max-r_min)/m_distance);

    //cout << r_max << ' ' << r_min << ' ' << m_distance << ' ' << L << ' ' << radian << '\n';

    cout << floor((r_max-r_min)*L + 2*L*r_min + (PI-radian)*r_max*r_max + radian*r_min*r_min)<< ' ' 
    << floor(2*L + 2*(PI-radian)*r_max + 2*radian*r_min);
    return 0;
}

// g++ gaduri.cpp -g -o gaduri && gaduri.exe < ./sample/01.inp