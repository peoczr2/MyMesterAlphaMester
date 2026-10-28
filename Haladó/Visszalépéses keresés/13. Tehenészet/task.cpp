/*
Tehenészetek
Feladat: N ≤ 10 tehenészet (napi tejmennyiség T[i]) és M ≤ 7 tejüzem (kapacitás U[j]) adott, valamint
a literenkénti szállítási költség c[i][j]. Minden tehenészet a teljes tejét egyetlen tejüzembe viszi,
egy üzem sem léphet túl a kapacitásán. A cél a minimális összköltség (T[i] · c[i][j] összege), és ki
kell írni, melyik tehenészet melyik üzembe szállít.

Megoldási ötlet: üzemenként döntünk, melyik tehenészet-csoportot kapja (részhalmaz-DP).
dp[j][mask] = minimális költség, ha az első j üzem pontosan a mask tehenészeteinek tejét veszi át.
A (j+1). üzem a mask egy sub részhalmazát kapja, ha tej(sub) ≤ U[j]:
  dp[j+1][mask] = min dp[j][mask − sub] + koltseg[j][sub],
ahol koltseg[j][sub] = a sub tehenészeteinek szállítási költsége a j. üzembe (előre kiszámolva).
A részhalmazokat a sub = (sub − 1) & mask lépéssel járjuk be; az összes (mask, sub) pár száma 3^N,
így az idő O(M · 3^N) ≈ 4·10^5, a memória O(M · 2^N). A visszafejtéshez üzemenként eltároljuk a
választott sub-ot. A bemenetre a feladat szerint mindig van megoldás.
*/
/*
Hint 1: || Ne tehenészetenként dönts, hanem üzemenként: melyik tehenészet-csoport tejét veszi át az adott üzem? Egy csoport akkor jó, ha a tejmennyiségek összege belefér az üzem kapacitásába. ||
Hint 2: || N ≤ 10, így a tehenészetek halmaza bitmaszkkal írható le. Állapot: (hány üzemet dolgoztunk már fel, mely tehenészetek vannak már beosztva); a következő üzem a maradék egy részhalmazát kapja. ||
Hint 3: || dp[j+1][mask] = min dp[j][mask − sub] + költség(j, sub), ahol sub ⊆ mask és tej(sub) ≤ U[j] (az üres halmaz is jó). A részhalmazokat a sub = (sub − 1) AND mask lépéssel járd be, ez összesen 3^N pár üzemenként. A beosztáshoz tárold, melyik sub adta a minimumot. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long INF = LLONG_MAX / 4;

    // beolvasás
    int n, m;
    cin >> n >> m;
    vector<long long> T(n), U(m);
    for (int i = 0; i < n; i++) cin >> T[i];
    for (int j = 0; j < m; j++) cin >> U[j];
    vector<vector<long long>> c(n, vector<long long>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> c[i][j];

    // tej[mask] = a mask tehenészeteinek összes teje,
    // koltseg[j][mask] = a mask tehenészeteinek szállítási költsége a j. üzembe
    // (mindkettőt a legalsó bit leválasztásával számoljuk)
    int teljes = (1 << n) - 1;
    vector<long long> tej(1 << n, 0);
    vector<vector<long long>> koltseg(m, vector<long long>(1 << n, 0));
    for (int mask = 1; mask <= teljes; mask++) {
        int i = __builtin_ctz(mask);
        int maradek = mask & (mask - 1);
        tej[mask] = tej[maradek] + T[i];
        for (int j = 0; j < m; j++) koltseg[j][mask] = koltseg[j][maradek] + T[i] * c[i][j];
    }

    // dp[j][mask], és valaszt[j][mask] = melyik sub-ot kapta a j. üzem
    vector<vector<long long>> dp(m + 1, vector<long long>(1 << n, INF));
    vector<vector<int>> valaszt(m + 1, vector<int>(1 << n, 0));
    dp[0][0] = 0;

    // átmenet: a j. üzem (0-tól számozva) a mask egy részhalmazát kapja
    for (int j = 0; j < m; j++)
        for (int mask = 0; mask <= teljes; mask++) {
            // részhalmazok bejárása: sub = (sub - 1) & mask, az üres halmazig bezárólag
            for (int sub = mask;; sub = (sub - 1) & mask) {
                if (tej[sub] <= U[j] && dp[j][mask ^ sub] != INF) {
                    long long uj = dp[j][mask ^ sub] + koltseg[j][sub];
                    if (uj < dp[j + 1][mask]) {
                        dp[j + 1][mask] = uj;
                        valaszt[j + 1][mask] = sub;
                    }
                }
                if (sub == 0) break;
            }
        }

    // rekonstrukció: az utolsó üzemtől visszafelé leválasztjuk a kapott csoportokat
    vector<int> uzem(n);
    int mask = teljes;
    for (int j = m; j >= 1; j--) {
        int sub = valaszt[j][mask];
        for (int i = 0; i < n; i++)
            if (sub >> i & 1) uzem[i] = j;
        mask ^= sub;
    }

    // kiírás
    cout << dp[m][teljes] << '\n';
    for (int i = 0; i < n; i++) cout << uzem[i] << (i + 1 < n ? ' ' : '\n');
    return 0;
}
