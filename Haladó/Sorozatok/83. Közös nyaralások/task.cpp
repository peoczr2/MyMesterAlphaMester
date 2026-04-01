/*
Megoldás lényege:
Mindkét ember nyaralási időszakai rendezettek és saját magukon belül diszjunktak. Ezért a közös
időszakok listája kétmutatós összefésüléssel előállítható: mindig az aktuális két intervallum metszetét
nézzük meg, majd amelyik előbb véget ér, annál lépünk tovább.

Így minden intervallumot legfeljebb egyszer érintünk, tehát a megoldás lineáris.
*/
/*
Hint 1: || Két rendezett, diszjunkt intervallumlista metszetét kell kiírni. ||
Hint 2: || Az aktuális két intervallum közös része: [max(kezdet), min(vég)]. ||
Hint 3: || Amelyik intervallum előbb elfogy, annál biztosan tovább lehet lépni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for (auto &interval : a) cin >> interval.first >> interval.second;

    int m;
    cin >> m;
    vector<pair<int,int>> b(m);
    for (auto &interval : b) cin >> interval.first >> interval.second;

    vector<pair<int,int>> answer;
    int i = 0;
    int j = 0;
    while (i < n && j < m) {
        int left = max(a[i].first, b[j].first);
        int right = min(a[i].second, b[j].second);
        if (left <= right) {
            answer.push_back({left, right});
        }
        if (a[i].second < b[j].second) {
            ++i;
        } else {
            ++j;
        }
    }

    cout << answer.size() << '\n';
    for (const auto &interval : answer) {
        cout << interval.first << ' ' << interval.second << '\n';
    }
    return 0;
}