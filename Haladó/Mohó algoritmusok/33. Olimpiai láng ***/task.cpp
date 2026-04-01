/*
Feladat: A lángot a célba a lehető legkevesebb futóval kell eljuttatni.
Ötlet: A pillanatnyi határig elérhető futók közül mindig a legtovább vivőt választjuk. Ez az intervallumfedés klasszikus mohója.
Hint 1: || Az aktuális kilométerig az összes olyan futó szóba jöhet, aki eddig elindulhat. ||
Hint 2: || Ezek közül a legtávolabbra nyúló futóval érdemes továbbmenni. ||
Hint 3: || Ha nem találsz új futót, akkor nincs megoldás. ||
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