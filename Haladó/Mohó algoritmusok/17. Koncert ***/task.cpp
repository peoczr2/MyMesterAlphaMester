/*
Megoldás lényege:
Az igényeket a jobb végpontjuk (B) szerint növekvő sorrendben dolgozzuk fel, és mindegyiknek a még szabad, A-nál nem kisebb legkisebb sorszámú helyet adjuk, ha az nem nagyobb B-nél. A szabad helyeket egy DSU „következő szabad hely” struktúra tartja nyilván: find(x) az x-től kezdve legkisebb szabad sorszámot adja, foglaláskor pedig x a következő helyre mutat. Ez a mohó választás optimális, mert a legkisebb szabad hely elfoglalása a későbbi, nagyobb jobb végpontú igényeknek is a legtöbb lehetőséget hagyja. A kiosztás egy megfelelő jegykiosztás, így bármelyik helyes kimenet elfogadható. Az időigény O(N log N + M log M), a DSU út-tömörítése miatt.
*/
/*
Hint 1: || Ha egy igénynek szűk a jobb határa, azt később nehezebb lesz kielégíteni, ezért érdemes korábban kezelni. ||
Hint 2: || Egy igényhez a legkisebb megfelelő helyet kiosztani jó mohó döntés: több nagyobb hely marad másoknak. ||
Hint 3: || DSU-ban parent[x] lehet a következő még szabad index, foglaláskor union(x, x+1). ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Req {
    int a, b, id;
};

struct DSU {
    vector<int> p;
    explicit DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n + 2);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    void occupy(int x) { p[find(x)] = find(x + 1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;
    vector<Req> req(N);
    for (int i = 0; i < N; ++i) {
        cin >> req[i].a >> req[i].b;
        req[i].id = i + 1;
    }

    sort(req.begin(), req.end(), [](const Req& x, const Req& y) {
        if (x.b != y.b) return x.b < y.b;
        return x.a < y.a;
    });

    DSU dsu(M + 1);
    vector<pair<int,int>> ans;
    ans.reserve(min(M, N));

    for (const auto& r : req) {
        int seat = dsu.find(r.a);
        if (seat <= r.b && seat <= M) {
            ans.push_back({r.id, seat});
            dsu.occupy(seat);
        }
    }

    cout << ans.size() << '\n';
    for (auto [id, seat] : ans) cout << id << ' ' << seat << '\n';
    return 0;
}
