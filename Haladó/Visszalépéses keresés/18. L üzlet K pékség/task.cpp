/*
L üzlet – K pékség
Feladat: L ≤ 12 üzlet (igény) és K ≤ 12 pékség (napi kapacitás, ár) adott. Minden üzlet a teljes
igényét egyetlen, vele kapcsolatban lévő pékségtől rendeli; egy pékség sem léphet túl a kapacitásán.
A cél a minimális összköltség (ár · igény összege); ki kell írni minden üzlet pékségét.

Megoldási ötlet: pékségenként döntünk, melyik üzletcsoportot szolgálja ki (részhalmaz-DP).
dp[k][mask] = minimális költség, ha az első k pékség pontosan a mask üzleteit szolgálja ki.
A (k+1). pékség a mask egy sub részhalmazát kapja (mind kapcsolatban van vele, igény(sub) ≤ kapacitás):
  dp[k+1][mask] = min dp[k][mask − sub] + ár · igény(sub).
A részhalmazokat a sub = (sub − 1) & mask lépéssel járjuk be; az összes (mask, sub) pár száma 3^L,
így az idő O(K · 3^L) ≈ 6,4·10^6, a memória O(K · 2^L). A visszafejtéshez pékségenként eltároljuk a
választott sub-ot. Ha nincs megoldás (a feladat erről nem szól), -1-et írunk ki.
*/
/*
Hint 1: || Ne üzletenként dönts, hanem pékségenként: melyik üzletcsoportot szolgálja ki az adott pékség? Egy csoport akkor jó, ha minden tagja kapcsolatban van vele, és az igények összege belefér a kapacitásba. ||
Hint 2: || Állapot: (hány pékséget dolgoztunk már fel, mely üzletek vannak kiszolgálva). A következő pékség a még kiszolgálatlan üzletek egy részhalmazát kapja: ez részhalmaz-felsorolás. ||
Hint 3: || dp[k+1][mask] = min dp[k][mask − sub] + ár[k] · igény(sub), ahol sub ⊆ mask (az üres halmaz is jó). A részhalmazokat a sub = (sub − 1) AND mask lépéssel járd be; az összes (mask, sub) pár száma 3^L. A visszafejtéshez tárold, melyik sub adta a minimumot. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long INF = LLONG_MAX / 4;

    // beolvasás; kapcs[k] = a k. pékséggel kapcsolatban lévő üzletek maszkja
    int L, K;
    cin >> L >> K;
    vector<long long> kap(K), ar(K), igeny(L);
    vector<int> kapcs(K, 0);
    for (int k = 0; k < K; k++) cin >> kap[k];
    for (int k = 0; k < K; k++) cin >> ar[k];
    for (int i = 0; i < L; i++) {
        for (int k = 0; k < K; k++) {
            int x;
            cin >> x;
            if (x) kapcs[k] |= 1 << i;
        }
        cin >> igeny[i];
    }

    // osszeg[mask] = a mask üzleteinek összigénye (a legalsó bitet leválasztva)
    int teljes = (1 << L) - 1;
    vector<long long> osszeg(1 << L, 0);
    for (int mask = 1; mask <= teljes; mask++) {
        int i = __builtin_ctz(mask);
        osszeg[mask] = osszeg[mask & (mask - 1)] + igeny[i];
    }

    // dp[k][mask], és valaszt[k][mask] = melyik sub-ot kapta a k. pékség
    vector<vector<long long>> dp(K + 1, vector<long long>(1 << L, INF));
    vector<vector<int>> valaszt(K + 1, vector<int>(1 << L, 0));
    dp[0][0] = 0;

    // átmenet: a k. pékség (0-tól számozva) a mask egy részhalmazát kapja
    for (int k = 0; k < K; k++)
        for (int mask = 0; mask <= teljes; mask++) {
            int lehet = mask & kapcs[k];  // csak kapcsolatban lévő üzletet kaphat
            // részhalmazok bejárása: sub = (sub - 1) & lehet, az üres halmazig bezárólag
            for (int sub = lehet;; sub = (sub - 1) & lehet) {
                if (osszeg[sub] <= kap[k] && dp[k][mask ^ sub] != INF) {
                    long long c = dp[k][mask ^ sub] + ar[k] * osszeg[sub];
                    if (c < dp[k + 1][mask]) {
                        dp[k + 1][mask] = c;
                        valaszt[k + 1][mask] = sub;
                    }
                }
                if (sub == 0) break;
            }
        }

    if (dp[K][teljes] == INF) {  // a feladat nem írja, mi legyen ilyenkor
        cout << -1 << '\n';
        return 0;
    }

    // rekonstrukció: az utolsó pékségtől visszafelé leválasztjuk a kapott csoportokat
    vector<int> pekseg(L);
    int mask = teljes;
    for (int k = K; k >= 1; k--) {
        int sub = valaszt[k][mask];
        for (int i = 0; i < L; i++)
            if (sub >> i & 1) pekseg[i] = k;
        mask ^= sub;
    }

    // kiírás
    for (int i = 0; i < L; i++) cout << pekseg[i] << (i + 1 < L ? ' ' : '\n');
    return 0;
}
