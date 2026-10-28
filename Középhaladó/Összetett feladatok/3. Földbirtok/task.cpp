/*
Megoldás lényege:
Minden alkalmazás [E, U] napjait különbségtömbbel rögzítjük: az E napon eggyel nő, az U+1 napon eggyel csökken a számláló. A prefixösszeg adja meg minden napra, hány alkalmazott dolgozott. Ebből a teljes bér összege (napok száma szorozva a napi bérrel), a legtöbbet kereső (teljes bér szerint) alkalmazott munkanapjainak legkevesebbje, a legnagyobb egyidejű létszám és a maximumot elérő leghosszabb egybefüggő napsor adódik. A nulla létszámú napok egybefüggő szakaszait a legkorábbi kezdet és a legkésőbbi vég között egy végigjárással írjuk ki; az összidő O(max nap + M).
*/
/*
Hint 1: || A napok száma kicsi (legfeljebb 10 000), ezért a napokat közvetlenül végigjárhatod, és minden napra kiszámolhatod a dolgozók számát. ||
Hint 2: || A létszámot különbségtömbbel építsd: az E napon növeld, az U+1 napon csökkentsd eggyel, majd a prefixösszeg adja a napi létszámot. ||
Hint 3: || Ugyanebből a tömbből jön minden részfeladat: a teljes bér a napok száma és a napi bér szorzatainak összege, a legnagyobb teljes bérű alkalmazott közül a legkevesebb napot dolgozót kell kiírni, a maximumot és a leghosszabb maximumos napsort egy bejárással megkapod, végül a nulla létszámú napok szakaszait az első kezdet és az utolsó vég között keresd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m;
    cin >> m;

    const int MAXD = 10005;
    vector<int> diff(MAXD, 0);
    long long total = 0;
    long long maxEarn = -1;
    int daysOfTopEarner = 0;
    int firstDay = INT_MAX, lastDay = 0;

    for (int i = 0; i < m; ++i) {
        int e, u, b;
        cin >> e >> u >> b;
        int days = u - e + 1;
        long long earn = (long long)days * b;
        total += earn;
        if (earn > maxEarn) {
            maxEarn = earn;
            daysOfTopEarner = days;
        } else if (earn == maxEarn) {
            daysOfTopEarner = min(daysOfTopEarner, days);
        }
        diff[e] += 1;
        diff[u + 1] -= 1;
        firstDay = min(firstDay, e);
        lastDay = max(lastDay, u);
    }

    vector<int> people(lastDay + 2, 0);
    int running = 0;
    for (int d = 1; d <= lastDay; ++d) {
        running += diff[d];
        people[d] = running;
    }

    int peak = 0;
    for (int d = firstDay; d <= lastDay; ++d) peak = max(peak, people[d]);

    int longestPeak = 0, cur = 0;
    for (int d = firstDay; d <= lastDay; ++d) {
        if (people[d] == peak) {
            ++cur;
            longestPeak = max(longestPeak, cur);
        } else {
            cur = 0;
        }
    }

    // 1. részfeladat: a teljes bér
    cout << "#\n" << total << "\n";
    // 2. részfeladat: a legtöbbet kereső munkanapjai (a legkevesebb)
    cout << "#\n" << daysOfTopEarner << "\n";
    // 3. részfeladat: egyszerre dolgozók maximális száma
    cout << "#\n" << peak << "\n";
    // 4. részfeladat: a leghosszabb maximumos napsor hossza
    cout << "#\n" << longestPeak << "\n";

    // 5. részfeladat: senki által nem dolgozott szakaszok
    cout << "#\n";
    int d = firstDay;
    while (d <= lastDay) {
        if (people[d] != 0) {
            ++d;
            continue;
        }
        int start = d;
        while (d <= lastDay && people[d] == 0) ++d;
        cout << start << " " << d - 1 << "\n";
    }
    return 0;
}
