/*
Megoldas lenyege:
Minden szomszédos állomáspárhoz megvizsgáljuk, hogy a balról induló és a jobbról
induló vonatok közül van-e olyan pár, amely az adott szakaszon egyszerre tartózkodik.
Az egyes vonatok szakaszonként egy-egy intervallumot adnak, és mivel kevés induló
van, minden szakaszon elég a két rendezett intervallumlista kétmutatós metszetvizsgálata.
*/
/*
Hint 1: || Egy szakaszon minden vonat egy időintervallumot fed le. ||
Hint 2: || A balról és jobbról induló vonatok intervallumait külön rendezett listaként lehet kezelni. ||
Hint 3: || Ha a két intervallumhalmaznak nincs közös pontja, akkor az a szakasz egyvágányos lehet. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Interval {
    int l, r;
};

static bool overlapExists(const vector<Interval>& a, const vector<Interval>& b) {
    int i = 0, j = 0;
    while (i < (int)a.size() && j < (int)b.size()) {
        if (max(a[i].l, b[j].l) < min(a[i].r, b[j].r)) return true;
        if (a[i].r <= b[j].l) ++i;
        else if (b[j].r <= a[i].l) ++j;
        else if (a[i].r < b[j].r) ++i;
        else ++j;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, e, u;
    cin >> n >> e >> u;
    vector<int> dist(n);
    for (int i = 0; i < n - 1; ++i) cin >> dist[i];

    vector<int> leftDep(e), rightDep(u);
    for (int i = 0; i < e; ++i) cin >> leftDep[i];
    for (int i = 0; i < u; ++i) cin >> rightDep[i];

    vector<int> pref(n, 0);
    for (int i = 1; i < n; ++i) pref[i] = pref[i - 1] + dist[i - 1];
    int total = pref[n - 1];

    vector<int> ans;
    for (int seg = 0; seg < n - 1; ++seg) {
        vector<Interval> leftInt, rightInt;
        for (int t : leftDep) leftInt.push_back({t + pref[seg], t + pref[seg + 1]});
        for (int t : rightDep) rightInt.push_back({t + (total - pref[seg + 1]), t + (total - pref[seg])});
        if (!overlapExists(leftInt, rightInt)) ans.push_back(seg + 1);
    }

    cout << ans.size() << '\n';
    for (int x : ans) cout << x << ' ' << x + 1 << '\n';
    return 0;
}
