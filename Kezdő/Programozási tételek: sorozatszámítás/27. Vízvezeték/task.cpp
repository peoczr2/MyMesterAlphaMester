/*
Megoldás lényege:
Minden városba pontosan egy vezeték érkezik, a vezetékek nem ágaznak el, így a hálózat diszjunkt irányított
láncokból és zárt körökből áll. Minden lánc egy vízlelőhelyről indul, ahonnan korlátlan víz érkezik. A lánc mentén
haladva a szakasz kapacitása korlátozza a továbbjutó vizet, és minden városban az ott kivett F mennyiség csökkenti a
tovább menő maradékot. A lelőhely nélküli zárt körben a víz nem fogy el, ezért ott a bemenő szakasz kapacitása a
válasz. A városok száma M, mert minden vezeték egy városba fut. Az időigény O(N + M).
*/
/*
Hint 1: || Minden városba pontosan egy vezeték fut, így a városok száma M. A hálózat láncokból áll, amelyek egy lelőhelyről indulnak, és lehetnek lelőhely nélküli zárt körök is. ||
Hint 2: || Egy lánc mentén haladva a szakasz a rajta átfolyó vizet a kapacitásáig engedi tovább. Egy városba érkező víz a szakasz kapacitásának és a lelőhelytől eddig megmaradt víznek a minimuma. ||
Hint 3: || Egy város a megérkező vízből legfeljebb F-et von le, a maradék megy tovább. Zárt körben nincs kimerülő forrás, ott csak a bemenő szakasz kapacitása korlátoz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, f;
    cin >> n >> m >> f;

    vector<int> kov(n + 1, 0), kap(n + 1, 0), bejovo(n + 1, 0), bekap(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b, k;
        cin >> a >> b >> k;
        kov[a] = b;
        kap[a] = k;
        bejovo[b]++;
        bekap[b] = k;
    }

    const int VEGTELEN = INT_MAX / 2;
    // erk[v] >= 0: v városba ennyi víz juthat el; -1: nem város
    vector<int> erk(n + 1, -1);
    for (int v = 1; v <= n; v++) {
        if (bejovo[v] != 0 || kov[v] == 0) continue;  // csak vízlelőhelyről indulunk
        int maradek = VEGTELEN;                       // a lelőhelyről korlátlan víz indul
        int cur = v;
        while (kov[cur] != 0) {
            int nxt = kov[cur];
            int megerkezo = min(kap[cur], maradek);
            erk[nxt] = megerkezo;
            maradek = megerkezo - min(f, megerkezo);  // a város kivesz F-et, ha van annyi
            cur = nxt;
        }
    }
    // lelőhely nélküli zárt körök: nincs kimerülő forrás, csak a bemenő szakasz korlátoz
    for (int v = 1; v <= n; v++)
        if (bejovo[v] == 1 && erk[v] < 0) erk[v] = bekap[v];

    int varosok = 0;
    for (int v = 1; v <= n; v++)
        if (erk[v] >= 0) varosok++;
    cout << varosok << "\n";
    for (int v = 1; v <= n; v++)
        if (erk[v] >= 0) cout << v << " " << erk[v] << "\n";
    return 0;
}
