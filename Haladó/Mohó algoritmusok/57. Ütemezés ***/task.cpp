/*
Feladat: Események közül (időtartam, határidő) minél többet kell megtartani úgy, hogy egy esemény folyamatos napblokkon fusson, és befejezése ne lépje túl a saját határidőt.
Ötlet: Moore–Hodgson típusú mohó. Határidő szerint haladva berakjuk az eseményt, és ha az összidő túllépi az aktuális határidőt, eldobjuk a leghosszabb időtartamút (max-kupac). Így marad meg a maximális darabszám. A kiválasztott eseményeket végül határidő szerint egymás után ütemezzük 1. naptól indulva.
Hint 1: || A kritikus erőforrás a felhasznált össznapok száma a határidős prefixekben. ||
Hint 2: || Túlcsorduláskor a leghosszabb esemény kidobása veszít a legkevesebb darabszámot időegységenként. ||
Hint 3: || A végső kiválasztott halmazt határidő szerinti sorrendben egymás mögé rakva érvényes kezdőnapokat kapsz. ||
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
