/*
Megoldás lényege:
Minden településre két feltételt kell vizsgálni: a Kukutyintól mért távolság legalább 100, a Piripócstól mért távolság pedig 100-nál kisebb.
Egyetlen bejárásban olvassuk be a távolságpárokat, és ha mindkét feltétel teljesül, a település sorszámát egy vektorba tesszük.
Mivel a településeket sorszám szerint dolgozzuk fel, a vektorban a sorszámok már növekvő sorrendben vannak.
A kiírásnál először a darabszám következik, utána a sorszámok, egy-egy szóközzel elválasztva.
Az időigény N-nel arányos, és N legfeljebb 100, így ez bőven belefér.
*/
/*
Hint 1: || Egy településre a két távolságot külön kell ellenőrizni: az egyik legalább 100, a másik szigorúan kisebb 100-nál. Figyelj arra, melyik összehasonlításban van egyenlőség. ||
Hint 2: || Egyetlen for-ciklussal haladj a települések között, a sorszámot 1-től számold, és a feltételnek megfelelő sorszámokat gyűjtsd egy vektorba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> chosen;
    for (int i = 1; i <= n; ++i) {
        int from_kukutyin, from_piripocs;
        cin >> from_kukutyin >> from_piripocs;
        if (from_kukutyin >= 100 && from_piripocs < 100) chosen.push_back(i);
    }

    cout << chosen.size();
    for (int town : chosen) cout << ' ' << town;
    cout << '\n';
    return 0;
}
