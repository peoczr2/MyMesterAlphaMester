/*
Megoldás lényege:
Egy versenyző helyezése a lövése befejezésekor 1 plusz azoknak a száma, akik korábban nála több pontot értek el.
A holtversenyesek száma 1 plusz a korábban pontosan ugyanannyit elért versenyzők száma (a későbbiek most még nem számítanak).
Mivel a pontszám legfeljebb M = 1000, egy Fenwick-fában (bináris indexelt fában) tartjuk, hány korábbi versenyző érte el az egyes pontszámokat.
Így a "nála nagyobb" darabszám egy prefixösszeg-lekérdezéssel O(log M) alatt megadható, az azonos pontszámúak száma pedig egy tömbből olvasható ki.
Az időigény O(N log M), a memóriaigény O(M).
*/
/*
Hint 1: || Egy versenyző helyezése csak a korábban lövő versenyzőktől függ: azok közül minden olyan, aki nála több pontot ért el, egy hellyel előrébb sorolja. ||
Hint 2: || Mivel a pontszám legfeljebb M = 1000, pontszámonként tarts nyilván, hányan értek el eddig az adott pontot. A nála nagyobb pontszámok darabszámát Fenwick-fával (bináris indexelt fával) kérdezd le. ||
*/
#include <bits/stdc++.h>
using namespace std;

int m;
vector<int> fa;

void add(int i) {
    for (; i <= m; i += i & -i) fa[i]++;
}

int prefixSum(int i) {
    int s = 0;
    for (; i > 0; i -= i & -i) s += fa[i];
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n >> m;
    fa.assign(m + 1, 0);
    vector<int> cnt(m + 1, 0);
    int seen = 0;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        int higher = seen - prefixSum(p);
        int same = cnt[p];
        cout << higher + 1 << " " << same + 1 << "\n";
        add(p);
        cnt[p]++;
        seen++;
    }
    return 0;
}
