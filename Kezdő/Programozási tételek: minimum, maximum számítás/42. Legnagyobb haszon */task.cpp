/*
Megoldás lényege:
Csak azok a termékek jöhetnek szóba, amelyeket a leértékelés hetében (a 2. héten) többször adtak el, mint az elsőben, tehát a második heti eladási szám nagyobb az elsőnél. Egy ilyen termék hasznát a 2. héten eladott darabszám és az egy darabra jutó nyereség (kedvezményes ár − beszerzési ár) szorzata adja. Egy menetben végigmegyünk a termékeken, és a maximális hasznot tároljuk, kezdetben 0-val, így ha nincs hasznot hozó termék, a 0 marad. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egy terméket csak akkor vegyél figyelembe, ha a leértékelés hetében (a 2. héten) többet adtak el belőle, mint az első héten. Ezt egy feltétellel ellenőrizd minden terméknél. ||
Hint 2: || A termék hasznát úgy kapod meg, hogy a 2. héten eladott darabszámot megszorzod az egy darabra jutó különbséggel: a kedvezményes ár és a beszerzési ár különbségével. A végén a legnagyobb ilyen értéket keresd, a kezdőértéke 0 legyen. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int best = 0;
    for (int i = 0; i < n; i++) {
        int buyPrice, basePrice, discountPrice, soldFirst, soldSecond;
        cin >> buyPrice >> basePrice >> discountPrice >> soldFirst >> soldSecond;

        if (soldSecond > soldFirst) {
            int profit = soldSecond * (discountPrice - buyPrice);
            best = max(best, profit);
        }
    }

    cout << best << "\n";
    return 0;
}
