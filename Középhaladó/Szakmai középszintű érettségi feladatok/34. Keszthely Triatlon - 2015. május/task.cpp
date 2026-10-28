/*
Megoldás lényege:
A bemenet első sorából az N versenyzőszámot és a K kategóriát olvassuk. Minden versenyző sorából a nevet, a születési évet, a rajtszámot, a nemet és a kategóriát olvassuk, majd az öt időt perc:másodperc alakból másodperccé alakítjuk (perc * 60 + másodperc), és összegezzük; a másodpercek 60 fölé is mehetnek, ez az összegzést nem zavarja. A K kategóriába tartozók rajtszámait a bemenet sorrendjében gyűjtjük, az első részfeladatban ezek darabszámát és a rajtszámokat írjuk ki. Az életkor 2014 - születési év, az átlagot az életkorok összegéből és N-ből kapjuk, és egész aritmetikával kerekítjük egy tizedesjegyre. A női (n) versenyzőknél nyilvántartjuk a legkisebb összidőt, és az azt elérő nevek a bemenet sorrendjében kerülnek a kimenetbe. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Az idő perc:másodperc alakú, de a másodperc mező 60-nál nagyobb is lehet (például 01:82), ezért ne normalizáld az értéket. Ha a perc értéket 60-nal szorzod, és hozzáadod a másodpercet, az összegzés így is pontos. ||
Hint 2: || Az átlag tizedesjegyre kerekítését egész számokkal is elvégezheted: a számlálóhoz a nevező felét hozzáadva, majd osztva a 10-szeres értéket adó egész osztással, a félértéknél felfelé kerekítő eredményt kapsz. Így nincs lebegőpontos hiba. ||
Hint 3: || A női versenyzőknél tartsd nyilván a legkisebb összidőt. Ha új, kisebb időt találsz, az eddig gyűjtött nevek listáját ürítsd ki, ha egyenlő az idő, add hozzá a nevet. Mivel a versenyzőket egyszer olvasod végig, a bemenet sorrendje megmarad. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A "perc:másodperc" alakú időt másodpercre váltja
long long masodperc(const string& ido) {
    size_t kettospont = ido.find(':');
    long long perc = stoll(ido.substr(0, kettospont));
    long long mp = stoll(ido.substr(kettospont + 1));
    return perc * 60 + mp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> rajtszamok;
    long long eletkorOsszeg = 0;
    long long legjobbIdo = LLONG_MAX;
    vector<string> gyoztesek;

    for (int i = 0; i < n; i++) {
        string nev, nem, ido;
        int szuletesiEv, rajtszam, kategoria;
        cin >> nev >> szuletesiEv >> rajtszam >> nem >> kategoria;

        long long osszIdo = 0;
        for (int j = 0; j < 5; j++) {
            cin >> ido;
            osszIdo += masodperc(ido);
        }

        if (kategoria == k) rajtszamok.push_back(rajtszam);
        eletkorOsszeg += 2014 - szuletesiEv;

        if (nem == "n") {
            if (osszIdo < legjobbIdo) {
                legjobbIdo = osszIdo;
                gyoztesek.clear();
            }
            if (osszIdo == legjobbIdo) gyoztesek.push_back(nev);
        }
    }

    // 1. részfeladat: a K kategóriában indulók száma és rajtszámai
    cout << "#\n";
    cout << rajtszamok.size();
    for (int r : rajtszamok) cout << " " << r;
    cout << "\n";

    // 2. részfeladat: az átlagéletkor egy tizedesjegyre kerekítve
    cout << "#\n";
    long long tized = (20 * eletkorOsszeg + n) / (2LL * n);
    cout << tized / 10 << "." << tized % 10 << "\n";

    // 3. részfeladat: a legjobb összidejű női versenyző(k) neve
    cout << "#\n";
    for (const string& nev : gyoztesek) cout << nev << "\n";

    return 0;
}
