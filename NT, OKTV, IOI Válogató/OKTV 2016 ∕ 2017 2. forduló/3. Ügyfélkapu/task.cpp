/*
Megoldás lényege: az ügyintézést percenként szimuláljuk. Minden t percben először beérkeznek a t-kor érkezők a várakozók közé, majd ha az ügyintéző szabad, a várakozók közül a legrövidebb ügyet hívja be (azonosságnál a korábban érkezőt, majd a kisebb sorszámút). Eközben minden ügyfélnél rögzítjük a várakozás idejét (kezdési idő mínusz érkezés), és minden percben a döntés után megszámoljuk a várakozókat. A legnagyobb várakozású ügyfél a kisebb sorszámot kapja döntetlennél, és ha senki sem várakozott, a válasz 0. A várakozókat prioritási sorban tartjuk, így lépésenként O(log N) a költség, az összes idő pedig néhány tízezer perc.
*/
/*
Hint 1: || Nem kell eseményenként külön logika: a 0. perctől percenként léptetve szimulálható az ügyintézés, ha a várakozókat prioritási sorban tartod. ||
Hint 2: || A prioritási sor kulcsa legyen (Ugyi, Erk, sorszám) hármas, így a legrövidebb ügy kerül előre, döntetlennél a korábbi érkezés, majd a kisebb sorszám. Az ügyintéző akkor szabad, ha az aktuális idő legalább az előző ügy befejezési ideje (T+U). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> erk(n + 1), ugy(n + 1);
    for (int i = 1; i <= n; i++) cin >> erk[i] >> ugy[i];

    vector<int> ord(n);
    for (int i = 0; i < n; i++) ord[i] = i + 1;
    sort(ord.begin(), ord.end(), [&](int x, int y) {
        if (erk[x] != erk[y]) return erk[x] < erk[y];
        return x < y;
    });

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    vector<int> wait(n + 1, 0);
    int busy = 0;
    int served = 0;
    int p = 0;
    int maxq = 0;

    for (int t = 0; served < n; t++) {
        while (p < n && erk[ord[p]] <= t) {
            int id = ord[p];
            pq.push(make_tuple(ugy[id], erk[id], id));
            p++;
        }
        if (busy <= t && !pq.empty()) {
            auto top = pq.top();
            pq.pop();
            int id = get<2>(top);
            int e = get<1>(top);
            int u = get<0>(top);
            wait[id] = t - e;
            busy = t + u;
            served++;
        }
        maxq = max(maxq, (int)pq.size());
    }

    int best = 0, bestw = 0;
    for (int i = 1; i <= n; i++) {
        if (wait[i] > bestw) {
            bestw = wait[i];
            best = i;
        }
    }

    cout << best << '\n';
    cout << maxq << '\n';
    return 0;
}
