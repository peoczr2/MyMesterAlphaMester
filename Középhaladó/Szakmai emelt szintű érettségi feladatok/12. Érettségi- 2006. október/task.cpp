/*
Megoldás lényege:
Beolvassuk a diákok számát és a keresett tárgy nevét, majd soronként a diák vezetéknevét, keresztnevét és tárgyát. Ha a diák tárgya egyezik a keresett tárggyal, a teljes nevét (vezetéknév és keresztnév szóközzel) egy vektorba tesszük. Ezután a vektort ábécérendbe rendezzük és soronként kiírjuk. Ha a vektor üres, a Nincs szót írjuk ki. Az időigény O(N log N), a rendezés miatt.
*/
/*
Hint 1: || Minden diák adata három szó: vezetéknév, keresztnév, tárgy. A cin >> művelettel szavanként olvasható, így a sorok határaival nem kell külön foglalkozni. ||
Hint 2: || Az egyező diákok teljes nevét (vezetéknév + szóköz + keresztnév) tárold egy string-vektorban, majd rendezd. Ha a vektor a végén üres, a Nincs szót írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string targy;
    cin >> n >> targy;
    vector<string> nevsor;
    for (int i = 0; i < n; i++) {
        string vezeteknev, keresztnev, t;
        cin >> vezeteknev >> keresztnev >> t;
        if (t == targy) {
            nevsor.push_back(vezeteknev + " " + keresztnev);
        }
    }
    sort(nevsor.begin(), nevsor.end());
    if (nevsor.empty()) {
        cout << "Nincs" << endl;
    } else {
        for (const string &s : nevsor) {
            cout << s << "\n";
        }
    }
    return 0;
}
