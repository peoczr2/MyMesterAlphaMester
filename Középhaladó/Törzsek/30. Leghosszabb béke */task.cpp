/*
Megoldás lényege:
Béke akkor van, ha nincs folyamatban háború, ezért először a háborús időszakokat egyesítjük: kezdő év szerint rendezzük a háborúkat, és az átfedő vagy érintkező háborúkat egy szakaszba vonjuk. Két egymást követő összevont háborús szakasz közötti rés az első szakasz vége és a második kezdete között van, ez egy békés időszak. A leghosszabb, pozitív hosszúságú rést keressük, döntetlennél a korábbit, és ha nincs ilyen, a válasz 0 0. Az időigény O(K log K).
*/
/*
Hint 1: || A béke a háborús szakaszok közötti űrökben van, ezért először a háborúkat kell egyesíteni, majd a szomszédos szakaszok közti rések hosszát vizsgálni. ||
Hint 2: || Egy rés hossza a következő összevont szakasz kezdete mínusz az előző szakasz vége. Végigjárva a réseket keresd a legnagyobbat, és ha egyik sem pozitív hosszú, a válasz 0 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> haboru(k); // (kezdés, befejezés)
    for (auto &h : haboru) {
        int a, b;
        cin >> a >> b >> h.first >> h.second;
    }
    sort(haboru.begin(), haboru.end());

    // Összevont háborús időszakok
    vector<pair<int, int>> idoszak;
    for (const auto &h : haboru) {
        if (!idoszak.empty() && h.first <= idoszak.back().second)
            idoszak.back().second = max(idoszak.back().second, h.second);
        else
            idoszak.push_back(h);
    }

    pair<int, int> legjobb = {0, 0};
    int legjobb_hossz = 0;
    for (size_t i = 0; i + 1 < idoszak.size(); i++) {
        int kezd = idoszak[i].second;
        int veg = idoszak[i + 1].first;
        if (veg - kezd > legjobb_hossz) {
            legjobb_hossz = veg - kezd;
            legjobb = {kezd, veg};
        }
    }
    cout << legjobb.first << " " << legjobb.second << "\n";
    return 0;
}
