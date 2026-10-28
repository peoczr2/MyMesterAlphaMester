/*
Megoldás lényege:
Egy háromfős csapat pontosan akkor alakulhat, ha a három tag páronként kedveli egymást, vagyis a gráfban
háromszöget alkot. Egy csapat lisztigénye a három tag igényének maximuma, ezért az eredmény minden háromszög
maximumának összege. A háromszögeket úgy keressük meg, hogy minden élt a kisebb fokszámú végpontból a nagyobb
felé irányítunk (azonos fokszámnál a kisebb sorszámú felé). Így minden háromszöget pontosan egyszer találunk
meg, mégpedig a legkisebb rangú csúcsától indulva, és a csúcs szomszédait egy jelölő tömbbel gyorsan
ellenőrizzük. Ez O(M * sqrt(M)) időigényű, ami N <= 100 000 és M <= 250 000 mellett elég gyors. Az összeg
64 bites egész.
*/
/*
Hint 1: || Egy csapat pontosan egy háromszög a gráfban. Mivel minden háromszöget végig kell néznünk, az összes hármas kipróbálása túl lassú, ezért olyan bejárást kell választanod, amely csak a valóban létező háromszögeket találja meg. ||
Hint 2: || Irányítsd az éleket úgy, hogy a kisebb fokszámú csúcsból a nagyobb fokszámú felé mutassanak (döntetlennél a kisebb sorszámból). Így a háromszög legkisebb rangú csúcsát rögzítve csak a kimenő éleket kell nézned. ||
Hint 3: || Egy u csúcs kimenő szomszédait jelöld meg egy tömbben, majd a kimenő szomszédjaik kimenő éleit végigvéve ellenőrizd, melyik vég van megjelölve. Így minden talált háromszög maximumát azonnal hozzáadhatod az összeghez. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> liszt(n + 1);
    for (int i = 1; i <= n; i++) cin >> liszt[i];

    vector<pair<int, int>> el;
    el.reserve(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u == v) continue;
        if (u > v) swap(u, v);
        el.push_back({u, v});
    }
    // Az ismétlődő éleket egyszer vesszük figyelembe
    sort(el.begin(), el.end());
    el.erase(unique(el.begin(), el.end()), el.end());

    vector<int> fok(n + 1, 0);
    for (auto [u, v] : el) {
        fok[u]++;
        fok[v]++;
    }

    // Irányítás: a kisebb fokszámú (döntetlennél a kisebb sorszámú) csúcs felől a nagyobb felé
    auto kisebb = [&](int x, int y) {
        return fok[x] < fok[y] || (fok[x] == fok[y] && x < y);
    };
    vector<vector<int>> ki(n + 1);
    for (auto [u, v] : el) {
        if (kisebb(u, v)) {
            ki[u].push_back(v);
        } else {
            ki[v].push_back(u);
        }
    }

    vector<int> jel(n + 1, 0);
    long long osszeg = 0;
    for (int u = 1; u <= n; u++) {
        for (int v : ki[u]) jel[v] = u;
        for (int v : ki[u]) {
            for (int w : ki[v]) {
                if (jel[w] == u) {
                    osszeg += max({liszt[u], liszt[v], liszt[w]});
                }
            }
        }
    }

    cout << osszeg << '\n';
    return 0;
}
