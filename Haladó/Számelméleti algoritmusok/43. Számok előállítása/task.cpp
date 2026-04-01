/*
 * Kétcoin-szemiksoport feladat több lekérdezésre. A legkisebb coin alapján
 * residue-graph Dijkstra-val előállítjuk a minimális reprezentálható értékeket.
 
Hint 1: || A sok összeg helyett nézd a maradékosztályokat a legkisebb érme szerint: ugyanaz a maradékosztály mindig `+minCoin` lépésekkel folytatható. ||
Hint 2: || Dijkstra-val megkaphatod minden maradékosztály legkisebb előállítható értékét, onnan minden `Bi`-hez csak fel kell kerekíteni a megfelelő osztályban. ||
Hint 3: || A végső válasz egy rögzített maradékosztályból induló aritmetikai sorozat legkisebb eleme lesz, ami még legalább `Bi`. ||
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
    while (q--) {
        long long b;
        cin >> b;
        long long t = (b + g - 1) / g;
        long long best = (1LL<<62);
        for (int r = 0; r < m; ++r) {
            long long d = dist[r];
            if (d >= t) best = min(best, d);
            else best = min(best, d + ((t - d + m - 1) / m) * m);
        }
        cout << best * g << '\n';
    }
    return 0;
}
