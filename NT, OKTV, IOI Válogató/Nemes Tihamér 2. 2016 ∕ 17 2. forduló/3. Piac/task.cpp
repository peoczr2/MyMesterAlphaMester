#include <bits/stdc++.h>
using namespace std;

/*
    A bevételekhez összegezzük a mennyiség*ár értékeket. A K. legnagyobb össz-
    mennyiségű termékhez elég a termékenkénti összmennyiséget, a harmadik részben
    pedig termékenként megkeressük a maximális eladási árat és megszámoljuk,
    mely kereskedőnél van ilyen termék.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<long long> bev(n + 1, 0);
    vector<long long> osszMenny(m + 1, 0);
    vector<vector<pair<int, pair<int, int>>>> aruk(n + 1);

    for (int i = 1; i <= n; ++i) {
        int f;
        cin >> f;
        for (int j = 0; j < f; ++j) {
            int s, ar, menny;
            cin >> s >> ar >> menny;
            bev[i] += 1LL * ar * menny;
            osszMenny[s] += menny;
            aruk[i].push_back({s, {ar, menny}});
        }
    }

    double atlag = 0;
    for (int i = 1; i <= n; ++i) atlag += bev[i];
    atlag /= n;

    vector<int> jobb;
    for (int i = 1; i <= n; ++i) {
        if (bev[i] > atlag + 1e-12) jobb.push_back(i);
    }
    cout << jobb.size();
    for (int x : jobb) cout << ' ' << x;
    cout << '\n';

    vector<pair<long long, int>> rendezet(1);
    for (int s = 1; s <= m; ++s) rendezet.push_back({osszMenny[s], s});
    sort(rendezet.begin() + 1, rendezet.end(), [](auto& a, auto& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });
    cout << rendezet[k].second << '\n';

    vector<int> maxAr(m + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (auto [s, p] : aruk[i]) maxAr[s] = max(maxAr[s], p.first);
    }

    int bestId = 1, bestCnt = -1;
    for (int i = 1; i <= n; ++i) {
        int cnt = 0;
        for (auto [s, p] : aruk[i]) {
            if (p.first == maxAr[s]) ++cnt;
        }
        if (cnt > bestCnt) {
            bestCnt = cnt;
            bestId = i;
        }
    }
    cout << bestId << '\n';
    return 0;
}