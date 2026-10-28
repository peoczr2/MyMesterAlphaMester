/*
Beruházás alvállalkozókkal

Feladat: N egynapos munkát kell elvégezni, mindegyiknek van határideje (H_i). Egy alvállalkozó naponta
legfeljebb egy munkát végez. Legalább hány alvállalkozó kell, hogy minden munka határidőre elkészüljön?
Meg kell adni egy beosztást is: minden munkához a vállalkozó és a nap sorszámát.

Megoldás: Az első d napban K vállalkozó legfeljebb K*d munkát végezhet el, és ezalatt az összes d-nél
nem későbbi határidejű munkának el kell készülnie. Ezért K >= ceil(db(H <= d) / d) minden d-re, vagyis
K legalább ezek maximuma. Ennyi elég is: a munkákat határidő szerint rendezve sorban kiosztjuk a
helyeket napról napra (1. nap: 1..K. vállalkozó, 2. nap: 1..K. vállalkozó, ...). A rendezett sorban
s-edik (0-tól számozva) munka napja s/K + 1, és mivel a nála nem későbbi határidejűek száma legfeljebb
K*H, a napja nem lesz későbbi a határidejénél.

Időigény: O(N log N + maxH).
*/
/*
Hint 1: || Az első d napban K vállalkozó összesen legfeljebb K*d munkát tud elvégezni. ||
Hint 2: || A d-ig lejáró munkák számából kapsz egy alsó korlátot K-ra; vedd ezek maximumát minden d-re. ||
Hint 3: || A határidő szerint rendezett munkákat sorban oszd ki: napról napra, azon belül vállalkozónként. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // beolvasás
    int n;
    cin >> n;
    vector<int> H(n);
    int maxH = 0;
    for (int i = 0; i < n; i++) {
        cin >> H[i];
        maxH = max(maxH, H[i]);
    }

    // K = max ceil(db(H <= d) / d)
    vector<int> db(maxH + 1, 0);
    for (int i = 0; i < n; i++) db[H[i]]++;
    int K = 0, eddig = 0;
    for (int d = 1; d <= maxH; d++) {
        eddig += db[d];
        K = max(K, (eddig + d - 1) / d);
    }

    // munkák határidő szerint rendezve
    vector<int> sorrend(n);
    iota(sorrend.begin(), sorrend.end(), 0);
    stable_sort(sorrend.begin(), sorrend.end(), [&](int a, int b) { return H[a] < H[b]; });

    // kiosztás: az s-edik hely napja s/K+1, vállalkozója s%K+1
    vector<int> vallalkozo(n), nap(n);
    for (int s = 0; s < n; s++) {
        vallalkozo[sorrend[s]] = s % K + 1;
        nap[sorrend[s]] = s / K + 1;
    }

    // kiírás munkák sorrendjében: munka, vállalkozó, nap
    cout << K << '\n';
    for (int i = 0; i < n; i++) cout << i + 1 << ' ' << vallalkozo[i] << ' ' << nap[i] << '\n';
    return 0;
}
