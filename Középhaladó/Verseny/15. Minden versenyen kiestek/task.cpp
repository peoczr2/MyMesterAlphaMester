/*
Megoldás lényege:
Egy tanuló akkor kerül a kimenetbe, ha sehol sem érte el a minimális pontszámot, vagyis egyetlen versenyen sem volt olyan eredménye, amely legalább a versenyhez tartozó minimum. Ezért minden tanulóhoz egy jelzőt tartunk nyilván, amely igazzá válik, ha valahol elérte a minimumot. A versenyen nem induló tanulók jelzője hamis marad, így ők is bekerülnek a kimenetbe. A végén a jelző nélküli tanulók sorszámát írjuk ki növekvő sorrendben, a darabszámukkal együtt. Az időigény O(N·M), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Elég minden tanulóról eldönteni, hogy valahol elérte-e a versenyhez tartozó minimumot. Ha egyszer igen, ez a tanuló már nem kerül a kimenetbe. ||
Hint 2: || Egy versenyen csak azok számítanak, akik legalább a versenyhez tartozó minimumot elérték. A versenyen nem induló tanuló is megfelel a kérdésnek, ha sehol sem ért el minimumot, ezért őt is ki kell írni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> mins(m);
    for (int i = 0; i < m; i++) {
        cin >> mins[i];
    }

    vector<bool> reached(n + 1, false);
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            if (p >= mins[i]) {
                reached[s] = true;
            }
        }
    }

    vector<int> ans;
    for (int s = 1; s <= n; s++) {
        if (!reached[s]) {
            ans.push_back(s);
        }
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
