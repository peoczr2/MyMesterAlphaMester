/*
Feladat: A fák közül a lehető legkevesebbet kell kivágni, hogy mindegyik kidőljön, és meg kell adni azt a fát is, amelyik a legtöbb fát dönti le.
Ötlet: Először minden fáról kiszámítjuk, meddig terjed a döntési lánc. Ezután a teljes sort a lehető leghosszabb lefedő intervallumokkal fedjük le balról jobbra.
Hint 1: || Egy fa kidőlése a jobb oldali fák láncán keresztül tovább terjedhet. ||
Hint 2: || Ha ismered egy fa legvégső elérését, a következő fa elérését is ebből tudod építeni. ||
Hint 3: || A minimális kivágásszám ezután egy sima intervallumfedés. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> x(n + 1), h(n + 1), reach(n + 1);
    for (int i = 1; i <= n; ++i) cin >> x[i] >> h[i];

    for (int i = 1; i <= n; ++i) {
        long long cur = x[i] + h[i];
        int j = i + 1;
        while (j <= n && x[j] <= cur) {
            cur = max(cur, x[j] + h[j]);
            ++j;
        }
        reach[i] = cur;
    }

    int bestIdx = 1;
    long long bestFall = 1;
    for (int i = 1; i <= n; ++i) {
        long long cnt = upper_bound(x.begin() + 1, x.end(), reach[i]) - (x.begin() + i);
        if (cnt > bestFall) {
            bestFall = cnt;
            bestIdx = i;
        }
    }

    int cuts = 0;
    int i = 1;
    while (i <= n) {
        ++cuts;
        long long far = reach[i];
        int j = i + 1;
        while (j <= n && x[j] <= far) {
            far = max(far, reach[j]);
            ++j;
        }
        i = j;
    }

    cout << cuts << '\n' << bestIdx << '\n';
    return 0;
}