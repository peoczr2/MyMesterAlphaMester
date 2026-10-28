/*
Megoldás lényege:
Egy falu legközelebbi szomszédja az a falu, amelyhez a legrövidebb út vezet, ezért minden faluhoz elég a rá illeszkedő utak minimumát tárolni.
Az utakat egyszer végigolvassuk, és mindkét végpont minimumát frissítjük; a hurokéleket (ahol a két végpont megegyezik) kihagyjuk, mert azok nem vezetnek másik faluba.
Ezután a falvakat sorszám szerint járjuk be, és csak szigorúan nagyobb értéknél cserélünk, így döntetlen esetén a kisebb sorszám marad.
Az időigény O(N + M), a memóriaigény O(N).
*/
/*
Hint 1: || Egy falu legközelebbi szomszédja az, amelyhez a legrövidebb út vezet, tehát minden faluhoz csak a rá illeszkedő utak minimumát kell ismerned. ||
Hint 2: || Minden út beolvasásakor frissítsd mindkét végpont minimumát, majd keresd a legnagyobb minimumú falut; a sorszámokat növekvő sorrendben nézd, így döntetlennél a kisebb sorszám marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    const int INF = INT_MAX;
    vector<int> nearest(n + 1, INF);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u == v) continue;
        nearest[u] = min(nearest[u], w);
        nearest[v] = min(nearest[v], w);
    }

    int best = 1;
    for (int v = 2; v <= n; v++) {
        if (nearest[v] > nearest[best]) best = v;
    }
    cout << best << '\n';
    return 0;
}
