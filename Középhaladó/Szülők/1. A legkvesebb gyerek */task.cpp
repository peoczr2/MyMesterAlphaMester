/*
Megoldás ötlete:
Minden emberhez megszámoljuk, hány gyereke van (gyerekszámláló tömb).
Azok közül, akiknek legalább 1 gyerekük van, megkeressük a legkisebb gyerekszámot.
Ha több ember is rendelkezik ezzel a minimális gyerekszámmal, a legkisebb sorszámú
embert adjuk vissza (a tömb elejéről az első ilyen elem automatikusan megfelel).
*/
/*
Hint 1: || Hozz létre egy gyerekszám[] tömböt N+1 méretben, és minden (szülő, gyerek)
          pár beolvasásakor növeld gyerekszám[szülő]-t. ||
Hint 2: || Iterálj végig az összes emberen (1..N): keresd a minimum értéket csak azoknál,
          ahol gyerekszám[i] > 0. ||
Hint 3: || A legkisebb sorszámot automatikusan kapod, ha az első minimum-találatot
          azonnal megjegyzed, és csak szigorúan kisebb értéknél frissítesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> gyerekszam(n + 1, 0);

    for (int i = 0; i < k; i++) {
        int szulo, gyerek;
        cin >> szulo >> gyerek;
        gyerekszam[szulo]++;
    }

    int minSorszam = -1, minGyerek = INT_MAX;
    for (int i = 1; i <= n; i++) {
        if (gyerekszam[i] > 0 && gyerekszam[i] < minGyerek) {
            minGyerek = gyerekszam[i];
            minSorszam = i;
        }
    }

    cout << minSorszam << "\n";
    return 0;
}
