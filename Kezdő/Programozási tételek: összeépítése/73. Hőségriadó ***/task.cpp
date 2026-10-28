/*
Megoldás lényege:
Egy hőségriadó akkor jön létre, ha egymás után legalább K napon a hőmérséklet meghaladja H fokot. Ennek a riadónak az első napja (E) a forró szakasz K-adik napja, utolsó napja (U) az a legkisebb nap, amely már nem forró, vagyis a szakasz után következő nap. Ha a forró szakasz az utolsó napig tart, nincs U, ezért nem alkot teljes riadót. A napokat egy menetes bejárással dolgozzuk fel: minden forró szakasz végén, ha teljes riadót ad, kiszámoljuk a távolságot az előző riadóhoz képest (a későbbi E mínusz a korábbi U), és ezek minimumát tartjuk nyilván. Ha nincs riadó, -1-et, ha csak egy van, -2-t írunk. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Keresd meg az egymás után következő, H foknál melegebb napok szakaszait. Egy szakasz csak akkor ad teljes riadót, ha legalább K nap hosszú és utána van még egy nem forró nap. ||
Hint 2: || A riadó első napja a szakasz K-adik napja, utolsó napja a szakasz utáni nap. Két egymás utáni riadó távolsága a későbbi első nap és a korábbi utolsó nap különbsége. ||
Hint 3: || Egy ciklussal haladj végig a napokon, és a szakasz végén döntsd el, lett-e belőle teljes riadó, majd az előzővel együtt frissítsd az eddigi legkisebb távolságot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, h;
    cin >> n >> k >> h;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int darab = 0;
    int elozoU = -1;
    int legkisebb = INT_MAX;

    int i = 1;
    while (i <= n) {
        if (a[i] <= h) {
            i++;
            continue;
        }
        int s = i;
        while (i <= n && a[i] > h) {
            i++;
        }
        int t = i - 1;
        if (t - s + 1 >= k && t + 1 <= n) {
            int e = s + k - 1;
            int u = t + 1;
            if (elozoU != -1) {
                legkisebb = min(legkisebb, e - elozoU);
            }
            elozoU = u;
            darab++;
        }
    }

    if (darab == 0) {
        cout << -1 << "\n";
    } else if (darab == 1) {
        cout << -2 << "\n";
    } else {
        cout << legkisebb << "\n";
    }
    return 0;
}
