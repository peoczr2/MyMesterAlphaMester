/*
Megoldás lényege:
Egy település egy adott napon akkor melegszik, ha az aznapi hőmérséklete nagyobb az előző napinál; az első napnak nincs előzője, ezért a számlálás a második naptól indul. Mivel a bemenet településenként érkezik, egy sor beolvasásakor a szomszédos elemeket azonnal összevethetjük, és a melegedő települések számát a megfelelő napnál növeljük. Egy nap akkor kerül a kimenetbe, ha a melegedők száma legalább a települések fele, vagyis 2*db >= N. Az idő O(N*M), a memória O(M).
*/
/*
Hint 1: || Egy nap akkor „melegedő” egy településen, ha az aznapi érték nagyobb az előző napinál. Az első napnak nincs előzője, ezért a számlálás a második naptól induljon. ||
Hint 2: || Egy település sorát egyben beolvashatod, és a szomszédos elemeket rögtön összehasonlíthatod: minden napra külön számlálót tarts. A „legalább a felében” feltétel egész számokkal 2*db >= N. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> melegedo(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        int elozo;
        cin >> elozo;
        for (int j = 2; j <= m; j++) {
            int h;
            cin >> h;
            if (h > elozo) melegedo[j]++;
            elozo = h;
        }
    }

    vector<int> napok;
    for (int j = 2; j <= m; j++) {
        if (2 * melegedo[j] >= n) napok.push_back(j);
    }

    cout << napok.size();
    for (int d : napok) cout << ' ' << d;
    cout << '\n';
    return 0;
}
