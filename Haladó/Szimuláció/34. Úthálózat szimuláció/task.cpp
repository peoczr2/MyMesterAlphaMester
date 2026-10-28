/*
Megoldás lényege:
Az autók nem befolyásolják egymást, mert a kereszteződésekben nincs kapacitáskorlát,
ezért minden autót külön szimulálunk az érkezési időtől a kilépéséig. Egy lépés egy
kereszteződésből a szomszédoshoz 1 időegység, és minden kereszteződésben meg kell várni
az autó érkezési oldalának zöld fázisát (a fázisok N, W, S, E sorrendben, egyenként K
hosszúak, a ciklus 4K). A kereszteződésben az autó a célhoz közelebbi irányba megy: ha
két irány is lehetséges, a nagyobb koordinátakülönbségű irányt választja; egyenlő
különbségnél a kilépési pont oldala dönt (északi vagy déli oldal esetén függőleges,
keleti vagy nyugati esetén vízszintes irány). A kilépési pont kereszteződésében is meg
kell várni a zöldet, és az utolsó kereszteződésből való indulás ideje a válasz.
*/
/*
Hint 1: || Az autók egymástól függetlenek, így minden autó útja külön szimulálható; a lámpa állapota csak az időpont 4K szerinti maradékától függ. ||
Hint 2: || Minden kereszteződésben a következő zöld időpontot kell megkeresni az autó érkezési oldalához, egyenlő koordinátakülönbségnél pedig a kilépési pont oldala dönt. ||
*/

#include <bits/stdc++.h>
using namespace std;

enum Dir { NORTH = 0, WEST = 1, SOUTH = 2, EAST = 3 };  // a lámpafázisok sorrendje

struct Pos {
    int row, col;
};

// Belépési/kilépési pont (1..2(N+M)) kereszteződése: északi oldal: 1..M, keleti: M+1..M+N,
// déli: M+N+1..2M+N, nyugati: 2M+N+1..2(N+M).
static Pos pointToPos(int id, int n, int m) {
    if (id <= m) return {1, id};
    id -= m;
    if (id <= n) return {id, m};
    id -= n;
    if (id <= m) return {n, m - id + 1};
    id -= m;
    return {n - id + 1, 1};
}

// Az a oldal, ahonnan az autó a pontba érkezik (ez határozza a lámpafázist).
static Dir entrySide(int id, int n, int m) {
    if (id <= m) return NORTH;
    if (id <= m + n) return EAST;
    if (id <= 2 * m + n) return SOUTH;
    return WEST;
}

// Az a kilépési pontoldal, amelyre a kilépő autó tart (a döntetlen esetet ez dönti el).
static Dir exitSide(int id, int n, int m) {
    return entrySide(id, n, m);
}

// Legkorábbi t >= time időpont, amikor a dir irányú lámpa zöld.
static long long nextGreen(long long time, Dir dir, int k) {
    long long cycle = 4LL * k;
    long long start = 1LL * dir * k;
    long long within = time % cycle;
    if (within < start) return time + (start - within);
    if (within < start + k) return time;
    return time + (cycle - within + start);
}

// Az autó mozgásiránya a célhoz közelebb: a nagyobb különbségű koordináta mentén.
static Dir chooseMove(const Pos& cur, const Pos& target, Dir targetSide) {
    int dr = target.row - cur.row;
    int dc = target.col - cur.col;

    if (dr == 0) return dc > 0 ? EAST : WEST;
    if (dc == 0) return dr > 0 ? SOUTH : NORTH;

    int adr = abs(dr);
    int adc = abs(dc);
    if (adr > adc) return dr > 0 ? SOUTH : NORTH;
    if (adc > adr) return dc > 0 ? EAST : WEST;

    // Egyenlő különbség: a kilépési pont oldalának megfelelő irány.
    if (targetSide == NORTH || targetSide == SOUTH) return dr > 0 ? SOUTH : NORTH;
    return dc > 0 ? EAST : WEST;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, a;
    if (!(cin >> n >> m >> k >> a)) return 0;

    vector<long long> answer(a);
    for (int idx = 0; idx < a; ++idx) {
        long long arrival;
        int e, t;
        cin >> arrival >> e >> t;

        Pos cur = pointToPos(e, n, m);
        Pos target = pointToPos(t, n, m);
        Dir incoming = entrySide(e, n, m);
        Dir outSide = exitSide(t, n, m);

        long long time = arrival + 1;  // 1 időegység a belépési ponttól az első kereszteződésig
        while (cur.row != target.row || cur.col != target.col) {
            time = nextGreen(time, incoming, k);
            Dir move = chooseMove(cur, target, outSide);
            if (move == NORTH) --cur.row;
            else if (move == SOUTH) ++cur.row;
            else if (move == WEST) --cur.col;
            else ++cur.col;
            time += 1;
            // Az új kereszteződésbe az ellenkező oldalról érkezik az autó.
            incoming = (move == NORTH ? SOUTH : move == SOUTH ? NORTH : move == WEST ? EAST : WEST);
        }

        // A kilépési pont kereszteződésében is zöld kell a kilépéshez.
        time = nextGreen(time, incoming, k);
        answer[idx] = time;
    }

    for (int i = 0; i < a; ++i) cout << answer[i] << '\n';
    return 0;
}
