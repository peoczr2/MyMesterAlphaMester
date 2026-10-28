/*
Megoldás lényege:
A kérdés nem a sorozat pozícióira, hanem a számok értékére vonatkozik: egy [A,B] intervallumban azokat a különböző értékeket kell megszámolni, amelyek a sorsolásban legalább egyszer előfordultak.
Ezért először egy jelölőtömbben megjelöljük, mely értékek szerepeltek. Ezután prefixösszeget építünk erre a tömbre: az [A,B] intervallum válasza a B-ig és az A-1-ig tartó prefixösszegek különbsége. Az időigény O(N + K + maximális érték), ami 100000-ig bőven belefér az időlimitbe.
*/
/*
Hint 1: || Figyelj a feladat szövegére: a kérdés a számok értékére vonatkozik, nem a sorozatbeli pozíciókra. A példa magyarázata is ezt mutatja. ||
Hint 2: || Jelöld meg egy tömbben, mely értékek fordultak elő legalább egyszer, majd készíts prefixösszeget ezen a tömbön. Egy kérdés válasza két prefixösszeg különbsége. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 100000;

int main() {
    int n, m;
    cin >> n >> m;

    // van[v] = 1, ha a v szám szerepelt a sorsolásban
    vector<int> van(MAXV + 1, 0);
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        van[p] = 1;
    }

    // pref[v]: a sorsolt különböző számok száma az 1..v tartományban
    vector<int> pref(MAXV + 1, 0);
    for (int v = 1; v <= MAXV; v++) {
        pref[v] = pref[v - 1] + van[v];
    }

    int k;
    cin >> k;
    while (k--) {
        int a, b;
        cin >> a >> b;
        cout << pref[b] - pref[a - 1] << "\n";
    }
    return 0;
}
