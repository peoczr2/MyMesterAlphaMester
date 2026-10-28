/*
Megoldás lényege:
A fuvarok nincsenek időrendben, ezért a hét első és utolsó útját a (nap, fuvar sorszáma) rendezett pár alapján keressük meg: az első a legkisebb, az utolsó a legnagyobb ilyen pár. Naponként összesítjük a fuvarok számát és a megtett kilométereket, így a nem dolgozott napok azok, amelyekhez nincs fuvar, a legtöbb fuvaros nap pedig a legnagyobb fuvarszámú. Egy út díját a hossza alapján az a kategória adja, amelynek Tóli és Igi közötti tartományába az út hossza esik. A heti bér az összes fuvar díjának összege. Legfeljebb 240 fuvar és 7 nap van, így minden lépés gyorsan lefut.
*/
/*
Hint 1: || A fuvarok nincsenek időrendben, ezért a hét első és utolsó útját ne a beolvasási sorrendből határozd meg, hanem a nap és a napon belüli fuvarszám alapján. ||
Hint 2: || Napi tömbökben számold a fuvarok számát és a megtett kilométereket. Az út díját úgy kapod meg, hogy megkeresed azt a kategóriát, amelynek Tóli és Igi közé esik a hossza. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Kategoria {
    int tol;
    int ig;
    int dij;
};

struct Fuvar {
    int nap;
    int sorszam;
    int km;
};

int main() {
    int n, tavolsag;
    cin >> n >> tavolsag;

    vector<Kategoria> kategoriak(5);
    for (Kategoria& k : kategoriak) {
        cin >> k.tol >> k.ig >> k.dij;
    }

    vector<Fuvar> fuvarok(n);
    for (Fuvar& f : fuvarok) {
        cin >> f.nap >> f.sorszam >> f.km;
    }

    auto dijat = [&](int km) {
        for (const Kategoria& k : kategoriak) {
            if (k.tol <= km && km <= k.ig) return k.dij;
        }
        return 0;
    };

    // 1. és 2. részfeladat: a hét első és utolsó útja
    const Fuvar* elso = &fuvarok[0];
    const Fuvar* utolso = &fuvarok[0];
    for (const Fuvar& f : fuvarok) {
        if (make_pair(f.nap, f.sorszam) < make_pair(elso->nap, elso->sorszam)) elso = &f;
        if (make_pair(f.nap, f.sorszam) > make_pair(utolso->nap, utolso->sorszam)) utolso = &f;
    }
    cout << "#\n" << elso->km << "\n";
    cout << "#\n" << utolso->km << "\n";

    // napi fuvarszám és napi kilométer (a napok 1-től 7-ig)
    int fuvarDb[8] = {0};
    int napiKm[8] = {0};
    for (const Fuvar& f : fuvarok) {
        fuvarDb[f.nap]++;
        napiKm[f.nap] += f.km;
    }

    // 3. részfeladat: a nem dolgozott napok
    cout << "#\n";
    bool elsoSzam = true;
    for (int nap = 1; nap <= 7; nap++) {
        if (fuvarDb[nap] == 0) {
            if (!elsoSzam) cout << ' ';
            cout << nap;
            elsoSzam = false;
        }
    }
    cout << "\n";

    // 4. részfeladat: a legtöbb fuvaros nap
    int legtobb = 1;
    for (int nap = 2; nap <= 7; nap++) {
        if (fuvarDb[nap] > fuvarDb[legtobb]) legtobb = nap;
    }
    cout << "#\n" << legtobb << "\n";

    // 5. részfeladat: napi kilométerek
    cout << "#\n";
    for (int nap = 1; nap <= 7; nap++) {
        if (nap > 1) cout << ' ';
        cout << napiKm[nap];
    }
    cout << "\n";

    // 6. részfeladat: a Táv hosszú út díja
    cout << "#\n" << dijat(tavolsag) << "\n";

    // 7. részfeladat: a heti bér
    long long heti = 0;
    for (const Fuvar& f : fuvarok) {
        heti += dijat(f.km);
    }
    cout << "#\n" << heti << "\n";

    return 0;
}
