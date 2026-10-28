/*
Megoldás lényege:
Az utak mindkét irányban használhatók, ezért a szomszédsági listákat szimmetrikusan vesszük. Időegységenként
haladunk szélességi bejárással: minden robot aktuális helyéről a még nem látogatott szomszédokba léphet, de csak
akkor, ha a célpont szomszédságában az előző időpontban más robot nem állt. Ha egy robotnak nincs szabályos lépése,
megáll, és a helye a továbbiakban is blokkolja a szomszédait. Pontonként nyilvántartjuk, mely robotok állnak
a szomszédságában, így a lépések ellenőrzése O(1) körüli költségű. Az első időpontban C-be érkező robot idejét
és kezdőpontját írjuk ki. Mivel minden pontot legfeljebb egyszer foglalunk el, az időigény O(N + M).
*/
/*
Hint 1: || Egy pont akkor foglalható egy időegységben, ha ott és a szomszédságában az előző időpontban nem állt másik robot; ezt minden időpontban külön ellenőrizd. ||
Hint 2: || Tartsd nyilván minden pontról, mely robotok állnak a szomszédságában, és a lépő robot saját helyét ebből a számlálásból hagyd ki. ||
Hint 3: || Minden időpontban előbb gyűjtsd össze az összes érvényes lépést az előző helyzet alapján, és csak utána frissítsd a robotok helyét és a nyilvántartást. ||
*/

#include <bits/stdc++.h>
using namespace std;

// own[q]: (robot, darab) párok: hány olyan robot-pozíció van q szomszédságában, és melyik robotról van szó
vector<vector<pair<int, int>>> own;

void addOwner(int q, int r) {
    for (auto &p : own[q]) {
        if (p.first == r) {
            ++p.second;
            return;
        }
    }
    own[q].push_back({r, 1});
}

void removeOwner(int q, int r) {
    auto &vec = own[q];
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i].first == r) {
            if (--vec[i].second == 0) {
                vec[i] = vec.back();
                vec.pop_back();
            }
            return;
        }
    }
}

// Igaz, ha q szomszédságában r-től különböző robot áll
bool blockedFor(int q, int r) {
    for (const auto &p : own[q]) {
        if (p.first != r) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, c;
    cin >> n >> k >> c;
    vector<int> start(k);
    for (auto &s : start) cin >> s;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; ++i) {
        int j;
        while (cin >> j && j != 0) {
            if (j == i) continue;
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }
    for (int v = 1; v <= n; ++v) {
        sort(adj[v].begin(), adj[v].end());
        adj[v].erase(unique(adj[v].begin(), adj[v].end()), adj[v].end());
    }

    own.assign(n + 1, {});
    vector<char> visited(n + 1, 0);
    vector<pair<int, int>> live;  // (pont, robot) párok: a még mozgó robotok aktuális helyei
    for (int r = 0; r < k; ++r) {
        if (start[r] == c) {
            cout << 0 << '\n' << start[r] << '\n';
            return 0;
        }
        visited[start[r]] = 1;
        live.push_back({start[r], r});
    }
    for (auto [v, r] : live) {
        for (int q : adj[v]) addOwner(q, r);
    }

    for (int t = 1; !live.empty(); ++t) {
        // 1. fázis: az összes érvényes lépés összegyűjtése az előző időpont helyzete alapján
        vector<vector<int>> children(live.size());
        for (size_t i = 0; i < live.size(); ++i) {
            int v = live[i].first, r = live[i].second;
            for (int q : adj[v]) {
                if (visited[q] || blockedFor(q, r)) continue;
                if (q == c) {
                    cout << t << '\n' << start[r] << '\n';
                    return 0;
                }
                visited[q] = 1;
                children[i].push_back(q);
            }
        }

        // 2. fázis: a lépő robotok régi helyeinek törlése a nyilvántartásból (a holtpontok helye marad)
        for (size_t i = 0; i < live.size(); ++i) {
            if (children[i].empty()) continue;
            int v = live[i].first, r = live[i].second;
            for (int q : adj[v]) removeOwner(q, r);
        }

        // 3. fázis: az új helyek felvétele
        vector<pair<int, int>> next;
        for (size_t i = 0; i < live.size(); ++i) {
            int r = live[i].second;
            for (int q : children[i]) {
                next.push_back({q, r});
                for (int w : adj[q]) addOwner(w, r);
            }
        }
        live.swap(next);
    }

    cout << -1 << '\n' << -1 << '\n';
    return 0;
}
