/*
Megoldás lényege:
Minden héten megszámoljuk, hány napon esett eső, vagyis hány csapadékadat nagyobb nullánál.
Így a feladat egy N/2 hosszú csúszó ablakra egyszerűsödik a heti számok sorozatán: az
ablakban lévő esős napok összegét kell minimalizálni. Az ablakot egyesével léptetjük: az
előző ablak első hetét kivonjuk, az új utolsó hetet hozzáadjuk, így minden lépés O(1).
Ha az ablak összege szigorúan kisebb a legjobbnál, frissítünk, így a legkisebb sorszámú
ablak marad meg. Az időigény O(N·7).
*/
/*
Hint 1: || Hetenként számold meg, hány napon volt pozitív csapadék. ||
Hint 2: || Az N/2 hosszú ablak összegét ne minden alkalommal újraszámold: egy hét ki- és egy hét belépése elég. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> rainyDays(n + 1, 0);  // rainyDays[i]: az i. héten hány napon esett eső
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 7; j++) {
            int c;
            cin >> c;
            if (c > 0) rainyDays[i]++;
        }
    }

    int k = n / 2;  // az ablak hossza hetekben

    int sum = 0;
    for (int i = 1; i <= k; i++) sum += rainyDays[i];

    int best = sum, bestStart = 1;
    for (int start = 2; start + k - 1 <= n; start++) {
        sum += rainyDays[start + k - 1] - rainyDays[start - 1];
        if (sum < best) {
            best = sum;
            bestStart = start;
        }
    }

    cout << bestStart << '\n';
    return 0;
}
