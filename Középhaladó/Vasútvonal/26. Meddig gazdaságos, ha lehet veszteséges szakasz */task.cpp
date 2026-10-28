/*
Megoldás lényege:
A Budapest-től s. állomásig tartó útszakasz akkor gazdaságos, ha a teljes bevétele legalább annyi, mint a kiadása.
Az i. szakaszon a vonaton lévő utasok száma U forintot fizet személyenként, így a szakasz bevétele U-szor az utasok száma, kiadása pedig V.
Budapesttől az s. állomásig s-1 szakasz van, így a kiadás (s-1)*V, a bevétel pedig az eddigi szakaszok bevételének összege.
Végigmegyünk az állomásokon, folyamatosan összegezzük a bevételt, és minden állomásnál ellenőrizzük a gazdaságosságot; az utolsó gazdaságos állomás sorszáma lesz a válasz, különben 0.
A köztes veszteséges szakaszok nem állítják meg a számolást, mert a feltétel a teljes Budapest-től számított útszakaszra vonatkozik.
Az időigény O(N), a memóriaigény O(1); a bevétel nagy lehet, ezért long long.
*/
/*
Hint 1: || A szakaszon utazók száma az állomás után a vonaton lévő utasok száma: előző létszám + felszállók - leszállók. Ennyi utas fizet az adott szakaszon U forintot. ||
Hint 2: || Tartsd nyilván a Budapesttől eddig megtett szakaszok összes bevételét. Az s. állomásig s-1 szakasz tartozik a kiadáshoz, vagyis (s-1)*V. Ha a bevétel legalább ennyi, az s. állomás gazdaságos. ||
Hint 3: || Minden gazdaságos állomás sorszámát jegyezd fel, és a végén az utolsó (legnagyobb) ilyen sorszám a válasz. Ha egyik állomás sem gazdaságos, a válasz 0. Az összeg akár 10^10 körüli is lehet, ezért long long kell. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long u, v;
    cin >> n >> u >> v;

    long long cur = 0;   // a vonaton lévő utasok száma
    long long rev = 0;   // Budapesttől eddig összesen a bevétel
    int answer = 0;      // az utolsó gazdaságos állomás sorszáma
    for (int s = 1; s <= n; s++) {
        long long le, fel;
        cin >> le >> fel;
        cur = cur - le + fel;
        if (s < n) {
            rev += u * cur;                      // az s. -> s+1. szakasz bevétele
            long long cost = (long long)s * v;   // Budapesttől az s+1. állomásig s szakasz
            if (rev >= cost) answer = s + 1;
        }
    }

    cout << answer << "\n";
    return 0;
}
