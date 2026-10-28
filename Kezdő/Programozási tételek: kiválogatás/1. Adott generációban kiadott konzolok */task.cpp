/*
Megoldás lényege:
A gyártók nevét a bemenet sorrendjében, 1-től sorszámozva tároljuk, így a feljegyzés első számából
közvetlenül megkapjuk a gyártó nevét. A feljegyzéseket egyesével olvassuk be, és ha a generáció a 7-es,
a gyártó nevét eltesszük a kiírandó listába. A lista sorrendje a feljegyzések bemeneti sorrendje lesz.
Mivel ugyanazon gyártóhoz és generációhoz legfeljebb egy feljegyzés tartozik, nincs duplikált kiírás.
Ha nincs 7. generációs feljegyzés, a kimenet „0 NINCS”. A neveket teljes sorként olvassuk, így a többszavas
nevek is helyesek. Az időigény a feljegyzések számával arányos, O(M).
*/
/*
Hint 1: || Nem kell rendezni és összegezni: minden feljegyzésnél elég megnézni, hogy a generáció a 7-es-e. ||
Hint 2: || A feljegyzés első száma a gyártó sorszáma. Ha a neveket 1-től kezdve egy vektorba teszed, a sorszámmal közvetlenül kikeresheted a nevet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> names(n + 1);
    for (int i = 1; i <= n; ++i) {
        getline(cin, names[i]);
        if (!names[i].empty() && names[i].back() == '\r') names[i].pop_back();
    }

    int m;
    cin >> m;
    vector<string> result;
    for (int i = 0; i < m; ++i) {
        int gy, gen, db;
        cin >> gy >> gen >> db;
        if (gen == 7) result.push_back(names[gy]);
    }

    if (result.empty()) {
        cout << "0 NINCS\n";
        return 0;
    }
    cout << result.size();
    for (const string& name : result) cout << ' ' << name;
    cout << '\n';
    return 0;
}
