/*
Megoldás lényege:
Az eseményeket határidő szerint haladva dolgozzuk fel, és közben követjük a kiválasztott események összidejét. Ha egy új esemény hozzávételével az összidő túllépi az aktuális határidőt, a kiválasztott események közül a leghosszabbat (max-kupac) elhagyjuk. Így a megmaradt halmaz a lehető legtöbb eseményt tartalmazza úgy, hogy mindegyik a határidejére befejeződhessen (Moore–Hodgson-elv). A kiválasztott eseményeket határidő szerint egymás után, az 1. naptól kezdve ütemezzük, így minden esemény a határidejére vagy korábban ér véget. Az időigény O(M log M), ahol M az események száma.
*/
/*
Hint 1: || Az összidő-prefixeket határidő szerinti rendezés után érdemes követni, így a feltétel minden lépésben egyszerűen ellenőrizhető. ||
Hint 2: || Ha túllépnénk a határidőt, a leghosszabb esemény kidobása a legtöbb szabad időt adja, és csak egyetlen eseményt veszítünk. ||
Hint 3: || A megtartott halmazt határidő szerinti sorrendben egymás mögé ütemezve, az 1. naptól kezdve, minden esemény érvényes kezdőnapot kap. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Event {
    int v, h, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<Event> ev(M);
    for (int i = 0; i < M; ++i) {
        cin >> ev[i].v >> ev[i].h;
        ev[i].id = i + 1;
    }

    sort(ev.begin(), ev.end(), [](const Event& a, const Event& b) {
        if (a.h != b.h) return a.h < b.h;
        if (a.v != b.v) return a.v < b.v;
        return a.id < b.id;
    });

    long long total = 0;
    priority_queue<pair<int,int>> pq; // (v, id)
    vector<char> selected(M + 1, 0);

    for (const auto& e : ev) {
        pq.push({e.v, e.id});
        selected[e.id] = 1;
        total += e.v;
        if (total > e.h) {
            auto [dv, did] = pq.top();
            pq.pop();
            selected[did] = 0;
            total -= dv;
        }
    }

    vector<Event> keep;
    keep.reserve(pq.size());
    for (const auto& e : ev) {
        if (selected[e.id]) keep.push_back(e);
    }

    int day = 1;
    vector<pair<int,int>> ans;
    ans.reserve(keep.size());
    for (const auto& e : keep) {
        ans.push_back({e.id, day});
        day += e.v;
    }

    cout << ans.size() << '\n';
    for (auto [id, st] : ans) {
        cout << id << ' ' << st << '\n';
    }
    return 0;
}
