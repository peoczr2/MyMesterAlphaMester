/*
Megoldás lényege: törzsenként egy halmazban gyűjtjük, kivel háborúzott valamikor. Egy háborúban a két törzs egymás ellenfele, ezért mindkettejük halmazába bekerül a másik sorszáma, az ismétlődéseket a halmaz automatikusan kiszűri. Azt a törzset keressük, amelynek halmaza pontosan N-1 elemű, vagyis minden más törzzsel háborúzott, és a sorszám szerint első ilyet írjuk ki, különben 0 a válasz. Az időigény O(K log N), ami a korlátok mellett gyorsan lefut.
*/
/*
Hint 1: || Egy törzs akkor felel meg, ha az összes másik törzzsel legalább egyszer háborúzott. Ehhez nem kell a háborúk időpontjait vizsgálni, csak azt, hogy ki kivel került szembe. ||
Hint 2: || Törzsenként tárolj egy halmazt az ellenfelek sorszámairól: minden háborúnál a két törzs kerüljön a másik halmazába. A keresett törzs halmazának N-1 elemet kell tartalmaznia, és a sorszámokat növekvő sorrendben kell megnézni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<set<int>> ellenfel(n + 1);
    for (int i = 0; i < k; i++) {
        int haboruzo, ellenseges;
        int kezdet, vege;
        cin >> haboruzo >> ellenseges >> kezdet >> vege;
        if (haboruzo != ellenseges) {
            ellenfel[haboruzo].insert(ellenseges);
            ellenfel[ellenseges].insert(haboruzo);
        }
    }

    int valasz = 0;
    for (int t = 1; t <= n; t++) {
        if ((int)ellenfel[t].size() == n - 1) {
            valasz = t;
            break;
        }
    }
    cout << valasz << "\n";
    return 0;
}
