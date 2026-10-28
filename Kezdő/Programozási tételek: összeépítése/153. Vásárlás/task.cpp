/*
Megoldás lényege:
Mindkét testvér részvényértékei növekvő sorrendben vannak. Azt a párt keressük, amelyre az összeg legalább X, a különbség (összeg - X) pedig a lehető legkisebb. Minden első testvérbeli i részvényhez az a legkisebb j index a jó, amelyre A_i + B_j már legalább X, mert nagyobb j-nél csak nagyobb összeg adódna.
Ahogy i nő, ez a határ a második sorozatban csak lefelé mozdulhat, ezért egyetlen mutatóval, visszafelé haladva, egy menetben bejárhatjuk a második sorozatot. Az időigény O(N + M), a memóriaigény O(N + M).
*/
/*
Hint 1: || Rögzítsd az első testvér egy részvényét, és a második testvér sorozatában keresd meg azt a legkisebb értéket, amellyel az összeg már eléri X-et. A sorozatok rendezettek, ezt érdemes kihasználni. ||
Hint 2: || Ahogy az első testvér részvénye nő, a határ a második sorozatban csak lefelé mozdulhat, ezért a második mutatót egyszer végigvihetjük. Minden lépésnél számold ki az összeg és X különbségét, és tartsd nyilván a legkisebbet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long x;
    cin >> n >> m >> x;
    vector<long long> a(n), b(m);
    for (auto &v : a) cin >> v;
    for (auto &v : b) cin >> v;

    long long best = LLONG_MAX;
    int bestI = -1, bestJ = -1;
    int p = m - 1;  // a legnagyobb olyan j, amelyre a[i] + b[j] < x (vagy -1)
    for (int i = 0; i < n; i++) {
        while (p >= 0 && a[i] + b[p] >= x) p--;
        if (p + 1 < m && a[i] + b[p + 1] < best) {
            best = a[i] + b[p + 1];
            bestI = i;
            bestJ = p + 1;
        }
    }

    if (bestI < 0) {
        cout << -1 << "\n";
    } else {
        cout << best - x << "\n" << bestI + 1 << "\n" << bestJ + 1 << "\n";
    }
    return 0;
}
