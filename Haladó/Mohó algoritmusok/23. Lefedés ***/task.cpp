/*
Feladat: N számot legfeljebb K darab zárt intervallummal kell lefedni minimális összhosszal, ahol minden intervallumra a<b.
Ötlet: Rendezett, duplikátummentes pontoknál 1 intervallum esetén [x1, xU+1] optimális (hossz: xU-x1+1). K intervallumhoz a K-1 legnagyobb rést „vágjuk ki” a pontok közül. A kivágás nyeresége gap-1, ahol gap = x[i+1]-x[i].
Hint 1: || Először rendezd a számokat és távolítsd el a duplikátumokat. ||
Hint 2: || Ha két egymást követő pont között nagy rés van, ott érdemes elvágni a lefedést. ||
Hint 3: || Egy pontot tartalmazó blokk minimális intervalluma [x, x+1], mert a<b kötelező. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<int> v(N);
    for (int i = 0; i < N; ++i) cin >> v[i];

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int U = (int)v.size();

    if (U == 0) {
        cout << 0 << '\n';
        return 0;
    }

    vector<pair<int,int>> gaps; // (gap-1 benefit, split index i between i and i+1)
    gaps.reserve(max(0, U - 1));
    for (int i = 0; i + 1 < U; ++i) {
        int g = v[i + 1] - v[i];
        gaps.push_back({g - 1, i});
    }

    sort(gaps.begin(), gaps.end(), [](const auto& a, const auto& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });

    int cuts = min(K - 1, U - 1);
    vector<int> cutAfter;
    cutAfter.reserve(cuts);
    for (int i = 0; i < cuts; ++i) {
        if (gaps[i].first > 0) cutAfter.push_back(gaps[i].second);
    }
    sort(cutAfter.begin(), cutAfter.end());

    vector<pair<int,int>> intervals;
    int l = 0;
    for (int idx : cutAfter) {
        int r = idx;
        if (l == r) intervals.push_back({v[l], v[l] + 1});
        else intervals.push_back({v[l], v[r]});
        l = r + 1;
    }
    if (l == U - 1) intervals.push_back({v[l], v[l] + 1});
    else intervals.push_back({v[l], v[U - 1]});

    long long total = 0;
    for (auto [a, b] : intervals) total += (b - a);

    cout << total << '\n';
    for (auto [a, b] : intervals) cout << a << ' ' << b << '\n';
    return 0;
}
