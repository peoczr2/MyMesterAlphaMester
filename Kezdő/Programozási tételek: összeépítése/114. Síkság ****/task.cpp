/*
Megoldás lényege:
Ha egy szakasz jó, azaz a legnagyobb és a legkisebb mérés különbsége legfeljebb 1, akkor minden részszakasza is jó.
Ezért kétmutatós csúszóablakot használunk: a jobb végpontot egyesével léptetjük, és a bal végpontot addig visszük jobbra, amíg a szakasz max-min különbsége 1-nél nagyobb.
A szakasz maximumát és minimumát két monoton deque tartja karban, amelyek a mérések indexeit tárolják az értékük szerint.
Minden jobb végponthoz így a leghosszabb jó szakasz adódik, és a legjobbat csak szigorúan hosszabb találatnál írjuk felül, így a legkisebb kezdőindex marad.
Az indexek legfeljebb egyszer kerülnek be és ki a deque-kbe, így az időigény O(N).
*/
/*
Hint 1: || Ha egy szakasz jó, minden részszakasza is jó. Ezért a bal végpont sosem megy vissza balra, elég jobbra léptetni. ||
Hint 2: || A szélsőértékeket nem kell minden lépésben újraszámolni: a legnagyobb és a legkisebb elemek indexeit egy-egy monoton deque-ben tartva a szakasz maximuma és minimuma mindig a deque elején van. ||
Hint 3: || Ha a max és a min különbsége 1-nél nagyobb, léptesd a bal végpontot, és a deque-k elejéről dobd ki azokat az indexeket, amelyek már a szakaszon kívülre kerültek. Hossz frissítésénél csak szigorúan nagyobb hossznál írd felül a legjobbat, így a legkisebb sorszám marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> m(n);
    for (auto &x : m) cin >> x;

    deque<int> mx, mn;  // mx: csökkenő értékek indexei, mn: növekvő értékek indexei
    int best_len = 0, best_start = 0;
    int l = 0;
    for (int r = 0; r < n; ++r) {
        while (!mx.empty() && m[mx.back()] <= m[r]) mx.pop_back();
        mx.push_back(r);
        while (!mn.empty() && m[mn.back()] >= m[r]) mn.pop_back();
        mn.push_back(r);

        while (m[mx.front()] - m[mn.front()] > 1) {
            ++l;
            while (!mx.empty() && mx.front() < l) mx.pop_front();
            while (!mn.empty() && mn.front() < l) mn.pop_front();
        }

        int len = r - l + 1;
        if (len > best_len) {
            best_len = len;
            best_start = l;
        }
    }
    cout << best_len << ' ' << best_start + 1 << '\n';
    return 0;
}
