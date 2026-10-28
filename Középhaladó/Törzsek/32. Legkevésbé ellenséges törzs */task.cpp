/*
Megoldás lényege:
A kérdés a különböző ellenséges törzsek számát kéri, nem a háborúk számát, mert ugyanazzal a törzzsel többször is lehet háború. Törzsenként egy halmazban gyűjtjük az ellenségeket: egy háborúnál mindkét résztvevőnél felvesszük a másikat. A békés törzsek halmaza üres, ezek kimaradnak; a többi közül a legkisebb halmazméretű törzs sorszámát írjuk ki, egyenlőség esetén a kisebbet. Az időigény O(K log N), ami K ≤ 2000 mellett azonnali.
*/
/*
Hint 1: || Nem a háborúk számát kell megszámolni, hanem a különböző ellenséges törzseket: ugyanaz a két törzs többször is háborúzhat egymással. ||
Hint 2: || Törzsenként egy halmazban (set) gyűjtsd az ellenségeket: egy háborúnál mindkét résztvevőnél vedd fel a másik törzset. Ezután a nem üres halmazú törzsek közül keresd a legkisebb halmazméretűt, egyenlőségnél a kisebb sorszámút. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 4>> wars(k); // támadó, védő, kezdet, befejezés
    int maxId = n;
    for (auto &w : wars) {
        cin >> w[0] >> w[1] >> w[2] >> w[3];
        maxId = max({maxId, w[0], w[1]});
    }

    vector<set<int>> enemies(maxId + 1);
    for (const auto &w : wars) {
        enemies[w[0]].insert(w[1]);
        enemies[w[1]].insert(w[0]);
    }

    int best = -1;
    for (int t = 1; t <= maxId; t++) {
        if (enemies[t].empty()) continue; // békés törzs: nem háborúzott
        if (best == -1 || enemies[t].size() < enemies[best].size()) best = t;
    }

    cout << best << "\n";
    return 0;
}
