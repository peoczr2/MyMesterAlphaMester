/*
Megoldas lenyege:
A legnagyobb hasznalhato tegla egy olyan teglalap, amely egy osszefuggo szakaszon mindenhol
elfer a fal alatt. Ez pontosan a histogram legnagyobb teglalapja feladat: a szelesseg az adott
szakasz hossza, a magassag pedig a szakasz minimuma.

Monoton novekvo veremmel minden poziciohoz meghatarozzuk, meddig terjedhet az a maximalis
szakasz, ahol az adott magassag a minimum. Amikor egy magasabb oszlopot lepopolunk, azonnal
szamolhato a hozza tartozo maximalis teglalap terulete.
*/
/*
Hint 1: || Egy tégla magasságát az a legalacsonyabb oszlop korlátozza, amely fölé kerül. ||
Hint 2: || A klasszikus legnagyobb histogram-teglalap megoldas itt is kozvetlenul alkalmazhato. ||
Hint 3: || A veremben novekvo magassagokat tarts, es kilepeskor szamold a teruletet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long limit;
    cin >> n >> limit;

    vector<long long> h(n + 1);
    for (int i = 0; i < n; ++i) cin >> h[i];
    h[n] = 0;

    vector<int> st;
    long long best = 0;
    for (int i = 0; i <= n; ++i) {
        while (!st.empty() && h[st.back()] > h[i]) {
            int mid = st.back();
            st.pop_back();
            int left = st.empty() ? 0 : st.back() + 1;
            int width = i - left;
            best = max(best, h[mid] * width);
        }
        st.push_back(i);
    }

    cout << best << '\n';
    return 0;
}