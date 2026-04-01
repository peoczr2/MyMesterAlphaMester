/*
Megoldas lenyege:
A két üzlet készletei rendezett listák. Egy összefésüléses bejárással minden
kódot egyszer látunk: a közös kódokból az A részhez a kisebb készlet kerül, a B
részhez pedig csak az egyetlen üzletben szereplő kódok készletei kerülhetnek.
*/
/*
Hint 1: || A két lista rendezett, ezért elég egyszerre haladni rajtuk. ||
Hint 2: || Az A feltételnél a közös kódoknál a kisebb készlet kell. ||
Hint 3: || A B feltételnél csak az egyoldalúan szereplő kódok maradnak. ||
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
            ansB.push_back(a[i].second);
            ++i;
        } else if (i == n || b[j].first < a[i].first) {
            ansB.push_back(b[j].second);
            ++j;
        } else {
            ansA.push_back(min(a[i].second, b[j].second));
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
