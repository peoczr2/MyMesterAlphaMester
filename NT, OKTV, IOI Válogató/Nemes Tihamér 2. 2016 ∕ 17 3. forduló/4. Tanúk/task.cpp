/*
Megoldás lényege:
Az események időpontja növekvő sorrendben van, ezért balról jobbra haladva a még le nem fedett legkorábbi eseményhez választunk olyan vendéget, aki akkor jelen van, és a legkésőbb távozik. Ez az intervallumok ponthalmaz-lefedésének klasszikus mohó algoritmusa, amely minimális számú vendéget ad. Az E számláló azokat az eseményeket számolja, amelyeket valamelyik kiválasztott vendég lefed: a senki által nem látott események kimaradnak. A vendégek és az események mutatója egyszer halad végig, így az idő O(N + M).
*/
/*
Hint 1: || Egy vendég egy eseményhez csak akkor lehet tanú, ha az esemény időpontja az érkezése és a távozása közé esik (a határokat is beleértve). Az események rendezettek, ezért elég a még le nem fedett esemény időpontját nézni. ||
Hint 2: || A legkorábbi le nem fedett eseményhez válassz olyan vendéget, aki ott van, és a legkésőbb távozik. Így a kiválasztott vendég a lehető legtöbb következő eseményt lefedi, és kevesebb vendég kell. ||
Hint 3: || Az E-t úgy kapod meg, hogy a kiválasztás után a kiválasztott vendég által lefedett eseményeket számolod. Ha egy eseményhez nincs jelölt vendég, azt kihagyod, mert nem számít bele. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> vendeg(n + 1);
    for (int i = 1; i <= n; ++i) cin >> vendeg[i].first >> vendeg[i].second;
    vector<int> esemeny(m);
    for (int i = 0; i < m; ++i) cin >> esemeny[i];

    int i = 1, j = 0, E = 0;
    vector<int> valasztott;
    while (j < m) {
        int t = esemeny[j];
        int best = -1, bestEnd = -1;
        while (i <= n && vendeg[i].first <= t) {
            if (vendeg[i].second >= t && vendeg[i].second > bestEnd) {
                bestEnd = vendeg[i].second;
                best = i;
            }
            ++i;
        }
        if (best == -1) {
            ++j;
            continue;
        }
        valasztott.push_back(best);
        while (j < m && esemeny[j] <= bestEnd) { ++j; ++E; }
    }

    cout << E << '\n' << valasztott.size() << '\n';
    for (int k = 0; k < (int)valasztott.size(); ++k) {
        if (k) cout << ' ';
        cout << valasztott[k];
    }
    cout << '\n';
    return 0;
}