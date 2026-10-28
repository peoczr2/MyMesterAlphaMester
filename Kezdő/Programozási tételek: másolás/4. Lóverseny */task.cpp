/*
Megoldás lényege:
Három esetet kell megkülönböztetni: az 50-nél nem nagyobb erősségűek 0 métert indulnak, a 90-nél nagyobbak 45 métert. Az 51 és 90 közötti erősségek 5 pontos csoportokba esnek, és az első csoport 5 métert, a második 10 métert kap, és így tovább. A csoport sorszámát egész osztással kapjuk meg: ha a csoportokat 1-től számozzuk, a sorszám (E - 51) / 5 + 1, a távolság pedig ennek ötszöröse. Minden lóra állandó idejű munka kell, így az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Három külön ágat kell kezelni: az 50-nél nem nagyobb erősségek fix 0 métert, a 90-nél nagyobbak fix 45 métert kapnak, csak a közbülső tartomány igényel számolást. ||
Hint 2: || Az 51-től 90-ig tartó értékeket 5-ösével csoportosítsd: ha az erősséget 51-gyel csökkented, majd 5-tel egész osztod, megkapod a csoport sorszámát 0-tól kezdve. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int e;
        cin >> e;

        int dist;
        if (e <= 50) {
            dist = 0;
        } else if (e > 90) {
            dist = 45;
        } else {
            dist = ((e - 51) / 5 + 1) * 5;
        }

        cout << dist << "\n";
    }
    return 0;
}
