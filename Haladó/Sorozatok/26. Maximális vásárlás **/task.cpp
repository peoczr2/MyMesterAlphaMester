/*
Megoldas lenyege:
Mindkét üzlet listája már árukód szerint rendezett. Egy összefésüléses bejárással
végigmegyünk a két listán, és minden kódhoz meghatározzuk az együttesen elérhető
mennyiséget. Az A feltételnél a két üzlet közül a nagyobb készlet kell, a B
feltételnél pedig a készletek összege.
*/
/*
Hint 1: || A két bemeneti lista rendezett, ezért elég egyszerre haladni rajtuk. ||
Hint 2: || Ha ugyanaz a kód mindkét oldalon szerepel, akkor A-hoz a nagyobb készlet, B-hez az összeg kell. ||
Hint 3: || A kimenet csak a mennyiségeket tartalmazza, a kódokat nem kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<long long, long long>> a(n), b(m);
    for (auto &x : a) cin >> x.first >> x.second;
    for (auto &x : b) cin >> x.first >> x.second;

    vector<long long> ansA, ansB;
    int i = 0, j = 0;
    while (i < n || j < m) {
        if (j == m || (i < n && a[i].first < b[j].first)) {
            ansA.push_back(a[i].second);
            ansB.push_back(a[i].second);
            ++i;
        } else if (i == n || b[j].first < a[i].first) {
            ansA.push_back(b[j].second);
            ansB.push_back(b[j].second);
            ++j;
        } else {
            ansA.push_back(max(a[i].second, b[j].second));
            ansB.push_back(a[i].second + b[j].second);
            ++i;
            ++j;
        }
    }

    for (int k = 0; k < (int)ansA.size(); ++k) {
        if (k) cout << ' ';
        cout << ansA[k];
    }
    cout << '\n';
    for (int k = 0; k < (int)ansB.size(); ++k) {
        if (k) cout << ' ';
        cout << ansB[k];
    }
    cout << '\n';
    return 0;
}
