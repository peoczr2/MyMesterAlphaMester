/*
Megoldás lényege:
Minden rádió számait egymás után, szünet nélkül játsszák, ezért egy szám kezdési ideje ugyanazon a rádión a korábbi számok hosszának összege. A bemenet már az elhangzás sorrendjében van, így a számokat egyetlen bejárással, sorban dolgozhatjuk fel. A számlálás, az E első és utolsó számának különbsége az 1. adón, valamint az SZ kezdetekor hallható számok keresése mind egyszerű bejárás a kezdési és befejezési idők alapján. Az X karaktersorozat illeszkedését mohón ellenőrizzük: az azonosítón végigmegyünk, és az egyező betűknél előrelépünk X-ben, a kis- és nagybetű különbség nélkül. Az új szerkezetben az 1. adón egy szimulációval követjük az időt: minden szám elé 1 perc bevezető kerül, és minden egész órában (a 0. percben is) 3 perces hír szól, a szám pedig csak akkor kezdődik, ha bevezetővel együtt a következő hír előtt befejeződik. Az időigény O(Z), ami a korlátok mellett messze elfér.
*/
/*
Hint 1: || Egy rádió számai egymás után szólnak, szünet nélkül, így egy szám kezdési ideje ugyanazon a rádión a korábbi számok hosszának összege. A bemenet már az elhangzás sorrendjében van, tehát a számokat sorban dolgozhatod fel. ||
Hint 2: || A 2., 3. és 4. részfeladat időtartományokkal dolgozik: egy szám a [kezdet, kezdet + hossz) intervallumban szól. Az SZ kezdeténél rádiónként azt a számot keresd, amelynek intervalluma tartalmazza ezt az időpontot. ||
Hint 3: || Az X-re illeszkedéshez járd végig a szám azonosítóját, és ha az aktuális betű megegyezik X következő betűjével, lépj előre X-ben. Ha X minden betűje megtalálható sorrendben, a szám illeszkedik. A mintából kiderül, hogy a kis- és nagybetűk között nem teszünk különbséget. ||
Hint 4: || Az 1. adó új szerkezetéhez tartsd nyilván az aktuális időt, és minden számnál vedd figyelembe az 1 perces bevezetőt, valamint a következő egész órában (a 0. percben is) kezdődő 3 perces hírt. Ha a szám bevezetővel együtt nem fejeződik be a hír kezdetéig, az időt a hír végére ugratod, és a számot utána kezded. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Zeneszam {
    int radio;
    long long kezdet;
    long long hossz;
    string azonosito;
    string eloado;
};

string levag(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

// Idő kiírása óra:perc:másodperc alakban, vezető nullák nélkül.
string idoSzoveg(long long mp) {
    return to_string(mp / 3600) + ":" + to_string(mp % 3600 / 60) + ":" + to_string(mp % 60);
}

// Igaz, ha x karakterei sorrendben megtalálhatók a szövegben (kis- és nagybetű nem számít).
bool reszsorozat(const string& x, const string& szoveg) {
    size_t j = 0;
    for (unsigned char c : szoveg) {
        if (j < x.size() && tolower(c) == tolower((unsigned char)x[j])) j++;
    }
    return j == x.size();
}

int main() {
    string eloado, sz, x;
    getline(cin, eloado);
    getline(cin, sz);
    getline(cin, x);
    eloado = levag(eloado);
    sz = levag(sz);
    x = levag(x);

    int z;
    cin >> z;

    vector<Zeneszam> zenek(z);
    long long kovetkezo[4] = {0, 0, 0, 0};  // rádiónként a következő szám kezdete
    for (Zeneszam& s : zenek) {
        long long perc, masodperc;
        cin >> s.radio >> perc >> masodperc;
        string rest;
        getline(cin, rest);
        s.azonosito = levag(rest);
        s.eloado = s.azonosito.substr(0, s.azonosito.find(':'));
        s.hossz = perc * 60 + masodperc;
        s.kezdet = kovetkezo[s.radio];
        kovetkezo[s.radio] += s.hossz;
    }

    // 1. részfeladat: számok rádiónként
    long long db[4] = {0, 0, 0, 0};
    for (const Zeneszam& s : zenek) db[s.radio]++;
    cout << "#\n";
    cout << db[1] << " " << db[2] << " " << db[3] << "\n";

    // 2. részfeladat: E első számának kezdete és utolsó számának vége az 1. adón
    long long elsoKezdet = -1, utolsoVeg = -1;
    for (const Zeneszam& s : zenek) {
        if (s.radio == 1 && s.eloado == eloado) {
            if (elsoKezdet < 0) elsoKezdet = s.kezdet;
            utolsoVeg = s.kezdet + s.hossz;
        }
    }
    cout << "#\n";
    cout << idoSzoveg(utolsoVeg - elsoKezdet) << "\n";

    // 3. részfeladat: az SZ szám rádiója és kezdete
    int szRadio = 0;
    long long szKezdet = 0;
    for (const Zeneszam& s : zenek) {
        if (s.azonosito == sz) {
            szRadio = s.radio;
            szKezdet = s.kezdet;
            break;
        }
    }
    cout << "#\n";
    cout << szRadio << "\n";

    // 4. részfeladat: a másik két rádión az SZ kezdetekor szóló számok
    cout << "#\n";
    for (int r = 1; r <= 3; r++) {
        if (r == szRadio) continue;
        for (const Zeneszam& s : zenek) {
            if (s.radio == r && s.kezdet <= szKezdet && szKezdet < s.kezdet + s.hossz) {
                cout << s.azonosito << "\n";
                break;
            }
        }
    }

    // 5. részfeladat: az X-re illeszkedő számok, elhangzás sorrendjében
    vector<const Zeneszam*> talalatok;
    for (const Zeneszam& s : zenek) {
        if (reszsorozat(x, s.azonosito)) talalatok.push_back(&s);
    }
    cout << "#\n";
    cout << talalatok.size() << "\n";
    for (const Zeneszam* s : talalatok) cout << s->azonosito << "\n";

    // 6. részfeladat: az adás vége az új szerkezetben, az 1. adón
    const long long BEVEZETO = 60, HIR = 180, ORA = 3600;
    long long t = 0;
    for (const Zeneszam& s : zenek) {
        if (s.radio != 1) continue;
        while (true) {
            long long kovHir = (t + ORA - 1) / ORA * ORA;  // a következő egész óra, t-nél nem kisebb
            if (t + BEVEZETO + s.hossz <= kovHir) {
                t += BEVEZETO + s.hossz;
                break;
            }
            t = kovHir + HIR;  // a szám a hírek után kezdődik
        }
    }
    cout << "#\n";
    cout << idoSzoveg(t) << "\n";
    return 0;
}
