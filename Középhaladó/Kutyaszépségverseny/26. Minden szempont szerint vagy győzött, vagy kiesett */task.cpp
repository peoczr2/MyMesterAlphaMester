/*
Megoldás lényege:
Szempontonként csak az alsó határt elérő (értékelhető) kutyák között keressük a legnagyobb pontszámot, és megszámoljuk, hányan érik el. Egy kutya ebben a szempontban akkor győzött, ha értékelhető, a pontja ez a maximum, és rajta kívül senki más nem éri el. Az a kutya felel meg, amelyik minden szempontban vagy kiesett, vagy győzött. Az időigény O(N·M).
*/
/*
Hint 1: || Szempontonként először a kiesőket hagyd ki, a megmaradók közül keresd meg a legnagyobb pontszámot, és jegyezd fel, hányan érik el pontosan ezt. ||
Hint 2: || Egy kutyára minden szempontban az a feltétel, hogy a pontja a határ alatt van, vagy a pontja a legnagyobb, és ezt a darabszám alapján egyedül éri el. ||
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

    // szempontonként a legnagyobb értékelhető pont és az azt egyedül elérő kutya jelzése
    vector<int> legjobb(m, -1), darab(m, 0);
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++) {
            if (p[i][j] < minPont[j]) continue;
            if (p[i][j] > legjobb[j]) {
                legjobb[j] = p[i][j];
                darab[j] = 1;
            } else if (p[i][j] == legjobb[j]) {
                darab[j]++;
            }
        }

    bool van = false;
    for (int i = 0; i < n && !van; i++) {
        bool mindenSzempont = true;
        for (int j = 0; j < m; j++) {
            bool kiesett = p[i][j] < minPont[j];
            bool gyozott = !kiesett && p[i][j] == legjobb[j] && darab[j] == 1;
            if (!kiesett && !gyozott) {
                mindenSzempont = false;
                break;
            }
        }
        if (mindenSzempont) van = true;
    }

    cout << (van ? "VAN" : "NINCS") << '\n';
    return 0;
}
