/*
Megoldás lényege:
A városok fát alkotnak, és egy lépés egy úton való átmenetet jelent. Az ügynök M lépésben egy részfát járhat
be: egy k csúcsú összefüggő részfa bejárásához legalább 2(k-1) lépés kell, de ha a bejárás a részfa két
végpontja között fut, a két végpont távolságát (d) egyszer megspóroljuk: a költség 2(k-1) - d. Egy részfa
átmérője legfeljebb a fa átmérője (D), ezért a legjobb a fa átmérőjét tartalmazó részfa. Ha M < D, akkor
M + 1 város érhető el egy M hosszú úton. Ha M >= D, akkor a k csúcsú részfára 2(k-1) - D <= M teljesül,
vagyis legfeljebb (M + D) / 2 + 1 város (és legfeljebb N). Az átmérőt két szélességi bejárással kapjuk meg.
Az időigény O(N).
*/
/*
Hint 1: || Egy M lépéses útvonal akkor érhet el sok várost, ha minél kevesebbet kell visszafordulnod: keresd meg a fa leghosszabb útját (átmérőjét), mert ez határozza meg, mennyit tudsz kihasználni. ||
Hint 2: || Egy részfa bejárása a részfa éleinek kétszereséhez kell, de ha a végén nem kell visszatérned a kiindulóhoz, a két végpont távolságát megspórolod. Gondold át, hogy az M lépésszám vagy a fa átmérője a szűk keresztmetszet, és ez mikor változik. ||
Hint 3: || Ha a bejárás k csúcsot fed le, legalább 2(k-1) - d lépés kell, ahol d a bejárás két végpontjának távolsága. Válaszd úgy a részfát, hogy d a lehető legnagyobb legyen, és a lépésszámból számold ki, hány csúcsot érhetsz el. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Szélességi bejárás s-ből: visszaadja a legtávolabbi csúcsot és a hozzá tartozó távolságot
pair<int, int> legtavolabbi(int s, int n, const vector<vector<int>> &g) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    int utolso = s;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        utolso = u;  // a szélességi bejárásban az utolsó kivett csúcs a legtávolabbi
        for (int v : g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return {utolso, dist[utolso]};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // A fa átmérője két szélességi bejárással
    int u = legtavolabbi(1, n, g).first;
    int d = legtavolabbi(u, n, g).second;

    long long valasz;
    if (m < d) {
        valasz = m + 1;
    } else {
        valasz = (m + d) / 2 + 1;
    }
    valasz = min<long long>(valasz, n);

    cout << valasz << '\n';
    return 0;
}
