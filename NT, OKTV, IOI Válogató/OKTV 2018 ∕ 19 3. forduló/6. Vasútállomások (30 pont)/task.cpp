/*
Megoldás lényege:
Az eseményeket (vonat indulása és érkezése minden megállóban) időrendben dolgozzuk fel. Egy vonaton
utazó állapotot három érték ír le: az eddig fizetett díj, az első indulás ideje az 1. állomásról (ennek
legkésőbbi értékét keressük), és az érkezés ideje, ami a vonat menetrendjéből adódik. Egy állomáson
mindig a legjobb állapotot tartjuk nyilván: legkisebb díj, azonos díjnál legnagyobb indulási idő. Egy vonatra
szállás akkor lehetséges, ha az állomásra korábban érkeztünk, mint ahogy a vonat indul, ezért azonos időpontnál
az indulást előbb dolgozzuk fel. Az 1. állomásról bármikor lehet indulni, így ott a díj 0 és az indulás ideje
maga az indulás. Az egyes állomásokra a legkorábbi érkezést, azon belül a legkisebb díjat és a legnagyobb
indulási időt az érkezési események közül választjuk ki. Az időigény O(E log E), ahol E a menetrendi elemek száma.
*/
/*
Hint 1: || Az eseményeket időrendben dolgozd fel: a vonatok indulásait és érkezéseit egy közös listában rendezd idő szerint. Azonos időpontnál az indulás kerüljön előre, mert csak az érkezés után később induló vonatra lehet átszállni. ||
Hint 2: || Egy útvonalat három szám jellemez: az érkezés ideje, a teljes menetdíj és az 1. állomásról való legkésőbbi indulás. Egy állomásra érkezés ideje a menetrendből adódik, így a többi kérdés csak a díjat és az indulási időt érinti. ||
Hint 3: || Minden állomáson tartsd nyilván az eddig érkezett utazások közül a legjobbat: legkisebb díj, azonos díjnál legnagyobb indulási idő. Egy vonatra szálláskor ezt az állapotot vedd át, a következő megállóba érkezéskor pedig add hozzá a menetdíjat. ||
Hint 4: || Egy állomás végeredménye az érkezési események közül kerül ki: a legkorábbi érkezési idő, azon belül a legkisebb díj, majd a legnagyobb indulási idő. Ha egy állomásra nem jutsz el, a sorba 0 0 0 kerül. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Stop {
    int station;
    long long arr, dep, fare;
};

// Egy útvonal állapota: eddig fizetett díj és az 1. állomásról való legkésőbbi indulás.
struct Lab {
    long long cost;
    long long L;
};

// Jobb-e a kisebb díj; azonos díjnál a későbbi indulási idő.
static bool betterLab(const Lab& a, const Lab& b) {
    if (a.cost != b.cost) return a.cost < b.cost;
    return a.L > b.L;
}

struct Opt {
    bool ok = false;
    Lab lab{0, 0};
};

// Egy állomás végeredménye: legkorábbi érkezés, majd legkisebb díj, majd legnagyobb indulás.
struct Res {
    bool ok = false;
    long long time = 0, cost = 0, L = 0;
};

static bool betterRes(const Res& a, const Res& b) {
    if (a.time != b.time) return a.time < b.time;
    if (a.cost != b.cost) return a.cost < b.cost;
    return a.L > b.L;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<Stop>> trains(m);
    for (int t = 0; t < m; t++) {
        int k;
        cin >> k;
        trains[t].resize(k);
        for (Stop& s : trains[t]) {
            cin >> s.station >> s.arr >> s.dep >> s.fare;
        }
    }

    // Események: (idő, típus, vonat, megálló). Típus 0: indulás, 1: érkezés.
    // Azonos időben az indulás előbb van, így az érkezés nem számít át ugyanabban a pillanatban.
    vector<tuple<long long, int, int, int>> events;
    for (int t = 0; t < m; t++) {
        int k = trains[t].size();
        for (int j = 0; j < k; j++) {
            if (j + 1 < k) events.emplace_back(trains[t][j].dep, 0, t, j);
            if (j >= 1) events.emplace_back(trains[t][j].arr, 1, t, j);
        }
    }
    sort(events.begin(), events.end());

    vector<vector<Opt>> board(m);   // a vonat j. megállójából való indulás legjobb állapota
    for (int t = 0; t < m; t++) {
        board[t].assign(trains[t].size(), Opt());
    }
    vector<Opt> best(n + 1);        // állomásonként az eddig érkezett legjobb állapot
    vector<Res> ans(n + 1);         // állomásonként a végeredmény

    for (const auto& e : events) {
        int type = get<1>(e);
        int t = get<2>(e);
        int j = get<3>(e);
        const Stop& s = trains[t][j];

        if (type == 0) {
            Opt b;
            if (s.station == 1) {
                b.ok = true;
                b.lab = Lab{0, s.dep};
            } else if (best[s.station].ok) {
                b = best[s.station];
            }
            board[t][j] = b;
        } else {
            const Opt& prev = board[t][j - 1];
            if (!prev.ok) continue;
            Lab lab{prev.lab.cost + trains[t][j - 1].fare, prev.lab.L};

            Res cand;
            cand.ok = true;
            cand.time = s.arr;
            cand.cost = lab.cost;
            cand.L = lab.L;
            if (!ans[s.station].ok || betterRes(cand, ans[s.station])) {
                ans[s.station] = cand;
            }

            if (!best[s.station].ok || betterLab(lab, best[s.station].lab)) {
                best[s.station].ok = true;
                best[s.station].lab = lab;
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        if (ans[i].ok) {
            cout << ans[i].time << ' ' << ans[i].cost << ' ' << ans[i].L << '\n';
        } else {
            cout << "0 0 0\n";
        }
    }
    return 0;
}
