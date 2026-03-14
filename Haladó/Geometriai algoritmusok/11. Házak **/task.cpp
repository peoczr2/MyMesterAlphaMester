/*
Megoldás lényege:
A napfény balról-fentről, párhuzamos sugarakkal érkezik (DX,DY > 0), ezért az árnyékhatár
minden épületnél azonos meredekségű egyenes. Egy korábbi épület j árnyékát az x helyen a
h_j - (DY/DX)*(x-r_j) képlet adja (r_j: jobb oldali x).
Mivel minden árnyékegyenes meredeksége azonos, elég a legnagyobb
(h_j + (DY/DX)*r_j) értéket tárolni (intercept). Az i-edik épület akkor kap napot, ha a jobb felső
sarka az árnyékhatár fölött van:
    h_i + (DY/DX)*r_i  >  max_intercept
Szigorú > kell, mert az egyenlőség esetén csak érintés lenne (nem kap közvetlen napfényt).

Idő: O(N).
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long double DX, DY;
    if (!(cin >> N >> DX >> DY)) return 0;

    const long double k = DY / DX;
    const long double NEG_INF = -1e300L;
    const long double EPS = 1e-15L;

    long double bestIntercept = NEG_INF;
    vector<int> sunny;
    sunny.reserve(N);

    for (int i = 1; i <= N; ++i) {
        long double x, w, h;
        cin >> x >> w >> h;
        long double r = x + w;

        long double val = h + k * r;
        if (val > bestIntercept + EPS) {
            sunny.push_back(i);
        }

        if (val > bestIntercept) bestIntercept = val;
    }

    cout << sunny.size() << '\n';
    for (int i = 0; i < (int)sunny.size(); ++i) {
        if (i) cout << ' ';
        cout << sunny[i];
    }
    cout << '\n';

    return 0;
}
