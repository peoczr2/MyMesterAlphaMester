/*
Megoldás lényege:
Minden időpontot a nap kezdetétől eltelt másodpercekre váltunk, így a hívás hossza és a csúcsidős kezdés egyszerű összehasonlítással számolható. A hívás hosszából a másodpercek számát 60-nal felfelé kerekítjük, mert minden megkezdett perc egy teljes percnek számít. A hívott szám első két jegye dönti el, hogy mobil (20, 30, 70) vagy vezetékes a szám; ezt a számot szövegként kezelve egyszerű. A csúcsidős hívás kezdése 7:00:00 és 18:00:00 között van, és a csúcsidős hívások díja a percek száma szorozva a percenkénti díjjal (mobil Dm, vezetékes Dv). Az időigény O(N), N ≤ 100 mellett bőven elég.
*/
/*
Hint 1: || Az időpontokat célszerű a nap kezdetétől eltelt másodpercekre váltani, így a hívás hossza és a csúcsidős kezdés egyszerűen összehasonlítható. ||
Hint 2: || Egy megkezdett perc egy teljes perc, ezért a hívás hosszából a másodpercek számát 60-nal felfelé kerekítve kapod a díjazott percek számát. A csúcsidő a 7:00:00 és a 18:00:00 közötti kezdésű hívásokra vonatkozik. ||
Hint 3: || A hívott számot szövegként olvasd be: az első két karakter alapján dönthető el, hogy a szám mobil (20, 30, 70) vagy vezetékes. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Hivas {
    int kezd, veg;   // másodperc a nap kezdetétől
    string szam;     // a hívott szám (szövegként, az első két jegy számít)
};

bool mobil(const string& szam) {
    string e = szam.substr(0, 2);
    return e == "20" || e == "30" || e == "70";
}

// Megkezdett percek száma: a másodperceket felfelé kerekítjük percre.
long long perc(const Hivas& x) {
    long long masodperc = x.veg - x.kezd;
    return (masodperc + 59) / 60;
}

int main() {
    int n;
    cin >> n;
    long long dv, dm;
    cin >> dv >> dm;
    vector<Hivas> h(n);
    for (auto& x : h) {
        int ko, kp, kmp, vo, vp, vmp;
        cin >> ko >> kp >> kmp >> vo >> vp >> vmp >> x.szam;
        x.kezd = ko * 3600 + kp * 60 + kmp;
        x.veg = vo * 3600 + vp * 60 + vmp;
    }
    const int CSUCS_KEZD = 7 * 3600, CSUCS_VEG = 18 * 3600;

    // 1. részfeladat: a hívott számok mobil (m) vagy vezetékes (v) volta
    cout << "#\n";
    for (const auto& x : h) cout << (mobil(x.szam) ? 'm' : 'v');
    cout << "\n";

    // 2. részfeladat: hívásonként a hívás hossza (percben) és a hívott szám
    cout << "#\n";
    bool elso = true;
    for (const auto& x : h) {
        if (!elso) cout << " ";
        cout << perc(x) << " " << x.szam;
        elso = false;
    }
    cout << "\n";

    // 3. részfeladat: csúcsidőben és azon kívül indult hívások száma
    int csucsban = 0, kivul = 0;
    for (const auto& x : h) {
        if (x.kezd >= CSUCS_KEZD && x.kezd < CSUCS_VEG) csucsban++;
        else kivul++;
    }
    cout << "#\n" << csucsban << " " << kivul << "\n";

    // 4. részfeladat: a mobil és a vezetékes számmal beszélt percek
    long long mobil_perc = 0, vezetekes_perc = 0;
    for (const auto& x : h) {
        if (mobil(x.szam)) mobil_perc += perc(x);
        else vezetekes_perc += perc(x);
    }
    cout << "#\n" << mobil_perc << " " << vezetekes_perc << "\n";

    // 5. részfeladat: a csúcsidőben folytatott beszélgetések díja
    long long dij = 0;
    for (const auto& x : h) {
        if (x.kezd >= CSUCS_KEZD && x.kezd < CSUCS_VEG)
            dij += perc(x) * (mobil(x.szam) ? dm : dv);
    }
    cout << "#\n" << dij << "\n";
    return 0;
}
