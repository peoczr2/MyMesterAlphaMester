/*
Megoldás lényege:
A termelők helyét az előző távolságok összegzésével kapjuk meg. Ha a raktárt a j-edik termelő helyére építjük, minden i termelő a |x_i - x_j| * B_i költséggel járul hozzá, így a teljes költség a bal és a jobb oldali termelők hozzájárulásának összege. Ezt a bal oldali és a jobb oldali prefixösszegekkel minden j helyre konstans idő alatt kiszámolhatjuk, ezért a legkisebb költségű hely egy lineáris bejárással megtalálható. Az időigény O(N), és több azonos költségű hely esetén a legkisebb sorszámút írjuk ki.
*/
/*
Hint 1: || A szállítási költség a megtett út hossza szorozva a mennyiséggel, így a teljes költség a termelők hozzájárulásának összege. Ha a raktár helyét változtatod, az egyik oldalon lévő termelők közelebb, a másikon távolabb kerülnek; gondold végig, hogy egy adott hely két oldalának hozzájárulása hogyan írható fel. ||
Hint 2: || Számold ki a termelő helyeket az előző távolságok összegzésével, majd a mennyiségek és a hely-szorzat (hely * mennyiség) prefixösszegeit. Ezekkel minden j helyhez a bal és a jobb oldal hozzájárulása O(1) időben kiszámolható. ||
Hint 3: || A minimum ott van, ahol a bal oldali mennyiség először eléri a teljes mennyiség felét. Ezt nem kell külön megkeresned: ha minden helyre kiszámolod a költséget, a legkisebb érték magától kijön. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> x(n), b(n);
    long long pos = 0;
    for (int i = 0; i < n; i++) {
        long long dist;
        cin >> dist >> b[i];
        pos += dist;   // az első távolság 0, így x[0] = 0
        x[i] = pos;
    }

    // pw[k]: az első k termelő mennyiségének összege, px[k]: az első k termelő hely*mennyiség összege
    vector<long long> pw(n + 1, 0), px(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pw[i + 1] = pw[i] + b[i];
        px[i + 1] = px[i] + x[i] * b[i];
    }
    long long W = pw[n], TX = px[n];

    long long bestCost = -1;
    int bestIdx = 0;
    for (int j = 0; j < n; j++) {
        long long left = x[j] * pw[j] - px[j];
        long long right = (TX - px[j + 1]) - x[j] * (W - pw[j + 1]);
        long long cost = left + right;
        if (bestCost < 0 || cost < bestCost) {
            bestCost = cost;
            bestIdx = j;
        }
    }
    cout << bestCost << '\n' << bestIdx + 1 << '\n';
    return 0;
}
