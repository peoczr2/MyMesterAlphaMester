/*
Megoldás lényege:
Napról napra haladunk, és minden nap elején beállítjuk az aznapi árakat. A bemenetben a bejegyzések napok szerint növekvő sorrendben érkeznek, ezért egy mutatóval végig lehet menni rajtuk. Az árak egy tömbben vannak tárolva, a 0 jelöli, ha az árus még nem árul almát. Ha legalább K árus árul, a (ár, sorszám) párokat rendezzük: az első K elem lesz a legolcsóbb K árus, a holtversenyt pedig automatikusan a kisebb sorszám dönti el. A kiválasztott sorszámokat növekvő sorrendben írjuk ki, különben egyetlen 0 kerül a sorba.
Egy nap O(M log M) munka, így az összes nap O(N · M log M), ami M ≤ 100 és N ≤ 1000 mellett bőven belefér az időkorlátba.
*/
/*
Hint 1: || Nem kell minden napra újra az egész állapotot felépíteni: az árak csak akkor változnak, amikor a bemenetben az adott napra bejegyzés van. Elég egy tömb, amelyben minden árus utolsó ismert ára szerepel (0, ha még nem árult). ||
Hint 2: || Egy napon a már áruló árusokat rendezd (ár, sorszám) párok szerint: így az azonos áraknál a kisebb sorszám kerül előre. Ha kevesebb mint K árus árul, a sor egyetlen 0; különben a K első sorszámát kell növekvő sorrendben kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, k, a;
    cin >> m >> n >> k >> a;

    vector<int> nap(a), sorszam(a), ar(a);
    for (int i = 0; i < a; i++) {
        cin >> nap[i] >> sorszam[i] >> ar[i];
    }

    // aktualis[s]: az s. árus aktuális ára (0: még nem árul)
    vector<int> aktualis(m + 1, 0);
    int mutato = 0;

    for (int i = 1; i <= n; i++) {
        while (mutato < a && nap[mutato] <= i) {
            aktualis[sorszam[mutato]] = ar[mutato];
            mutato++;
        }

        vector<pair<int, int>> arusok;  // (ár, sorszám)
        for (int s = 1; s <= m; s++) {
            if (aktualis[s] > 0) {
                arusok.push_back({aktualis[s], s});
            }
        }

        if ((int)arusok.size() < k) {
            cout << 0 << '\n';
            continue;
        }

        sort(arusok.begin(), arusok.end());
        vector<int> valasz;
        for (int j = 0; j < k; j++) {
            valasz.push_back(arusok[j].second);
        }
        sort(valasz.begin(), valasz.end());

        for (int j = 0; j < k; j++) {
            cout << valasz[j] << (j + 1 < k ? ' ' : '\n');
        }
    }

    return 0;
}
