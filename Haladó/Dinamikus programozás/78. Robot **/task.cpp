/*
Megoldási ötlet:
A robot egy menetben legfeljebb három, egymás után érkezett tárgyat vihet el. Ha egy menetbe már kiválasztottuk az 1, 2 vagy 3 tárgyat,
akkor a leadási sorrend szabad, ezért a menet optimális költsége legfeljebb 3! permutáció kipróbálásával kiszámítható.

Ezután egy egyszerű sor-DP marad: dp[i] legyen az első i tárgy elszállításának minimális ideje. Az utolsó menet 1, 2 vagy 3 tárgyból
állhat, ezért ezek közül választjuk a legjobb folytatást, és a csoportméretet vissza is tároljuk.
*/
/*
Hint 1: || Egy menet költsége csak a benne levő legfeljebb három célponttól függ. ||
Hint 2: || Egy fix 2 vagy 3 elemű menetnél a leadási sorrendet nyersen is ki lehet próbálni, mert nagyon kevés eset van. ||
Hint 3: || A teljes feladat a sor elejéről felépíthető: az utolsó menet 1, 2 vagy 3 tárgyat visz. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x;
    int y;
};

static int dist(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

static int tripCost(const vector<Point>& batch) {
    vector<int> perm(batch.size());
    iota(perm.begin(), perm.end(), 0);
    Point origin{0, 0};
    int best = INT_MAX;
    do {
        int cur = dist(origin, batch[perm[0]]);
        for (int i = 1; i < (int)perm.size(); ++i) {
            cur += dist(batch[perm[i - 1]], batch[perm[i]]);
        }
        cur += dist(batch[perm.back()], origin);
        best = min(best, cur);
    } while (next_permutation(perm.begin(), perm.end()));
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> p(n + 1);
    for (int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;

    vector<array<int, 4>> cost(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int len = 1; len <= 3; ++len) {
            if (i + len - 1 > n) continue;
            vector<Point> batch;
            for (int j = i; j < i + len; ++j) batch.push_back(p[j]);
            cost[i][len] = tripCost(batch);
        }
    }

    const long long INF = (1LL << 60);
    vector<long long> dp(n + 1, INF);
    vector<int> prevIdx(n + 1, -1), batchSize(n + 1, 0);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int len = 1; len <= 3; ++len) {
            if (i - len < 0) continue;
            long long cand = dp[i - len] + cost[i - len + 1][len];
            if (cand < dp[i]) {
                dp[i] = cand;
                prevIdx[i] = i - len;
                batchSize[i] = len;
            }
        }
    }

    vector<int> groups;
    for (int cur = n; cur > 0; cur = prevIdx[cur]) groups.push_back(batchSize[cur]);
    reverse(groups.begin(), groups.end());

    cout << dp[n] << '\n';
    for (int i = 0; i < (int)groups.size(); ++i) {
        if (i) cout << ' ';
        cout << groups[i];
    }
    cout << '\n';
    return 0;
}