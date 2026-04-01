/*
Feladat: M tábor között kell a csomagokat úgy elosztani, hogy minden tábor kapjon legalább X-et, és X maximális legyen. Egy hegymászó csak az 1..H_i táborok valamelyikébe rakhat.
Ötlet: Fix X esetén a (i..M) táborok igénye (M-i+1)*X, ezt csak azok a csomagok tudják fedezni, amelyekhez H>=i. Emiatt minden i-re szükséges (és itt elégséges is), hogy suffixSupply[i] >= (M-i+1)*X. A maximum X tehát az összes ilyen hányados minimuma.
Hint 1: || Gondolkodj nem prefixben, hanem suffixben: a magas sorszámú táborokhoz már kevesebb hegymászó fér hozzá. ||
Hint 2: || Ha az i. tábortól felfelé nézed az igényt, azt csak H>=i hegymászók csomagjai tudják teljesíteni. ||
Hint 3: || Minden i-re kapsz egy felső korlátot X-re; a válasz ezek minimuma. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<long long> byH(M + 2, 0);
    for (int i = 0; i < N; ++i) {
        long long d;
        int h;
        cin >> d >> h;
        byH[h] += d;
    }

    vector<long long> suf(M + 3, 0);
    for (int i = M; i >= 1; --i) suf[i] = suf[i + 1] + byH[i];

    long long ans = (1LL << 62);
    for (int i = 1; i <= M; ++i) {
        long long camps = M - i + 1;
        ans = min(ans, suf[i] / camps);
    }

    cout << ans << '\n';
    return 0;
}
