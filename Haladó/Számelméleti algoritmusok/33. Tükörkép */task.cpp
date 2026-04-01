/*
 * A helyes karakterizáció: a számjegyek 0/1/2 lehetnek, az első és az utolsó
 * számjegy nem lehet 0, és a digitköltség (1 -> 1, 2 -> 4) legfeljebb 9.
 * A lexikografikusan legkisebb N-jegyű megoldásokat DP-s számlálással generáljuk.
 
Hint 1: || Először keresd meg, milyen számjegyek jelenhetnek meg egyáltalán olyan számban, amely szorzás után palindromot ad. ||
Hint 2: || Ha megvan a karakterizáció, már csak lexikografikusan kell generálni a jó N-jegyű számokat, és kiírni az első M darabot. ||
*/

#include "../common.hpp"

static int cost_of(int digit) {
    return digit == 0 ? 0 : (digit == 1 ? 1 : 4);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    if (n == 1) {
        for (int x = 1; x <= min(m, 3); ++x) cout << x << '\n';
        return 0;
    }

    vector<vector<unsigned long long>> ways(n + 1, vector<unsigned long long>(10, 0));
    for (int b = 0; b <= 9; ++b) ways[n][b] = 1;
    for (int pos = n - 1; pos >= 0; --pos) {
        for (int b = 0; b <= 9; ++b) {
            unsigned long long count = 0;
            int start = (pos == 0 ? 1 : 0);
            int finish = (pos == n - 1 ? 2 : 2);
            for (int d = start; d <= finish; ++d) {
                int c = cost_of(d);
                if (c <= b) count += ways[pos + 1][b - c];
            }
            ways[pos][b] = count;
        }
    }

    unsigned long long total = ways[0][9];
    if ((unsigned long long)m > total) m = (int)total;

    for (int rank = 0; rank < m; ++rank) {
        int budget = 9;
        string s;
        for (int pos = 0; pos < n; ++pos) {
            int start = (pos == 0 ? 1 : 0);
            int finish = (pos == n - 1 ? 2 : 2);
            for (int d = start; d <= finish; ++d) {
                int c = cost_of(d);
                if (c > budget) continue;
                unsigned long long cnt = ways[pos + 1][budget - c];
                if ((unsigned long long)rank >= cnt) {
                    rank -= (int)cnt;
                    continue;
                }
                s.push_back(char('0' + d));
                budget -= c;
                break;
            }
        }
        cout << s << '\n';
    }
    return 0;
}
