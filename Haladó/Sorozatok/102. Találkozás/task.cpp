/*
Megoldás lényege:
Egy [s,e] intervallum akkor találkozik egy vendéggel, ha s <= távozás és érkezés <= e.
Ezért a vendégek száma egy adott intervallumban csak a kezdő- és végponttól függ,
előre kiszámított prefixösszegekkel pedig O(1)-ben megkapható.

A keresett legrövidebb intervallumot bináris kereséssel kapjuk meg a hosszra,
majd az adott hosszra balról jobbra végigpróbáljuk az összes lehetséges kezdőpontot.
*/
// Hint 1: || Egy vendég akkor benne van a találkozásban, ha az intervallum metszi a saját [érkezés, távozás] szakaszát. ||
// Hint 2: || Fix hosszra a vendégszámot prefixekből O(1)-ben ki lehet számolni. ||
// Hint 3: || A minimális hosszhoz elég binárisan keresni, majd az első jó kezdőpontot megkeresni. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> L(N), R(N);
    int maxT = 0;
    for (int i = 0; i < N; ++i) {
        cin >> L[i] >> R[i];
        maxT = max(maxT, R[i]);
    }

    vector<int> start(maxT + 2, 0), finish(maxT + 2, 0);
    for (int i = 0; i < N; ++i) {
        ++start[L[i]];
        ++finish[R[i]];
    }
    for (int t = 1; t <= maxT; ++t) {
        start[t] += start[t - 1];
        finish[t] += finish[t - 1];
    }

    int need = (N + 1) / 2;

    auto enough = [&](int len) {
        for (int s = 1; s + len <= maxT; ++s) {
            int e = s + len;
            int cnt = start[e] - (s > 1 ? finish[s - 1] : 0);
            if (cnt >= need) return true;
        }
        return false;
    };

    int lo = 0, hi = maxT;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (enough(mid)) hi = mid;
        else lo = mid + 1;
    }

    int bestLen = lo;
    int bestS = 1;
    for (int s = 1; s + bestLen <= maxT; ++s) {
        int e = s + bestLen;
        int cnt = start[e] - (s > 1 ? finish[s - 1] : 0);
        if (cnt >= need) {
            bestS = s;
            break;
        }
    }

    cout << bestLen + 1 << '\n' << bestS << ' ' << bestS + bestLen << '\n';
    return 0;
}
