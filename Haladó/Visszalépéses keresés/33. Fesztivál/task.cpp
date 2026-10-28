/*
Megoldás lényege:
Visszalépéses keresés a beosztásra: minden lépésben a még be nem osztott, legkevesebb szabad helyszínnel rendelkező embert választjuk, mert ez korán kiszűri a zsákutcákat. Zsákutca, ha valakinek nincs szabad helyszíne, vagy ha a szabad helyek száma kevesebb a hátralévő embernél. Az egyforma, még üres helyszínek közül elég az elsőt kipróbálni. A kimenetre a lexikografikusan legkisebb megoldást adjuk: az emberekre sorban a lehető legkisebb helyszínt választjuk, amelyhez a maradék még beosztható. A mérések szerint N ≤ 20 és M ≤ 5 esetén a 0,2 mp időlimit bőven tartható.
*/
/*
Hint 1: || Egy embert csak akkor lehet egy helyszínre írni, ha nincs vele összeférhetetlen, már ott lévő ember, és a helyszínen van szabad hely. ||
Hint 2: || Ha valakinek nincs szabad helyszíne, vagy a szabad helyek száma kisebb a hátralévő emberek számánál, az ág zsákutca. ||
Hint 3: || Mindig a legkevesebb lehetőségű embert érdemes következőnek választani, az üres helyszínek közül pedig elég az elsőt kipróbálni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, h;
vector<vector<int>> szomszed;   // szimmetrikus konfliktusgráf (0-tól számozva)
vector<int> hely, darab;        // hely[i]: 1..m, 0 = még nincs beosztva; darab[p]: a p-n lévők száma

// Szabad-e az i-edik embernek a p-edik helyszín (0-tól) a jelenlegi beosztás szerint?
bool szabad(int i, int p) {
    if (darab[p] >= h) return false;
    for (int x : szomszed[i]) if (hely[x] == p + 1) return false;
    return true;
}

// Visszalépéses keresés: mindig a legkevesebb lehetőségű, még be nem osztott embert választjuk.
// Az üres helyszínek egyformák, ezért közülük csak az elsőt próbáljuk ki.
bool keres() {
    int osszesen = 0, hatra = 0;
    for (int p = 0; p < m; ++p) osszesen += h - darab[p];
    for (int i = 0; i < n; ++i) hatra += (hely[i] == 0);
    if (hatra > osszesen) return false;
    if (hatra == 0) return true;
    int kivalasztott = -1, legkevesebb = INT_MAX, legtobbSzomszed = -1;
    for (int i = 0; i < n; ++i) {
        if (hely[i]) continue;
        int lehetoseg = 0;
        for (int p = 0; p < m; ++p) lehetoseg += szabad(i, p);
        if (lehetoseg == 0) return false;
        int nyitott = 0;
        for (int x : szomszed[i]) nyitott += (hely[x] == 0);
        if (lehetoseg < legkevesebb || (lehetoseg == legkevesebb && nyitott > legtobbSzomszed)) {
            legkevesebb = lehetoseg;
            legtobbSzomszed = nyitott;
            kivalasztott = i;
        }
    }
    bool ures_probalva = false;
    for (int p = 0; p < m; ++p) {
        if (!szabad(kivalasztott, p)) continue;
        if (darab[p] == 0) {
            if (ures_probalva) continue;
            ures_probalva = true;
        }
        hely[kivalasztott] = p + 1;
        ++darab[p];
        if (keres()) return true;
        --darab[p];
        hely[kivalasztott] = 0;
    }
    return false;
}

// Be lehet-e fejezni a jelenlegi részleges beosztást? A globális állapotot nem módosítja.
bool lehetseges() {
    vector<int> mentHely = hely, mentDarab = darab;
    bool ok = keres();
    hely = mentHely;
    darab = mentDarab;
    return ok;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> h;
    szomszed.assign(n, {});
    for (int i = 1; i < n; ++i) {
        int x;
        while (cin >> x && x != 0) {
            --x;
            szomszed[i].push_back(x);
            szomszed[x].push_back(i);
        }
    }
    hely.assign(n, 0);
    darab.assign(m, 0);
    if (!lehetseges()) {
        cout << -1 << '\n';
        return 0;
    }
    // Sorrendben, mindig a legkisebb lehetséges helyszínt választjuk, ha a maradék még beosztható.
    for (int i = 0; i < n; ++i) {
        for (int p = 0; p < m; ++p) {
            if (!szabad(i, p)) continue;
            hely[i] = p + 1;
            ++darab[p];
            if (lehetseges()) break;
            --darab[p];
            hely[i] = 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << hely[i];
    }
    cout << '\n';
    return 0;
}
