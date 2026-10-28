/*
Megoldás lényege:
Minden versenyző csak egyszer ugrik, így az ugrása után a pontszáma már végleges. Hó Elemér helyezése egy ugrás után 1 + azon versenyzők száma, akiknek pontszáma szigorúan nagyobb az övénél, az egyenlő pontszám nem előz meg.
A számlálást Hó Elemér saját, M. ugrásától kezdjük és az N. ugrásig folytatjuk. Elég egyetlen léptetett számláló: ha egy újabb ugró szigorúan jobb pontszámot ért el, eggyel növeljük, majd a kapott helyezés gyakoriságát a tömbben eggyel emeljük.
Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Hó Elemér helyezése csak a saját ugrása után számít, és a helyezést mindig az addig ugrottak pontszámai határozzák meg. Egyetlen számlálóval elég nyilvántartani, hány nála szigorúan jobb pontszámú versenyző van. ||
Hint 2: || A helyezés a számláló + 1. Egy tömbben (indexe a helyezés, 1-től N-ig) számold, hányszor fordult elő az adott helyezés, és ezt csak az M. ugrástól kezdve tedd. Figyelj arra, hogy az egyenlő pontszám nem számít jobbnak. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];

    vector<int> helyezes(n + 2, 0);  // helyezes[r]: hányszor állt Hó Elemér az r. helyen
    int jobb = 0;                    // az eddig ugrottak közül hányan vannak szigorúan Hó Elemér előtt
    for (int i = 1; i <= n; i++) {
        if (i != m && p[i] > p[m]) jobb++;
        if (i >= m) helyezes[jobb + 1]++;
    }

    for (int r = 1; r <= n; r++) {
        cout << helyezes[r];
        cout << (r == n ? '\n' : ' ');
    }
    return 0;
}
