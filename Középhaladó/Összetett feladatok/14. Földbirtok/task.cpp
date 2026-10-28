/*
Megoldás lényege:
Egy alkalmazott munkanapjainak száma U - E + 1, a keresete ennek és a napi bérnek a szorzata; az összes kifizetendő bér ezek összege. A legtöbbet kereső alkalmazott a legnagyobb keresetű (döntetlennél a kevesebb napot dolgozó), és az ő napjainak száma a 2. részfeladat válasza.
A napokra (1..10000) egy különbségi tömbbel számoljuk a napi létszámot: minden [E, U] intervallumhoz +1 kerül az E. napnál és -1 az U+1. napnál, a prefix összeg pedig a d. napon dolgozók számát adja. Ebből a maximális létszám és a leghosszabb, maximális létszámú szakasz egy bejárással kiszámítható.
Az 5. részfeladatban az első és az utolsó munkanap közötti, nulla létszámú napok összefüggő szakaszait írjuk ki növekvő sorrendben.
Az időigény O(M + 10000), ami messze belefér a 0,1 mp-es időkorlátba.
*/
/*
Hint 1: || Az 1. és 2. részfeladathoz elég minden alkalmazott keresetét kiszámolni: a dolgozott napok száma és a napi bér szorzata, az összeget pedig egyszerűen összegezni; a legnagyobb keresetet kell megkeresni. ||
Hint 2: || A napok száma legfeljebb 10 000, ezért tarts egy különbségi tömböt: minden [E, U] intervallumhoz a diff[E] értékét növeld 1-gyel, a diff[U+1] értékét csökkentsd 1-gyel. A prefix összegek adják a d. napon dolgozók számát. ||
Hint 3: || A 4. és 5. részfeladatnál egy menetben végigmész a napokon: a maximális létszámú napok futamainak hosszából a leghosszabbat választod, a nulla létszámú napok futamainak elejét és végét pedig az első és utolsó munkanap közötti tartományban írod ki. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXD = 10000;

    int m;
    cin >> m;

    vector<int> diff(MAXD + 2, 0);
    long long total = 0;
    long long bestEarn = -1;
    int bestDays = 0;
    int firstDay = MAXD + 1;
    int lastDay = 0;

    for (int i = 0; i < m; ++i) {
        int e, u;
        long long w;
        cin >> e >> u >> w;

        int days = u - e + 1;
        long long earn = (long long)days * w;
        total += earn;

        // 2. részfeladat: a legnagyobb keresetű alkalmazott (döntetlennél a kevesebb nap)
        if (earn > bestEarn || (earn == bestEarn && days < bestDays)) {
            bestEarn = earn;
            bestDays = days;
        }

        diff[e] += 1;
        diff[u + 1] -= 1;
        firstDay = min(firstDay, e);
        lastDay = max(lastDay, u);
    }

    // napi létszám: a különbségi tömb prefix összege
    vector<int> cnt(MAXD + 2, 0);
    int run = 0;
    for (int d = 1; d <= MAXD; ++d) {
        run += diff[d];
        cnt[d] = run;
    }

    // 3. részfeladat: a legtöbb egyszerre dolgozó alkalmazott
    int maxCnt = 0;
    for (int d = 1; d <= MAXD; ++d) maxCnt = max(maxCnt, cnt[d]);

    // 4. részfeladat: a leghosszabb, maximális létszámú szakasz hossza
    int longest = 0;
    int cur = 0;
    for (int d = 1; d <= MAXD; ++d) {
        if (cnt[d] == maxCnt) {
            cur++;
            longest = max(longest, cur);
        } else {
            cur = 0;
        }
    }

    // 5. részfeladat: az első és utolsó munkanap közötti üres időszakok
    vector<pair<int, int>> gaps;
    for (int d = firstDay; d <= lastDay;) {
        if (cnt[d] == 0) {
            int s = d;
            while (d <= lastDay && cnt[d] == 0) ++d;
            gaps.push_back({s, d - 1});
        } else {
            ++d;
        }
    }

    cout << "#\n" << total << "\n";
    cout << "#\n" << bestDays << "\n";
    cout << "#\n" << maxCnt << "\n";
    cout << "#\n" << longest << "\n";
    cout << "#\n";
    for (const auto &g : gaps) {
        cout << g.first << ' ' << g.second << "\n";
    }

    return 0;
}
