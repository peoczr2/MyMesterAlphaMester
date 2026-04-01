/*
Megoldás lényege:
Az őrizetlen napok uniója mindig rendezett, diszjunkt intervallumokból áll. Egy új szakasz csak a
bal és jobb szomszédos őrzött komponenssel tud összekapcsolódni, ezért az őrizetlen szakaszok
száma csak lokálisan változhat.

A komponenseket rendezett map-ben tároljuk, és mindig csak az előző/ következő intervallumot kell
megnézni.
*/
// Hint 1: || Most a lefedetlen részek számát kell követni. ||
// Hint 2: || Egy új szakasz belső üres részt kettévág, vagy két üres részt összefűz. ||
// Hint 3: || Elég az előző és a következő lefedett intervallumot megvizsgálni. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    map<int,int> segs;

    for (int i = 0; i < N; ++i) {
        int l, r;
        cin >> l >> r;

        auto it = segs.lower_bound(l);
        auto left = (it == segs.begin() ? segs.end() : prev(it));
        bool adjL = left != segs.end() && left->second + 1 == l;
        bool adjR = it != segs.end() && r + 1 == it->first;

        int nl = l, nr = r;
        if (adjL) {
            nl = left->first;
            nr = max(nr, left->second);
            segs.erase(left);
        }
        if (adjR) {
            nr = it->second;
            segs.erase(it);
        }

        segs[nl] = nr;

        int coveredParts = (int)segs.size();
        int holes = max(0, coveredParts - 1);
        if (segs.begin()->first > 1) ++holes;
        if (segs.rbegin()->second < M) ++holes;
        cout << holes << '\n';
    }
    return 0;
}