/*
Megoldás lényege:
Egy k központi raktárat rögzítve a bal szélső cég bevétele Σ S_i·(k−i) az i = 1 … k raktárakra (a szélső raktár áruját is elszállítja), a jobb szélső cégé pedig Σ S_i·(i−k) az i = k … N raktárakra. Ha A_k az S_1 … S_k összege, B_k pedig az i·S_i tagok összege (i = 1 … k), akkor a bal oldali bevétel k·A_k − B_k, a jobb oldali (B_N − B_k) − k·(A_N − A_k).
Az A és B előtag-összegek egyszeri előre kiszámítása után minden k-ra O(1) idő alatt megkapjuk a két bevétel maximumát, a legkisebb maximumú k a válasz. Holtverseny esetén a legkisebb sorszámút tartjuk meg, mert csak szigorúan kisebb maximum esetén frissítünk. Az időigény O(N).
*/
/*
Hint 1: || Egy k-ra a két bevétel közvetlen kiszámítása O(N), így minden k-ra újra végigmenni túl lassú lenne N = 10 000 esetén. Keress olyan előre kiszámított összegeket, amelyekből egy adott k bevétele konstans idő alatt kijön. ||
Hint 2: || Vezess be két előtag-összeget: A_k az első k raktár áruinak összege, B_k pedig az i·S_i tagok összege i = 1 … k. Ezekből a bal oldali bevétel k·A_k − B_k, a jobb oldalié pedig (B_N − B_k) − k·(A_N − A_k). ||
Hint 3: || Minden k-ra vedd a két bevétel nagyobbikát, és tartsd nyilván a legkisebb ilyen értéket és a hozzá tartozó k-t. Csak szigorúan kisebb érték esetén írd felül a régit, így holtverseny esetén a kisebb sorszám marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> s(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    vector<long long> a(n + 1, 0), b(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        a[i] = a[i - 1] + s[i];
        b[i] = b[i - 1] + (long long)i * s[i];
    }

    long long legjobb = 0;
    int legjobbK = 1;
    for (int k = 1; k <= n; k++) {
        long long bal = (long long)k * a[k] - b[k];
        long long jobb = (b[n] - b[k]) - (long long)k * (a[n] - a[k]);
        long long maximum = max(bal, jobb);
        if (k == 1 || maximum < legjobb) {
            legjobb = maximum;
            legjobbK = k;
        }
    }

    cout << legjobbK << "\n";
    return 0;
}
