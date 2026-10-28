/*
Megoldás lényege:
Minden napra megszámoljuk, hány hajó érkezett (cnt[d]), így a napok száma és az érkezések száma is összegzéssel kapható meg. Az 1. részfeladatban a nulla értékű napokat számoljuk. A 2. részfeladatban a 2. és az M-1. nap közül keressük az első olyat, ahol cnt[d] > 0, de cnt[d-1] és cnt[d+1] nulla. A 3. részfeladatban az érkezés nélküli napok leghosszabb összefüggő szakaszát keressük, a 4. részfeladatban a legnagyobb cnt értékű első napot. Az 5. részfeladatban a nem nulla értékű napok leghosszabb összefüggő szakaszának első és utolsó napját írjuk ki; egyenlőségnél a korábbit, mert csak szigorúan nagyobb hossz frissíti a választ.
Az időigény O(N + M), ami N, M ≤ 1000 esetén elhanyagolható.
*/
/*
Hint 1: || Elég a napokhoz egy számlálót rendelni: cnt[d] megmondja, hány hajó érkezett a d. napon. Az 1. és 4. részfeladat ebből egyszerű számlálással és kereséssel adódik. ||
Hint 2: || A 3. és az 5. részfeladatban összefüggő szakaszokat kell követni: érkezés nélküli napoknál a hosszt növeled, egyébként nullázod. Az 5. részfeladatban a szakasz első napja az aktuális nap mínusz a hossz plusz egy. ||
Hint 3: || A 2. részfeladatban a 2. és M-1. nap közötti napokat nézd végig, és az első olyat írd ki, amelyre a feltétel igaz. Ha nincs ilyen, a feladat szerint -1 a válasz. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // cnt[d]: hány hajó érkezett a d. napon (1..m)
    vector<int> cnt(m + 2, 0);
    for (int i = 0; i < n; ++i) {
        int e;
        cin >> e;
        ++cnt[e];
    }

    // 1. részfeladat: az érkezés nélküli napok száma
    int noArrival = 0;
    for (int d = 1; d <= m; ++d)
        if (cnt[d] == 0) ++noArrival;
    cout << "#\n" << noArrival << "\n";

    // 2. részfeladat: az első olyan nap (2..m-1), amelyen érkezett hajó, de az előző és a következő napon nem
    int isolated = -1;
    for (int d = 2; d <= m - 1; ++d)
        if (cnt[d] > 0 && cnt[d - 1] == 0 && cnt[d + 1] == 0) {
            isolated = d;
            break;
        }
    cout << "#\n" << isolated << "\n";

    // 3. részfeladat: a leghosszabb érkezés nélküli szakasz hossza (0, ha nincs)
    int longestGap = 0, run = 0;
    for (int d = 1; d <= m; ++d) {
        if (cnt[d] == 0) {
            ++run;
            longestGap = max(longestGap, run);
        } else {
            run = 0;
        }
    }
    cout << "#\n" << longestGap << "\n";

    // 4. részfeladat: a legtöbb hajó érkezésének napja (egyenlőségnél a legkorábbi)
    int busiest = 1;
    for (int d = 2; d <= m; ++d)
        if (cnt[d] > cnt[busiest]) busiest = d;
    cout << "#\n" << busiest << "\n";

    // 5. részfeladat: a leghosszabb, minden napon érkezéssel teli szakasz első és utolsó napja
    int bestLen = 0, bestFirst = -1, bestLast = -1;
    run = 0;
    for (int d = 1; d <= m; ++d) {
        run = (cnt[d] > 0) ? run + 1 : 0;
        if (run > bestLen) {
            bestLen = run;
            bestFirst = d - run + 1;
            bestLast = d;
        }
    }
    cout << "#\n" << bestFirst << ' ' << bestLast << "\n";

    return 0;
}
