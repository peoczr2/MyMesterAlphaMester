/*
Megoldás lényege:
A világcsúcs-beállítások (az előzővel egyenlő magasságú ugrások) nem számítanak, ezért
csak azokat a rekordokat kell figyelembe venni, amelyek magassága nagyobb az előzőnél.
Az első rekord mindig új világcsúcs, ezért azt is beszámoljuk. Évenként egy számlálót
növelünk minden ilyen rekordnál, majd a számlálók közül a legnagyobbat írjuk ki.
Mivel az évszámok legfeljebb 2015 lehetnek, egy tömb elegendő a számlálásra.
Az időigény O(N).
*/
/*
Hint 1: || Egy rekord akkor számít, ha a magassága nagyobb az előzőnél, és az első rekord mindig számít. ||
Hint 2: || Egy tömbben évenként tartsd a darabszámot, és a végén keresd meg a legnagyobbat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> cnt(2016, 0);  // cnt[év]: az adott évben elért, az előzőnél magasabb rekordok száma
    int prev = 0;

    for (int i = 0; i < n; i++) {
        int year, height;
        cin >> year >> height;
        if (i == 0 || height > prev) {
            cnt[year]++;
        }
        prev = height;
    }

    int best = 0;
    for (int y = 0; y < 2016; y++) {
        best = max(best, cnt[y]);
    }

    cout << best << '\n';
    return 0;
}
