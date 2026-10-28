/*
Megoldás lényege: Az E_i = 1 jelölésű érkezők a csapatvezetők, a többiek tagok, az érkezési sorrend a bemenet sorrendje. Egy belépő tag mindig a még nem teli csapatok közül a legmagasabb pontszámú vezetőhöz csatlakozik, döntetlennél a kisebb sorszámú csapathoz. Ezt szimuláljuk: a nyitott csapatokat egy prioritási sorban tartjuk, a kulcs a vezető pontszáma és a csapat sorszáma, és ha egy csapat betelt, kivesszük a sorból. A végén a legnagyobb összpontszámú csapat vezetőjének sorszámát és az összpontszámát írjuk ki. Az időigény O(K*M*log K), a memóriaigény O(K).
*/
/*
Hint 1: || Nem kell előre kiszámolni a csapatokat: az érkezők sorrendben lépnek be, és minden tag a szabad csapatok közül a legjobb vezetőhöz csatlakozik, ezt kell szimulálni. ||
Hint 2: || A szabad csapatok közül mindig a legmagasabb vezetői pontszámút kell gyorsan megtalálni, és betelés után eltávolítani: ehhez prioritási sor (heap) használható. ||
Hint 3: || Minden csapatnak tárold az összpontszámát és a létszámát. Belépő vezetőt tegyél a sorba, belépő tagnál vedd ki a sor tetejét, és ha a csapat még nem telt be, tedd vissza. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, m;
    cin >> k >> m;
    vector<long long> total(k, 0);
    vector<int> cnt(k, 0);
    priority_queue<pair<long long, int>> open;
    int leaders = 0;
    for (int i = 0; i < k * m; i++) {
        int e;
        long long t;
        cin >> e >> t;
        if (e == 1) {
            int id = leaders++;
            total[id] = t;
            cnt[id] = 1;
            if (m > 1) open.push({t, -id});
        } else {
            if (open.empty()) continue;
            auto [score, nid] = open.top();
            open.pop();
            int id = -nid;
            total[id] += t;
            if (++cnt[id] < m) open.push({score, nid});
        }
    }

    int best = 0;
    for (int id = 1; id < k; id++)
        if (total[id] > total[best]) best = id;
    cout << best + 1 << " " << total[best] << "\n";
    return 0;
}
