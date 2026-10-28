/*
Megoldás lényege:
A bent lévő felhasználók száma csak eseményekkor változik, ezért elég az eseményeket időrendbe rakni (stabil rendezés, azonos időpontnál marad a bemeneti sorrend), és végigmenni rajtuk. Minden változásnál lezárjuk az addigi szakaszt. Aki első eseménye KI, az előző naptól bent van: őt a kezdeti létszámba beszámítjuk. Az érvénytelen műveleteket (már bent lévő felhasználó BE-je, ki nem jelentkezett felhasználó KI-ja) figyelmen kívül hagyjuk. Az azonos időpontú eseményeket együtt dolgozzuk fel, így nem keletkeznek nulla hosszúságú szakaszok. A legtöbb felhasználót tartalmazó szakaszok számát, kezdetét és végét írjuk ki. Az időigény O(N log N), a set és a map miatt.
*/
/*
Hint 1: || Tartsd nyilván felhasználónként, hogy éppen bent van-e. Egy BE csak akkor növeli a bent lévők számát, ha a felhasználó ki volt jelentkezve, és egy KI csak akkor csökkenti, ha bent volt. ||
Hint 2: || A nap elején bent lévők azok, akiknek az első eseménye KI: ezeket előre számold bele a kezdeti létszámba és állítsd be bent-nek. Az eseményeket időrendben dolgozd fel, és amikor a létszám változik, zárd le az addigi szakaszt a változás időpontjával. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Szakasz {
    int kezdet, veg, letszam;   // percek a nap elejétől
};

struct Esemeny {
    string muvelet, nev;
    int ido;                    // az időpont percben
};

int main() {
    int n;
    cin >> n;
    vector<Esemeny> esemenyek(n);
    for (Esemeny& e : esemenyek) {
        int ora, perc;
        cin >> e.muvelet >> e.nev >> ora >> perc;
        e.ido = ora * 60 + perc;
    }
    stable_sort(esemenyek.begin(), esemenyek.end(),
                [](const Esemeny& a, const Esemeny& b) { return a.ido < b.ido; });

    // Kezdeti állapot: aki első eseménye KI, az előző naptól bent van.
    set<string> latott;
    map<string, bool> bent;
    int letszam = 0;
    for (const Esemeny& e : esemenyek) {
        if (latott.insert(e.nev).second && e.muvelet == "KI") {
            bent[e.nev] = true;
            letszam++;
        }
    }

    // Az azonos időpontú események együtt számítanak.
    vector<Szakasz> szakaszok;
    int aktualisKezdet = 0, aktualisLetszam = letszam;
    int i = 0;
    while (i < n) {
        int t = esemenyek[i].ido;
        int ujLetszam = aktualisLetszam;
        while (i < n && esemenyek[i].ido == t) {
            const Esemeny& e = esemenyek[i];
            if (e.muvelet == "BE") {
                if (!bent[e.nev]) {
                    bent[e.nev] = true;
                    ujLetszam++;
                }
            } else {
                if (bent[e.nev]) {
                    bent[e.nev] = false;
                    ujLetszam--;
                }
            }
            i++;
        }
        if (ujLetszam != aktualisLetszam) {
            if (aktualisKezdet < t) szakaszok.push_back({aktualisKezdet, t, aktualisLetszam});
            aktualisKezdet = t;
            aktualisLetszam = ujLetszam;
        }
    }
    szakaszok.push_back({aktualisKezdet, 24 * 60, aktualisLetszam});

    int legtobb = 0;
    for (const Szakasz& s : szakaszok) legtobb = max(legtobb, s.letszam);

    int db = 0;
    for (const Szakasz& s : szakaszok)
        if (s.letszam == legtobb) db++;

    cout << db;
    for (const Szakasz& s : szakaszok)
        if (s.letszam == legtobb)
            cout << " " << s.kezdet / 60 << " " << s.kezdet % 60
                 << " " << s.veg / 60 << " " << s.veg % 60;
    cout << endl;
    return 0;
}
