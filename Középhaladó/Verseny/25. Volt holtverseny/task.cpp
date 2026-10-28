/*
Megoldás lényege:
Minden versenyen először összegyűjtjük a minimumot elérő pontszámokat, és megkeressük köztük a legnagyobbat. Akkor van holtverseny az első helyen, ha ez a maximum legalább a verseny minimumával egyezik, és legalább két tanuló éri el. Ha senki nem érte el a minimumot, a versenyen nincs első hely, így holtverseny sincs. A holtversenyes versenyek sorszámait sorrendben gyűjtjük, majd az elején kiírjuk a darabszámukat. Minden versenyt egyszer dolgozunk fel, így az időigény O(N·M), ami a korlátok mellett elhanyagolható.
*/
/*
Hint 1: || Egy versenyen akkor van holtverseny az első helyen, ha a minimumot elérő tanulók közül a legjobb pontszámot legalább két tanuló éri el. ||
Hint 2: || Versenyenként keresd meg a minimumot elérő pontok maximumát, majd számold meg, hányan érték el pontosan ezt. Ha a darabszám legalább kettő, a verseny sorszámát mentsd el. ||
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

    vector<int> ties;
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        vector<int> score(ind);
        int top = -1;
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            score[j] = p;
            if (p >= mini[i]) {
                top = max(top, p);
            }
        }
        if (top < 0) {
            continue;  // senki nem érte el a minimumot, nincs első hely
        }
        int cnt = count(score.begin(), score.end(), top);
        if (cnt >= 2) {
            ties.push_back(i + 1);
        }
    }

    cout << ties.size();
    for (int x : ties) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
