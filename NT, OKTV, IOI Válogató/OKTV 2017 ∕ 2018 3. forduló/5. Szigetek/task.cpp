/*
Megoldás lényege:
A felfedezések fát alkotnak: az 1-es sziget a gyökér, és minden sziget szülője az a sziget, amelyről felfedezték. Egy felfedezési sorrend pontosan akkor érvényes, ha minden sziget a szülője után kerül sorra. Az ilyen sorrendek száma egy N csúcsú gyökeres fában N! osztva az összes csúcs részfa-méretének szorzatával. A részfa-méreteket a gyökértől indított BFS sorrend fordított bejárásával kapjuk meg, így nincs mélységi rekurzió. Az osztást moduló prímszámmal, Fermat-tétel szerinti hatványozással (inverz = x^(MOD-2)) végezzük. Az időigény O(N log MOD).
*/
/*
Hint 1: || Gondold végig, mikor kerülhet egy sziget a sorba: csak akkor, ha az a sziget, amelyről felfedezték, már korábban szerepelt. Így a szülő mindig a gyerek előtt áll. ||
Hint 2: || Egy gyökeres fában a csúcsok azon sorrendjeinek száma, ahol a szülő mindig a gyerek előtt van, N! osztva az egyes csúcsok részfa-méreteinek szorzatával. Ehhez elég minden csúcsra kiszámolni a részfa méretét. ||
Hint 3: || A részfa-méretek a gyökértől lefelé haladó bejárás fordított sorrendjében összegezhetők, mert a gyerek mindig előbb kerül feldolgozásra. A mélység akár 20 000 is lehet, ezért BFS-sel járd be a fát, ne rekurzióval. Az osztást a moduló prímszám szerinti inverzzel végezd el. ||
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

long long power(long long base, long long exp) {
    long long result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) result = result * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> child(n + 1);
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        child[i].resize(k);
        for (int j = 0; j < k; ++j) cin >> child[i][j];
    }

    // BFS a gyökértől: a sorrendben minden szülő a gyermeke előtt áll.
    vector<int> order;
    order.reserve(n);
    order.push_back(1);
    for (size_t head = 0; head < order.size(); ++head) {
        int v = order[head];
        for (int c : child[v]) order.push_back(c);
    }

    // Részfa-méretek: a fordított sorrendben a gyerekek már ki vannak számolva.
    vector<long long> sz(n + 1, 1);
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int v = order[i];
        for (int c : child[v]) sz[v] += sz[c];
    }

    long long numerator = 1;
    for (int i = 1; i <= n; ++i) numerator = numerator * i % MOD;

    long long denominator = 1;
    for (int i = 1; i <= n; ++i) denominator = denominator * sz[i] % MOD;

    long long answer = numerator * power(denominator, MOD - 2) % MOD;
    cout << answer << "\n";
    return 0;
}
