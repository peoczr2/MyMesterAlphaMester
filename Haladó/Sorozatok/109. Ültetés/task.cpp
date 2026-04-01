/*
Megoldás lényege:
Az ülésrend egy permutáció: az i. diák jelenleg az S[i] székben ül, de az i. széket szeretné.
Ez a permutáció ciklusokra bomlik. Egy k hosszú, nem triviális ciklus rendezéséhez az extra üres
székkel pontosan k+1 átülés kell, ezért a minimális lépésszám a nemtriviális ciklusokra összesítve
Σ(k+1).
*/
// Hint 1: || A feladat a diák -> jelenlegi szék permutáció ciklusfelbontására vezethető vissza. ||
// Hint 2: || Egy k hosszú rossz ciklus rendezése az extra üres székkel k+1 lépés. ||
// Hint 3: || Az 1 hosszú (helyes) ciklusokhoz 0 lépés tartozik. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> seat(N + 1);
    for (int i = 1; i <= N; ++i) cin >> seat[i];

    vector<char> vis(N + 1, 0);
    long long ans = 0;

    for (int i = 1; i <= N; ++i) {
        if (vis[i] || seat[i] == i) continue;
        int v = i, len = 0;
        while (!vis[v]) {
            vis[v] = 1;
            v = seat[v];
            ++len;
        }
        ans += len + 1;
    }

    cout << ans << '\n';
    return 0;
}
