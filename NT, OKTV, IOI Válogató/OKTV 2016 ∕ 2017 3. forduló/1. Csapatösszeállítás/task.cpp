/*
Megoldás lényege:
A csapatot a tagok növekvő sorszámú sorozatával írjuk le, ezek lexikografikus sorrendjét követjük.
A rákövetkező csapathoz a jobbról első olyan tagot keressük, amely még nagyobb értéket vehet fel
(az i-edik tag legfeljebb N-M+i lehet); ezt eggyel növeljük, a mögötte lévő tagok pedig egymás utáni
számok lesznek. Az előző csapathoz hasonlóan a jobbról első olyan tagot keressük, amelyet még eggyel
csökkenteni lehet (x_i-1 > x_{i-1}), ezt csökkentjük, a mögötte lévő tagok pedig a lehető legnagyobb
értéket kapják (N-M+j). Ha nincs ilyen tag, a sorozat az utolsó, illetve az első, így ciklikusan
az első a rákövetkező, az utolsó az előző csapat. Az időigény O(M).
*/
/*
Hint 1: || Lexikografikus sorrendben a rákövetkező sorozat a lehető leghosszabb közös kezdetet tartja meg. Keresd meg a jobb szélső olyan tagot, amelyet még lehet változtatni. ||
Hint 2: || Az i-edik tag legnagyobb lehetséges értéke N-M+i. Ha x_i ennél kisebb, akkor x_i+1 a rákövetkező sorozat i-edik tagja, a többi tag pedig eggyel nagyobb számokból, egymás után következik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> x(m + 1, 0);  // x[1..m] a csapat tagjai, x[0] = 0
    for (int i = 1; i <= m; ++i) cin >> x[i];

    // Rákövetkező csapat
    vector<int> nxt(m + 1);
    int i = m;
    while (i >= 1 && x[i] == n - m + i) --i;
    if (i == 0) {
        for (int j = 1; j <= m; ++j) nxt[j] = j;  // az utolsó után ciklikusan az első jön
    } else {
        for (int j = 1; j < i; ++j) nxt[j] = x[j];
        nxt[i] = x[i] + 1;
        for (int j = i + 1; j <= m; ++j) nxt[j] = nxt[j - 1] + 1;
    }

    // Előző csapat
    vector<int> prv(m + 1);
    i = m;
    while (i >= 1 && x[i] - 1 == x[i - 1]) --i;
    if (i == 0) {
        for (int j = 1; j <= m; ++j) prv[j] = n - m + j;  // az első előtt ciklikusan az utolsó áll
    } else {
        for (int j = 1; j < i; ++j) prv[j] = x[j];
        prv[i] = x[i] - 1;
        for (int j = i + 1; j <= m; ++j) prv[j] = n - m + j;
    }

    for (int j = 1; j <= m; ++j) cout << nxt[j] << (j < m ? ' ' : '\n');
    for (int j = 1; j <= m; ++j) cout << prv[j] << (j < m ? ' ' : '\n');
    return 0;
}
