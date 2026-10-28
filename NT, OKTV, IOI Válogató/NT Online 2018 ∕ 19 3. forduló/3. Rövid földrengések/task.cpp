/*
Megoldás lényege:
Az összes szigetek földrengéseinek időpontját egy listába gyűjtjük, rendezzük, és a
szomszédos időpontok közötti szabad perceket vizsgáljuk. A 0 perc a kezdő, M perc a
záró határ: két egymás utáni r1 < r2 időpont között r2 - r1 - 1 szabad perc van,
az első földrengésig r1 - 1, az utolsótól M-ig M - r_utolsó. Ezek maximuma a válasz.
Az időigény O(N log N), ahol N a földrengések száma (legfeljebb 100 000).
*/
/*
Hint 1: || A szigetek sorrendje és azonossága nem számít: minden földrengés időpontja ugyanúgy foglalt perc. Ezeket gyűjtsd egy közös vektorba, és rendezd. ||
Hint 2: || Rendezés után a szomszédos időpontok különbségéből számolj: két egymás utáni időpont között a szabad percek száma a különbség - 1. Az elejére a 0 perc, a végére az M perc adja a határt, és ezek közül a legnagyobb szabad szakaszt kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, m;
    cin >> k >> m;
    vector<int> idopontok;
    while (k--) {
        int f;
        cin >> f;
        for (int i = 0; i < f; ++i) {
            int r;
            cin >> r;
            idopontok.push_back(r);
        }
    }

    sort(idopontok.begin(), idopontok.end());
    idopontok.erase(unique(idopontok.begin(), idopontok.end()), idopontok.end());

    int ans = 0;
    int prev = 0;
    for (int x : idopontok) {
        ans = max(ans, x - prev - 1);
        prev = x;
    }
    ans = max(ans, m - prev);

    cout << ans << '\n';
    return 0;
}
