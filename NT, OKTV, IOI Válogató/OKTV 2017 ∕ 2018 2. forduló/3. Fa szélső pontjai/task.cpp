/*
Megoldás lényege:
Egy fa szélső pontja az a pont, amely a saját szintjén a legbaloldalibb vagy a legjobboldalibb. Ha egy szinten csak egy pont van, az egyszerre mindkettő, de csak egyszer kell kiírni.
A fát szélességi bejárással, szintenként dolgozzuk fel: a gyökértől indulunk, és az aktuális szint pontjainak gyerekeit sorban egymás után fűzzük a következő szinthez.
Mivel a gyerekek a bemenetben balról jobbra vannak felsorolva, a bejárás sorrendje is balról jobbra halad, így minden szint első pontja a bal szélső, utolsó pontja a jobb szélső pont.
A bal szélek felülről lefelé, majd a jobb szélek felülről lefelé kerülnek kiírásra; az idő O(N), a kiírt M a szélső pontok száma.
*/
/*
Hint 1: || Egy szinten a szélső pontok a legbaloldalibb és a legjobboldalibb pontok. Ha a szinten csak egy pont van, akkor ez a két pont ugyanaz, és egyszer kell kiírni. ||
Hint 2: || Haladj szintenként a gyökértől lefelé: tartsd nyilván az aktuális szint pontjait, ahol a sorrend már balról jobbra van. Így minden szint első és utolsó eleme szélső pont. ||
Hint 3: || A következő szint úgy áll elő, hogy az aktuális szint pontjainak gyerekeit sorban, egymás után fűzöd össze. A gyerekek felsorolása minden pontnál a 0 szám előtt ér véget. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> ch(n + 1);
    for (int i = 1; i <= n; i++) {
        int c;
        while (cin >> c && c != 0) ch[i].push_back(c);
    }

    // Szintenkénti bejárás: minden szint első (bal) és utolsó (jobb) pontja szélső pont
    vector<int> lefts, rights;
    vector<int> cur = {1};
    while (!cur.empty()) {
        lefts.push_back(cur.front());
        if (cur.back() != cur.front()) rights.push_back(cur.back());

        vector<int> nxt;
        for (int u : cur) {
            for (int v : ch[u]) nxt.push_back(v);
        }
        cur.swap(nxt);
    }

    // Előbb a bal szélek felülről lefelé, utána a jobb szélek felülről lefelé
    vector<int> res = lefts;
    res.insert(res.end(), rights.begin(), rights.end());

    cout << res.size() << "\n";
    for (size_t i = 0; i < res.size(); i++) {
        cout << res[i] << (i + 1 < res.size() ? ' ' : '\n');
    }
    return 0;
}
