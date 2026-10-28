/*
Megoldás lényege:
Az első képet egy N×M-es tömbbe olvassuk, a második képet pedig soronként, az azonos helyen lévő képpontokat összehasonlítva. Minden eltérő képpontnál frissítjük a legkisebb és legnagyobb eltérő sorindexet, valamint a legkisebb és legnagyobb eltérő oszlopindexet. A négy szélső érték adja a keresett téglalap bal felső és jobb alsó sarkát, 1-től indexelve. Az algoritmus egyetlen végigolvasással, O(N·M) időben működik, ami legfeljebb 10^6 képpontnál elég gyors.
*/
/*
Hint 1: || Nem kell a teljes képet másképp elemezni: elég megkeresni a legszélső olyan sort és oszlopot, ahol a két kép legalább egy képpontban eltér. ||
Hint 2: || Tárold az első képet, a másodikat olvasd be soronként, és minden azonos helyen lévő pár összehasonlításakor, ha különböznek, frissítsd a felső, alsó, bal és jobb határt. A kiírásnál a 0-tól számolt indexekhez adj 1-et. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> elso(n * m);
    for (int &x : elso) cin >> x;

    int felso = n, also = -1, bal = m, jobb = -1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int x;
            cin >> x;
            if (x != elso[i * m + j]) {
                felso = min(felso, i);
                also = max(also, i);
                bal = min(bal, j);
                jobb = max(jobb, j);
            }
        }

    cout << felso + 1 << ' ' << bal + 1 << ' ' << also + 1 << ' ' << jobb + 1 << '\n';
}
