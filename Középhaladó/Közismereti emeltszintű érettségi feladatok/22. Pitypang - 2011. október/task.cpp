/*
Megoldás lényege:
Egy foglalás éjszakái a [érkezés, távozás) félnyílt intervallumot alkotják, ezért két foglalás csak akkor ütközik, ha az éjszakáik intervalluma átfedi egymást. A foglalás ára az érkezés napjának szezonjától függ: az egy éjszakai szobaár plusz 2000 Ft pótágy, ha 3 vendég van, és vendégenként 1100 Ft reggeli, ha kérnek; ezt az éjszakák számával szorozzuk. A leghosszabb tartózkodás a távozás és az érkezés különbsége. A havi vendégéjszakákat egy napokra vonatkozó különbségtömbbel számoljuk: az érkezés napján hozzáadjuk a vendégek számát, a távozás napján levonjuk, majd a napi összeget a hónapokhoz rendeljük. Az új foglalás szabad szobáit úgy kapjuk, hogy minden olyan szobát kizárunk, amelyben átfedő foglalás van. Mivel N legfeljebb 35000, minden részfeladat O(N + 365) lépésben lefut.
*/
/*
Hint 1: || Az éjszakákat érdemes napokhoz kötve kezelni: egy foglalás az érkezés napjától a távozás napja előtti napig foglal éjszakát. Két foglalás csak akkor ütközik, ha az éjszakáik átfedik egymást. ||
Hint 2: || A foglalás ára az érkezés napjának szezonjától függ, és az éjszakák számával szorzódik. Figyelj arra, hogy a pótágy csak 3 vendégnél jár, a reggeli pedig vendégenként számít. ||
Hint 3: || A havi vendégéjszakákhoz elég egy napokra vonatkozó különbségtömb: az érkezés napján hozzáadod a vendégek számát, a távozás napján levonod, majd a napokat hónapok szerint összegzed. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Honap {
    string nev;
    int napok;
    int elso;  // a hónap első napjának sorszáma (január 1. = 1)
};

struct Foglalas {
    int sorszam;
    int szoba;
    int erkezes;
    int tavozas;
    int vendegek;
    int reggeli;
    string azonosito;
};

// Egy szoba ára egy éjszakára az érkezés napja alapján.
// Tavasz: 1-120. nap, nyár: 121-243. nap, ősz: 244-365. nap.
long long szobaAr(int nap) {
    if (nap < 121) return 9000;
    if (nap < 244) return 10000;
    return 8000;
}

// A foglalás teljes ára: az éjszakánkénti ár az éjszakák számával szorozva.
long long foglalasAr(const Foglalas& f) {
    long long ejszakankent = szobaAr(f.erkezes);
    if (f.vendegek == 3) ejszakankent += 2000;  // pótágy
    if (f.reggeli == 1) ejszakankent += 1100LL * f.vendegek;
    return ejszakankent * (f.tavozas - f.erkezes);
}

int main() {
    vector<Honap> honapok(12);
    for (Honap& h : honapok) {
        cin >> h.nev >> h.napok >> h.elso;
    }

    int k, n;
    cin >> k >> n;
    vector<Foglalas> foglalasok(n);
    for (Foglalas& f : foglalasok) {
        cin >> f.sorszam >> f.szoba >> f.erkezes >> f.tavozas >> f.vendegek >> f.reggeli >> f.azonosito;
    }

    int ujErkezes, ujNapok;
    cin >> ujErkezes >> ujNapok;
    int ujTavozas = ujErkezes + ujNapok;

    // Melyik hónaphoz tartozik az egyes nap (0-tól számozott hónap-index)
    vector<int> honapIndex(366, 0);
    for (int h = 0; h < 12; h++) {
        for (int nap = honapok[h].elso; nap < honapok[h].elso + honapok[h].napok; nap++) {
            honapIndex[nap] = h;
        }
    }

    // 1. részfeladat: a leghosszabb tartózkodás
    const Foglalas* leghosszabb = &foglalasok[0];
    for (const Foglalas& f : foglalasok) {
        if (f.tavozas - f.erkezes > leghosszabb->tavozas - leghosszabb->erkezes) {
            leghosszabb = &f;
        }
    }
    cout << "#\n"
         << leghosszabb->azonosito << ' ' << leghosszabb->erkezes << ' '
         << (leghosszabb->tavozas - leghosszabb->erkezes) << "\n";

    // 2. részfeladat: foglalásonként a fizetett összeg
    cout << "#\n";
    for (const Foglalas& f : foglalasok) {
        cout << f.sorszam << ' ' << foglalasAr(f) << "\n";
    }

    // 3. részfeladat: a teljes évi bevétel
    long long bevetel = 0;
    for (const Foglalas& f : foglalasok) {
        bevetel += foglalasAr(f);
    }
    cout << "#\n" << bevetel << "\n";

    // 4. részfeladat: vendégéjszakák havonta
    vector<long long> kulonbseg(367, 0);
    for (const Foglalas& f : foglalasok) {
        kulonbseg[f.erkezes] += f.vendegek;
        kulonbseg[f.tavozas] -= f.vendegek;
    }
    vector<long long> vendegejszakak(12, 0);
    long long aktualis = 0;  // az adott napon éjszakázó vendégek száma
    for (int nap = 1; nap <= 365; nap++) {
        aktualis += kulonbseg[nap];
        vendegejszakak[honapIndex[nap]] += aktualis;
    }
    cout << "#\n";
    for (long long db : vendegejszakak) {
        cout << db << "\n";
    }

    // 5. részfeladat: az új foglalás teljes időszakában szabad szobák száma
    vector<bool> foglalt(k + 1, false);
    for (const Foglalas& f : foglalasok) {
        if (f.erkezes < ujTavozas && ujErkezes < f.tavozas) {
            foglalt[f.szoba] = true;
        }
    }
    int szabad = 0;
    for (int s = 1; s <= k; s++) {
        if (!foglalt[s]) szabad++;
    }
    cout << "#\n" << szabad << "\n";

    return 0;
}
