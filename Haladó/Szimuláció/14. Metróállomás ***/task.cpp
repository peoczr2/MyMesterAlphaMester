/*
Megoldás lényege: időegységenként, darabszámmal szimuláljuk az állomást: az utcai sorból a lefelé menő lépcsőre legfeljebb 2 fő lép, és K időegység múlva a váróterembe ér. A metró M-enként érkezik, elviszi az addig a váróteremben összegyűlt utasokat, a kiszállók pedig a felfelé menő lépcső sorába kerülnek, ahonnan időegységenként legfeljebb 2 fő léphet fel, de csak a következő időegységtől. A váróterem kapacitását a metróra várók és a felfelé induló kiszállók együtt számítják, a túllépésnél a szimuláció megáll. Az időegységenkénti sorrend: felfelé lépés, metró, váróterembe érkezés, kapacitás-ellenőrzés, lefelé lépés; így a szimuláció O(N+K+M) időben fut.
*/
/*
Hint 1: || Két lépcsőt kell követni: a lefelé menő lépcső az utcai várakozókat K időegység után a váróterembe viszi, a felfelé menő lépcső pedig a metróról leszállókat. ||
Hint 2: || A metróról leszállók nem mennek azonnal fel: egy külön sorba kerülnek, amelyből időegységenként legfeljebb 2 fő léphet a lépcsőre, és csak a következő időegységtől. ||
Hint 3: || A váróterem kapacitását a metróra várók és a felfelé sorban állók együtt számítják, és minden időegység végén ellenőrizni kell. ||
Hint 4: || Egy időegységen belül a sorrend számít: előbb a felfelé sorból lépnek fel, utána érkezik a metró és a leszálló csoport, majd a váróterembe érkezők, végül a lefelé lépcsőre lépők. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k, l, m, u;
    cin >> n >> k >> l >> m >> u;
    vector<long long> arrivals(n + 1, 0);
    for (long long i = 0; i < u; ++i) {
        long long a;
        cin >> a;
        arrivals[a]++;
    }
    vector<long long> drops;
    for (long long x; cin >> x; ) drops.push_back(x);

    long long last = n + k + m;
    vector<long long> toRoom(last + k + 2, 0);
    long long street = 0;
    long long room = 0;
    long long upQueue = 0;
    size_t metroIdx = 0;
    vector<long long> served;

    for (long long t = 0; t <= last; ++t) {
        long long goUp = min(2LL, upQueue);
        upQueue -= goUp;

        if (t > 0 && t % m == 0) {
            served.push_back(room);
            room = 0;
            if (metroIdx < drops.size()) upQueue += drops[metroIdx];
            ++metroIdx;
        }

        room += toRoom[t];
        if (room + upQueue > l) break;

        if (t <= n) street += arrivals[t];
        long long enter = min(2LL, street);
        street -= enter;
        toRoom[t + k] += enter;
    }

    cout << served.size() << '\n';
    for (size_t i = 0; i < served.size(); ++i) {
        if (i) cout << ' ';
        cout << served[i];
    }
    cout << '\n';
    return 0;
}
