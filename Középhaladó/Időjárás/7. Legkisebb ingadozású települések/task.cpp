/*
Megoldás lényege:
Egy település ingadozása a legmagasabb és a legalacsonyabb előrejelzett hőmérséklet különbsége. Minden sort beolvasás közben egyszer végigfutunk, és közben nyilvántartjuk a sor maximumát és minimumát. A sor végén a különbségüket eltároljuk, majd megkeressük a legkisebb ingadozást, és kiírjuk az összes olyan település sorszámát, amely ezt eléri, növekvő sorrendben. Az idő O(N·M), a memória O(N).
*/
/*
Hint 1: || Egy település ingadozása a napi előrejelzések legnagyobbika és legkisebbike közötti különbség. Ezt minden településre külön kell kiszámolni. ||
Hint 2: || Sor beolvasása közben tartsd nyilván a sor minimumát és maximumát, a sor végén a különbségüket írd egy tömbbe. Utána keresd meg a legkisebb különbséget, és írd ki az összes ezt elérő település sorszámát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> ingadozas(n + 1);
    for (int i = 1; i <= n; i++) {
        int legkisebb = INT_MAX, legnagyobb = INT_MIN;
        for (int j = 1; j <= m; j++) {
            int h;
            cin >> h;
            legkisebb = min(legkisebb, h);
            legnagyobb = max(legnagyobb, h);
        }
        ingadozas[i] = legnagyobb - legkisebb;
    }

    int legkisebb_ingadozas = *min_element(ingadozas.begin() + 1, ingadozas.end());

    vector<int> telepulesek;
    for (int i = 1; i <= n; i++) {
        if (ingadozas[i] == legkisebb_ingadozas) telepulesek.push_back(i);
    }

    cout << telepulesek.size();
    for (int i : telepulesek) cout << ' ' << i;
    cout << '\n';
    return 0;
}
