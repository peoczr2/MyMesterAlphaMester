/*
Megoldási ötlet:
Egy K hosszú ablak hibás, ha valamelyik prím két különböző elemben is megjelenik. Mivel K legfeljebb 1000, egy
ablak prímfaktor-állapotát viszonylag olcsón tudjuk karbantartani.

Az egész sorozaton egy mozgó ablakot használunk: az aktuális ablak prímfaktor-számlálóit és a duplikált prímek számát
tartjuk nyilván. Egy pontbeli frissítés csak legfeljebb K ablakot érint, ezeket egy lokális újrasöpréssel számoljuk
újra, így az egész feladat kezelhető marad.
*/
/*
Hint 1: || Egy ablak akkor hibás, ha valamelyik prím előfordulása legalább 2. ||
Hint 2: || Az update csak azokat az ablakokat érinti, amelyek tartalmazzák az adott pozíciót. ||
Hint 3: || Kicsi K miatt ezeket az ablakokat külön újraszámolhatod egy lokális mozgó ablakkal. ||
*/

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

static const int MAXV = 100000;
static vector<vector<int>> factors;

static void buildFactors() {
    if (!factors.empty()) return;
    vector<int> spf(MAXV + 1);
    for (int i = 2; i <= MAXV; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            if (1LL * i * i <= MAXV) {
                for (int j = i * i; j <= MAXV; j += i) if (!spf[j]) spf[j] = i;
            }
        }
    }
    factors.assign(MAXV + 1, {});
    for (int x = 2; x <= MAXV; ++x) {
        int y = x;
        while (y > 1) {
            int p = spf[y];
            factors[x].push_back(p);
            while (y % p == 0) y /= p;
        }
    }
}

static void addValue(int value, unordered_map<int, int>& cnt, int& duplicated) {
    for (int p : factors[value]) {
        int& c = cnt[p];
        if (c == 1) ++duplicated;
        ++c;
    }
}

static void removeValue(int value, unordered_map<int, int>& cnt, int& duplicated) {
    for (int p : factors[value]) {
        int& c = cnt[p];
        if (c == 2) --duplicated;
        --c;
        if (c == 0) cnt.erase(p);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    buildFactors();

    int T;
    cin >> T;
    while (T--) {
        int n, k, m;
        cin >> n >> k >> m;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        vector<pair<int, int>> updates(m);
        for (int i = 0; i < m; ++i) cin >> updates[i].first >> updates[i].second;

        int windowCount = n - k + 1;
        vector<char> bad(windowCount + 1, 0);
        int badTotal = 0;

        unordered_map<int, int> cnt;
        cnt.reserve(4096);
        int duplicated = 0;
        for (int i = 1; i <= k; ++i) addValue(a[i], cnt, duplicated);
        bad[1] = duplicated > 0;
        badTotal += bad[1];
        for (int start = 2; start <= windowCount; ++start) {
            removeValue(a[start - 1], cnt, duplicated);
            addValue(a[start + k - 1], cnt, duplicated);
            bad[start] = duplicated > 0;
            badTotal += bad[start];
        }

        long long sum = 0;
        for (int i = 1; i <= n; ++i) sum += a[i];

        vector<int> outputs;
        outputs.reserve(m + 2);
        outputs.push_back(badTotal);

        for (auto [pos, value] : updates) {
            int oldValue = a[pos];
            if (oldValue != value) {
                sum += value - oldValue;
                a[pos] = value;
                int left = max(1, pos - k + 1);
                int right = min(pos, windowCount);
                if (left <= right) {
                    unordered_map<int, int> localCnt;
                    localCnt.reserve(4096);
                    int localDup = 0;
                    for (int i = left; i < left + k; ++i) addValue(a[i], localCnt, localDup);
                    for (int start = left; start <= right; ++start) {
                        char newBad = localDup > 0;
                        badTotal += static_cast<int>(newBad) - static_cast<int>(bad[start]);
                        bad[start] = newBad;
                        if (start < right) {
                            removeValue(a[start], localCnt, localDup);
                            addValue(a[start + k], localCnt, localDup);
                        }
                    }
                }
            }
            outputs.push_back(badTotal);
        }

        outputs.push_back(static_cast<int>(sum));
        for (int i = 0; i < static_cast<int>(outputs.size()); ++i) {
            if (i) cout << ' ';
            cout << outputs[i];
        }
        cout << '\n';
    }
    return 0;
}
