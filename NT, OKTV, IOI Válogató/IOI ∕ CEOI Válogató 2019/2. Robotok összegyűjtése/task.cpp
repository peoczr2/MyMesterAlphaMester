/*
Megoldás lényege:
A városokat állapotoknak, a két jelzőtáblát két függvénynek (z és p) tekintjük: a kérdés az, van-e olyan betűsorozat, amely minden állapotot ugyanarra az állapotra visz. Ez pontosan akkor teljesül, ha bármely két városhoz van olyan gombnyomás-sorozat, amely a kettőt egy helyre viszi: ilyenkor a jelenlegi képhalmazból mindig tudunk két elemet egyesíteni, így a halmaz lépésenként csökken, amíg egy elem nem marad. A páronkénti összevonhatóságot visszafelé BFS-sel számoljuk: egy (a,b) pár jó, ha z(a)=z(b) vagy p(a)=p(b), illetve ha (z(a),z(b)) vagy (p(a),p(b)) jó pár. Minden párt legfeljebb egyszer dolgozunk fel az előképek listáival, így az időigény tesztesetenként O(N^2), a memória O(N^2).
*/
/*
Hint 1: || Gondolj a városok párjaira: elég-e minden párról tudni, hogy egy gombnyomás-sorozattal egy helyre vihető-e? Ha minden pár összevonható, hogyan lehet ebből a teljes városhalmazt egy elemre szűkíteni? ||
Hint 2: || Egy (a,b) pár akkor összevonható, ha valamelyik gombbal azonos városba kerül, vagy a gombbal kapott új pár összevonható. Ez visszafelé járható be: a jó párokból kiindulva a gombok előképeit kell venned. ||
Hint 3: || Készíts n×n-es jelölőtáblát és sort: kezdetben jelöld meg a z- vagy p-szerint azonos képű párokat, majd BFS-ben minden megjelölt (x,y) párra vedd a z^{-1}(x) × z^{-1}(y) és a p^{-1}(x) × p^{-1}(y) párokat. A végén ellenőrizd, hogy minden pár meg van-e jelölve. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> z(n), p(n);
        for (int& x : z) {
            cin >> x;
            --x;
        }
        for (int& x : p) {
            cin >> x;
            --x;
        }

        // előképek: pz[x] = { i : z_i = x }, pp[x] = { i : p_i = x }
        vector<vector<int>> pz(n), pp(n);
        for (int i = 0; i < n; ++i) {
            pz[z[i]].push_back(i);
            pp[p[i]].push_back(i);
        }

        // Jó párok: bittömb (a<b, index a*n+b), és a BFS sora (fix méretű tömb, a végén a jó párok).
        // A párok száma legfeljebb n(n-1)/2, ezért a sor sosem fut túl.
        vector<uint64_t> bits((size_t)n * n / 64 + 1, 0);
        vector<pair<int, int>> q(n * (n - 1) / 2 + 1);
        size_t qs = 0;
        // a és b (a != b) jó párrá tétele; ha új, a sor végére kerül
        auto mark = [&](int a, int b) {
            int lo = min(a, b), hi = max(a, b);
            size_t idx = (size_t)lo * n + hi;
            uint64_t bit = 1ULL << (idx & 63);
            bool fresh = !(bits[idx >> 6] & bit);
            bits[idx >> 6] |= bit;
            q[qs] = {lo, hi};
            qs += fresh;
        };

        for (int a = 0; a < n; ++a)
            for (int b = a + 1; b < n; ++b)
                if (z[a] == z[b] || p[a] == p[b]) mark(a, b);

        // visszafelé: ha {x,y} jó, akkor jó minden {a,b}, amelyre {z(a),z(b)} = {x,y} vagy {p(a),p(b)} = {x,y}
        // (x != y, így a != b a szorzatokban is)
        for (size_t h = 0; h < qs; ++h) {
            auto [x, y] = q[h];
            for (int a : pz[x])
                for (int b : pz[y]) mark(a, b);
            for (int a : pp[x])
                for (int b : pp[y]) mark(a, b);
        }

        bool ok = qs == (size_t)n * (n - 1) / 2;
        cout << (ok ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}
