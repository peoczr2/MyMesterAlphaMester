/*
Megoldás lényege:
    Egy kisebb konténer mindig ráfér egy nagyobbra vagy egy üres helyre, ezért a
    szomszédos konténerek cseréjével a sorrend megváltoztatható. Beszúró rendezést
    végzünk: a t = 1, 2, ... konténert addig toljuk balra, amíg el nem éri a t. helyet.
    Az 1..t-1 konténerek már a helyükön állnak, így a t. konténer bal oldali
    szomszédai a t-nél nagyobbak vagy üresek. Egy t-nél nagyobb x bal oldali
    szomszédos cseréje 4 lépésben megy: t-t x fölé rakjuk, majd a bal oldali másik
    szomszédra tesszük (ha az üres vagy nála nagyobb), x átmegy a felszabadult helyre,
    végül t visszalép. Ha nincs használható bal oldali szomszéd, a jobb oldali
    szomszédot használjuk. Így a t. konténer legfeljebb N-t helyet lép, az összes
    művelet száma O(N^2).
*/
/*
Hint 1: || Egy kisebb konténert bármely nagyobbra vagy üres helyre rakhatunk, így a szomszédos konténerek cseréje megvalósítható, és ezekből felépíthető a teljes sorrend. ||
Hint 2: || Beszúró rendezést csinálj: t = 1, 2, … sorrendben a t. konténert addig mozgasd balra, amíg a t. helyre nem ér. Az 1..t-1 konténereket nem mozgatjuk: a t-nél nagyobbak és az üres hely a t. helytől jobbra vagy a t. helyen vannak. ||
Hint 3: || Egy x > t konténer és a t szomszédos cseréje 4 lépés: t rakd x fölé, t-t vidd x bal oldali szomszédjára (ha az üres vagy nagyobb), x lépjen a felszabadult helyre, végül t lépjen vissza. Ha a bal oldalon nincs használható szomszéd, a cserét a jobb oldali szomszéddal végezd el. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> rakas;          // rakas[h]: a h. helyen lévő konténerek, a vége a legfelső
vector<pair<int, char>> muveletek;  // a végrehajtott lépések (hely, irány)

// A legfelső konténert átrakja a szomszédos helyre: irany = -1 balra (B), +1 jobbra (J).
void mozgat(int honnan, int irany) {
    int hova = honnan + irany;
    int x = rakas[honnan].back();
    rakas[honnan].pop_back();
    rakas[hova].push_back(x);
    muveletek.push_back({honnan, irany == -1 ? 'B' : 'J'});
}

// A k konténer aktuális helyét adja meg.
int hol_van(int k) {
    for (int i = 1; i <= n + 1; ++i) {
        for (int x : rakas[i]) {
            if (x == k) return i;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    rakas.assign(n + 2, {});
    for (int i = 1; i <= n; ++i) {
        int m;
        cin >> m;
        rakas[i].push_back(m);
    }

    for (int t = 1; t <= n; ++t) {
        int q = hol_van(t);
        while (q > t) {
            if (rakas[q - 1].empty()) {
                // üres bal szomszéd: egy lépés
                mozgat(q, -1);
            } else if (q - 2 >= t) {
                // x = rakas[q-1] > t: t x fölé, majd a bal szomszédra, x jobbra, t vissza
                mozgat(q, -1);
                mozgat(q - 1, -1);
                mozgat(q - 1, +1);
                mozgat(q - 2, +1);
            } else {
                // q = t+1: t jobbra a szomszédra, x jobbra, t x fölé, majd balra
                mozgat(q, +1);
                mozgat(q - 1, +1);
                mozgat(q + 1, -1);
                mozgat(q, -1);
            }
            q = hol_van(t);
        }
    }

    for (auto [p, c] : muveletek) {
        cout << p << ' ' << c << '\n';
    }
    return 0;
}
