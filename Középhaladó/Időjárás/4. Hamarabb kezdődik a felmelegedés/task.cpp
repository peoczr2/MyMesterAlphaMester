/*
Megoldás lényege:
Egy település felmelegedésének kezdete az a nap, amelyen az első csökkenés után először nő a hőmérséklet. Ezt egyetlen balról jobbra haladó bejárással megkapjuk: egy jelző mutatja, volt-e már csökkenés, és az első növekedés napját eltároljuk. A kezdőnapok közül a válasz az a település, amelynek kezdete egyedül a legkorábbi; ha a legkorábbi többször fordul elő, vagy egyik településnek sincs kezdete, a válasz -1. Az idő O(N·M), a memória O(N).
*/
/*
Hint 1: || Egy település felmelegedése azzal kezdődik, hogy az első csökkenés után először nő a hőmérséklet. Keresd meg minden településre ezt a napot; ha nincs ilyen, a településnek nincs kezdete. ||
Hint 2: || A sor beolvasása közben is megteheted: egy logikai jelzővel rögzíted, volt-e már csökkenés, és az első növekedésnél megjegyzed a napot. Ha a kezdet már megvan, a további napokat nem kell vizsgálni. ||
Hint 3: || A kezdőnapokat egy tömbben gyűjtsd. A válasz az a település, amelynek kezdőnapja a legkisebb, és ez a legkisebb érték más településen nem fordul elő. Ha nincs ilyen, a válasz -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int NINCS = INT_MAX;

    int n, m;
    cin >> n >> m;

    vector<int> kezdet(n + 1, NINCS);
    for (int i = 1; i <= n; i++) {
        int elozo;
        cin >> elozo;
        bool volt_csokkenes = false;
        for (int j = 2; j <= m; j++) {
            int h;
            cin >> h;
            if (!volt_csokkenes) {
                if (h < elozo) volt_csokkenes = true;
            } else if (kezdet[i] == NINCS && h > elozo) {
                kezdet[i] = j;
            }
            elozo = h;
        }
    }

    int legkorabbi = NINCS, darab = 0, valasz = -1;
    for (int i = 1; i <= n; i++) {
        if (kezdet[i] < legkorabbi) {
            legkorabbi = kezdet[i];
            darab = 1;
            valasz = i;
        } else if (kezdet[i] == legkorabbi) {
            darab++;
        }
    }

    cout << (legkorabbi != NINCS && darab == 1 ? valasz : -1) << '\n';
    return 0;
}
