/*
Megoldás lényege:
Egy napon egy település akkor „nyer”, ha a várt hőmérséklete szigorúan nagyobb minden más településénél, vagyis a nap maximumát egyedül éri el. Napról napra haladunk: megkeressük a nap legmagasabb hőmérsékletét, és azt, hányszor fordul elő. Ha pontosan egyszer, a település nyer, és a számlálóját eggyel növeljük. A végén a legtöbb nyert napot elérő, legkisebb sorszámú település a válasz; ha egyetlen nyerő nap sincs, a kimenet -1. A K korlát a feladat feltételében nem szerepel, ezért a program csak beolvassa. Az idő a hőmérsékletek számával arányos, vagyis O(N*M).
*/
/*
Hint 1: || A bemenetben egy sor egy település, egy oszlop pedig egy nap. Egy napot úgy vizsgálsz, hogy az adott oszlop összes értékét megnézed. ||
Hint 2: || Egy menetben nyilvántarthatod a nap eddigi legnagyobb hőmérsékletét, a hozzá tartozó település sorszámát és azt, hányszor fordult elő. Ha új, nagyobb érték jön, a számlálót újrakezded. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    // h[i][j]: az i. település várt hőmérséklete a j. napon
    vector<vector<int>> h(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> h[i][j];
        }
    }

    // nyert[i]: hány napon nyert az i. település
    vector<int> nyert(n, 0);
    for (int j = 0; j < m; j++) {
        int legnagyobb = -1, hely = -1, darab = 0;
        for (int i = 0; i < n; i++) {
            if (h[i][j] > legnagyobb) {
                legnagyobb = h[i][j];
                hely = i;
                darab = 1;
            } else if (h[i][j] == legnagyobb) {
                darab++;
            }
        }
        if (darab == 1) {
            nyert[hely]++;
        }
    }

    int legtobb = 0, valasz = -1;
    for (int i = 0; i < n; i++) {
        if (nyert[i] > legtobb) {
            legtobb = nyert[i];
            valasz = i + 1;
        }
    }

    cout << valasz << "\n";
    return 0;
}
