/*
Megoldás lényege:
Minden pontra végigmegyünk az összes körön, és megnézzük, hogy a pont a kör belsejébe esik-e: a pont és a kör középpontja közötti távolság négyzete, vagyis (x - a)^2 + (y - b)^2, kisebb-e a sugár négyzeténél. Mivel a feltétel szigorú egyenlőtlenség, a körvonalon lévő pontok nem számítanak belülre. Minden számítás egész számokkal történik (long long-gal a biztonság kedvéért), így nincs lebegőpontos pontatlanság, és nem kell gyököt vonni. Az időigény O(N * K), ami legfeljebb 10 * 10^4 vizsgálatot jelent, a memóriaigény O(N).
*/
/*
Hint 1: || A kérdés minden pontra külön áll: számold meg, hány kör belsejébe esik. Ez két egymásba ágyazott ciklus: a külső a pontokon, a belső a köröknél fut. ||
Hint 2: || A (a, b) pont akkor van az (x, y, r) körön belül, ha (x - a) · (x - a) + (y - b) · (y - b) kisebb, mint r · r. Egész számokkal számolj, így nincs lebegőpontos hiba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<long long> x(n), y(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> r[i];
    }

    for (int j = 0; j < k; j++) {
        long long a, b;
        cin >> a >> b;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            long long dx = x[i] - a;
            long long dy = y[i] - b;
            if (dx * dx + dy * dy < r[i] * r[i]) cnt++;
        }
        cout << cnt << "\n";
    }

    return 0;
}
