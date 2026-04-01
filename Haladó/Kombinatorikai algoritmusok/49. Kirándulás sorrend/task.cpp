/*
   Kirándulás sorrend: először legrövidebb utakat számolunk a városok között,
   majd bitmaskos TSP-dinamikával megkeressük a legolcsóbb körutat, amely a
   lakóhelyről indul, minden más várost pontosan egyszer érint, és visszatér.
*/
#include <bits/stdc++.h>
using namespace std;

static const long long INF = (1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, L;
    cin >> N >> M >> L;
    --L;
    vector<vector<long long>> dist(N, vector<long long>(N, INF));
    for (int i = 0; i < N; ++i) dist[i][i] = 0;
    for (int i = 0; i < M; ++i) {
        int a, b;
        long long t;
        cin >> a >> b >> t;
        --a; --b;
        dist[a][b] = min(dist[a][b], t);
        dist[b][a] = min(dist[b][a], t);
    }

    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    vector<int> cities;
    for (int i = 0; i < N; ++i) if (i != L) cities.push_back(i);
    int K = (int)cities.size();
    int FULL = 1 << K;
    vector<vector<long long>> dp(FULL, vector<long long>(K, INF));
    vector<vector<int>> parent(FULL, vector<int>(K, -1));

    for (int i = 0; i < K; ++i) dp[1 << i][i] = dist[L][cities[i]];

    for (int mask = 1; mask < FULL; ++mask) {
        for (int last = 0; last < K; ++last) if (mask & (1 << last)) {
            long long cur = dp[mask][last];
            if (cur >= INF) continue;
            for (int nxt = 0; nxt < K; ++nxt) if (!(mask & (1 << nxt))) {
                int nmask = mask | (1 << nxt);
                long long cand = cur + dist[cities[last]][cities[nxt]];
                if (cand < dp[nmask][nxt]) {
                    dp[nmask][nxt] = cand;
                    parent[nmask][nxt] = last;
                }
            }
        }
    }

    long long best = INF;
    int bestLast = -1;
    int all = FULL - 1;
    for (int last = 0; last < K; ++last) {
        long long cand = dp[all][last] + dist[cities[last]][L];
        if (cand < best) {
            best = cand;
            bestLast = last;
        }
    }

    cout << best << '\n';
    vector<int> order;
    int mask = all, last = bestLast;
    while (last != -1) {
        order.push_back(cities[last]);
        int pl = parent[mask][last];
        mask ^= 1 << last;
        last = pl;
    }
    reverse(order.begin(), order.end());
    for (int i = 0; i < (int)order.size(); ++i) {
        if (i) cout << ' ';
        cout << order[i] + 1;
    }
    cout << '\n';
    return 0;
}