/*
Megoldás lényege:
A törzs összes háborúját (ahol a törzs támadóként vagy védekezőként szerepel) kezdő év szerint rendezzük, majd egy menetben haladunk végig rajtuk.
Közben nyilvántartjuk az eddig látott legkésőbbi befejezési évet, ami a folyamatos háborús időszak végét jelenti.
Ha a következő háború kezdete nagyobb ennél az évnél, a köztes szakasz békés, és hossza a két év különbsége.
A leghosszabb ilyen szakaszt tartjuk meg; egyenlőségnél a korábbi marad, mert az összehasonlítás szigorú.
Ha nincs pozitív hosszúságú béke, a válasz 0 0. Az idő O(K log K), a memória O(K).
*/
/*
Hint 1: || Csak azokat a háborúkat nézd, amelyekben a kérdezett törzs részt vesz, és ezeket kezdő év szerint rendezd. ||
Hint 2: || Végigmenve a háborúkon tartsd nyilván az eddig látott legkésőbbi befejezési évet. Ha a következő háború később kezdődik, mint ez az év, a közbeeső évek békések; a leghosszabb ilyen szakaszt keresd. ||
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

    int bestLen = 0, bestFrom = 0, bestTo = 0;
    if (!mine.empty()) {
        int lastEnd = mine[0].second;
        for (size_t i = 1; i < mine.size(); i++) {
            if (mine[i].first > lastEnd) {
                int len = mine[i].first - lastEnd;
                if (len > bestLen) {
                    bestLen = len;
                    bestFrom = lastEnd;
                    bestTo = mine[i].first;
                }
            }
            lastEnd = max(lastEnd, mine[i].second);
        }
    }

    cout << bestFrom << " " << bestTo << "\n";
    return 0;
}
