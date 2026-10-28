/*
Megoldás lényege:
A termelőhelyek egy egyenes mentén vannak, ezért minden termelő a hozzá közelebbi raktárba szállít, így a két raktár kiszolgálási területe egy-egy összefüggő szakasz: van egy L határ, az 1..L termelők az egyik, az L+1..N termelők a másik raktárhoz tartoznak.
Egy [l..r] szakasz összköltsége egy k helyen épített raktárnál Σ w_t·|p_t - p_k|, ami súly- és súly·pozíció-prefixösszegekkel O(1) időben számolható. Minden szakaszra végigpróbáljuk a k helyeket és megtartjuk a legolcsóbbat, majd minden L határon összeadjuk a bal és a jobb oldal optimumát. Az időigény O(N^2), N <= 2000 esetén ez belefér.
*/
/*
Hint 1: || Egy egyenesen a termelők két összefüggő csoportra oszlanak, a két csoport között egy határ van. Érdemes ezt a szerkezetet kihasználni, és a határ minden lehetséges helyét végigpróbálni. ||
Hint 2: || Ha egy szakasz minden termelőjét egy adott k helyre szállítjuk, a költség Σ w_t·|p_t - p_k|. Két prefixösszeg-tömb (a súlyok és a súly·pozíció összege) segítségével ez egy k-ra O(1) időben kiszámolható. ||
Hint 3: || Minden L-re számold ki az [1..L] szakasz legolcsóbb egy raktáras költségét, és az [L+1..N] szakaszra is ugyanezt. A kiíráskor az első raktár indexe, utána az L, majd a második raktár indexe kell. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> p(n + 1, 0), w(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long d;
        cin >> d >> w[i];
        p[i] = p[i - 1] + d;
    }

    // W[i] = w_1 + ... + w_i, S[i] = w_1*p_1 + ... + w_i*p_i
    vector<long long> W(n + 1, 0), S(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        W[i] = W[i - 1] + w[i];
        S[i] = S[i - 1] + w[i] * p[i];
    }

    // a [l..r] szakasz költsége, ha a raktár a k. termelő helyén van (l <= k <= r)
    auto cost = [&](int l, int r, int k) -> long long {
        long long left = p[k] * (W[k] - W[l - 1]) - (S[k] - S[l - 1]);
        long long right = (S[r] - S[k]) - p[k] * (W[r] - W[k]);
        return left + right;
    };

    // egy raktár optimuma a [l..r] szakaszra, a legjobb k-val együtt
    auto best1 = [&](int l, int r, int &bestK) -> long long {
        long long res = LLONG_MAX;
        for (int k = l; k <= r; k++) {
            long long c = cost(l, r, k);
            if (c < res) {
                res = c;
                bestK = k;
            }
        }
        return res;
    };

    vector<long long> pre(n + 2, LLONG_MAX), suf(n + 2, LLONG_MAX);
    vector<int> preK(n + 2, 0), sufK(n + 2, 0);
    for (int L = 1; L < n; L++) pre[L] = best1(1, L, preK[L]);
    for (int l = 2; l <= n; l++) suf[l] = best1(l, n, sufK[l]);

    long long best = LLONG_MAX;
    int ans1 = 0, ansL = 0, ans2 = 0;
    for (int L = 1; L < n; L++) {
        long long c = pre[L] + suf[L + 1];
        if (c < best) {
            best = c;
            ans1 = preK[L];
            ansL = L;
            ans2 = sufK[L + 1];
        }
    }

    cout << best << "\n" << ans1 << " " << ansL << " " << ans2 << "\n";
    return 0;
}
