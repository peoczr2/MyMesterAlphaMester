/*
Megoldás lényege:
Minden versenyzőnek összeadjuk az öt verseny pontszámát: a K. helyezett 1 pontot kap, a (K-1). helyezett 3-at, és így tovább, vagyis a h. helyezett 2*(K-h)+1 pontot, a K-nál rosszabb helyezések pedig nullát. A pontszám szerint csökkenően rendezett listában a K. helyen álló versenyző pontszáma adja a határt, és minden olyan versenyző kijut, akinek a pontszáma legalább ekkora, így a holtversenyesek is bekerülnek. A rendezés stabil, ezért az azonos pontszámúak sorszám szerint növekvően maradnak egymás mellett. Az időigény O(N log N), ami a korlátok mellett bőven elég.
*/
/*
Hint 1: || A pont csak a legjobb K helyezésért jár, és a helyezés és a pontszám közötti kapcsolat egyenes (lineáris) képlettel írható fel. ||
Hint 2: || A K. helyezett pontszáma adja a kijutási határt; minden olyan versenyző kijut, akinek a pontszáma nem kisebb ennél, így a holtversenyek automatikusan bekerülnek. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // pont[x]: a versenyző összpontszáma az öt versenyen
    vector<long long> pont(n + 1, 0);
    for (int x = 1; x <= n; ++x) {
        for (int v = 0; v < 5; ++v) {
            int h;
            cin >> h;
            if (h >= 1 && h <= k) pont[x] += 2LL * (k - h) + 1;
        }
    }

    // stabil rendezés: azonos pontszámnál a sorszám marad növekvő
    vector<int> sorrend(n);
    iota(sorrend.begin(), sorrend.end(), 1);
    stable_sort(sorrend.begin(), sorrend.end(), [&](int a, int b) { return pont[a] > pont[b]; });

    // a K. helyezett pontszáma: ennyit elérők mind kijutnak
    long long hatar = pont[sorrend[k - 1]];
    int o = 0;
    while (o < n && pont[sorrend[o]] >= hatar) ++o;

    cout << o << '\n';
    for (int i = 0; i < o; ++i) {
        if (i) cout << ' ';
        cout << sorrend[i];
    }
    cout << '\n';
    return 0;
}
