/*
   Lassú permutáció: a szomszédos karakterek azonosak vagy az ábécében
   szomszédosak. Az előző és következő szó a prefixfán végzett rangsorolással
   és unrankinggel adható meg.
*/
#include <bits/stdc++.h>
using namespace std;

static const long long LIM = 1000000001LL;

static bool allowed(int a, int b) { return abs(a - b) <= 1; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    string s;
    cin >> K >> s;

    vector<vector<long long>> ways(K + 1, vector<long long>(26, 0));
    for (int c = 0; c < 26; ++c) ways[1][c] = 1;
    for (int len = 2; len <= K; ++len) {
        for (int c = 0; c < 26; ++c) {
            long long val = 1;
            if (c > 0) val += ways[len - 1][c - 1];
            val += ways[len - 1][c];
            if (c + 1 < 26) val += ways[len - 1][c + 1];
            ways[len][c] = min(LIM, val);
        }
    }

    auto totalWords = [&]() -> long long {
        long long sum = 0;
        for (int c = 0; c < 26; ++c) sum = min(LIM, sum + ways[K][c]);
        return sum;
    };

    auto rankOf = [&](const string& str) -> long long {
        long long rank = str.size();
        for (int i = 0; i < (int)str.size(); ++i) {
            int cur = str[i] - 'a';
            int prev = (i == 0 ? -1 : str[i - 1] - 'a');
            for (int c = 0; c < cur; ++c) {
                if (prev != -1 && !allowed(prev, c)) continue;
                rank = min(LIM, rank + ways[K - i][c]);
            }
        }
        return rank;
    };

    auto unrank = [&](long long k) {
        string ans;
        int rem = K;
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

    long long r = rankOf(s);
    cout << (r == 1 ? string("-") : unrank(r - 1)) << '\n';
    long long tot = totalWords();
    cout << (r == tot ? string("-") : unrank(r + 1)) << '\n';
    return 0;
}