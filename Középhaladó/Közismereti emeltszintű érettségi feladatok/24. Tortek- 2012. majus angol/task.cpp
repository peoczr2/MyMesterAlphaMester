/*
Megoldás lényege:
Minden törtet először legegyszerűbb alakra hozunk a számláló és a nevező legnagyobb közös osztójával való osztással.
Egész számként akkor írható fel, ha a legegyszerűbb alakban a nevező 1, ekkor az érték a számláló.
Összeadásnál a két nevező legkisebb közös többszörösére bővítünk, szorzásnál a számlálókat és a nevezőket szorozzuk össze.
Az eredményt minden esetben egyszerűsítjük, így a kiírt alak mindig a legegyszerűbb.
Egy művelet a gcd miatt O(log) időben fut, így a teljes feldolgozás a bemenet méretével arányos.
*/
/*
Hint 1: || Egy tört pontosan akkor írható fel egész számként, ha a számláló osztható a nevezővel. Érdemes minden törtet először legegyszerűbb alakra hozni, mert akkor a nevező 1 jelzi az egész értéket. ||
Hint 2: || A legegyszerűbb alakhoz a számlálót és a nevezőt is elosztjuk a legnagyobb közös osztójukkal. Összeadásnál a közös nevező a két nevező legkisebb közös többszöröse, szorzásnál a számlálók és a nevezők szorzata adja az eredményt. ||
Hint 3: || Minden eredményt egyszerűsíts, és csak akkor írd egész számként az értéket, ha a nevező 1; egyébként a számláló és a nevező kerüljön a sorba. Az összeadás és a szorzás eredményére ugyanez a kiírási szabály vonatkozik, mint a 2. részfeladatban. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Tort {
    long long szamlalo;
    long long nevezo;
};

// Legegyszerűbb alak: a számlálót és a nevezőt elosztjuk a legnagyobb közös osztójukkal.
Tort egyszerusit(long long a, long long b) {
    long long g = gcd(a, b);
    return {a / g, b / g};
}

// Egész-e a tört: legegyszerűbb alakban a nevező pontosan akkor 1, ha a tört egész.
bool egesz(const Tort& t) {
    return t.nevezo == 1;
}

// Kiírás: egész esetén az érték, egyébként a számláló és a nevező szóközzel elválasztva.
void kiir(const Tort& t) {
    if (egesz(t)) cout << t.szamlalo << "\n";
    else cout << t.szamlalo << " " << t.nevezo << "\n";
}

// Összeadás: a közös nevező a két nevező legkisebb közös többszöröse.
Tort osszead(const Tort& x, const Tort& y) {
    long long g = gcd(x.nevezo, y.nevezo);
    long long szamlalo = x.szamlalo * (y.nevezo / g) + y.szamlalo * (x.nevezo / g);
    long long nevezo = x.nevezo / g * y.nevezo;
    return egyszerusit(szamlalo, nevezo);
}

// Szorzás: a számlálók és a nevezők szorzata, majd egyszerűsítés.
Tort szoroz(const Tort& x, const Tort& y) {
    return egyszerusit(x.szamlalo * y.szamlalo, x.nevezo * y.nevezo);
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Tort> torty(n);
    for (Tort& t : torty) {
        long long a, b;
        cin >> a >> b;
        t = egyszerusit(a, b);
    }

    // 1. részfeladat: egész-e a tört
    cout << "#\n";
    for (const Tort& t : torty) {
        if (egesz(t)) cout << t.szamlalo << "\n";
        else cout << "Nem\n";
    }

    // 2. részfeladat: legegyszerűbb alak
    cout << "#\n";
    for (const Tort& t : torty) kiir(t);

    // 3. részfeladat: a megadott műveletek
    cout << "#\n";
    for (int i = 0; i < m; i++) {
        long long a, b, c, d;
        char op;
        cin >> a >> b >> c >> d >> op;
        Tort x = egyszerusit(a, b);
        Tort y = egyszerusit(c, d);
        Tort eredmeny = (op == '+') ? osszead(x, y) : szoroz(x, y);
        kiir(eredmeny);
    }

    return 0;
}
