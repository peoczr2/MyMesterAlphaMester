/*
Megoldás lényege:
Az intervallumok által lefedett pozíciók összefüggő komponensekre bontják az 1..N tartományt.
A részrendezések addig ismétlődnek, amíg minden komponensen belül a sorozat növekvő nem lesz,
tehát minden komponensen elég egyszer rendezni a benne álló elemeket.

Ezután minden komponensben megszámoljuk, hány pozíció marad a helyén.
*/
// Hint 1: || Az átfedő vagy egymást érintő intervallumok egy komponensbe olvadnak. ||
// Hint 2: || A fixpontokat komponensenként úgy kapjuk meg, hogy a komponens elemeit rendezve összehasonlítjuk az indexekkel. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> S(N + 1);
    for (int i = 1; i <= N; ++i) cin >> S[i];

    vector<pair<int,int>> segs(M);
    for (int i = 0; i < M; ++i) cin >> segs[i].first >> segs[i].second;
    sort(segs.begin(), segs.end());

    vector<pair<int,int>> merged;
    for (auto [l, r] : segs) {
        if (merged.empty() || l > merged.back().second) {
            merged.push_back({l, r});
        } else {
            merged.back().second = max(merged.back().second, r);
        }
    }

    int ans = 0;
    int coveredUntil = 0;
    vector<int> part;
    for (auto [l, r] : merged) {
        for (int i = coveredUntil + 1; i < l; ++i) {
            if (S[i] == i) ++ans;
        }
        part.clear();
        for (int i = l; i <= r; ++i) part.push_back(S[i]);
        sort(part.begin(), part.end());
        for (int i = l; i <= r; ++i) {
            if (part[i - l] == i) ++ans;
        }
        coveredUntil = r;
    }

    for (int i = coveredUntil + 1; i <= N; ++i) {
        if (S[i] == i) ++ans;
    }

    cout << ans << '\n';
    return 0;
}
