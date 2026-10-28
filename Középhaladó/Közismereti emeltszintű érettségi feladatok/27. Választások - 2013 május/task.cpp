/*
Megoldás lényege:
Minden jelöltet egy rekordként tárolunk: választókerület, szavazatszám, vezetéknév, utónév és párt. A részvételi arányt és a párti arányokat egész százalékra kerekítjük a 200*r + n / 2n képlettel, így nincs lebegőpontos pontatlanság.
Az 1. kérdésben egy bejárással keressük a Jelölt nevét, nem találat esetén -1.
A 2. kérdésben a szavazatok összege adja a leadott szavazatok számát, ebből a részvételi arány az M választójogosult ismeretében számolható.
A 3. kérdésben pártonként összegezzük a jelöltek szavazatait, és ezt viszonyítjuk az összes leadott szavazathoz.
A 4. és 5. kérdésben egy-egy lineáris maximumkeresés elég: az összesített maximumot, illetve kerületenként a legtöbb szavazatot kapó jelöltet keressük, döntetlennél a bemenetben előbb szereplő nyer.
Az időigény O(N * (P + VK)), ami a korlátok mellett bőven elfér.
*/
/*
Hint 1: || Egy jelölt adatait érdemes egy rekordban tárolni: választókerület, szavazatszám, vezetéknév, utónév és párt. Ezután minden kérdés a rekordok egy-egy bejárásával megválaszolható. ||
Hint 2: || A kerekítés egész számokkal is pontosan megoldható: a p/q arány százalékos értéke round(100 * p / q), ami egész számtani alakban (200 * p + q) / (2 * q) módon adódik. A nulla nevezőt külön kezeld. ||
Hint 3: || Kerületenként külön maximumkeresés kell: a k. kerület nyertese az a jelölt, akinek a választókerület-száma k, és a szavazatszáma a legnagyobb. Ha nincs ilyen jelölt, a sor végére a „nincs nyertes” szöveg kerül. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Jelolt {
    int kerulet;
    long long szavazat;
    string vezeteknev;
    string utonev;
    string part;
};

// A resz / egesz arány százaléka egészre kerekítve (félre felfelé), egész számtani alakban.
long long szazalek(long long resz, long long egesz) {
    if (egesz == 0) return 0;
    return (200 * resz + egesz) / (2 * egesz);
}

int main() {
    int M, N, VK, P;
    string vnev, unev;
    cin >> M >> N >> VK >> P >> vnev >> unev;

    vector<string> partok(P);
    for (string& p : partok) cin >> p;

    vector<Jelolt> jeloltek(N);
    for (Jelolt& j : jeloltek)
        cin >> j.kerulet >> j.szavazat >> j.vezeteknev >> j.utonev >> j.part;

    // 1. részfeladat: a megadott jelölt szavazatai (ha nincs a nyilvántartásban, -1)
    cout << "#\n";
    long long kapott = -1;
    for (const Jelolt& j : jeloltek)
        if (j.vezeteknev == vnev && j.utonev == unev) kapott = j.szavazat;
    cout << kapott << "\n";

    // 2. részfeladat: a leadott szavazatok száma és a részvételi arány (egészre kerekítve)
    cout << "#\n";
    long long osszes = 0;
    for (const Jelolt& j : jeloltek) osszes += j.szavazat;
    cout << osszes << " " << szazalek(osszes, M) << "\n";

    // 3. részfeladat: pártonként a leadott szavazatok aránya (P sor)
    cout << "#\n";
    for (const string& p : partok) {
        long long pSzavazat = 0;
        for (const Jelolt& j : jeloltek)
            if (j.part == p) pSzavazat += j.szavazat;
        cout << p << " " << szazalek(pSzavazat, osszes) << "\n";
    }

    // 4. részfeladat: a legtöbb szavazatot kapó jelölt (döntetlennél az első)
    cout << "#\n";
    int legjobb = 0;
    for (int i = 1; i < N; i++)
        if (jeloltek[i].szavazat > jeloltek[legjobb].szavazat) legjobb = i;
    cout << jeloltek[legjobb].vezeteknev << " " << jeloltek[legjobb].utonev << " "
         << jeloltek[legjobb].part << "\n";

    // 5. részfeladat: kerületenként a nyertes (sorszám szerint növekvő sorrendben)
    cout << "#\n";
    for (int k = 1; k <= VK; k++) {
        int nyertes = -1;
        for (int i = 0; i < N; i++)
            if (jeloltek[i].kerulet == k &&
                (nyertes < 0 || jeloltek[i].szavazat > jeloltek[nyertes].szavazat))
                nyertes = i;
        cout << k;
        if (nyertes < 0) {
            cout << " nincs nyertes\n";
        } else {
            cout << " " << jeloltek[nyertes].vezeteknev << " " << jeloltek[nyertes].utonev << " "
                 << jeloltek[nyertes].part << "\n";
        }
    }

    return 0;
}
