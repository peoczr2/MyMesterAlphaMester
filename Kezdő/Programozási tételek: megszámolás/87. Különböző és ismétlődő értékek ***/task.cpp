/*
Megoldás lényege:
Minden értékre megszámoljuk, hányszor sorsolták ki, és két prefixösszeg-tömböt építünk: az egyik 1-től x-ig a legalább egyszer kisorsolt
különböző értékek számát, a másik 1-től x-ig az összes húzás számát adja meg. Egy [A, B] kérdésre a különböző számok száma az első tömb
B-hez és A-1-hez tartozó értékének különbsége. Az ismétlődő húzások száma az összes húzás száma ugyanebben az intervallumban mínusz
a különbözők száma, mert egy érték első húzása új, a további húzások ismétlődések. Az időigény O(N + M + K), a memóriaigény O(M).
*/
/*
Hint 1: || Egy szám akkor "különböző" az intervallumban, ha legalább egyszer kisorsolták. Egy érték első húzása nem ismétlődés, a további húzások már azok. ||
Hint 2: || Kérdésenként ne menj végig a számokon: készíts prefixösszeg-tömböt az értékekre. Az egyikben az 1-től x-ig kisorsolt különböző számok, a másikban az 1-től x-ig történt húzások száma szerepeljen. ||
Hint 3: || Egy [A, B] kérdésre a két prefixösszeg különbsége adja a különböző számok számát az intervallumban. Az ismétlődő húzások száma az intervallumbeli összes húzás mínusz a különbözők száma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> p(n);
    for (int &x : p) cin >> x;

    int lim = max(m, 100000);
    vector<int> cnt(lim + 1, 0);
    for (int x : p) cnt[x]++;

    vector<int> prefDist(lim + 1, 0), prefAll(lim + 1, 0);
    for (int x = 1; x <= lim; x++) {
        prefDist[x] = prefDist[x - 1] + (cnt[x] > 0 ? 1 : 0);
        prefAll[x] = prefAll[x - 1] + cnt[x];
    }

    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        int kulonbozo = prefDist[b] - prefDist[a - 1];
        int osszes = prefAll[b] - prefAll[a - 1];
        cout << kulonbozo << " " << osszes - kulonbozo << "\n";
    }
    return 0;
}
