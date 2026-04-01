/*
Megoldás lényege:
Az útvonal kezdetétől a következő bódékig haladva csak azt kell eldönteni, hogy
az adott prefix még teljesíthető-e. A K és M bódék 1-gyel növelik a hordozható
köretkészletet, a H bódék 1-gyel csökkentik. Egy prefix akkor és csak akkor
járható végig, ha minden részprefixben a K+M darabszám legalább a H darabszám.

Ezért a sorozatot 1/-1 értékűvé alakítjuk: K és M legyen +1, H legyen -1.
Előre kiszámítjuk a prefixösszegeket, majd minden pozícióra megkeressük az első
olyan jobb oldali helyet, ahol a prefixösszeg kisebb lesz a kezdőértéknél.
Ez a monoton stackkel lineáris időben megtehető.

A válasz az így kapott legnagyobb teljes prefixben szereplő H-bódék száma.
*/
/*
Hint 1: || A feladatot prefixösszegre lehet bontani: a K és M bódék +1-et, a H bódék -1-et jelentenek. ||
Hint 2: || Ha egy jobb oldali ponttól kezdve a prefixösszeg már kisebb, ott a járható szakasz véget ér; ezt monoton stackkel lehet gyorsan megtalálni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    string s;
    cin >> s;

    vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i - 1] + (s[i - 1] == 'H' ? -1 : 1);
    }

    vector<int> nextLess(n + 1, n + 1);
    vector<int> st;
    st.reserve(n + 1);
    for (int i = n; i >= 0; --i) {
        while (!st.empty() && pref[st.back()] >= pref[i]) st.pop_back();
        nextLess[i] = st.empty() ? n + 1 : st.back();
        st.push_back(i);
    }

    for (int i = 1; i <= n; ++i) {
        int endPos = nextLess[i - 1] - 1;
        int len = (endPos >= i ? endPos - i + 1 : 0);
        int ans = len / 2;
        if (i > 1) cout << ' ';
        cout << ans;
    }
    cout << '\n';
    return 0;
}