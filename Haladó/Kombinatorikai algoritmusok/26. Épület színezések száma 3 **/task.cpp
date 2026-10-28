/*
Megoldás lényege:
Egy emelet színe csak az előző emelet színétől függ, ezért DP-vel számoljuk a sorozatokat az utolsó szín szerint: f, p, z jelöli az adott hosszúságú, F, P, illetve Z színnel végződő színezések számát.
A megengedett átmenetek: F után csak P jöhet, Z után nem jöhet P, P után bármi. Így F elé P vagy Z, P elé F vagy P, Z elé P vagy Z kerülhet, vagyis f' = p + z, p' = f + p, z' = p + z.
Egy emeletnél mindhárom érték 1, és ha f = p = z = x, akkor a következő lépésben mindhárom új érték 2x; így a három állapot minden lépésben egyenlő marad, a végeredmény 3·2^(N−1) modulo 20160109.
Az időigény O(N), a tárigény O(1).
*/
/*
Hint 1: || Egy emelet színe csak az előző emelet színétől függ, ezért elég az utolsó szín szerinti darabszámokat nyilvántartani. ||
Hint 2: || Írd fel, melyik szín elé mely szín kerülhet: F elé P vagy Z, P elé F vagy P, Z elé P vagy Z. Ebből három összegzés adódik, a végén a három állapot összege a válasz. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const int MOD = 20160109;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    long long f = 1, p = 1, z = 1;
    for (int i = 2; i <= n; ++i) {
        long long nf = (p + z) % MOD;
        long long np = (f + p) % MOD;
        long long nz = (p + z) % MOD;
        f = nf;
        p = np;
        z = nz;
    }

    cout << (f + p + z) % MOD << '\n';
    return 0;
}