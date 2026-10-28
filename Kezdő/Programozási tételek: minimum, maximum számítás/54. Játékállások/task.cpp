/*
Megoldás lényege:
Minden játszmánál a győztes pontszáma eggyel nő, a vesztesé eggyel csökken; a többi játékos pontja
nem változik. A pontszámokat egy tömbben tároljuk. Minden játszma után megkeressük a maximális
pontszámot, majd sorszám szerint végigmegyünk a játékosokon, és kiírjuk azokat, akiknek ez a pontszámuk.
Mivel N legfeljebb 250 és M legfeljebb 10 000, a játszmánkénti O(N) bejárás összesen kb. 2,5 millió
lépés, ami bőven belefér az időkorlátba.
*/
/*
Hint 1: || Egy játszma csak két játékos pontszámát változtatja meg: a győztesét eggyel növeli, a vesztesét eggyel csökkenti. A többiek pontja ugyanaz marad, mint az előző kiíráskor. ||
Hint 2: || Tárold a pontszámokat egy tömbben, és minden játszma után keresd meg a maximumot. Mivel a kiírás sorszám szerint növekvő sorrendű, az egész tömböt bejárva a ciklusváltozó sorrendje adja a kívánt kiírást. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> pont(n + 1, 0);   // pont[i]: az i. játékos pontszáma (1-től indexelünk)

    for (int j = 0; j < m; j++) {
        int a, b;                 // A legyőzte B-t
        cin >> a >> b;
        pont[a] += 1;
        pont[b] -= 1;

        int legtobb = *max_element(pont.begin() + 1, pont.end());
        bool elso = true;
        for (int i = 1; i <= n; i++) {
            if (pont[i] == legtobb) {
                if (!elso) cout << ' ';
                cout << i;
                elso = false;
            }
        }
        cout << '\n';
    }
    return 0;
}
