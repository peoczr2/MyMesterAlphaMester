/*
Megoldás lényege:
Szempontonként először megkeressük a legjobb pontszámot: az ezt elérő kutyák ott győznek, a holtverseny is győzelem. Csak olyan szempont számít, ahol a legjobb pont legalább az alsó határ, mert az alatta lévő pont nem értékelhető. Egy kutya akkor felel meg, ha van legalább egy győzelme, és minden győzelmét a szempont maximális pontszámával szerezte. Ha egy kutyának nincs győzelme, nem kerül be a listába. A legjobb pontok és az ellenőrzés is O(N·M) időben fut.
*/
/*
Hint 1: || Szempontonként keresd meg a legnagyobb pontszámot, és jelöld, mely kutyák érik el: ezek a szempontban győztesek. ||
Hint 2: || Egy kutya akkor felel meg, ha van legalább egy győzelme, és minden győzelmében a szempont megadott maximumát kapta. Ezt egy bejárással ellenőrizd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &sor : p)
        for (int &x : sor) cin >> x;

    // Szempontonként a legjobb pontszám (a holtverseny is ugyanez a pont).
    vector<int> legjobb(m, -1);
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            legjobb[j] = max(legjobb[j], p[i][j]);

    vector<int> valasz;
    for (int i = 0; i < n; i++) {
        bool van_gyozelem = false;
        bool mind_maximum = true;
        for (int j = 0; j < m; j++) {
            // Csak az értékelhető (alsó határt elérő) legjobb pont számít győzelemnek.
            if (legjobb[j] >= minPont[j] && p[i][j] == legjobb[j]) {
                van_gyozelem = true;
                if (p[i][j] != maxPont[j]) mind_maximum = false;
            }
        }
        if (van_gyozelem && mind_maximum) valasz.push_back(i + 1);
    }

    cout << valasz.size();
    for (int x : valasz) cout << ' ' << x;
    cout << '\n';
    return 0;
}
