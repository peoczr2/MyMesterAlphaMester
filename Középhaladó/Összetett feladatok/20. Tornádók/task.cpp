/*
Megoldás lényege:
Minden napra megszámoljuk a tornádók számát egy gyakorisági tömbben (cnt[nap]). Az üres napok száma az M mínusz a tornádós napok száma, a szomszédos napokon való tornádó egyszerűen ellenőrizhető a cnt[nap - 1], cnt[nap], cnt[nap + 1] értékekből, a legtöbb tornádó pedig a tömb maximuma. A leghosszabb tornádómentes, illetve a csupa tornádós napokból álló szakaszt egy lineáris bejárással keressük: az aktuális szakasz hosszát növeljük, a megszakadásnál összevetjük a legjobbal, döntetlennél a korábbi szakasz marad. Mivel M legfeljebb 1000, az időigény O(M + T).
*/
/*
Hint 1: || Használj gyakorisági tömböt: a cnt[nap] megmondja, hány tornádó volt az adott napon. Az 1., 2. és 4. kérdés ebből egyetlen bejárással megválaszolható. ||
Hint 2: || A leghosszabb egymást követő napokból álló szakaszt úgy keresd, hogy végigmész a napokon, nyilvántartod az aktuális szakasz kezdetét és hosszát, és amikor a feltétel megszakad, összehasonlítod a legjobb eddigivel. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Run {
    int len, first, last;
};

// A leghosszabb, egymást követő napokból álló szakasz, amelyen minden nap
// tornádós (tornado = true), illetve tornádómentes (tornado = false).
// Döntetlennél a korábbi szakasz marad.
Run longestRun(int m, const vector<int>& cnt, bool tornado) {
    Run best{0, 0, 0};
    int start = 0;
    for (int d = 1; d <= m + 1; d++) {
        bool ok = d <= m && ((cnt[d] > 0) == tornado);
        if (ok) {
            if (start == 0) start = d;
        } else if (start != 0) {
            int len = d - start;
            if (len > best.len) best = {len, start, d - 1};
            start = 0;
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, t;
    cin >> m >> t;
    vector<int> cnt(m + 2, 0);
    for (int i = 0; i < t; i++) {
        int e;
        cin >> e;
        cnt[e]++;
    }

    // 1. részfeladat: a tornádó nélküli napok száma
    int withTornado = 0, maxPerDay = 0;
    for (int d = 1; d <= m; d++) {
        if (cnt[d] > 0) withTornado++;
        maxPerDay = max(maxPerDay, cnt[d]);
    }
    cout << "#\n" << m - withTornado << "\n";

    // 2. részfeladat: az első olyan nap, amelynek az előző és a következő napján is volt tornádó
    int firstDay = 0;
    for (int d = 1; d <= m; d++) {
        if (cnt[d - 1] > 0 && cnt[d] > 0 && cnt[d + 1] > 0) {
            firstDay = d;
            break;
        }
    }
    cout << "#\n" << firstDay << "\n";

    // 3. részfeladat: a leghosszabb tornádómentes időszak hossza
    cout << "#\n" << longestRun(m, cnt, false).len << "\n";

    // 4. részfeladat: egy napon belül a legtöbb tornádó
    cout << "#\n" << maxPerDay << "\n";

    // 5. részfeladat: a leghosszabb olyan időszak első és utolsó napja, amikor minden nap volt tornádó
    Run r = longestRun(m, cnt, true);
    cout << "#\n" << r.first << ' ' << r.last << "\n";
    return 0;
}
