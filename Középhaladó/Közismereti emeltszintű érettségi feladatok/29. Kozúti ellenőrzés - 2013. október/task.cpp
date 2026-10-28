/*
Az időpontokat először másodpercre váltjuk, így a különbségek és az 5 perces ellenőrzés hossza egyszerűen kezelhető. A rendőrök munkaideje egész órákból áll, és a legkorábbi és a legkésőbbi áthaladás óráját kell lefednie, ezért a munkaórák száma az utolsó és az első óra különbsége plusz egy. A műszaki ellenőrzést óránként a legelső arra haladó jármű kapja, ezért egy 24 elemű tömbben óránként csak az első előfordulást jegyezzük fel. A leghosszabb forgalommentes időszakot a szomszédos áthaladások időpontjainak különbségéből kapjuk meg. A rendőri ellenőrzésnél egy változó tárolja, meddig tart a jelenlegi ellenőrzés, és csak az ezután érkező járművet állítják meg.
*/
/*
Hint 1: || Az időpontokat érdemes másodpercre váltani: óra * 3600 + perc * 60 + másodperc. Így a különbségek és az ellenőrzés 300 másodperces hossza is egyszerűen számolható. ||
Hint 2: || A munkaórák számához elég az első és az utolsó áthaladás órája. Az óránkénti ellenőrzéshez egy 24 elemű tömb kell, amely az adott órában eddig megtalált első jármű sorszámát tárolja. ||
Hint 3: || A rendőri ellenőrzésnél tárold, meddig tart az aktuális ellenőrzés. Egy jármű akkor áll meg, ha áthaladásának ideje ennél a határidőnél nem korábbi. A rendszámok ismétlődését set-tel szűrheted. ||
*/

#include <bits/stdc++.h>
using namespace std;

// Két rendszám illeszkedik-e a keresőkifejezésre: a * karakter bármilyen karaktert helyettesít.
bool illeszkedik(const string &kereso, const string &rendszam) {
    if (kereso.size() != rendszam.size()) return false;
    for (size_t i = 0; i < kereso.size(); i++)
        if (kereso[i] != '*' && kereso[i] != rendszam[i]) return false;
    return true;
}

// Másodpercet óra perc másodperc alakba ír (két számjeggyel, szóközzel elválasztva).
string idopont(int masodperc) {
    int ora = masodperc / 3600;
    int perc = (masodperc % 3600) / 60;
    int mp = masodperc % 60;
    string s;
    for (int x : {ora, perc, mp}) {
        if (!s.empty()) s += " ";
        if (x < 10) s += "0";
        s += to_string(x);
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string kereso;
    cin >> n >> kereso;

    vector<int> ido(n);
    vector<string> rsz(n);
    for (int i = 0; i < n; i++) {
        int ora, perc, mp;
        cin >> ora >> perc >> mp >> rsz[i];
        ido[i] = ora * 3600 + perc * 60 + mp;
    }

    // 1. részfeladat: a rendőrök legalább hány órát dolgoztak
    int elso_ora = *min_element(ido.begin(), ido.end()) / 3600;
    int utolso_ora = *max_element(ido.begin(), ido.end()) / 3600;
    cout << "#\n" << (utolso_ora - elso_ora + 1) << "\n";

    // 2. részfeladat: óránként az első arra haladó jármű, amelyet műszakilag is ellenőriznek
    vector<int> ora_elso(24, -1);  // az adott órában legkorábbi jármű indexe
    for (int i = 0; i < n; i++) {
        int ora = ido[i] / 3600;
        if (ora_elso[ora] == -1 || ido[i] < ido[ora_elso[ora]]) ora_elso[ora] = i;
    }
    cout << "#\n";
    for (int ora = 0; ora < 24; ora++) {
        if (ora_elso[ora] == -1) continue;
        string ora_szoveg = (ora < 10 ? "0" : "") + to_string(ora);
        cout << ora_szoveg << " " << rsz[ora_elso[ora]] << "\n";
    }

    // 3. részfeladat: busz, kamion, motor, személygépjármű áthaladások száma
    int busz = 0, kamion = 0, motor = 0, szemely = 0;
    for (const string &r : rsz) {
        if (r[0] == 'B') busz++;
        else if (r[0] == 'K') kamion++;
        else if (r[0] == 'M') motor++;
        else szemely++;
    }
    cout << "#\n" << busz << " " << kamion << " " << motor << " " << szemely << "\n";

    // 4. részfeladat: a leghosszabb forgalommentes időszak (a bemenet időrendben van)
    int leghosszabb = -1, hol = 1;
    for (int i = 1; i < n; i++) {
        int kulonbseg = ido[i] - ido[i - 1];
        if (kulonbseg > leghosszabb) {
            leghosszabb = kulonbseg;
            hol = i;
        }
    }
    cout << "#\n" << idopont(ido[hol - 1]) << "\n" << idopont(ido[hol]) << "\n";

    // 5. részfeladat: a keresőkifejezésre illeszkedő rendszámok
    set<string> talalatok;
    for (const string &r : rsz)
        if (illeszkedik(kereso, r)) talalatok.insert(r);
    cout << "#\n";
    if (talalatok.empty()) cout << "nincs\n";
    for (const string &r : talalatok) cout << r << "\n";

    // 6. részfeladat: a rendőri ellenőrzésen megállított járművek (egy ellenőrzés 5 percig tart)
    const int ELLENORZES_HOSSZA = 300;
    long long ellenorzes_vege = -1000000;
    set<string> megallitva;
    for (int i = 0; i < n; i++) {
        if (ido[i] >= ellenorzes_vege) {
            megallitva.insert(rsz[i]);
            ellenorzes_vege = (long long)ido[i] + ELLENORZES_HOSSZA;
        }
    }
    cout << "#\n";
    for (const string &r : megallitva) cout << r << "\n";

    return 0;
}
