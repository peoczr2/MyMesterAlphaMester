/*
Megoldás lényege:
Az 1..2N számok 2×N-es táblába rendezése úgy, hogy a sorokban és oszlopokban
is növekedjenek, pontosan a 2×N alakú standard Young-táblák száma.

Ez a szám a Catalan-szám: C_N. Mivel N legfeljebb 20, egyszerű dinamikával
vagy a Catalan-rekurzióval kiszámítható.
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