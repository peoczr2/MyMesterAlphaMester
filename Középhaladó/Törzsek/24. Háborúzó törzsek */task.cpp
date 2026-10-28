/*
Megoldás lényege:
Egy háború akkor tartozik egy századhoz, ha a kezdő- vagy a befejező éve benne van a század évtartományában (XVII.: 1601–1700, XVIII.: 1701–1800, XIX.: 1801–1900). Századonként végigmegyünk a háborúkon, és a találatok két törzsét egy halmazba tesszük, így minden törzs csak egyszer számít, akkor is, ha több háborúban részt vett. A három halmaz mérete adja a három kiírandó számot. Az időigény O(3·K·log N), ami K ≤ 2000 mellett messze belefér a 0,1 mp-es időkorlátba.
*/
/*
Hint 1: || Minden törzsről csak az számít, hogy részt vett-e háborúban az adott században. Ha egy törzs több háborúban is szerepel, akkor is csak egyszer kell számolni. ||
Hint 2: || Századonként külön vizsgáld a háborúkat: a háború akkor számít, ha a kezdő- vagy a befejező éve benne van a század évtartományában. A találatok két törzsét tedd halmazba (set), és a halmaz méretét írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 4>> haboru(k);
    for (auto &h : haboru)
        cin >> h[0] >> h[1] >> h[2] >> h[3];

    // Az évszázadok évtartománya: XVII., XVIII., XIX.
    const int kezd[3] = {1601, 1701, 1801};
    const int vege[3] = {1700, 1800, 1900};

    for (int c = 0; c < 3; ++c) {
        set<int> torzsek;
        for (const auto &h : haboru) {
            bool belep = (h[2] >= kezd[c] && h[2] <= vege[c]) || (h[3] >= kezd[c] && h[3] <= vege[c]);
            if (belep) {
                torzsek.insert(h[0]);
                torzsek.insert(h[1]);
            }
        }
        cout << torzsek.size() << (c < 2 ? " " : "\n");
    }
    return 0;
}
