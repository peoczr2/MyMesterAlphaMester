/*
Megoldás lényege:
Egy csomagpár költsége a közöttük lévő élek száma a fában, így a teljes költség felbontható élekre: egy él annyi csomagpárt terhel meg, amelyeknek pontosan az egyik végpontja van az él egyik oldalán. A bináris keresőfában minden részfa a kulcsok egy összefüggő [l, r] intervallumát foglalja el, ezért a részfa szülőéléhez tartozó költség a cut(l, r) érték, vagyis az intervallumot elhagyó vagy oda belépő csomagok súlya. Ezt 2D prefixösszegekkel O(1) idő alatt megkapjuk. Az intervallum-DP g(l, r) = cut(l, r) + min_k (g(l, k - 1) + g(k + 1, r)) a legkisebb költséget adja egy [l, r] kulcsú részfára, az üres intervallum értéke 0. A gyökér R miatt a válasz g(1, R - 1) + g(R + 1, N), az időigény O(N^3), ami N <= 500 esetén bőven belefér.
*/
/*
Hint 1: || Egy csomagpár költsége a közöttük lévő élek száma. Vizsgáld meg egy-egy élt külön: hány csomagpár megy át rajta, vagyis melyek azok a párok, amelyeknek pontosan az egyik vége van az él egyik oldalán. ||
Hint 2: || Bináris keresőfában minden részfa a kulcsok egy összefüggő intervallumát tartalmazza. Egy részfa szülőéléhez tartozó költség az [l, r] intervallum kivágott súlya, vagyis azoknak a csomagoknak az összege, amelyeknek pontosan az egyik vége esik az intervallumba. Ezt 2D prefixösszegekkel gyorsan kiszámolhatod. ||
Hint 3: || Írj intervallum-DP-t: legyen g(l, r) a legkisebb költség egy [l, r] kulcsú részfára a szülőéllel együtt. Ekkor g(l, r) = cut(l, r) + min_k (g(l, k - 1) + g(k + 1, r)), ahol az üres intervallum értéke 0. A keresett válasz g(1, R - 1) + g(R + 1, N), mert a gyökér bal és jobb részfája ezek. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, r;
    cin >> n >> m >> r;

    // W[i][j]: az i és j közötti csomagok száma (szimmetrikus)
    vector<vector<long long>> W(n + 2, vector<long long>(n + 2, 0));
    for (int i = 0; i < m; ++i) {
        int s, d;
        long long w;
        cin >> s >> d >> w;
        W[s][d] = w;
        W[d][s] = w;
    }

    // P[i][j] = Σ_{a <= i, b <= j} W[a][b]
    vector<vector<long long>> P(n + 2, vector<long long>(n + 2, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            P[i][j] = W[i][j] + P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1];

    // a [i1..i2] x [j1..j2] téglalap összege
    auto rect = [&](int i1, int i2, int j1, int j2) -> long long {
        if (i1 > i2 || j1 > j2) return 0;
        return P[i2][j2] - P[i1 - 1][j2] - P[i2][j1 - 1] + P[i1 - 1][j1 - 1];
    };

    // cut(l, r): az [l..r] intervallumot elhagyó csomagpárok súlya
    auto cut = [&](int l, int rr) -> long long {
        return rect(l, rr, 1, l - 1) + rect(l, rr, rr + 1, n);
    };

    // g[l][rr]: legkisebb költség egy [l..rr] kulcsú részfára a szülőéllel együtt
    // (üres intervallumokra a tömb értéke 0 marad)
    vector<vector<long long>> g(n + 2, vector<long long>(n + 2, 0));
    for (int len = 1; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int rr = l + len - 1;
            long long best = LLONG_MAX;
            for (int k = l; k <= rr; ++k) {
                best = min(best, g[l][k - 1] + g[k + 1][rr]);
            }
            g[l][rr] = cut(l, rr) + best;
        }
    }

    cout << g[1][r - 1] + g[r + 1][n] << '\n';
    return 0;
}
