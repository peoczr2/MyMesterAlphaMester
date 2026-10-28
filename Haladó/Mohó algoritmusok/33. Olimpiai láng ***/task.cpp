/*
Megoldás lényege:
A futókat a kezdő kilométerük szerint dolgozzuk fel, és az aktuális pontig elérhető futók közül mindig azt választjuk, aki a legtávolabbra (kezdet + H) viszi a lángot. Ez az intervallumlefedés klasszikus mohója: a legtávolabbi elérhető pont minden lépésben a lehető legtöbbet adja, ezért a futók száma minimális. Mivel minden futó pontosan H kilométert fut, a kiválasztott futók kezdőpontjai növekvők lesznek, és a lánc feltétele automatikusan teljesül. A rendezés miatt az időigény O(N log N). Ha egyik elérhető futó sem visz tovább az aktuális pontnál, a láng nem juttatható célba, és a válasz 0.
*/
/*
Hint 1: || Tekintsd az aktuális pontot haladó határnak: a futók közül csak azok jöhetnek szóba, akiknek a kezdőpontja nem nagyobb ennél. ||
Hint 2: || Ezek közül mindig a legtávolabbra érő futót (kezdőpont + H) válaszd, és a határt erre a távolságra toljuk. ||
Hint 3: || Rendezd a futókat kezdőpont szerint, és egy mutatóval haladj végig; ha nincs olyan futó, aki a határt tovább tolja, a válasz 0. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Runner { int x, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, N, H;
    cin >> K >> N >> H;
    vector<Runner> a(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i].x;
        a[i].id = i + 1;
    }
    sort(a.begin(), a.end(), [](const Runner &p, const Runner &q) {
        if (p.x != q.x) return p.x < q.x;
        return p.id < q.id;
    });

    vector<int> ans;
    int ptr = 0, cur = 0;
    while (cur < K) {
        int bestReach = cur, bestId = -1;
        while (ptr < N && a[ptr].x <= cur) {
            if (a[ptr].x + H > bestReach) {
                bestReach = a[ptr].x + H;
                bestId = a[ptr].id;
            }
            ++ptr;
        }
        if (bestId == -1) {
            cout << 0 << '\n';
            return 0;
        }
        ans.push_back(bestId);
        cur = bestReach;
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}