/*
Megoldás lényege:
Egy ponthatár távolsága az alatta lévő legnagyobb pontszámtól számított különbség. Ez akkor a legnagyobb, ha a ponthatárt
két egymást követő különböző pontszám közötti hézagba tesszük, a felső pontszám előtti egész számra. Egy hézagban d = felső - alsó - 1
egész szám van, és a ponthatár távolsága ekkor pontosan d. A d = 0 hézagba nem lehet ponthatárt tenni, mert az egyik pontszámra esne.
Négy ponthatár négy különböző hézagba kerül, így minden osztályzat kap legalább egy tanulót, és a legkisebb kiválasztott d
adja az optimumot. Ezért a négy legnagyobb, legalább 1 értékű hézagot kell kiválasztani. Ha kevesebb van, nincs megoldás, és 0-t írunk.
A pontszámokat jelölő tömbben tároljuk, így nincs szükség rendezésre. Az időigény O(N + M).
*/
/*
Hint 1: || Egy ponthatár jó, ha minél távolabb van attól a legközelebbi tanulótól, akinek kisebb a pontszáma. Ezért a ponthatárt két egymás utáni, különböző pontszám közé érdemes tenni. ||
Hint 2: || Egy hézagba akkor lehet ponthatárt tenni, ha van benne egész szám. A legjobb hely a felső pontszám előtti egész, a távolság pedig a két pontszám különbsége mínusz egy. Válaszd ki a négy legnagyobb ilyen hézagot; ha kevesebb van, a válasz 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Jelölő tömb: seen[x] = 1, ha van x pontot elért tanuló.
    vector<char> seen(m + 1, 0);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        seen[x] = 1;
    }

    // A négy legjobb hézag: (távolság d, ponthatár). Csökkenő d szerint, azonos d-nél a balsó marad előrébb.
    vector<pair<int, int>> top;
    int prev = -1;
    for (int x = 0; x <= m; ++x) {
        if (!seen[x]) continue;
        if (prev >= 0) {
            int d = x - prev - 1;  // ennyi egész van a két pontszám között
            if (d >= 1) {
                size_t pos = 0;
                while (pos < top.size() && top[pos].first >= d) ++pos;
                if (pos < 4) {
                    top.insert(top.begin() + pos, make_pair(d, x - 1));
                    if (top.size() > 4) top.pop_back();
                }
            }
        }
        prev = x;
    }

    if (top.size() < 4) {
        cout << 0 << '\n';
        return 0;
    }

    sort(top.begin(), top.end(), [](const pair<int, int>& p, const pair<int, int>& q) {
        return p.second < q.second;
    });
    for (const auto& p : top) cout << p.second << '\n';
    return 0;
}
