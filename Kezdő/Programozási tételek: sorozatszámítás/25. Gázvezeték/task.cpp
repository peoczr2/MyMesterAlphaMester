/*
Megoldás lényege:
A vezetékrendszerben nincs elágazás, ezért a szakaszok diszjunkt, irányított láncokat alkotnak. Minden lánc
egy lelőhelyről (ahová nem érkezik vezeték) indul, és egy fogyasztóban (ahonnan nem megy tovább vezeték) ér véget.
Minden lelőhelyről elindulva követjük a kimenő éleket, és közben a szakaszok kapacitásának minimumát tartjuk
nyilván. A lánc végén álló csúcs a fogyasztó, ide a minimum juthat el. A fogyasztókat végül sorszám szerint
növekvően írjuk ki. Az időigény O(N + M).
*/
/*
Hint 1: || Egy végpontba legfeljebb egy vezeték érkezik és legfeljebb egy megy ki belőle, így minden fogyasztóhoz egyetlen út vezet a lelőhelyéből. ||
Hint 2: || Tárold csúcsonként a kimenő szakasz végpontját és kapacitását, valamint a bejövő élek számát. Minden olyan csúcsból indulj el, amelybe nem érkezik vezeték, és a kimenő éleken haladva tartsd nyilván az érintett szakaszok kapacitásának minimumát. ||
Hint 3: || A lánc végén álló csúcsnál írd be az eddigi minimumot, majd a csúcsokat 1-től N-ig bejárva írd ki azokat, amelyek fogyasztók. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> kov(n + 1, 0), kap(n + 1, 0), bejovo(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b, k;
        cin >> a >> b >> k;
        kov[a] = b;
        kap[a] = k;
        bejovo[b]++;
    }

    // ans[v] >= 0: v fogyasztó, és ennyi gáz juthat el hozzá; -1: nem fogyasztó
    vector<int> ans(n + 1, -1);
    for (int v = 1; v <= n; v++) {
        if (bejovo[v] != 0 || kov[v] == 0) continue;  // csak lelőhelyről indulunk
        int minimum = INT_MAX;
        int cur = v;
        while (kov[cur] != 0) {
            minimum = min(minimum, kap[cur]);
            cur = kov[cur];
        }
        ans[cur] = minimum;
    }

    int g = 0;
    for (int v = 1; v <= n; v++)
        if (ans[v] >= 0) g++;
    cout << g << "\n";
    for (int v = 1; v <= n; v++)
        if (ans[v] >= 0) cout << v << " " << ans[v] << "\n";
    return 0;
}
