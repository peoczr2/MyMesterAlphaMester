/*
Megoldás lényege:
Mindkét hosszt a legkisebb egységre, hüvelykre váltjuk át, így a két érték egész számként összeadható és kivonható. Egy mérföld 1760 yard, egy yard 3 láb, egy láb 12 hüvelyk, ezért a váltás egymásba ágyazott szorzás: ((mérföld * 1760 + yard) * 3 + láb) * 12 + hüvelyk. Az eredményt visszaváltjuk a bemeneti alakra: a hüvelyk a 12-es, a láb a 3-as, a yard az 1760-as maradékos osztással adódik, a hányadosok pedig a következő nagyobb egység értékét adják. Ha a különbség negatív, a kiírt szám elé mínusz jelet teszünk, a visszaváltást az abszolút értékkel végezzük. A művelet állandó idejű.
*/
/*
Hint 1: || Válaszd ki a legkisebb egységet, amelyre átváltva mindkét hossz egész számokkal számolható. Hány hüvelyk van egy lábban, egy yardban és egy mérföldben? ||
Hint 2: || Az eredményt a legkisebb egységtől felfelé bontsd szét: a maradékos osztás (%) adja a hüvelyk, a láb és a yard értékét, a hányados pedig a következő nagyobb egység. Negatív különbségnél a kiírás előtt mínusz jel kell, a visszaváltást az abszolút értékkel végezd. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egy angol hosszúság értéke a legkisebb egységben, hüvelykben.
long long toInches(long long mile, long long yard, long long foot, long long inch) {
    return ((mile * 1760 + yard) * 3 + foot) * 12 + inch;
}

// Nemnegatív hüvelykszámot ír ki mérföld, yard, láb, hüvelyk alakban.
void printLength(long long inches) {
    long long footTotal = inches / 12, in = inches % 12;
    long long yardTotal = footTotal / 3, ft = footTotal % 3;
    long long mile = yardTotal / 1760, yd = yardTotal % 1760;
    cout << mile << ' ' << yd << ' ' << ft << ' ' << in;
}

int main() {
    long long m1, y1, f1, i1, m2, y2, f2, i2;
    cin >> m1 >> y1 >> f1 >> i1;
    cin >> m2 >> y2 >> f2 >> i2;

    long long a = toInches(m1, y1, f1, i1);
    long long b = toInches(m2, y2, f2, i2);

    printLength(a + b);
    cout << '\n';

    long long d = a - b;
    if (d < 0) {
        cout << '-';
        d = -d;
    }
    printLength(d);
    cout << '\n';
    return 0;
}
