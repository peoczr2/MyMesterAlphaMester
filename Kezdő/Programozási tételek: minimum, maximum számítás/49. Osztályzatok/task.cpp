/*
Megoldás lényege:
Minden tanuló osztályzata a pontszámából a négy ponthatár alapján egyértelműen meghatározható: a pontszámot sorban összevetjük a KH, HH, NH és OH küszöbökkel. Osztályzatonként egy maximumot tartunk nyilván, kezdetben -1 értékkel, így ha az osztályzat nem született, ez marad. A tanulók pontszámait egyesével beolvasva frissítjük a megfelelő maximumot. Mivel minden pontszámot csak egyszer kell megnézni, az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egy tanuló osztályzata a pontszámából egyértelműen adódik: a ponthatárokat (KH, HH, NH, OH) kell sorban összevetni vele. ||
Hint 2: || Tarts öt maximumot, osztályzatonként egyet, kezdetben -1 értékkel, és minden tanulónál frissítsd a megfelelő maximumot a pontszámával. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    int kh, hh, nh, oh;
    cin >> kh >> hh >> nh >> oh;

    int best[6];
    fill(begin(best), end(best), -1);   // best[1..5]: az adott osztályzat legnagyobb pontszáma

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        int grade;
        if (p < kh) grade = 1;
        else if (p < hh) grade = 2;
        else if (p < nh) grade = 3;
        else if (p < oh) grade = 4;
        else grade = 5;
        best[grade] = max(best[grade], p);
    }

    for (int g = 1; g <= 5; g++) {
        cout << best[g] << "\n";
    }
    return 0;
}
