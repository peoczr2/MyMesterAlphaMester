/*
Megoldás lényege:
A kiválasztott oszlopok között a híd költsége egy lánc: ha az utolsó használt oszlop j volt,
akkor az i-edik oszlopba érve dp[i] = min_j (dp[j] + (h_i - h_j)^2 + w_{j+1} + ... + w_{i-1}).
A w-k prefixösszegeivel a j-től független és j-től függő részekre bontható, így a
dp[i] = h_i^2 + pre_i + min_j (b_j + m_j * h_i) alakot kapjuk, ahol m_j = -2h_j és
b_j = dp[j] - pre_{j+1} + h_j^2. Ez egy minimum-egyenes lekérdezés, amelyet Li Chao fával
oldunk meg, mert a magasságok nincsenek rendezve. A fa a magasságok tömörített értékeire épül,
így az összidő O(N log N).
*/
/*
Hint 1: || Vezess be dp-t: dp[i] legyen a legkisebb költség, amellyel az első oszlopból az i-edik oszlopig eljutó híd építhető, ha i kiválasztott, és a közte lévő nem választott oszlopok eltüntetésével együtt. ||
Hint 2: || A (h_i - h_j)^2 tag és a közbülső oszlopok w-összege egyaránt szétbontható j-től függő és i-től függő részre, ha a w-k prefixösszegeit használod. Így minden j egy egyenesnek felel meg, amelynek meredeksége -2h_j, és a kérdés minden i-re a legkisebb érték egy adott x = h_i helyen. ||
Hint 3: || Mivel a magasságok nincsenek rendezve, az egyeneseket Li Chao fában tárold, amelynek a vízszintes tengelye a magasságok rendezett, egyedi értékei. Az i-edik lépésben előbb lekérdezed a dp[i]-t, majd beszúrod a j = i egyenest. A válasz dp[N]. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Line {
    ll m, b;
    ll eval(ll x) const { return m * x + b; }
};

struct LiChao {
    vector<ll> xs;
    vector<Line> t;
    int K;
    void init(const vector<ll>& coords) {
        xs = coords;
        K = (int)xs.size();
        t.assign(4 * K + 4, Line{0, LLONG_MAX / 4});
    }
    void add(Line ln, int node, int l, int r) {
        int mid = (l + r) / 2;
        bool leftBetter = ln.eval(xs[l]) < t[node].eval(xs[l]);
        bool midBetter = ln.eval(xs[mid]) < t[node].eval(xs[mid]);
        if (midBetter) swap(t[node], ln);
        if (l == r) return;
        if (leftBetter != midBetter)
            add(ln, 2 * node, l, mid);
        else
            add(ln, 2 * node + 1, mid + 1, r);
    }
    void insert(Line ln) { add(ln, 1, 0, K - 1); }
    ll query(int pos) const {
        ll res = LLONG_MAX / 4;
        int node = 1, l = 0, r = K - 1;
        while (true) {
            res = min(res, t[node].eval(xs[pos]));
            if (l == r) break;
            int mid = (l + r) / 2;
            if (pos <= mid) {
                node = 2 * node;
                r = mid;
            } else {
                node = 2 * node + 1;
                l = mid + 1;
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> h(n), w(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    for (int i = 0; i < n; i++) cin >> w[i];

    // pre[k] = w_0 + ... + w_{k-1}
    vector<ll> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + w[i];

    vector<ll> coords(h.begin(), h.end());
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    auto pos = [&](ll x) {
        return (int)(lower_bound(coords.begin(), coords.end(), x) - coords.begin());
    };

    LiChao lc;
    lc.init(coords);
    vector<ll> dp(n, 0);
    // j = 0 line: slope -2h_0, intercept dp_0 - pre_1 + h_0^2
    lc.insert(Line{-2 * h[0], dp[0] - pre[1] + h[0] * h[0]});
    for (int i = 1; i < n; i++) {
        ll best = lc.query(pos(h[i]));
        dp[i] = h[i] * h[i] + pre[i] + best;
        lc.insert(Line{-2 * h[i], dp[i] - pre[i + 1] + h[i] * h[i]});
    }
    cout << dp[n - 1] << "\n";
    return 0;
}
