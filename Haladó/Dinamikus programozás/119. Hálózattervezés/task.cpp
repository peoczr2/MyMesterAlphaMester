/*
Magyar megoldás:
Egy bináris keresőfa teljes költsége felírható az élek szerint: minden kommunikáló csomópár annyit fizet,
ahány él választja el a két végpontját. Ezért egy él költsége pontosan annak a súlya, hogy az él két oldalán
lévő két rész között összesen mennyi csomag megy át.

Ha egy részfában az intervallum [l, r] csúcsai vannak, és a gyökér k, akkor a bal gyerek részfája [l, k-1],
a jobb gyereké [k+1, r]. Az ezekhez vezető két él költsége rendre a teljes gráfban vett
cut([l, k-1]) és cut([k+1, r]), vagyis az adott intervallum és a komplementere közti kommunikáció súlya.
Ezért egy klasszikus intervallum-DP adódik:

best[l][r] = min_k (best[l][k-1] + best[k+1][r] + cut(l, k-1) + cut(k+1, r)).

Itt best[l][r] az [l, r] kulcsokból építhető optimális BST belső élköltsége. A teljes fa gyökere rögzítve R,
ezért a válasz a bal és jobb részfa optimális költségének, illetve a gyökér két kimenő élének összege.
Mivel N <= 500, az O(N^3) intervallum-DP belefér.
*/
/*
Hint 1: || Ne csomópáronként számolj távolságot, hanem élenként: egy él annyiszor számít bele, ahány kommunikáció áthalad rajta. ||
Hint 2: || Egy BST-ben minden részfa egy összefüggő intervallum az inorder sorrendben, ezért intervallum-DP természetes. ||
Hint 3: || A `cut(l, r)` érték az [l, r] intervallum és a többi csúcs közötti összsúly; ezt előre ki lehet számolni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, root;
    if (!(cin >> n >> m >> root)) return 0;

    vector<vector<long long>> w(n + 1, vector<long long>(n + 1, 0));
    vector<long long> deg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int s, d;
        long long weight;
        cin >> s >> d >> weight;
        w[s][d] = weight;
        w[d][s] = weight;
        deg[s] += weight;
        deg[d] += weight;
    }

    vector<long long> prefDeg(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prefDeg[i] = prefDeg[i - 1] + deg[i];
    }

    vector<vector<long long>> pref(n + 1, vector<long long>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        long long row = 0;
        for (int j = 1; j <= n; ++j) {
            row += w[i][j];
            pref[i][j] = pref[i - 1][j] + row;
        }
    }

    auto rectSum = [&](int x1, int y1, int x2, int y2) {
        if (x1 > x2 || y1 > y2) return 0LL;
        return pref[x2][y2] - pref[x1 - 1][y2] - pref[x2][y1 - 1] + pref[x1 - 1][y1 - 1];
    };

    vector<vector<long long>> cut(n + 2, vector<long long>(n + 2, 0));
    for (int l = 1; l <= n; ++l) {
        for (int r = l; r <= n; ++r) {
            long long incident = prefDeg[r] - prefDeg[l - 1];
            long long inside = rectSum(l, l, r, r) / 2;
            cut[l][r] = incident - 2LL * inside;
        }
    }

    const long long INF = (1LL << 62);
    vector<vector<long long>> best(n + 2, vector<long long>(n + 2, 0));
    for (int len = 1; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            long long ans = INF;
            for (int k = l; k <= r; ++k) {
                long long cur = 0;
                if (k > l) {
                    cur += best[l][k - 1] + cut[l][k - 1];
                }
                if (k < r) {
                    cur += best[k + 1][r] + cut[k + 1][r];
                }
                ans = min(ans, cur);
            }
            best[l][r] = ans;
        }
    }

    long long answer = 0;
    if (root > 1) {
        answer += best[1][root - 1] + cut[1][root - 1];
    }
    if (root < n) {
        answer += best[root + 1][n] + cut[root + 1][n];
    }

    cout << answer << '\n';
    return 0;
}