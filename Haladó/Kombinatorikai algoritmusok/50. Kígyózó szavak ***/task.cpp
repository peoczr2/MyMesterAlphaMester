/*
   Kígyózó szavak: a legfeljebb H hosszú, szomszédosan egymás melletti
   betűkből álló szavak közül a K-adikat kell megadni lexikografikus sorrendben.
   A sorrend a prefixfán végzett bejárásnak felel meg, ezért rangsorolással
   és unrankinggel megoldható.
*/
#include <bits/stdc++.h>
using namespace std;

static const long long LIM = 1000000001LL;

static bool allowed(int a, int b) {
    return abs(a - b) == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, Q;
    cin >> H >> Q;
    vector<long long> ask(Q);
    for (int i = 0; i < Q; ++i) cin >> ask[i];

    vector<vector<long long>> ways(H + 1, vector<long long>(26, 0));
    for (int c = 0; c < 26; ++c) ways[1][c] = 1;
    for (int len = 2; len <= H; ++len) {
        for (int c = 0; c < 26; ++c) {
            long long val = 1;
            if (c > 0) val += ways[len - 1][c - 1];
            if (c + 1 < 26) val += ways[len - 1][c + 1];
            ways[len][c] = min(LIM, val);
        }
    }

    auto unrank = [&](long long k) {
        string ans;
        int rem = H;
        int last = -1;
        while (true) {
            if (!ans.empty()) {
                if (k == 1) return ans;
                --k;
            }
            bool chosen = false;
            for (int c = 0; c < 26; ++c) {
                if (last != -1 && !allowed(last, c)) continue;
                long long cnt = ways[rem][c];
                if (k > cnt) {
                    k -= cnt;
                    continue;
                }
                ans.push_back(char('a' + c));
                last = c;
                --rem;
                chosen = true;
                break;
            }
            if (!chosen) return ans;
        }
    };

    for (long long k : ask) {
        cout << unrank(k) << '\n';
    }
    return 0;
}