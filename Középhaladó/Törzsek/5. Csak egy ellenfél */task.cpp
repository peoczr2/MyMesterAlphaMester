/*
Megoldás lényege:
Minden törzshöz egy halmazban gyűjtjük, hogy kivel háborúzott, így az ugyanazzal az ellenféllel vívott többszörös háborúk egyszer számítanak. A keresett törzs az, amelynek ez a halmaza pontosan egy elemű. A törzseket sorszám szerint növekvően végignézve az első ilyen adja a választ, ha nincs ilyen, a 0. A háborúk beolvasása O(K log N), a keresés O(N), ami N ≤ 1000 és K ≤ 2000 mellett elhanyagolható.
*/
/*
Hint 1: || Egy törzs ellenfeleinek száma nem egyezik a háborúi számával, mert ugyanazzal az ellenféllel többször is lehet háború. Törzsenként azt kell nyilvántartani, kivel háborúzott. ||
Hint 2: || Használj törzsenként egy halmazt (set): minden háborúnál mindkét törzs felveszi a másikat. A végén keresd meg a legkisebb sorszámú törzset, amelynek a halmazában pontosan egy elem van. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<set<int>> ellenfel(n + 1);
    for (int i = 0; i < k; i++) {
        int a, b, kezdet, vege;
        cin >> a >> b >> kezdet >> vege;
        ellenfel[a].insert(b);
        ellenfel[b].insert(a);
    }

    for (int t = 1; t <= n; t++) {
        if (ellenfel[t].size() == 1) {
            cout << t << "\n";
            return 0;
        }
    }
    cout << 0 << "\n";
    return 0;
}
