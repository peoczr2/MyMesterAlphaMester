/*
Megoldás ötlete:
Minden emberhez megszámoljuk, hány gyereke van egy külön gyerekszám[] tömbben.
A beolvasott (szülő, gyerek) kapcsolatok alapján csak a szülő számlálóját növeljük.
Ezután végigmegyünk az összes emberen, és megkeressük azt, akinek a legtöbb gyereke van.
Holtverseny esetén a kisebb sorszámot kell választani, ezt úgy kapjuk meg, hogy csak
szigorúan nagyobb gyerekszámnál frissítjük az eredményt.
*/
/*
Hint 1: || Tarts egy N+1 méretű tömböt, amiben gyerekszam[szulo]++ minden élre. ||
Hint 2: || A válaszhoz keresd a legnagyobb gyerekszámot az 1..N tartományban. ||
Hint 3: || Ha az új érték csak egyenlő a legjobbal, ne frissíts, így megmarad a kisebb sorszám. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> gyerekszam(n + 1, 0);
    for (int i = 0; i < k; ++i) {
        int szulo, gyerek;
        cin >> szulo >> gyerek;
        ++gyerekszam[szulo];
    }

    int valasz = 1;
    for (int i = 2; i <= n; ++i) {
        if (gyerekszam[i] > gyerekszam[valasz]) {
            valasz = i;
        }
    }

    cout << valasz << '\n';
    return 0;
}
