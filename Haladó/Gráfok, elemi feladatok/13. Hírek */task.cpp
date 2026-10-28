/*
Megoldás lényege:
Az üzenetküldés irányított gráfon elérhetőségi kérdés: A-ból B-be akkor juthat el hír, ha van irányított út A-tól B-ig.
Warshall-algoritmussal minden tanulóra kiszámoljuk, hogy kit ér el. Mivel N ≤ 400, a sorokat bitset-ként tároljuk, így a lezárás gyorsan elkészül.
A kérdésre: az (i, j) pár akkor jó, ha i eléri j-t és j is eléri i-t, vagyis egy erősen összefüggő komponensben vannak. Ezeket i < j párként számoljuk.
A kérdésre: az a tanuló jó, akinek a lezárásában N darab 1-es van. A főátlót (saját magát) előre 1-re állítjuk, hogy ez egyszerűen ellenőrizhető legyen.
Időigény: O(N^3 / 64), ami N = 400 esetén bőven belefér a 0,1 másodperces korlátba.
*/
/*
Hint 1: || Az üzenetküldés láncolható: ha A tud hírt küldeni B-nek, B pedig C-nek, akkor A is el tud juttatni hírt C-nek. Ez tranzitív lezárás kérdés, nem kell minden utat külön végigjárni. ||
Hint 2: || Tárold minden tanulóra bitsetben, kit ér el. A Warshall-algoritmus a k köztes csúcsra: ha i eléri k-t, akkor i sorát vagy-old (|=) k sorával. ||
Hint 3: || Az A kérdésnél csak i < j párokat nézz, és akkor számolj, ha i eléri j-t és j is eléri i-t. A B kérdésnél azt a sort keresd, amelyben N darab 1-es van; a főátlót előre állítsd 1-re. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<bitset<400>> reach(n);
    for (int i = 0; i < n; i++) {
        reach[i][i] = 1;
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            if (c == 'i')
                reach[i][j] = 1;
        }
    }

    // Warshall-algoritmus: ha i eléri k-t, akkor i eléri mindent, amit k elér
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (reach[i][k])
                reach[i] |= reach[k];

    long long pairs = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (reach[i][j] && reach[j][i])
                pairs++;

    int everyone = 0;
    for (int i = 0; i < n; i++)
        if (reach[i].count() == (size_t)n)
            everyone++;

    cout << pairs << "\n" << everyone << "\n";
    return 0;
}
