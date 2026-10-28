/*
Megoldás lényege:
Egy N×M-es logikai táblázatban jelöljük be azokat a mezőket, amelyeket valamelyik lámpa bevilágít. Egy lámpa a helyétől mindkét irányba r = (H−1)/2 távolságra világít, így a bevilágított sorok és oszlopok egy-egy intervallumot alkotnak; ezeket a téglalap szélénél le kell vágni. Minden lámpánál ezt a legfeljebb H×H-s részt jelöljük be, végül a bejelöletlen mezőket számoljuk meg. Az időigény O(K·H²), ami a korlátok mellett legfeljebb körülbelül 10^7 lépés, a memóriaigény O(N·M).
*/
/*
Hint 1: || Nem kell külön számolni a négyzetek átfedéseit: elég egy N×M-es logikai tömb, amelybe minden lámpa területét bejelölöd, és a végén a bejelöletlen mezőket számolod. ||
Hint 2: || Egy S,O helyű lámpánál a bejelölendő sorok az [S−r, S+r], az oszlopok az [O−r, O+r] tartományba esnek, ahol r = (H−1)/2. Ezeket a határokat szűkítsd le 1-re és N-re, illetve 1-re és M-re, hogy ne lógjanak ki a téren. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k, h;
    cin >> n >> m >> k >> h;
    int r = (h - 1) / 2;
    vector<vector<bool>> vilagos(n + 1, vector<bool>(m + 1, false));
    for (int i = 0; i < k; i++) {
        int s, o;
        cin >> s >> o;
        for (int x = max(1, s - r); x <= min(n, s + r); x++)
            for (int y = max(1, o - r); y <= min(m, o + r); y++)
                vilagos[x][y] = true;
    }
    int sotet = 0;
    for (int x = 1; x <= n; x++)
        for (int y = 1; y <= m; y++)
            if (!vilagos[x][y]) sotet++;
    cout << sotet << "\n";
    return 0;
}
