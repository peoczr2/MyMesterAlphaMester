/*
Megoldás lényege:
Minden alkalmazottra a legjobb és a legrosszabb időből kell a különbséget számolni, de a feladat szerint először minden értéket egy tizedesjegyre kell kerekíteni, és a kerekített értékekkel kell dolgozni. A kerekítés úgy történik, hogy a második tizedesjegy 5 vagy annál nagyobb esetén felfelé kerekítünk. Az értékeket tizedmásodpercben (10-szeres egész számban) tároljuk, így a kerekítés és a különbség lebegőpontos hiba nélkül számolható. Az első részfeladatnál az egyes különbségeket a bemenet sorrendjében írjuk ki egy tizedesjeggyel, a másodiknál pedig a legnagyobb különbségű alkalmazott sorszámát. Mindkét részfeladat elé egy „#” sor kerül. Az időigény O(N).
*/
/*
Hint 1: || Két részfeladat van, de mindkettő ugyanabból az adatból számolható: minden alkalmazottra a két mért érték különbségének abszolút értéke kell. A kerekítés miatt először az értékeket egy tizedesjegyre kell hozni, és csak utána képezd a különbséget. ||
Hint 2: || A számokat érdemes egész számokként kezelni: az értéket 10-szeresére szorozva tárold (például a 2.75-ből 28 lesz, mert a második tizedesjegy 5, ezért felfelé kerekítünk). A különbség így is egész szám, és a kiíráskor az utolsó jegy elé írd a tizedespontot. ||
Hint 3: || A második részfeladathoz elég egy menetben nyilvántartani az eddigi legnagyobb különbséget és az ahhoz tartozó sorszámot. A két részfeladat előtt pontosan egy „#” sort kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A szöveges értéket tizedmásodpercben adja vissza (10-szeres egész), egy tizedesjegyre kerekítve.
long long tizedesEgesz(string s) {
    replace(s.begin(), s.end(), ',', '.');
    size_t pont = s.find('.');
    string egesz = (pont == string::npos) ? s : s.substr(0, pont);
    string tort = (pont == string::npos) ? "" : s.substr(pont + 1);

    long long ertek = egesz.empty() ? 0 : stoll(egesz);
    int elso = tort.size() > 0 ? tort[0] - '0' : 0;
    int masodik = tort.size() > 1 ? tort[1] - '0' : 0;

    return ertek * 10 + elso + (masodik >= 5 ? 1 : 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> kulonbsegek(n);
    long long legnagyobb = -1;
    int legingadozobb = 0;

    for (int i = 0; i < n; i++) {
        string a, b;
        cin >> a >> b;

        long long kulonbseg = llabs(tizedesEgesz(a) - tizedesEgesz(b));
        kulonbsegek[i] = kulonbseg;

        if (kulonbseg > legnagyobb) {
            legnagyobb = kulonbseg;
            legingadozobb = i + 1;
        }
    }

    cout << "#\n";
    for (long long d : kulonbsegek) {
        cout << d / 10 << "." << d % 10 << "\n";
    }

    cout << "#\n";
    cout << legingadozobb << "\n";

    return 0;
}
