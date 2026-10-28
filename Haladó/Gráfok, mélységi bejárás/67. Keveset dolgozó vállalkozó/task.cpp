/*
Megoldás lényege:
Ez hátizsák-típusú dinamikus programozás. Állapotnak az elért bevételt választjuk, F-re levágva (min(F, bevétel)), az értéke pedig a legkisebb eddig elért munkaidő. Minden munka legfeljebb egyszer vállalható, ezért a 0/1 hátizsák szerint, munkánként a régi táblázatból indulva frissítünk. A visszakövetéshez munkánként eltároljuk, melyik állapotból jutottunk az aktuálisba, így az F-es állapotból visszafelé haladva megkapjuk a felvett munkákat. Az időigény és a memóriaigény O(N * F), ami legfeljebb 10^6 lépés.
*/
/*
Hint 1: || Az állapot az elért bevétel legyen (F-re levágva), az érték pedig a legkisebb munkaidő, amellyel ezt el lehet érni. ||
Hint 2: || Minden munkát legfeljebb egyszer vehetünk fel, ezért munkánként a korábbi táblázatból indulva frissíts: a bevételhez hozzáadjuk a munka bevételét, a munkaidőhöz pedig az idejét, és a bevételt F-nél levágjuk. ||
Hint 3: || Munkánként tárold, melyik előző állapotból jutottál az aktuálisba; az F-es állapotból visszafelé haladva kapod a felvett munkák sorszámait. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, f;
    cin >> n >> f;
    vector<int> t(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) cin >> t[i] >> b[i];

    const int INF = INT_MAX / 2;
    // dp[j]: legkisebb munkaidő, amellyel j (F-re levágott) bevétel érhető el.
    vector<int> dp(f + 1, INF);
    dp[0] = 0;
    // prv[i][j]: a j állapotot az i. munka felvételével értük el, ekkor ez az előző állapot; -1: nem így jutottunk el.
    vector<vector<int>> prv(n + 1, vector<int>(f + 1, -1));
    for (int i = 1; i <= n; ++i) {
        vector<int> nd = dp;
        for (int j = 0; j <= f; ++j) {
            if (dp[j] == INF) continue;
            int nj = min(f, j + b[i]);
            if (dp[j] + t[i] < nd[nj]) {
                nd[nj] = dp[j] + t[i];
                prv[i][nj] = j;
            }
        }
        dp = nd;
    }

    vector<int> chosen;
    int j = f;
    for (int i = n; i >= 1; --i) {
        if (prv[i][j] != -1) {
            chosen.push_back(i);
            j = prv[i][j];
        }
    }
    sort(chosen.begin(), chosen.end());

    cout << dp[f] << '\n';
    cout << chosen.size();
    for (int x : chosen) cout << ' ' << x;
    cout << '\n';
    return 0;
}
