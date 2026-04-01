/*
   Kincselosztás: a csökkenően rendezett felosztások lexikografikus sorrendjét
   partiíciószámláló DP-vel kezeljük. Az I-edik felosztást unrankeléssel,
   az adott felosztás előzőjét és következőjét rang alapján állítjuk elő.
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

int N;
vector<vector<ull>> memo;
vector<vector<char>> vis;

ull countPart(int rem, int mx) {
    if (rem == 0) return 1;
    if (mx == 0 || rem < 0) return 0;
    if (vis[rem][mx]) return memo[rem][mx];
    vis[rem][mx] = 1;
    ull ans = countPart(rem, mx - 1);
    if (rem >= mx) ans += countPart(rem - mx, mx);
    return memo[rem][mx] = ans;
}

vector<int> unrankPart(int rem, int mx, ull rank) {
    if (rem == 0) return {};
    for (int first = min(rem, mx); first >= 1; --first) {
        ull cnt = countPart(rem - first, first);
        if (rank > cnt) rank -= cnt;
        else {
            vector<int> tail = unrankPart(rem - first, first, rank);
            tail.insert(tail.begin(), first);
            return tail;
        }
    }
    return {};
}

ull rankPart(const vector<int>& a) {
    ull rank = 1;
    int rem = N, mx = N;
    for (int x : a) {
        for (int first = min(rem, mx); first > x; --first) {
            rank += countPart(rem - first, first);
        }
        rem -= x;
        mx = x;
    }
    return rank;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int I;
    cin >> N >> I;
    vector<int> part;
    int m;
    cin >> m;
    part.resize(m);
    for (int i = 0; i < m; ++i) cin >> part[i];

    memo.assign(N + 1, vector<ull>(N + 1));
    vis.assign(N + 1, vector<char>(N + 1, 0));

    ull Ibig = I;
    vector<int> kth = unrankPart(N, N, Ibig);
    ull r = rankPart(part);
    vector<int> next = unrankPart(N, N, r + 1);
    vector<int> prev = unrankPart(N, N, r - 1);

    for (int i = 0; i < (int)kth.size(); ++i) {
        if (i) cout << ' ';
        cout << kth[i];
    }
    cout << '\n';
    for (int i = 0; i < (int)next.size(); ++i) {
        if (i) cout << ' ';
        cout << next[i];
    }
    cout << '\n';
    for (int i = 0; i < (int)prev.size(); ++i) {
        if (i) cout << ' ';
        cout << prev[i];
    }
    cout << '\n';
    return 0;
}