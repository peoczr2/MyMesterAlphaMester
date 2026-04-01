/*
Feladat: A vendégeket a lehető legkevesebb olyan asztalra kell osztani, ahol minden asztalon van közös jelenléti időpont.
Ötlet: A vendégeket érkezési idő szerint kezeljük. Minden asztalról csak az aktuális közös metszet jobb széle és a létszám számít. Mindig azt az asztalt érdemes használni, amelynek a jobb széle a legnagyobb, mert az marad a leginkább rugalmas.
Hint 1: || Ha egy asztalhoz hozzáadunk egy új vendéget, a közös metszet bal széle csak későbbre tolódhat, ezért elég a jobb szélt és a darabszámot nyomon követni. ||
Hint 2: || Az aktuális vendéget mindig a legnagyobb jobb szélső metszetű, még nem telt asztalhoz tedd, ha van ilyen. ||
Hint 3: || Ha nincs megfelelő asztal, akkor új asztalt kell nyitni. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Table {
    int rightBound;
    int size;
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> guests(n + 1);
    for (int i = 1; i <= n; ++i) cin >> guests[i].first >> guests[i].second;

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [&](int a, int b) {
        if (guests[a].first != guests[b].first) return guests[a].first < guests[b].first;
        if (guests[a].second != guests[b].second) return guests[a].second < guests[b].second;
        return a < b;
    });

    priority_queue<tuple<int, int, int>> pq;
    vector<vector<int>> tables;

    for (int idx : order) {
        int s = guests[idx].first;
        int e = guests[idx].second;

        while (!pq.empty()) {
            auto [r, sz, id] = pq.top();
            if (r < s || sz == k) {
                pq.pop();
            } else {
                break;
            }
        }

        if (pq.empty()) {
            int id = (int)tables.size();
            tables.push_back({idx});
            pq.push({e, 1, id});
        } else {
            auto [r, sz, id] = pq.top();
            pq.pop();
            tables[id].push_back(idx);
            ++sz;
            r = min(r, e);
            if (sz < k) pq.push({r, sz, id});
        }
    }

    cout << tables.size() << '\n';
    for (auto &table : tables) {
        for (int i = 0; i < (int)table.size(); ++i) {
            if (i) cout << ' ';
            cout << table[i];
        }
        cout << '\n';
    }
    return 0;
}