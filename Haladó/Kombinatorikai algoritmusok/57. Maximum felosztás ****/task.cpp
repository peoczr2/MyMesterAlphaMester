/*
   Maximum felosztás: az A tömböt M darab nemüres, egymást követő részre kell
   bontani úgy, hogy az i-edik rész maximuma pontosan B[i] legyen. A kulcs:
   egy adott rész utolsó B[i]-előfordulását választjuk, majd range-add / prefix
   DP-vel számoljuk a lehetséges végpontokat.
*/
#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> A(N + 1), B(M + 1);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= M; ++i) cin >> B[i];

    unordered_map<int, vector<int>> positions;
    positions.reserve(N * 2);
    for (int i = 1; i <= N; ++i) positions[A[i]].push_back(i);

    vector<pair<int,int>> sortedA;
    sortedA.reserve(N);
    for (int i = 1; i <= N; ++i) sortedA.push_back({A[i], i});
    sort(sortedA.begin(), sortedA.end(), greater<pair<int,int>>());

    vector<pair<int,int>> parts;
    parts.reserve(M);
    for (int i = 1; i <= M; ++i) parts.push_back({B[i], i});
    sort(parts.begin(), parts.end(), greater<pair<int,int>>());

    struct OccInfo {
        int p;
        int l;
        int u;
    };

    vector<vector<OccInfo>> info(M + 1);
    set<int> active;
    int ptr = 0;

    for (int idx = 0; idx < M; ++idx) {
        int value = parts[idx].first;
        int partIndex = parts[idx].second;

        while (ptr < N && sortedA[ptr].first > value) {
            active.insert(sortedA[ptr].second);
            ++ptr;
        }

        const vector<int>& occ = positions[value];
        if (occ.empty()) {
            cout << 0 << '\n';
            return 0;
        }

        for (int j = 0; j < (int)occ.size(); ++j) {
            int p = occ[j];
            int nextOcc = (j + 1 < (int)occ.size() ? occ[j + 1] : N + 1);

            auto it = active.lower_bound(p);
            int R = (it == active.end() ? N + 1 : *it);
            int L = 0;
            if (it != active.begin()) L = *prev(it);

            int U = min(R - 1, nextOcc - 1);
            if (U < p) continue;
            info[partIndex].push_back({p, L, U});
        }
    }

    vector<long long> dpPrev(N + 1, 0), dpCur(N + 1, 0);
    dpPrev[0] = 1;

    for (int partIndex = 1; partIndex <= M; ++partIndex) {
        fill(dpCur.begin(), dpCur.end(), 0);
        vector<int> diff(N + 2, 0);

        vector<int> pref(N + 1, 0);
        pref[0] = (int)dpPrev[0];
        for (int i = 1; i <= N; ++i) {
            pref[i] = pref[i - 1] + (int)dpPrev[i];
            if (pref[i] >= MOD) pref[i] -= MOD;
        }

        for (const auto& occ : info[partIndex]) {
            int p = occ.p;
            int L = occ.l;
            int U = occ.u;

            int waysStart = pref[p - 1] - (L > 0 ? pref[L - 1] : 0);
            if (waysStart < 0) waysStart += MOD;
            if (waysStart == 0) continue;

            diff[p] += waysStart;
            if (diff[p] >= MOD) diff[p] -= MOD;
            if (U + 1 <= N) {
                diff[U + 1] -= waysStart;
                if (diff[U + 1] < 0) diff[U + 1] += MOD;
            }
        }

        long long cur = 0;
        for (int i = 1; i <= N; ++i) {
            cur += diff[i];
            if (cur >= MOD) cur -= MOD;
            dpCur[i] = cur;
        }
        dpPrev.swap(dpCur);
    }

    cout << dpPrev[N] % MOD << '\n';
    return 0;
}