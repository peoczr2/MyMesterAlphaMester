/*
 * Ugyanaz a feladat, mint a 43-as: több lekérdezésre a legkisebb reprezentálható
 * számot adjuk meg, amely legalább Bi.
 
Hint 1: || Ez ugyanaz az ötlet, mint a 43-as feladatban: maradékosztályonként kell a legkisebb előállítható értéket megtalálni. ||
Hint 2: || Ha már ismert minden maradékhoz a minimum, akkor egy kérdésre a megfelelő osztályban a legkisebb `>= Bi` számot kell kiválasztani. ||
Hint 3: || Az előállíthatóság itt is monoton a maradékban, ezért a minimális értékeket elég egyszer kiszámolni, utána már csak keresni kell közöttük. ||
*/

#include "../common.hpp"

struct Node { long long dist; int r; bool operator>(const Node& o) const { return dist > o.dist; } };

static vector<long long> compute_dist(vector<int> coins) {
    int m = coins.front();
    vector<long long> dist(m, (1LL<<62));
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, r] = pq.top(); pq.pop();
        if (d != dist[r]) continue;
        for (int c : coins) {
            int nr = (r + c) % m;
            long long nd = d + c;
            if (nd < dist[nr]) {
                dist[nr] = nd;
                pq.push({nd, nr});
            }
        }
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    int g = a[0];
    for (int x : a) g = gcdll(g, x);
    for (int& x : a) x /= g;
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int m = a[0];
    vector<long long> dist = compute_dist(a);
    int q;
    cin >> q;
    vector<long long> out(q);
    for (int i = 0; i < q; ++i) {
        long long b;
        cin >> b;
        long long t = (b + g - 1) / g;
        long long best = (1LL<<62);
        for (int r = 0; r < m; ++r) {
            long long d = dist[r];
            if (d >= t) best = min(best, d);
            else best = min(best, d + ((t - d + m - 1) / m) * m);
        }
        out[i] = best * g;
    }
    for (int i = 0; i < q; ++i) {
        if (i) cout << ' ';
        cout << out[i];
    }
    cout << '\n';
    return 0;
}
