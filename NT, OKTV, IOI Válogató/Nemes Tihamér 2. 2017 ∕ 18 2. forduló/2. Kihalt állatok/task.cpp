/*
Megoldás lényege:
Minden faj egy zárt [U, E] intervallum az évek tengelyén. A bemenetben a két szám sorrendje nem garantált (a mintában a 8 3 is szerepel), ezért előbb rendezzük őket. Különbségtömbbe a kezdőév indexére +1, a záróév utáni indexre −1 kerül, így a prefixösszeg egy adott évben élő fajok számát adja. A maximális fajszámot keressük, és ha több év is eléri, a nagyobb évszámot írjuk ki, mert ez a legrégebbi kor. Az időigény O(M + N).
*/
/*
Hint 1: || Nem kell minden faj minden évét külön végigvenni: elég a fajok kezdő- és záróévét jelölni, és a változásokat követni az évek mentén. ||
Hint 2: || Használj egy tömböt, ahol a kezdőév sorszámán +1, a záróév utáni sorszámon −1 áll; az évek végigjárásakor a futó összeg adja az adott évben élő fajok számát. Az U > E eset is előfordulhat, ezért a két értéket előbb rendezd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<int> diff(m + 3, 0);
    for (int i = 0; i < n; ++i) {
        int u, e;
        cin >> u >> e;
        if (u > e) swap(u, e);
        ++diff[u];
        --diff[e + 1];
    }

    int akt = 0, best = -1, kor = 1;
    for (int i = 1; i <= m; ++i) {
        akt += diff[i];
        if (akt > best || (akt == best && i > kor)) {
            best = akt;
            kor = i;
        }
    }

    cout << best << '\n' << kor << '\n';
    return 0;
}
