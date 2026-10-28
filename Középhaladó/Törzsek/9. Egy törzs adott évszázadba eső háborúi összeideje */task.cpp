/*
Megoldás lényege:
Minden háborút a kezdő és a befejező év közötti zárt évintervallumnak tekintünk, mindkét szélső évvel együtt. Csak azokat a háborúkat vesszük figyelembe, amelyekben az S törzs az egyik fél.
Egy ilyen háború a megadott Sz századba eső részének hosszát úgy kapjuk, hogy a háború intervallumát a század [alsó, felső] intervallumára metsszük, és a metszet hosszát (+1) adjuk az összeghez, ha a metszet nem üres.
A feladat szerint minden háborús év annyiszor számít, ahány háború volt abban az évben, ezért az egyes háborúk metszethosszainak összege pontosan a kért érték.
A római századszámot a záró pont elhagyása után XVII, XVIII vagy XIX alakban kezeljük, és a századhatárok: XVII. 1601–1700, XVIII. 1701–1800, XIX. 1801–1900.
Az idő O(K), ahol K a háborúk száma, ez bőven belefér a 0,3 mp-es időlimitbe.
*/
/*
Hint 1: || Nem kell évenként végigmenni: elég minden, az S törzset érintő háborúra külön kiszámolni, hány év esik az Sz századba, és ezeket összeadni. Az összeg így egyezik azzal, ahogy a feladat az éveket számolja. ||
Hint 2: || A század évei: XVII. = 1601–1700, XVIII. = 1701–1800, XIX. = 1801–1900. Egy háború a században a [kezdet, vége] és a [alsó, felső] intervallumok közös része: hossza min(vége, felső) − max(kezdet, alsó) + 1, ha ez nem negatív. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A római századszámból (XVII., XVIII., XIX.) a sorszámot adja vissza: 17, 18 vagy 19.
int szazadSorszam(string s) {
    s.erase(remove(s.begin(), s.end(), '.'), s.end());
    if (s == "XVII") return 17;
    if (s == "XVIII") return 18;
    return 19; // XIX
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 4>> haboru(k); // {háborúzó, ellenség, kezdet, befejezés}
    for (auto& h : haboru) cin >> h[0] >> h[1] >> h[2] >> h[3];

    int s;
    string szazad;
    cin >> s >> szazad;

    int c = szazadSorszam(szazad);
    int also = (c - 1) * 100 + 1; // a század első éve
    int felso = c * 100;          // a század utolsó éve

    long long osszeg = 0;
    for (const auto& h : haboru) {
        if (h[0] != s && h[1] != s) continue; // csak az S törzs háborúi
        int kezdet = max(h[2], also);
        int vege = min(h[3], felso);
        if (kezdet <= vege) osszeg += vege - kezdet + 1;
    }

    cout << osszeg << '\n';
    return 0;
}
