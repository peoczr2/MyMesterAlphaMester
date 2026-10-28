/*
Megoldás lényege:
Minden helységre megszámoljuk, hány madárfajt láttunk ott (c_i). Egy adott fajnál csak azokat a helységeket nézzük, ahol előfordult (E > 0), és ezekben a többi jelen lévő fajok száma c_i − 1. Ezeket fajonként összegezzük, majd elosztjuk az előfordulások számával, így kapjuk a faj átlagos társaságszámát. A minimális átlagú fajt keressük; a törtek összehasonlításához keresztszorzást használunk, így nincs lebegőpontos hiba. Egyenlőség esetén a legkisebb sorszámú faj marad. Az időigény O(M·N), ami a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Egy faj „társaságát” csak azokban a helységekben érdemes vizsgálni, ahol a faj ténylegesen előfordult (E > 0). ||
Hint 2: || Helységenként számold meg, hány faj volt jelen, majd fajonként gyűjtsd össze a többi jelen lévő fajok számát és az előfordulások számát. Az átlagok összehasonlításához egész számokat használj (keresztszorzás), ne lebegőpontos törtet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> e(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> e[i][j];

    // cnt[i]: a(z) i-edik helységben jelen lévő fajok száma
    vector<int> cnt(m, 0);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (e[i][j] > 0) cnt[i]++;

    // sum[j]: a j-edik faj előfordulásainál a többi jelen lévő fajok száma összesen
    // occ[j]: a j-edik faj előfordulásainak (E > 0 helységek) száma
    vector<long long> sum(n, 0), occ(n, 0);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (e[i][j] > 0) {
                sum[j] += cnt[i] - 1;
                occ[j]++;
            }

    int best = -1;
    for (int j = 0; j < n; j++) {
        if (occ[j] == 0) continue;  // soha nem figyeltük meg, nem értékelhető
        // sum[j]/occ[j] < sum[best]/occ[best]  <=>  sum[j]*occ[best] < sum[best]*occ[j]
        if (best == -1 || sum[j] * occ[best] < sum[best] * occ[j])
            best = j;
    }
    if (best == -1) best = 0;  // egyik fajt sem figyelték meg

    cout << best + 1 << "\n";
    return 0;
}
