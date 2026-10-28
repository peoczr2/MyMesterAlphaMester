/*
Megoldás lényege:
Egy csoport (részfeladat) költsége a benne lévő tesztek pontösszege, szorozva azzal, hogy hány versenyző
oldotta meg az összes tesztjét. A dp[i][t] az első t tesztet i csoportba bontva adja a minimális összköltséget:
dp[i][t] = min_s dp[i-1][s] + cnt(s,t) * (P_t - P_s), ahol cnt(s,t) a (s,t] szakaszt mindenben megoldók száma.
A cnt(s,t) a t-ig az utolsó hibás tesztek rendezett listájából olvasható ki: cnt(s,t) <= k pontosan akkor,
ha s kisebb a (k+1). legkisebb utolsó hibás indexnél. Minden k-ra a dp[i-1][s] - k*P_s előtagminimuma adja
a legjobb s-t, mert ha k nagyobb vagy egyenlő a valódi cnt-nél, a becslés nem lehet kisebb a valódi költségnél.
Az időigény O(S * N * T), ahol N <= 50 és S <= 50.
*/
/*
Hint 1: || Egy csoport költsége: a csoportot mindenben megoldók száma szorozva a csoport pontösszegével.
Az első t tesztre dinamikus programozással keressük a csoporthatárokat. ||
Hint 2: || Versenyzőnként tartsd nyilván, melyik a legutolsó hibás teszt a t-ig. A (s,t] szakaszt
pontosan akkor oldja meg a versenyző, ha az utolsó hibája s-nél nem nagyobb. ||
Hint 3: || Rögzített k megoldószámra a dp[i-1][s] - k*P_s előtagminimuma adja a legjobb s-t,
és minden t-re csak N+1 darab k-t kell kipróbálni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t, s;
    cin >> n >> t >> s;

    vector<long long> pre(t + 1, 0);
    for (int i = 1; i <= t; ++i) {
        long long p;
        cin >> p;
        pre[i] = pre[i - 1] + p;
    }

    vector<string> res(n);
    for (int c = 0; c < n; ++c) cin >> res[c];

    // sl[tt * n + k]: a k-adik legkisebb (0-indexelt) utolsó hibás index tt-ig
    vector<int> sl((size_t)(t + 1) * n, 0);
    vector<int> last(n, 0);
    for (int tt = 1; tt <= t; ++tt) {
        for (int c = 0; c < n; ++c)
            if (res[c][tt - 1] == '0') last[c] = tt;
        vector<int> v = last;
        sort(v.begin(), v.end());
        for (int k = 0; k < n; ++k) sl[(size_t)tt * n + k] = v[k];
    }

    const long long INF = (long long)1e18;
    vector<long long> prev(t + 1, INF), cur(t + 1, INF), pm(t + 1, INF), ans(s + 1, INF);
    prev[0] = 0;

    for (int i = 1; i <= s; ++i) {
        fill(cur.begin(), cur.end(), INF);
        for (int k = 0; k <= n; ++k) {
            long long best = INF;
            for (int x = 0; x <= t; ++x) {
                if (prev[x] < INF) best = min(best, prev[x] - (long long)k * pre[x]);
                pm[x] = best;
            }
            for (int tt = 1; tt <= t; ++tt) {
                int b = tt - 1;
                if (k < n) b = min(b, sl[(size_t)tt * n + k] - 1);
                if (b < 0) continue;
                if (pm[b] >= INF) continue;
                long long cand = pm[b] + (long long)k * pre[tt];
                if (cand < cur[tt]) cur[tt] = cand;
            }
        }
        ans[i] = cur[t];
        swap(prev, cur);
    }

    for (int i = 1; i <= s; ++i) cout << ans[i] << "\n";
    return 0;
}
