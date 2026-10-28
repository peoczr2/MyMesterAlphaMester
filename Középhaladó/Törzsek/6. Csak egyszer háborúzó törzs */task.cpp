/*
Megoldás lényege:
Minden háború két résztvevőjének számlálóját eggyel növeljük, így minden törzsnél megkapjuk, hány háborúban vett részt. A törzseket sorszám szerint növekvően végignézve az első olyan törzs sorszámát írjuk ki, amelynek pontosan egy háborúja volt; ha nincs ilyen, a 0. Az idő O(N + K), ami a korlátok mellett azonnali. Az 5. feladattól eltérően itt a háborúk darabszáma számít, nem a különböző ellenfelek száma.
*/
/*
Hint 1: || Egy háborúban két törzs vesz részt: a háborúzó és az ellenséges. Mindkettőnek egy-egy háborút kell jóvá írni. ||
Hint 2: || Tömbben számold meg törzsenként a háborúkat, majd keresd meg az első olyan sorszámot, ahol a szám pontosan 1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> haboruk(n + 1, 0);
    for (int i = 0; i < k; i++) {
        int a, b, kezdet, vege;
        cin >> a >> b >> kezdet >> vege;
        haboruk[a]++;
        haboruk[b]++;
    }

    for (int t = 1; t <= n; t++) {
        if (haboruk[t] == 1) {
            cout << t << "\n";
            return 0;
        }
    }
    cout << 0 << "\n";
    return 0;
}
