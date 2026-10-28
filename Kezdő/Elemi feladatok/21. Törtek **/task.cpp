/*
Megoldás lényege:
A törteket számlálóval és nevezővel, egész számokként kezeljük. Az összeg és a különbség a/b ± c/d = (a*d ± c*b)/(b*d),
a szorzat (a*c)/(b*d), a hányados (a*d)/(b*c) alakban adódik. Minden eredményt a számláló és a nevező legnagyobb
közös osztójával egyszerűsítünk; a std::gcd(0, x) = x miatt a nulla automatikusan 0/1 alakot kap. Negatív különbség
és nullával való osztás esetén a művelet nem végezhető el, ilyenkor a 0 0 párt írjuk ki. Az értékek legfeljebb 1800-ig
nőnek, így a műveletek száma konstans, az időigény elhanyagolható.
*/
/*
Hint 1: || Minden eredmény is tört, amelyet a számláló és a nevező legnagyobb közös osztójával lehet egyszerűsíteni. Érdemes egy külön függvényt írni, amely egy törtet egyszerűsít. ||
Hint 2: || Összeg és különbség: a/b ± c/d = (a*d ± c*b)/(b*d); szorzat: (a*c)/(b*d); hányados: (a*d)/(b*c). A különbség negatív és a c = 0 esetű osztás nem végezhető el, ekkor 0 0 a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egyszerűsített tört: a számlálót és a nevezőt a legnagyobb közös osztójukkal osztjuk
pair<long long, long long> egyszerusit(long long szamlalo, long long nevezo) {
    long long g = gcd(szamlalo, nevezo);
    return {szamlalo / g, nevezo / g};
}

int main() {
    long long a, b, c, d;
    cin >> a >> b >> c >> d;   // első tört: a/b, második tört: c/d

    // összeg
    auto [osszeg_sz, osszeg_nev] = egyszerusit(a * d + c * b, b * d);
    cout << osszeg_sz << " " << osszeg_nev << "\n";

    // különbség: csak nem negatív lehet
    long long kulonbseg = a * d - c * b;
    if (kulonbseg < 0) {
        cout << "0 0\n";
    } else {
        auto [k_sz, k_nev] = egyszerusit(kulonbseg, b * d);
        cout << k_sz << " " << k_nev << "\n";
    }

    // szorzat
    auto [szorzat_sz, szorzat_nev] = egyszerusit(a * c, b * d);
    cout << szorzat_sz << " " << szorzat_nev << "\n";

    // hányados: nullával nem osztunk
    if (c == 0) {
        cout << "0 0\n";
    } else {
        auto [h_sz, h_nev] = egyszerusit(a * d, b * c);
        cout << h_sz << " " << h_nev << "\n";
    }
    return 0;
}
