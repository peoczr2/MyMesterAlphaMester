/*
Megoldás lényege:
A bejárás a cellák sorszámainak egy permutációja, amelyben minden belső elem helyi szélsőérték
(mindkét szomszédja nagyobb, vagy mindkét szomszédja kisebb), tehát az ugrások iránya váltakozik.
A cellákat sorszámuk szerint növekvő sorrendben dolgozzuk fel, és közben nyilvántartjuk, hány
összefüggő láncot építettünk a végső bejárás részeiből, és hogy a K és a V cella már benne van-e.
Egy belső cella vagy új láncot indít (később jönnek a szomszédai, ez völgy), vagy két szomszédos
lánc végét köti össze (a szomszédai korábban jöttek, ez csúcs); egyoldali kapcsolódás nem lehet,
mert az monoton lépés volna. A K és a V cella egy szomszéddal rendelkezik, ezért új láncot indíthat,
vagy egy lánc szabad végéhez csatlakozhat. Az állapotok száma O(N^2), így az időigény O(N^2).
*/
/*
Hint 1: || Minden belső cella helyi minimum vagy helyi maximum, így a cellákat sorszámuk szerint
növekvő sorrendben érdemes feldolgozni, és az építés alatt álló láncokat számolni. ||
Hint 2: || Állapot: dp[láncok száma][K benne van-e][V benne van-e]. Egy belső cella új láncként
j+1-a-b helyen szúrható be, két szomszédos lánc összekötése j-1 módon történhet. K és V csak
a lánc szélére csatlakozhat, az elejére illetve a végére. ||
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

int main() {
    int n, k, v;
    cin >> n >> k >> v;
    if (k == v) {
        cout << 0 << "\n";
        return 0;
    }

    vector<array<array<long long, 2>, 2>> dp(n + 2), nd(n + 2);
    for (auto &x : dp)
        for (auto &y : x) y.fill(0);
    dp[0][0][0] = 1;

    for (int c = 1; c <= n; ++c) {
        for (auto &x : nd)
            for (auto &y : x) y.fill(0);

        for (int j = 0; j <= n; ++j)
            for (int a = 0; a < 2; ++a)
                for (int b = 0; b < 2; ++b) {
                    long long val = dp[j][a][b];
                    if (val == 0) continue;

                    if (c == k) {
                        if (a == 0) {
                            nd[j + 1][1][b] = (nd[j + 1][1][b] + val) % MOD;
                            if (j >= 1) nd[j][1][b] = (nd[j][1][b] + val) % MOD;
                        }
                    } else if (c == v) {
                        if (b == 0) {
                            nd[j + 1][a][1] = (nd[j + 1][a][1] + val) % MOD;
                            if (j >= 1) nd[j][a][1] = (nd[j][a][1] + val) % MOD;
                        }
                    } else {
                        long long w = j + 1 - a - b;
                        if (w > 0) nd[j + 1][a][b] = (nd[j + 1][a][b] + val * w) % MOD;
                        if (j >= 2) nd[j - 1][a][b] = (nd[j - 1][a][b] + val * (j - 1)) % MOD;
                    }
                }
        swap(dp, nd);
    }

    cout << dp[1][1][1] << "\n";
    return 0;
}
