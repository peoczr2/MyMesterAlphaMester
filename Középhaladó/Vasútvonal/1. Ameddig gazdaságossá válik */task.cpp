/*
Megoldás lényege:
Legyen c_k a vonaton lévő utasok száma a k. és a (k+1). állomás közötti szakaszon. Ezt léptetéssel kapjuk: c_k = c_{k-1} + fel_k - le_k.
A k. szakaszon utazó minden utas U forintot fizet, a vonat egy szakasz megtétele V forintba kerül. Így az 1. állomástól az m. állomásig tartó út
profitja P(m) = U * (c_1 + ... + c_{m-1}) - V * (m-1), és P(1) = 0. A keresett állomás az utolsó olyan m, amelyre P(m) <= 0 és P(m+1) > 0,
vagyis ahonnan a következő szakasz már nyereséget hoz. Ha ilyen nincs, a válasz 0.
A prefixösszeget egy menetben léptetjük, így az időigény O(N), a memóriaigény O(N). Az összegek meghaladhatják a 32 bites tartományt, ezért long long.
*/
/*
Hint 1: || Egy szakasz bevétele a rajta utazó utasok számától függ, a költsége viszont mindig ugyanaz. Mennyi a profit az 1. állomástól az m. állomásig? ||
Hint 2: || Számold ki minden szakaszon a vonaton lévő utasok számát: előző érték + felszállók - leszállók. Az m-ig tartó út profitja U-szor az első m-1 szakasz utasainak összege, mínusz V-szer m-1, ezt prefixösszegként léptetve kapod. ||
Hint 3: || Menj végig az állomásokon, és jegyezd meg mindig azt az m-et, amelynél a profit még legfeljebb nulla, de a következő állomásig már pozitív. A végén az utolsó ilyen m kell. A 64 bites egész (long long) azért szükséges, mert az összegek meghaladhatják az int tartományt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long u, v;
    cin >> n >> u >> v;

    vector<long long> le(n), fel(n);
    for (int i = 0; i < n; i++) cin >> le[i] >> fel[i];

    // c[i]: a vonaton lévő utasok száma az (i+1). és (i+2). állomás között
    vector<long long> c(n);
    long long cur = 0;
    for (int i = 0; i < n; i++) {
        cur += fel[i] - le[i];
        c[i] = cur;
    }

    // P[m]: az 1. állomástól az m. állomásig tartó út profitja (m = 1..n)
    vector<long long> P(n + 2, 0);
    long long sumc = 0;  // c_1 + ... + c_{m-1}
    for (int m = 1; m <= n; m++) {
        P[m] = u * sumc - v * (m - 1);
        sumc += c[m - 1];
    }

    int ans = 0;
    for (int m = 1; m < n; m++) {
        if (P[m] <= 0 && P[m + 1] > 0) ans = m;
    }
    cout << ans << "\n";
    return 0;
}
