/*
Megoldás lényege:
Minden településre külön végigmegyünk a napokon, és egy futó számlálóval követjük, hány egymást követő napon van a hőmérséklet K-nál nagyobb. Ha a hőmérséklet nagyobb K-nál, a számláló nő, különben nullázódik, és közben feljegyezzük a legnagyobb értékét. A település legjobb értékét a globális legjobbal szigorú nagyobbság esetén hasonlítjuk össze, így döntetlennél a kisebb sorszámú település marad. Ha egyetlen településen sincs K-nál melegebb nap, a legjobb érték 0, és ekkor -1-et írunk ki. Az időigény O(N * M), ami legfeljebb 10^6 lépés.
*/
/*
Hint 1: || Minden településre külön kell megkeresni a leghosszabb egymás utáni napokból álló szakaszt, amelyben a hőmérséklet szigorúan nagyobb K-nál. ||
Hint 2: || Egy futó számlálóval menj végig a napokon: ha a hőmérséklet nagyobb K-nál, növeld, különben nullázd, és közben tartsd nyilván a maximumot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    int bestLen = 0;
    int bestCity = -1;
    for (int city = 1; city <= n; city++) {
        int run = 0;
        int longest = 0;
        for (int day = 0; day < m; day++) {
            int h;
            cin >> h;
            if (h > k) {
                run++;
                longest = max(longest, run);
            } else {
                run = 0;
            }
        }
        if (longest > bestLen) {
            bestLen = longest;
            bestCity = city;
        }
    }

    cout << bestCity << "\n";
    return 0;
}
