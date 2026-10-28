/*
Megoldás lényege:
A törzs háborúit kezdő év szerint rendezzük, és összevonjuk az átfedő (vagy egymásba érő) háborúkat egy háborús időszakká.
Egy időszak kezdete az első háború kezdete, vége az addigi legkésőbbi befejezés; ha a következő háború kezdete ez után van, az időszak lezárul és új kezdődik.
Minden lezárt időszak hosszát (vég - kezdet) összevetjük az eddigi legrövidebbel, egyenlőségnél a korábbi marad.
Ha a törzs nem háborúzott, a válasz 0 0. Az idő O(K log K), a memória O(K).
*/
/*
Hint 1: || Egy háborús időszak folyamatos: addig tart, amíg legalább egy háború még tart, vagyis az egymást átfedő háborúk egy időszakba tartoznak. ||
Hint 2: || Rendezd a törzs háborúit kezdés szerint, és az aktuális időszaknál tartsd nyilván a kezdetét és az eddig látott legkésőbbi befejezést. ||
Hint 3: || Ha a következő háború kezdete a legkésőbbi befejezés után van, az időszak véget ér; a lezárt időszakok közül a legrövidebbet (vég - kezdet) tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 4>> wars(k); // támadó, védő, kezdet, befejezés
    for (auto &w : wars) cin >> w[0] >> w[1] >> w[2] >> w[3];
    int y;
    cin >> y;

    vector<pair<int, int>> mine; // (kezdet, befejezés)
    for (auto &w : wars)
        if (w[0] == y || w[1] == y) mine.push_back({w[2], w[3]});
    sort(mine.begin(), mine.end());

    bool found = false;
    int bestLen = 0, bestFrom = 0, bestTo = 0;
    auto consider = [&](int from, int to) {
        int len = to - from;
        if (!found || len < bestLen) {
            found = true;
            bestLen = len;
            bestFrom = from;
            bestTo = to;
        }
    };

    if (!mine.empty()) {
        int curFrom = mine[0].first, curTo = mine[0].second;
        for (size_t i = 1; i < mine.size(); i++) {
            if (mine[i].first > curTo) {
                consider(curFrom, curTo);
                curFrom = mine[i].first;
                curTo = mine[i].second;
            } else {
                curTo = max(curTo, mine[i].second);
            }
        }
        consider(curFrom, curTo);
    }

    cout << bestFrom << " " << bestTo << "\n";
    return 0;
}
