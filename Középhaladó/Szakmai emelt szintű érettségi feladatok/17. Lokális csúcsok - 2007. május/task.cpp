/*
Megoldás lényege:
Egy elem akkor lokális csúcs, ha nagyobb mindkét közvetlen szomszédjánál, tehát a döntés csak a három szomszédos elemtől függ. A sorozatot tömbbe olvassuk, és az első és utolsó elemet kihagyva minden belső elemre megnézzük a két szomszédját. Egy elem ellenőrzése konstans idejű, így az összes elem vizsgálata O(N) időt igényel, ami N = 100 000 mellett messze a 0,1 másodperces limit alatt marad.
*/
/*
Hint 1: || Egy elem lokális csúcs-voltát csak a két szomszédja határozza meg, így nem kell minden elemnél a teljes sorozatot újra bejárni. ||
Hint 2: || Tárold a számokat tömbben, és a második elemtől az utolsó előttiig (0-indexelve az 1-től N-2-ig) nézd meg, hogy az aktuális elem nagyobb-e mindkét szomszédjánál. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> e(n);
    for (int i = 0; i < n; i++) cin >> e[i];

    int csucsok = 0;
    for (int i = 1; i + 1 < n; i++) {
        if (e[i] > e[i - 1] && e[i] > e[i + 1]) csucsok++;
    }
    cout << csucsok << "\n";
    return 0;
}
