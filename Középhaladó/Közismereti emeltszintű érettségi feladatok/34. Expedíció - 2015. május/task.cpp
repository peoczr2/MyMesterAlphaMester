/*
Megoldás lényege:
Az üzeneteket fejléc (nap, amatőr) és szövegsor párokként olvassuk be; a szöveget szóközökkel együtt, sorként
kezeljük. A nyers feljegyzésekre (2., 3. részfeladat) a "farkas" előfordulását közvetlenül keressük. A napi
helyreállítás pozíciónként történik: ugyanazt az adást több amatőr rögzítette, így egy adott pozícióra a
feljegyzések bármelyikében álló nem '@' karakter a helyes; ha minden feljegyzés '@'-ot ad, a pozíció '@' marad.
A 6. részfeladatban az A. amatőr adott napi saját feljegyzésének elején álló "kifejlett/kölyök " fejlécet
olvassuk ki: a két szám összege a válasz, ha a számok után '@' áll vagy a fejléc hiányzik, a -2 értéket kell adni.
Az időigény a bemenet méretében lineáris, az üzenetek száma és hossza kicsi.
*/
/*
Hint 1: || Két különböző szűrést kell végezni: a nyers feljegyzések szövegén a "farkas" keresését, a napi csoportokon pedig az üzenetek összevonását. Egy feljegyzés fejléce a nap és az amatőr száma, a következő sor a szöveg, amelyet szóközökkel együtt kell beolvasni. ||
Hint 2: || A helyreállításhoz napokra kell gyűjteni az üzeneteket, majd minden pozícióra megnézni, van-e köztük nem '@' karakter. Az eredmény hossza a napi üzenetek közül a leghosszabbé legyen, de legfeljebb 90 karakter, és ha egy nap nincs üzenete, egyetlen '@' kerül ki. ||
Hint 3: || A 6. részfeladatban a szöveg elején "a/b " alakú számpárnak kell állnia: ha az első szám nem szám, vagy utána '@' jön, vagy a '/' után nincs szám és szóköz, a -2 jelet kell kiírni. Ha az adott amatőrnek nincs feljegyzése a napon, a -1 jelet kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Uzenet {
    int nap, rad;
    string szoveg;
};

// Egy sor beolvasása; a sor végi '\r' karaktert levágja.
bool olvas(string &sor) {
    if (!getline(cin, sor)) return false;
    while (!sor.empty() && (sor.back() == '\r' || sor.back() == '\n')) sor.pop_back();
    return true;
}

// Fejlécsor: az üres (csak szóközből álló) sorokat átugorja.
bool fejlec(string &sor) {
    while (olvas(sor))
        if (sor.find_first_not_of(" \t") != string::npos) return true;
    return false;
}

// A feljegyzés elején álló "kifejlett/kölyök " fejléc összege, vagy -2, ha nem állapítható meg.
int egyedek(const string &s) {
    size_t i = 0;
    while (i < s.size() && s[i] >= '0' && s[i] <= '9') i++;
    if (i == 0 || i >= s.size() || s[i] != '/') return -2;
    int kifejlett = stoi(s.substr(0, i));
    size_t j = ++i;
    while (i < s.size() && s[i] >= '0' && s[i] <= '9') i++;
    if (i == j || i >= s.size() || s[i] != ' ') return -2;
    int kolyok = stoi(s.substr(j, i - j));
    return kifejlett + kolyok;
}

int main() {
    int db, nk, nap, a;
    string sor;
    olvas(sor);
    {
        istringstream is(sor);
        is >> db >> nk >> nap >> a;
    }

    vector<Uzenet> uz;
    for (int i = 0; i < db; i++) {
        fejlec(sor);
        Uzenet u;
        istringstream is(sor);
        is >> u.nap >> u.rad;
        olvas(u.szoveg);
        uz.push_back(u);
    }

    // 1. részfeladat: első és utolsó feljegyző
    cout << "#\n" << uz.front().rad << " " << uz.back().rad << "\n";

    // 2. részfeladat: a "farkas" szót tartalmazó feljegyzések száma
    cout << "#\n";
    int farkasDb = 0;
    for (const Uzenet &u : uz)
        if (u.szoveg.find("farkas") != string::npos) farkasDb++;
    cout << farkasDb << "\n";

    // 3. részfeladat: ezeknek a feljegyzéseknek a napja és a feljegyző sorszáma
    cout << "#\n";
    for (const Uzenet &u : uz)
        if (u.szoveg.find("farkas") != string::npos) cout << u.nap << " " << u.rad << "\n";

    // 4. részfeladat: naponként a feljegyzést készítő különböző amatőrök száma
    cout << "#\n";
    vector<set<int>> amatorok(nk + 1);
    for (const Uzenet &u : uz) amatorok[u.nap].insert(u.rad);
    for (int d = 1; d <= nk; d++) cout << (d > 1 ? " " : "") << amatorok[d].size();
    cout << "\n";

    // 5. részfeladat: naponként a helyreállított üzenet
    cout << "#\n";
    for (int d = 1; d <= nk; d++) {
        vector<const string *> napi;
        for (const Uzenet &u : uz)
            if (u.nap == d) napi.push_back(&u.szoveg);
        cout << d << " ";
        if (napi.empty()) {
            cout << "@\n";
            continue;
        }
        // Legfeljebb 90 időegység van; a nap helyreállított üzenete a leghosszabb feljegyzés hosszát
        // veszi fel, de legfeljebb 90 karakterrel.
        size_t hossz = 0;
        for (const string *p : napi) hossz = max(hossz, min<size_t>(p->size(), 90));
        string r(hossz, '@');
        for (size_t i = 0; i < hossz; i++)
            for (const string *p : napi)
                if (i < p->size() && (*p)[i] != '@') {
                    r[i] = (*p)[i];
                    break;
                }
        cout << r << "\n";
    }

    // 6. részfeladat: az A. amatőr megfigyelt egyedeinek száma a NAP napon
    cout << "#\n";
    int valasz = -1;
    for (const Uzenet &u : uz)
        if (u.nap == nap && u.rad == a) {
            valasz = egyedek(u.szoveg);
            break;
        }
    cout << valasz << "\n";
    return 0;
}
