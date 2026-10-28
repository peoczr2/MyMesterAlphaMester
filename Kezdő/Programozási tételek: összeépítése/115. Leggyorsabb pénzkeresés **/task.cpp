/*
Megoldás lényege:
Mivel minden fizetés pozitív, egy szakasz összege bővítéskor nő, szűkítéskor csökken.
Kétmutatós módszerrel haladunk: a jobb végpontot egyesével léptetjük, és az összeghez hozzáadjuk az adott nap fizetését.
Amíg a bal végpont eldobása után az összeg még legalább P, a bal végpontot jobbra toljuk, így a két mutató közötti szakasz az adott jobb végponthoz tartozó legrövidebb érvényes szakasz lesz.
Ha ez a szakasz legalább P összegű, a hosszát vesszük a minimumba.
Mindkét mutató csak előre mozog, így az időigény O(N).
*/
/*
Hint 1: || Mivel minden fizetés pozitív, egy adott jobb végponthoz tartozó szakasz összege a bal végpont jobbra lépésével csökken. Keress minden jobb végponthoz a lehető legrövidebb, még elég nagy összegű szakaszt. ||
Hint 2: || Amikor az összeg már legalább P, a bal végpontot addig léptesd jobbra, amíg a következő elhagyás után az összeg még mindig legalább P; közben a talált hosszak minimumát tartsd nyilván. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long p;
    cin >> n >> p;
    vector<long long> f(n);
    for (auto &x : f) cin >> x;

    int best = INT_MAX;
    long long sum = 0;
    int l = 0;
    for (int r = 0; r < n; ++r) {
        sum += f[r];
        while (l <= r && sum - f[l] >= p) {
            sum -= f[l];
            ++l;
        }
        if (sum >= p) best = min(best, r - l + 1);
    }
    cout << best << '\n';
    return 0;
}
