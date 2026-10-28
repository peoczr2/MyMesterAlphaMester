/*
Megoldás lényege:
Q_{N,K} = 1 + azon x ≤ N számok száma, amelyek karakterlánca lexikografikusan kisebb K-énál. Ez a szám N növelésével csak akkor nő (1-gyel), ha az N karakterlánca kisebb K-énál, tehát monoton. Ezért a legkisebb N-et bináris kereséssel keressük: ha K-nál már több a kisebb szám, mint P−1, nincs megoldás; ha pont P−1, a válasz K; egyébként az a legkisebb N, amelyre a számláló eléri P−1-et. A számlálás hosszak szerint történik: egy ℓ jegyű x pontosan akkor kisebb K-nál lexikografikusan, ha numerikusan kisebb egy küszöbnél: ℓ < |K| esetén x legfeljebb K első ℓ jegyéből alkotott szám (ez a prefix miatt kisebb), ℓ = |K| esetén x < K, ℓ > |K| esetén x < K·10^{ℓ−|K|}. Így minden hosszra egy intervallum darabszáma O(1), egy N-re O(19). A válasz 10^18-nál kisebb, ezért 2·10^18 a keresési felső határ. Az időigény O(T · log(10^18) · 19).
*/
/*
Hint 1: || Q_{N,K} = 1 + hány x ≤ N szám van, amelynek karakterlánca kisebb, mint K karakterlánca. Figyeld meg, mikor nő ez a szám, ahogy N-et 1-gyel növeled. ||
Hint 2: || Mivel a szám N-nel monoton nő, a legkisebb N bináris kereséssel megtalálható. Előbb nézd meg N=K-t: ha ott a sorszám már nagyobb, mint P, nincs megoldás; ha pont P, a válasz K. ||
Hint 3: || Egy ℓ jegyű x lexikografikusan pontosan akkor kisebb K-nál, ha numerikusan kisebb egy küszöbnél: ℓ < |K| esetén K első ℓ jegyéből alkotott számnál vagy azzal egyenlő, ℓ = |K| esetén K-nál, ℓ > |K| esetén K·10^{ℓ−|K|}-nél. Így minden hosszra egy intervallum darabszáma adódik. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 i128;

i128 pw10[40];

// hány x szám van az [1, N] tartományban, amelynek karakterlánca lexikografikusan kisebb S-nél
ll countLess(ll N, const string &S) {
    int L = (int)S.size();
    i128 Sval = 0;
    for (char c : S) Sval = Sval * 10 + (c - '0');
    int lenN = (int)to_string(N).size();

    i128 total = 0;
    for (int len = 1; len <= lenN; ++len) {
        i128 lo = pw10[len - 1];
        i128 hi = min((i128)N, pw10[len] - 1);
        if (lo > hi) continue;

        // a len jegyű x-re: x < th numerikusan pontosan akkor, ha x lexikografikusan kisebb S-nél
        i128 th;
        if (len < L) {
            i128 pref = 0;
            for (int j = 0; j < len; ++j) pref = pref * 10 + (S[j] - '0');
            th = pref + 1;  // a prefix is kisebb
        } else if (len == L) {
            th = Sval;
        } else {
            th = Sval * pw10[len - L];
        }

        i128 up = min(hi, th - 1);
        if (up >= lo) total += up - lo + 1;
    }
    return (ll)total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    pw10[0] = 1;
    for (int i = 1; i < 40; ++i) pw10[i] = pw10[i - 1] * 10;

    const ll UB = 2000000000000000000LL;  // a válasz 10^18 alatt van, ha létezik

    int T;
    cin >> T;
    while (T--) {
        ll K, P;
        cin >> K >> P;
        string S = to_string(K);
        ll need = P - 1;  // K előtt hány szám lehet lexikografikusan kisebb
        ll c0 = countLess(K, S);

        ll ans;
        if (c0 > need) {
            ans = 0;
        } else if (c0 == need) {
            ans = K;
        } else if (countLess(UB, S) < need) {
            ans = 0;
        } else {
            // legkisebb N > K, amelyre a számláló eléri need-et
            ll lo = K, hi = UB;
            while (lo < hi) {
                ll mid = lo + (hi - lo) / 2;
                if (countLess(mid, S) >= need)
                    hi = mid;
                else
                    lo = mid + 1;
            }
            ans = lo;
        }
        cout << ans << '\n';
    }
    return 0;
}
