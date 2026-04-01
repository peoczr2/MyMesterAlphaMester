/*
Megoldás lényege:
A sorozat következő eleme csak az előzőből számítható, ezért elég végigszimulálni az N lépést.
Mivel M legfeljebb 3, az összes lehetséges érték legfeljebb 10^6, így egy tömbben meg tudjuk
számolni az előfordulásokat és eltárolni az utolsó előfordulási helyet is.

Az egymáshoz legközelebbi két egyforma elem távolságához elég az utolsó előfordulást figyelni,
a K. legnagyobb elemhez pedig a gyakoriságokat végigszkenneljük nagyobbtól a kisebb felé.
*/
// Hint 1: || A következő tagot mindig az előző szám középső 2M számjegye adja. ||
// Hint 2: || M<=3 miatt a lehetséges értékek száma legfeljebb egymillió, ez tömbös megoldást enged. ||
// Hint 3: || Az azonos elemek közti legkisebb távolságot az utolsó előfordulás alapján lehet frissíteni. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    long long X, A, B;
    int N, K;
    cin >> M >> X >> A >> B >> N >> K;

    long long p10[7] = {1};
    for (int i = 1; i <= 6; ++i) p10[i] = p10[i - 1] * 10LL;
    long long mod = p10[2 * M];
    long long div = p10[M];

    int limit = (int)mod;
    vector<int> freq(limit + 1, 0), last(limit + 1, -1);

    long long cur = X;
    int bestDist = N + 1;
    for (int i = 0; i < N; ++i) {
        int val = (int)cur;
        ++freq[val];
        if (last[val] != -1) bestDist = min(bestDist, i - last[val]);
        last[val] = i;

        unsigned long long nxt = (unsigned long long)cur * (unsigned long long)A + (unsigned long long)B;
        cur = (long long)((nxt / (unsigned long long)div) % (unsigned long long)mod);
    }

    int need = K;
    int kth = 0;
    for (int v = limit; v >= 0; --v) {
        if (freq[v] == 0) continue;
        if (need > freq[v]) {
            need -= freq[v];
        } else {
            kth = v;
            break;
        }
    }

    cout << bestDist << '\n' << kth << '\n';
    return 0;
}
