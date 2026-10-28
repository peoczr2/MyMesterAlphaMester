/*
Megoldás lényege:
A csúcs definíciója a teljes mérési sorozatra vonatkozik, ezért először egy 0/1 tömbbel megjelöljük a csúcsokat (az első és az utolsó mérés biztosan nem csúcs). Ezután prefixösszeg-tömböt készítünk, így bármely [A, B] szakasz csúcsszáma egy kivonással kapható meg: pref[B] - pref[A-1], és a két végpont is beleszámít. Az összes A kezdőpontot végigpróbáljuk, B = A + K - 1 mellett, és a legtöbb csúcsot tartalmazó szakasz kezdetét tartjuk meg (szigorú összehasonlítással, így a legkisebb ilyen A marad). Ha nincs csúcs, a kimenet -1 -1. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Egy mérés csúcs-e, az csak a szomszédos mérésektől függ, ezért minden csúcsot egyszer, előre megjelölhetsz. Az első és az utolsó mérés nem lehet csúcs. ||
Hint 2: || Készíts prefixösszeget a csúcsok 0/1 tömbjéből, így egy [A, B] szakaszban lévő csúcsok száma egy kivonással megkapható. Ügyelj arra, hogy a szakasz két végpontja is beleszámít. ||
Hint 3: || Az A kezdőpontot 1-től N-K+1-ig végigpróbálva B = A + K - 1, és a csúcsszám pref[B] - pref[A-1]. Tartsd nyilván a legnagyobb értéket és a hozzá tartozó A-t; ha a maximum 0, a kimenet -1 -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> m(n + 1);
    for (int i = 1; i <= n; ++i) cin >> m[i];

    vector<int> csucs(n + 1);
    for (int i = 2; i <= n - 1; ++i) {
        if (m[i] > m[i - 1] && m[i] > m[i + 1]) csucs[i] = 1;
    }

    vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) pref[i] = pref[i - 1] + csucs[i];

    int legjobb = 0;
    int kezd = -1;
    for (int a = 1; a + k - 1 <= n; ++a) {
        int veg = a + k - 1;
        int darab = pref[veg] - pref[a - 1];
        if (darab > legjobb) {
            legjobb = darab;
            kezd = a;
        }
    }

    if (legjobb == 0) cout << -1 << ' ' << -1 << '\n';
    else cout << kezd << ' ' << kezd + k - 1 << '\n';
    return 0;
}
