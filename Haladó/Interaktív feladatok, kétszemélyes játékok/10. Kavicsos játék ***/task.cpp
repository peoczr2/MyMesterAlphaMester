/*
Megoldás lényege:
A játék Wythoff-játék: egy lépésben az egyik kupacból tetszőleges számút, vagy mindkettőből azonos számú kavicsot vehetünk el.
A vesztes (P-) pozíciók ismertek: a (0,0), majd minden k >= 1-re (a_k, b_k), ahol a_k a legkisebb még nem szereplő
nemnegatív egész, b_k = a_k + k. A kezdő akkor nyer, ha a kezdőállás nem vesztes pozíció (a feladat ezt garantálja).
Minden lépésben olyan lépést teszünk, amely vesztes pozícióba visz; ilyen lépés mindig van. A táblázat a legnagyobb
kupacméretig előre elkészíthető, egy lépés ennek lineáris bejárásával megtalálható. A KavicsokSzama(m,n) adja a
kupacok kezdeti méretét, az EnLepesem(k1,k2) hívással közöljük a lépésünket, majd a TeLepesed(k1,k2) adja az
ellenfél lépését (az első és a második kupacból elvett kavicsok száma).
*/
/*
Hint 1: || Ez Wythoff-játék: a két kupacnak nem a mérete, hanem az, hogy a pozíció vesztes-e, dönti el a nyerést. Keresd a vesztes pozíciókat. ||
Hint 2: || A vesztes párok (a_k, b_k) úgy kaphatók, hogy a_k a legkisebb még nem használt szám, b_k = a_k + k, és mindkét számot megjelöljük. ||
Hint 3: || Az aktuális (m, n) állapotból keress olyan vesztes (x, y) párt, amelyet az egyik kupacból vagy mindkettőből azonos számú elvétellel el tudsz érni, és ezt a lépést tedd meg. ||
*/
#include "Ellenfel.h"
#include <bits/stdc++.h>
using namespace std;

const int HATAR = 20000;                 // ennyi nagyságig készítjük el a vesztes pozíciókat
vector<pair<int, int>> P;                // a vesztes párok (a_k, b_k), k = 0, 1, ...

// Olyan (k1, k2) lépés, amely (m, n) pozícióból vesztes pozícióba visz.
pair<int, int> lepes(int m, int n) {
    int legnagyobb = max(m, n);
    for (auto [a, b] : P) {
        if (a > legnagyobb) break;
        for (int t = 0; t < 2; t++) {
            int x = t ? b : a;           // az első kupac célértéke
            int y = t ? a : b;           // a második kupac célértéke
            if (x > m || y > n) continue;
            int dx = m - x, dy = n - y;  // ennyit kell elvenni a kupacokból
            if (dx + dy == 0) continue;
            if (dx == 0 || dy == 0 || dx == dy) return {dx, dy};
        }
    }
    return {0, 0};                       // nem fordulhat elő, ha a kezdőállás nyerő
}

int main() {
    vector<char> hasznalt(4 * HATAR, 0);
    P.push_back({0, 0});
    hasznalt[0] = 1;
    for (int k = 1;; k++) {
        int a = 1;
        while (hasznalt[a]) a++;
        if (a > HATAR) break;
        int b = a + k;
        hasznalt[a] = hasznalt[b] = 1;
        P.push_back({a, b});
    }

    int m, n;
    KavicsokSzama(m, n);                 // a két kupac kezdeti kavicsszáma
    for (;;) {
        auto [k1, k2] = lepes(m, n);
        EnLepesem(k1, k2);               // a mi lépésünk; az utolsó lépésnél a modul befejezi a programot
        m -= k1;
        n -= k2;
        if (m == 0 && n == 0) return 0;
        int a, b;
        TeLepesed(a, b);                 // az ellenfél lépése
        m -= a;
        n -= b;
        if (m == 0 && n == 0) return 0;
    }
}
