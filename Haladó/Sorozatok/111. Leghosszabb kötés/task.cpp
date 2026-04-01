/*
Megoldás lényege:
Ugyanazzal a veremszerű párosítással dolgozunk, mint a minimális összhossz esetén. Egy adott
legnagyobb megengedett kötélhosszra balról jobbra haladva csak akkor párosítunk, ha az aktuális
LED és a verem teteje eltérő színű, és a távolságuk nem nagyobb a megengedettnél.

Erre binárisan keresünk.
*/
// Hint 1: || Ugyanaz a veremes párosítás működik, mint a minimális összhossznál. ||
// Hint 2: || Egy adott D-re csak azt kell eldönteni, létrejöhet-e minden kötél hossza legfeljebb D. ||
// Hint 3: || Ha igen/nem ellenőrzés van, akkor a legkisebb jó D-t bináris kereséssel kapjuk. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string s;
    cin >> N >> s;

    auto ok = [&](int lim) {
        vector<pair<char,int>> st;
        st.reserve(2 * N);
        for (int i = 0; i < 2 * N; ++i) {
            char c = s[i];
            if (!st.empty() && st.back().first != c && i + 1 - st.back().second <= lim) {
                st.pop_back();
            } else {
                st.push_back({c, i + 1});
            }
        }
        return st.empty();
    };

    int lo = 0, hi = 2 * N;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (ok(mid)) hi = mid;
        else lo = mid + 1;
    }

    cout << lo << '\n';
    return 0;
}