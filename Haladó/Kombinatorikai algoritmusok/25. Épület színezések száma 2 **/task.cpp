/*
Megoldás lényege:
Az emeleteket alulról felfelé építjük, és a következő emelet megengedett színe csak
az előző emelet színétől függ. Piros után csak fehér állhat, zöld után nem állhat
zöld, fehér után bármi állhat. Ezért elég három számot nyilvántartani: hány
megfelelő színezés végződik fehér, piros, illetve zöld emelettel. Egy új emelet
értékei ezekből egy-egy összeadással számolhatók, a számokat MOD 20160109 szerint
tartjuk. Időigény O(N), memória O(1).
*/
/*
Hint 1: || A következő emelet megengedett színe csak az utolsó emelet színétől függ. Ezért nem kell a teljes sorozatot tárolni, elég az utolsó szín szerinti darabszámokat követni. ||
Hint 2: || Legyen f, p, z az i emeletes, megfelelő színezések száma, amelyek utolsó emelete fehér, piros, illetve zöld. Ekkor f' = f + p + z, p' = f + z, z' = f, kezdetben f = p = z = 1. A végén a három érték összege adja a választ mod 20160109. ||
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
        long long nf = (f + p + z) % MOD;
        long long np = (f + z) % MOD;
        long long nz = f % MOD;
        f = nf;
        p = np;
        z = nz;
    }

    cout << (f + p + z) % MOD << '\n';
    return 0;
}