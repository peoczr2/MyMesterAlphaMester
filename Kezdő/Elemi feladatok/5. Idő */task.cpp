/*
Megoldás lényege:
Az időpontot és az időtávolságot is egyetlen egységre, századmásodpercre váltjuk át, mert egy nap 24·60·60·100 = 8 640 000 századmásodperc. A korábbi időpont a kivonással, a későbbi az összeadással adódik, és mindkettőt a nap hosszával vett maradékkal kell venni, hogy az eredmény 0 és 23 óra közé essen. Az időtávolság legfeljebb 32 000 óra lehet, ezért a számok 64 bites egészként (long long) elférnek. Visszaalakításkor az órát az egész osztás, a percet és a másodpercet maradékképzés adja. A művelet ideje konstans.
*/
/*
Hint 1: || Alakítsd át az időpontot és az időtávolságot ugyanabba az egységbe, például a nap kezdete óta eltelt századmásodpercekbe. Így a korábbi és a későbbi időpont egyetlen kivonás, illetve összeadás lesz. ||
Hint 2: || Mivel a nap 24 óra, a végeredményt maradékosan kezeld: a nap hosszát (8 640 000 századmásodperc) vedd modulusnak. Kivonásnál a negatív maradékkal is számolj, a visszaalakításnál pedig használd az egész osztást és a maradékképzést. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Századmásodpercből "óra perc másodperc századmásodperc" alak
void kiir(long long x) {
    cout << x / 360000 << " " << (x / 6000) % 60 << " " << (x / 100) % 60 << " " << x % 100 << "\n";
}

int main() {
    long long o, p, mp, szmp;
    long long a, b, c, d;
    cin >> o >> p >> mp >> szmp;
    cin >> a >> b >> c >> d;

    const long long NAP = 24LL * 360000;  // egy nap századmásodpercben

    long long ido = ((o * 60 + p) * 60 + mp) * 100 + szmp;
    long long tavolsag = ((a * 60 + b) * 60 + c) * 100 + d;

    // A negatív maradékot is 0 és NAP közé visszük
    long long korabbi = ((ido - tavolsag) % NAP + NAP) % NAP;
    long long kesobbi = (ido + tavolsag) % NAP;

    kiir(korabbi);
    kiir(kesobbi);
    return 0;
}
