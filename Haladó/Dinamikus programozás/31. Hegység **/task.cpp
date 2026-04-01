/*
A lépések mindig szigorúan magasabb mezőre mennek, ezért az irányított gráf körmentes: a csúcsok feldolgozhatók
magasság szerint csökkenő sorrendben. Egy mező dp értéke a belőle induló leghosszabb emelkedő út hossza, ami a
magasabb szomszédok dp értékeiből számolható. Elég a legjobb kezdőmezőt megjegyezni, mert a feladat csak a maximális
lépésszámot és egy hozzá tartozó induló pozíciót kéri.
*/
/*
Hint 1: || A magasság szerinti szigorú növekedés miatt nincs kör, tehát dinamikus programozással lehet visszafelé számolni. ||
Hint 2: || Egy mezőből csak a nála magasabb négy szomszéd valamelyikére érdemes nézni. ||
Hint 3: || Ha a magasság kicsi tartományból jön, akkor topologikus rendezés helyett magasság szerinti csoportosítás is jó. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int total = n * m;

    vector<int> h(total);
    vector<int> cnt(10001, 0);
    for (int i = 0; i < total; ++i) {
        cin >> h[i];
        ++cnt[h[i]];
    }

    vector<int> start(10002, 0);
    for (int value = 1; value <= 10001; ++value) {
        start[value] = start[value - 1] + cnt[value - 1];
    }

    vector<int> ptr = start;
    vector<int> order(total);
    for (int idx = 0; idx < total; ++idx) {
        order[ptr[h[idx]]++] = idx;
    }

    vector<int> dp(total, 0);
    int best_len = 0;
    int best_idx = 0;
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    for (int value = 10000; value >= 0; --value) {
        int begin = start[value];
        int end = begin + cnt[value];
        for (int pos = begin; pos < end; ++pos) {
            int idx = order[pos];
            int r = idx / m;
            int c = idx % m;
            int best_here = 0;
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                    continue;
                }
                int nidx = nr * m + nc;
                if (h[nidx] > h[idx]) {
                    best_here = max(best_here, dp[nidx] + 1);
                }
            }
            dp[idx] = best_here;
            if (best_here > best_len) {
                best_len = best_here;
                best_idx = idx;
            }
        }
    }

    cout << best_len << '\n';
    cout << best_idx / m + 1 << ' ' << best_idx % m + 1 << '\n';
    return 0;
}
