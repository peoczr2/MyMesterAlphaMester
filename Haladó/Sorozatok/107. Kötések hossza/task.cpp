/*
Megoldás lényege:
Balról jobbra haladva egy veremben tartjuk a még nem párosított ledeket. Ha az aktuális LED
színe eltér a verem tetején állóétól, akkor ezt a két LED-et érdemes összekötni: így nem lesz
keresztezés, és a távolságuk hozzáadható az összhosszhoz.

Ez pontosan a minimális összhosszt adja.
*/
// Hint 1: || A nem keresztező párosítás veremszerűen épül fel balról jobbra. ||
// Hint 2: || Ha az aktuális LED színe eltér a verem tetejétől, akkor a kettőt összekötjük és kidobjuk a verem tetejét. ||
// Hint 3: || A válasz a párok távolságainak összege. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string s;
    cin >> N >> s;

    vector<pair<char,int>> st;
    long long ans = 0;
    for (int i = 0; i < 2 * N; ++i) {
        char c = s[i];
        if (!st.empty() && st.back().first != c) {
            ans += i + 1 - st.back().second;
            st.pop_back();
        } else {
            st.push_back({c, i + 1});
        }
    }

    cout << ans << '\n';
    return 0;
}