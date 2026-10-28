/*
Megoldás lényege:
Versenyenként külön dolgozzuk fel a résztvevőket: kiválogatjuk azokat, akik elérték a verseny minimális pontszámát, és párokat (pontszám, sorszám) készítünk belőlük. Ezt a listát pontszám szerint csökkenő, azonos pontszám esetén sorszám szerint növekvő sorrendbe rendezzük, így a döntetlenek kezelése egyetlen összehasonlító függvényben van. A kiírás sorát a kiválogatott tanulók K számával kezdjük, utána jönnek a sorszámok a rendezett sorrendben. Egy verseny rendezése O(K log K), az összes versenyé O(M·N log N), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Minden versenyt külön kell kezelni, és csak azokat a tanulókat szabad felvenni a rangsorba, akik elérték az adott verseny minimumát. ||
Hint 2: || Készíts (pont, sorszám) párokat, és rendezd őket úgy, hogy az elsődleges szempont a pontszám csökkenő, a másodlagos a sorszám növekvő legyen. A kiírás előtt a darabszámot is add meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> mini(m);
    for (int i = 0; i < m; i++) {
        cin >> mini[i];
    }

    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        vector<pair<int, int>> ok;  // (pont, sorszám)
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            if (p >= mini[i]) {
                ok.push_back({p, s});
            }
        }
        sort(ok.begin(), ok.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) {
                return a.first > b.first;
            }
            return a.second < b.second;
        });

        cout << ok.size();
        for (auto [p, s] : ok) {
            cout << ' ' << s;
        }
        cout << '\n';
    }
    return 0;
}
