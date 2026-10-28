/*
Megoldás lényege:
Az {1,…,2N} számokat úgy írjuk a 2×N-es táblázatba, hogy a sorokban és az oszlopokban is növekedjenek. Olvassuk a számokat 1-től 2N-ig, és mindegyiket az első vagy a második sorba tesszük. Az oszlopok növekedése pontosan azt jelenti, hogy bármely prefixben az első sorban legalább annyi szám van, mint a másodikban, vagyis ezek zárójelezések (Dyck-utak); számuk a Catalan-szám: C_N.
A Catalan-számok a C_0 = 1, C_n = Σ_{j=0}^{n-1} C_j·C_{n-1-j} rekurzióval számolhatók. Mivel N ≤ 20, C_20 ≈ 6,6·10^9 még 64 bites egészbe is elfér, az időigény O(N²).
*/
/*
Hint 1: || Olvasd a számokat 1-től 2N-ig, és mindegyiket tedd az első vagy a második sorba. Mikor kerülhet egy szám a második sorba, és mit kell ehhez a felette lévő számnak teljesítenie? ||
Hint 2: || Az elrendezések száma egy ismert sorozat (Catalan-szám): C_0 = 1 és C_n = Σ_{j=0}^{n-1} C_j·C_{n-1-j}. Ezt O(N²) időben, 64 bites egésszel kiszámolhatod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> cat(n + 1, 0);
    cat[0] = 1;
    for (int i = 1; i <= n; ++i) {
        __int128 sum = 0;
        for (int j = 0; j < i; ++j) sum += (__int128)cat[j] * cat[i - 1 - j];
        cat[i] = (long long)sum;
    }

    cout << cat[n] << '\n';
    return 0;
}
