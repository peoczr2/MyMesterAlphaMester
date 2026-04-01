/*
Feladat: A lángot a lehető legkevesebb futóval kell a célba juttatni.
Ötlet: Mindig az aktuálisan elérhető futók közül azt választjuk, aki a legtovább viszi a lángot. Ez ugyanaz a klasszikus intervallumfedési mohó stratégia.
Hint 1: || Az aktuális pontig minden olyan futó szóba jöhet, akinek a kezdete nem nagyobb ennél. ||
Hint 2: || Ezek közül mindig a legtovább érő intervallumot érdemes választani. ||
Hint 3: || Ha nem tudsz továbblépni, akkor nincs megoldás. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Runner { int s, e, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> k >> n;
    vector<Runner> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].s >> a[i].e;
        a[i].id = i + 1;
    }
    sort(a.begin(), a.end(), [](const Runner &x, const Runner &y) {
        if (x.s != y.s) return x.s < y.s;
        if (x.e != y.e) return x.e > y.e;
        return x.id < y.id;
    });

    priority_queue<pair<int, int>> pq;
    vector<int> chosen;
    int ptr = 0, cur = 0;
    while (cur < k) {
        while (ptr < n && a[ptr].s <= cur) {
            pq.push({a[ptr].e, a[ptr].id});
            ++ptr;
        }
        while (!pq.empty() && pq.top().first <= cur) pq.pop();
        if (pq.empty()) {
            cout << 0 << '\n';
            return 0;
        }
        auto [e, id] = pq.top();
        pq.pop();
        chosen.push_back(id);
        cur = e;
    }

    cout << chosen.size() << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}