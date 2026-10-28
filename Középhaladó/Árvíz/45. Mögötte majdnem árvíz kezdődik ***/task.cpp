/*
Megoldás lényege:
Egy i pont (2 ≤ i ≤ N−1) esetén az előzőhöz képest nőtt d = A[i] − A[i−1]. Ha a mögötte levő pont vízszintje ugyanennyivel nőne a pont szintjéhez képest, az A[i] + d lenne, és ez árvíz, ha meghaladja a 800 cm-t. A feladat szerint az i pontnak árvízmentesnek kell lennie, és a mögötte levő pont most is árvízmentes, ezért a feltétel: A[i] ≤ 800, A[i+1] ≤ 800 és A[i] + (A[i] − A[i−1]) > 800. Az első pontnak nincs előzője, az utolsónak nincs mögötte pontja, így ezeket nem vizsgáljuk. A pontok sorszámai a bejárás miatt már növekvő sorrendben jönnek ki. Egy bejárással, O(N) időben megoldható.
*/
/*
Hint 1: || Vizsgáld a pontokat egyenként, és csak olyan pont jöhet szóba, amelynek van előzője és mögötte levő pontja, és maga árvízmentes. ||
Hint 2: || Számold ki, mennyi a pont növekedése az előzőhöz képest: d = A[i] − A[i−1]. Ezzel a mögötte levő pont hipotetikus vízszintje A[i] + d lenne, ha ugyanennyivel nőne a pont szintjéhez képest. ||
Hint 3: || A pont akkor jó, ha a hipotetikus szint 800 cm fölé kerül, miközben a mögötte levő pont tényleges szintje még 800 cm alatt vagy azon van. Egyetlen bejárásban, i = 2-től N−1-ig vizsgáld meg a pontokat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 2, 0);  // 1-től indexelve
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> eredmeny;
    for (int i = 2; i < n; i++) {
        // i árvízmentes, a mögötte levő pont is árvízmentes, és a hipotetikus szint árvíz lenne
        if (a[i] <= 800 && a[i + 1] <= 800 && a[i] + (a[i] - a[i - 1]) > 800)
            eredmeny.push_back(i);
    }

    // 1. sor: a pontok darabszáma; ha nincs, csak ez a sor marad
    cout << eredmeny.size() << '\n';
    for (size_t i = 0; i < eredmeny.size(); i++) {
        if (i) cout << ' ';
        cout << eredmeny[i];
    }
    if (!eredmeny.empty()) cout << '\n';
    return 0;
}
