/*
Megoldás lényege:
Egy szabad hely távolságát a legközelebbi foglalt sor határozza meg: a sorindexek különbsége dönt, az oszlop legfeljebb 1-gyel módosítja a négyzetes távolságot. Ezért a szabad helyek jelöltjei csak két típusúak: a teljesen üres sorok, amelyek két egymás utáni foglalt sor közötti sávban vannak (ebben a sáv közepe körül van a legjobb hely), és a részben foglalt sorok szabad helye, amelynek távolsága mindig 1. A jelölteket egy rendezett halmazban tartjuk nyilván: minden sávra és részben foglalt sorra legfeljebb egy jelölt van. Egy érkezés vagy távozás után csak a változott sor két szomszédos sávját és a sor saját jelöltjét számoljuk újra, így egy esemény O(log N) időt igényel.
*/
/*
Hint 1: || Egy szabad hely legközelebbi foglalt helyének távolságát a legközelebbi foglalt sor adja meg, mert a sorindexek különbsége többet nyom, mint az oszlopé. Ezért nem kell minden helyet végigpróbálni. ||
Hint 2: || Két egymás utáni foglalt sor között az üres sávban a legjobb hely a sáv közepe körül van; a legfelső és a legalsó sáv szélső sora adja a jelöltet. Részben foglalt sorban a szabad hely távolsága 1. ||
Hint 3: || Tartsd nyilván a foglalt sorokat rendezett halmazban, és minden változáskor csak a változott sor és a tőle balra lévő sáv jelöltjét frissítsd. Az érkezőnek a halmaz első eleme adja a helyet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> cnt;                       // foglalt helyek száma soronként
vector<array<bool, 3>> foglalt;        // foglalt[r][c], c = 1 vagy 2
set<int> sorok;                        // a legalább egy foglalt helyet tartalmazó sorok
set<tuple<long long, int, int>> jeloltek;  // (-távolság, sor, oszlop): a legjobb van elöl
vector<char> sav_van;                  // a sáv (a kulcs) jelöltje létezik-e
vector<tuple<long long, int, int>> sav_j;
vector<char> resz_van;                 // a részben foglalt sor szabad helye
vector<tuple<long long, int, int>> resz_j;

// Az a és b foglalt sorok közötti üres sáv legjobb helye.
// a = 0 jelenti a felső, b = N+1 az alsó szélső sávot.
bool savLegjobb(int a, int b, long long &ertek, int &rr, int &cc) {
    bool van = false;
    if (a == 0) {                      // felső sáv: az 1. sor a legtávolabbi
        if (b < 2) return false;
        long long d = (long long)(b - 1) * (b - 1);
        for (int c = 1; c <= 2; ++c) {
            long long v = d + (foglalt[b][c] ? 0 : 1);
            if (!van || v > ertek) { van = true; ertek = v; rr = 1; cc = c; }
        }
        return van;
    }
    if (b == N + 1) {                  // alsó szélső sáv: az N. sor a legtávolabbi
        if (a >= N) return false;
        long long d = (long long)(N - a) * (N - a);
        for (int c = 1; c <= 2; ++c) {
            long long v = d + (foglalt[a][c] ? 0 : 1);
            if (!van || v > ertek) { van = true; ertek = v; rr = N; cc = c; }
        }
        return van;
    }
    if (b - a < 2) return false;       // nincs üres sor a két foglalt sor között
    int mid = (a + b) / 2;
    for (int r = max(a + 1, mid - 2); r <= min(b - 1, mid + 2); ++r) {
        for (int c = 1; c <= 2; ++c) {
            long long da = (long long)(r - a) * (r - a) + (foglalt[a][c] ? 0 : 1);
            long long db = (long long)(b - r) * (b - r) + (foglalt[b][c] ? 0 : 1);
            long long v = min(da, db);
            if (!van || v > ertek) { van = true; ertek = v; rr = r; cc = c; }
        }
    }
    return van;
}

// A sor előtti legnagyobb foglalt sor; 0, ha nincs.
int elozo(int r) {
    auto it = sorok.lower_bound(r);
    return it == sorok.begin() ? 0 : *prev(it);
}

void savTorol(int a) {
    if (sav_van[a]) {
        jeloltek.erase(sav_j[a]);
        sav_van[a] = 0;
    }
}

void savFrissit(int a) {
    savTorol(a);
    int b;
    if (a == 0) {
        if (sorok.empty()) return;
        b = *sorok.begin();
    } else {
        auto it = sorok.upper_bound(a);
        b = (it == sorok.end()) ? N + 1 : *it;
    }
    long long ertek = 0;
    int rr = 0, cc = 0;
    if (savLegjobb(a, b, ertek, rr, cc)) {
        sav_j[a] = make_tuple(-ertek, rr, cc);
        jeloltek.insert(sav_j[a]);
        sav_van[a] = 1;
    }
}

void reszTorol(int r) {
    if (resz_van[r]) {
        jeloltek.erase(resz_j[r]);
        resz_van[r] = 0;
    }
}

void reszFrissit(int r) {
    reszTorol(r);
    if (cnt[r] == 1) {
        int c = foglalt[r][1] ? 2 : 1;   // a szabad oszlop: távolsága 1
        resz_j[r] = make_tuple(-1LL, r, c);
        jeloltek.insert(resz_j[r]);
        resz_van[r] = 1;
    }
}

// Az (r, c) hely foglalásának (be = true) vagy felszabadításának (be = false) kezelése.
void valtoztat(int r, int c, bool be) {
    int pk = elozo(r);
    savTorol(pk);
    savTorol(r);
    reszTorol(r);
    foglalt[r][c] = be;
    cnt[r] += be ? 1 : -1;
    if (cnt[r] > 0) sorok.insert(r);
    else sorok.erase(r);
    savFrissit(pk);
    if (cnt[r] > 0) {
        savFrissit(r);
        reszFrissit(r);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    cnt.assign(N + 2, 0);
    foglalt.assign(N + 2, array<bool, 3>{false, false, false});
    sav_van.assign(N + 2, 0);
    sav_j.assign(N + 2, make_tuple(0LL, 0, 0));
    resz_van.assign(N + 2, 0);
    resz_j.assign(N + 2, make_tuple(0LL, 0, 0));

    vector<pair<int, int>> ules(M + 1);
    string tipus;
    for (int k = 1; k <= M; ++k) {
        cin >> tipus;
        if (tipus == "E") {
            int r = 1, c = 1;
            if (!sorok.empty()) {
                auto it = jeloltek.begin();
                r = get<1>(*it);
                c = get<2>(*it);
            }
            ules[k] = {r, c};
            valtoztat(r, c, true);
            cout << r << ' ' << c << '\n';
        } else {
            int p;
            cin >> p;
            valtoztat(ules[p].first, ules[p].second, false);
        }
    }
    return 0;
}
