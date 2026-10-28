/*
Megoldás lényege:
Az induló állomástól mért távolságokat prefixösszegként számoljuk: a 0. állomás távolsága 0, az i. megálló távolsága pedig az előző távolság plusz T_i. A teljes útvonal hossza D az utolsó távolság. Egy i. megálló akkor van közelebb az induló állomáshoz, mint a végállomáshoz, ha d_i < D - d_i, vagyis 2 * d_i < D. A távolságok szigorúan nőnek, így a feltételnek megfelelő legnagyobb sorszámú megálló a legtávolabbi. Ennek sorszámát, a d_i és a D - d_i távolságot írjuk ki. Az időigény O(N).
*/
/*
Hint 1: || A távolságot az induló állomástól érdemes számolni: egy megálló távolsága az induló állomástól az addigi T_i értékek összege. A teljes hossz az utolsó megálló távolsága. ||
Hint 2: || A teljes hosszt előbb kell tudnod, ezért az összes adatot olvasd be, és közben tárold el a távolságokat. Egy megálló akkor felel meg, ha a távolsága az induló állomástól kisebb, mint a végállomástól mért távolsága. A megfelelők közül a legutolsót keresd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    // pos[i]: az i. megálló távolsága az induló állomástól, pos[0] = 0
    vector<long long> pos(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long dist, arr, dep;
        cin >> dist >> arr >> dep;
        pos[i] = pos[i - 1] + dist;
    }
    long long total = pos[n];

    // a legnagyobb sorszámú (egyben a legtávolabbi) megálló, amely közelebb van az induló állomáshoz;
    // ha nincs ilyen, a 0. (induló) állomás marad, mert ott a távolság 0
    int best = 0;
    for (int i = 0; i <= n; i++) {
        if (2 * pos[i] < total) {
            best = i;
        }
    }

    cout << best << ' ' << pos[best] << ' ' << total - pos[best] << '\n';
    return 0;
}
