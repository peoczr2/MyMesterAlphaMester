/*
Megoldás lényege:
A bemenet sorrendje: az 1. állomás indulása, utána közbülső állomásonként az érkezés és az indulás, végül az N. állomás érkezése. Egy közbülső állomáson akkor nem áll meg a vonat, ha az érkezési és az indulási idő egyenlő. Egyetlen menetben a megálló nélküli, egymás melletti közbülső állomások leghosszabb sorozatát keressük. A sorozat előtti és utáni állomás sorszáma adja a választ, hiszen a vonat közöttük nem állt meg sehol. Csak szigorúan hosszabb sorozat esetén cserélünk, így döntetlennél a kisebb sorszámú marad. Ha nincs megálló nélküli közbülső sorozat (például N = 2), a válasz 0 0. Az idő O(N), ami N ≤ 100 esetén bőven belefér az időlimitbe.
*/
/*
Hint 1: || Az időpontokat célszerű percre átváltani (óra * 60 + perc), így az egyenlőség vizsgálata egyszerű. A bemenetben a közbülső állomásokhoz mindig érkezés és indulás párja tartozik, az első és az utolsó állomáshoz csak egy-egy időpont. ||
Hint 2: || Végigmenve a közbülső állomásokon keresd a folytonos, megálló nélküli szakaszokat, és jegyezd meg a leghosszabbat. Ha a szakasz az l..r állomásokat fedi le, a kiírandó pár az l-1 és az r+1 állomás sorszáma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    auto beolvas = [&]() {
        int ora, perc;
        cin >> ora >> perc;
        return ora * 60 + perc;
    };

    vector<int> erkezes(n + 1, 0), indulas(n + 1, 0);
    indulas[1] = beolvas();
    for (int k = 2; k <= n - 1; k++) {
        erkezes[k] = beolvas();
        indulas[k] = beolvas();
    }
    erkezes[n] = beolvas();

    int legjobb_hossz = 0, legjobb_bal = 0, legjobb_jobb = 0;
    int k = 2;
    while (k <= n - 1) {
        if (indulas[k] != erkezes[k]) {
            k++;
            continue;
        }
        int bal = k;
        while (k <= n - 1 && indulas[k] == erkezes[k]) {
            k++;
        }
        int jobb = k - 1;
        int hossz = jobb - bal + 1;
        if (hossz > legjobb_hossz) {
            legjobb_hossz = hossz;
            legjobb_bal = bal;
            legjobb_jobb = jobb;
        }
    }

    if (legjobb_hossz == 0) {
        cout << "0 0\n";
    } else {
        cout << legjobb_bal - 1 << " " << legjobb_jobb + 1 << "\n";
    }
    return 0;
}
