/*
Megoldás lényege:
Legyen f(t) a t. évben kikelő virágok száma. Az 1. évben f(1) = L, és egy virág az ültetésétől számítva az M. évében kezd magot hozni, K éven át, a mag pedig a következő évben kel ki.
Így minden t > 1 évre f(t) = f(t−M) + f(t−M−1) + … + f(t−M−K+1), ahol a hiányzó (nem létező) évek értéke 0.
Az X. évben élő virágok a t = X−N+1 … X évek f(t) értékének összege, hiszen egy virág N évig él.
A számokat 1-től X-ig kiszámoljuk, minden lépésnél a 20180113-mal vett maradékkal dolgozunk; az idő O(X·K), ami bőven belefér.
*/
/*
Hint 1: || Csak azt kell tudni, hogy egy évben hány virág kel ki, mert egy virág N évig él. Az X. évben élő virágok száma az X−N+1-től X-ig terjedő években kikelt virágok összege. ||
Hint 2: || Jelölje f(t) a t. évben kikelő virágok számát. Egy virág életének M. évétől (az ültetés évét első évnek véve) K éven át ad magot, és a mag a következő évben kel ki, így f(t) = f(t−M) + f(t−M−1) + … + f(t−M−K+1). ||
Hint 3: || Számold ki f(t) értékeit t = 1-től X-ig, a f(1) = L kezdőértékkel, és közben minden összeget vedd a 20180113-mal vett maradékként. A hiányzó (1-nél kisebb) indexű értékeket nullának tekintsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long MOD = 20180113LL;
    int n, m, k, l;
    cin >> n >> m >> k >> l;
    int x;
    cin >> x;

    // f[t]: a t. évben kikelő virágok száma (f[1] = L)
    vector<long long> f(x + 1, 0);
    f[1] = l;
    for (int t = 2; t <= x; t++) {
        long long s = 0;
        for (int d = m; d <= m + k - 1; d++) {
            if (t - d >= 1) s += f[t - d];
        }
        f[t] = s % MOD;
    }

    // Az X. évben élő virágok: a t = max(1, X−N+1) … X évben kikelt virágok összege
    long long ans = 0;
    for (int t = max(1, x - n + 1); t <= x; t++) {
        ans = (ans + f[t]) % MOD;
    }
    cout << ans << "\n";
    return 0;
}
