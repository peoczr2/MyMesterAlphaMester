/*
Megoldás lényege:
A csapatok lexikografikus sorrendben követik egymást, ezért a következő csapatot
úgy kapjuk, hogy a jobb szélső olyan tagot keressük, amelyet még eggyel
növelhetünk. Ezt megnöveljük, a mögötte lévő tagokat pedig szorosan egymás utáni
számokkal töltjük ki.
Az előző csapat ugyanilyen módon, fordított irányban adódik: a jobb szélső olyan
tagot keressük, amelyet még eggyel csökkenthetünk, ezt csökkentjük, a mögötte
lévő tagok pedig a lehető legnagyobb értékeket kapják.
Ha nincs ilyen tag, a sorrend ciklikus: az utolsó csapat rákövetkezője az első,
az első csapat megelőzője az utolsó. Mindkét keresés legfeljebb M pozíción
végigmegy, így az időigény O(M).
*/
/*
Hint 1: || Gondoljunk a számjegyes számok növelésére: a következő csapat a jobb
szélső elem növelésével keletkezik, és ha ez nem lehetséges, a tőle balra lévő
elemet próbáljuk növelni. Az előző csapat ugyanez csökkentéssel. ||
Hint 2: || Az i-edik (0-tól számozott) tag legnagyobb megengedett értéke
N-M+i+1. Keressük a jobb szélső olyan tagot, amely még nem érte el ezt: ezt
eggyel növelve a mögötte lévő tagok közvetlenül egymás utáni számok lesznek. Ha
nincs ilyen tag, az utolsó csapatról az elsőre ugrunk. ||
Hint 3: || Az előző csapatnál a jobb szélső olyan tag keresendő, amely nagyobb a
rá megengedett legkisebb értéknél (az előző tag + 1, az elsőnél 1). Ezt
csökkentve a mögötte lévő tagok a legnagyobb lehetséges értéket kapják. Ha nincs
ilyen tag, az első csapatról az utolsóra lépünk. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> a(m);
    for (int i = 0; i < m; ++i) cin >> a[i];

    vector<int> nxt = a;
    bool ok = false;
    for (int i = m - 1; i >= 0; --i) {
        int limit = n - m + i + 1;
        if (nxt[i] < limit) {
            ++nxt[i];
            for (int j = i + 1; j < m; ++j) nxt[j] = nxt[j - 1] + 1;
            ok = true;
            break;
        }
    }
    if (!ok) {
        for (int i = 0; i < m; ++i) nxt[i] = i + 1;
    }

    vector<int> prv = a;
    ok = false;
    for (int i = m - 1; i >= 0; --i) {
        int minVal = (i == 0 ? 1 : prv[i - 1] + 1);
        if (prv[i] > minVal) {
            --prv[i];
            for (int j = i + 1; j < m; ++j) prv[j] = n - (m - 1 - j);
            ok = true;
            break;
        }
    }
    if (!ok) {
        for (int i = 0; i < m; ++i) prv[i] = n - m + 1 + i;
    }

    for (int i = 0; i < m; ++i) {
        if (i) cout << ' ';
        cout << nxt[i];
    }
    cout << '\n';
    for (int i = 0; i < m; ++i) {
        if (i) cout << ' ';
        cout << prv[i];
    }
    cout << '\n';
    return 0;
}