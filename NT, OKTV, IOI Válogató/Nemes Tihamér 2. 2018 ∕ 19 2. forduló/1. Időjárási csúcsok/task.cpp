/*
Időjárási csúcsok (Nemes Tihamér 2018/19, 2. forduló, 2. korcsoport, 1. feladat)

Feladat: N nap déli hőmérséklete alapján meg kell számolni, hány olyan [l,r] időszak van, amelyben
pontosan K lokálisan meleg és L lokálisan hideg nap van.

Megoldás lényege:
A meleg és hideg napokat egyszer, a teljes sorozaton jelöljük meg: egy nap meleg, ha mindkét
szomszédjánál melegebb, hideg, ha mindkettőnél hidegebb (az első és az utolsó napnak nincs két
szomszédja, ezek egyik sem). Az időszak végpontjai is számítanak: a mintában például [1,8] jó,
pedig a 8. nap hideg.
Legyen W[i] és C[i] az első i nap meleg, illetve hideg napjainak száma (prefixösszeg). Az [l,r]
időszak pontosan akkor jó, ha W[r]-W[l-1] = K és C[r]-C[l-1] = L, azaz
(W[l-1], C[l-1]) = (W[r]-K, C[r]-L). Az r-rel balról jobbra haladva egy map-ben számoljuk, melyik
(W, C) pár hányszor fordult elő eddig (az üres prefix (0,0) is), és minden r-nél hozzáadjuk a
(W[r]-K, C[r]-L) pár darabszámát. Ez a "hány részösszeg egyenlő K-val" feladat, csak párokkal.
A válasz akár ~N^2/2 is lehet, ezért long long.

Időigény: O(N log N) (unordered_map-pel O(N)), memória: O(N).
*/
/*
Hint 1: || Először jelöld meg az egész sorozatban, mely napok melegek és melyek hidegek – ez nem függ a vizsgált időszaktól. Hogyan kapod meg O(1)-ben egy [l,r] időszak meleg napjainak számát? ||
Hint 2: || Prefixösszeg: [l,r] pontosan akkor jó, ha W[r] − W[l−1] = K és C[r] − C[l−1] = L, vagyis rögzített r-hez olyan l−1 kell, amelyre (W[l−1], C[l−1]) = (W[r] − K, C[r] − L). ||
Hint 3: || Menj végig r-rel 1-től N-ig, és egy map-ben számold, melyik (W, C) pár hányszor fordult elő eddig (kezdetben a (0,0) egyszer). Az N. nappal végződő időszakokat se hagyd ki, és long long-ot használj! ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // beolvasás
    int n, K, L;
    cin >> n >> K >> L;
    vector<int> h(n + 1);
    for (int i = 1; i <= n; i++) cin >> h[i];

    // meleg / hideg napok megjelölése (az első és az utolsó nap egyik sem)
    vector<int> meleg(n + 1, 0), hideg(n + 1, 0);
    for (int i = 2; i <= n - 1; i++) {
        meleg[i] = (h[i] > h[i - 1] && h[i] > h[i + 1]);
        hideg[i] = (h[i] < h[i - 1] && h[i] < h[i + 1]);
    }

    // db[(w, c)] = hány eddigi prefixre (0..r-1) igaz, hogy W = w és C = c
    map<pair<int, int>, int> db;
    db[{0, 0}] = 1;  // az üres prefix (W[0] = C[0] = 0) is számít!

    long long valasz = 0;  // akár ~N*N/2 időszak is lehet -> long long
    int W = 0, C = 0;
    for (int r = 1; r <= n; r++) {  // r = n is kell: az utolsó nappal végződő időszakok
        W += meleg[r];
        C += hideg[r];
        // azok az l-1 prefixek, amelyekre (W[l-1], C[l-1]) = (W-K, C-L)
        auto it = db.find({W - K, C - L});
        if (it != db.end()) valasz += it->second;
        db[{W, C}]++;
    }

    // kiírás
    cout << valasz << '\n';
    return 0;
}
