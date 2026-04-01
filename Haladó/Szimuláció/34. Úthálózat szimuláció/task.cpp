/*
Megoldás lényege:
Az autók egymástól függetlenek, mert a kereszteződésekben nincs kapacitáskorlát.
Ezért minden autót külön szimulálunk az érkezési időtől a távozásig.

A hálózat csúcsai a peremre eső kereszteződések. A belépési és kilépési pontok
ezeknek a csúcsoknak felelnek meg, körben számozva. A mozgás minden lépésben a
célhoz közelebbi irányba történik; ha mind a sor-, mind az oszlopirány szóba
jön, akkor a nagyobb távolságot csökkentő irányt választjuk, döntetlen esetén
pedig a cél oldala dönti el a függőleges vagy vízszintes lépést.

Ha az autó megérkezik egy csúcsba, várnia kell a saját belépési irányának
megfelelő zöld fázisra. A fázisok sorrendje és hossza adott, ezért a következő
engedélyezett indulási idő kiszámítható közvetlenül.
*/
/*
Hint 1: || Egy autó útja csak a következő szabad időpontokon múlik, ezért az egyes járművek szétválaszthatók. ||
Hint 2: || A célhoz közelebbi irány minden lépésben meghatározza, merre halad tovább az autó. ||
*/

#include <bits/stdc++.h>
using namespace std;

enum Dir { NORTH = 0, WEST = 1, SOUTH = 2, EAST = 3 };

struct Pos {
    int row, col;
};

static Pos pointToPos(int id, int n, int m) {
    if (id <= m) {
        return {1, id};
    }
    id -= m;
    if (id <= n) {
        return {id, m};
    }
    id -= n;
    if (id <= m) {
        return {n, m - id + 1};
    }
    id -= m;
    return {n - id + 1, 1};
}

static Dir pointIncomingDir(int id, int n, int m) {
    if (id <= m) return NORTH;
    if (id <= m + n) return WEST;
    if (id <= 2 * m + n) return SOUTH;
    return EAST;
}

static long long nextGreen(long long time, Dir dir, int k) {
    long long phaseLen = k;
    long long cycle = 4LL * phaseLen;
    long long start = 1LL * dir * phaseLen;
    long long within = time % cycle;
    if (within < start) return time + (start - within);
    if (within < start + phaseLen) return time;
    return time + (cycle - within + start);
}

static Dir chooseMove(const Pos& cur, const Pos& target, int n, int m) {
    int dr = target.row - cur.row;
    int dc = target.col - cur.col;

    if (dr == 0 && dc == 0) return NORTH;

    if (dr == 0) return (dc > 0 ? EAST : WEST);
    if (dc == 0) return (dr > 0 ? SOUTH : NORTH);

    int adr = abs(dr);
    int adc = abs(dc);
    if (adr > adc) return (dr > 0 ? SOUTH : NORTH);
    if (adc > adr) return (dc > 0 ? EAST : WEST);

    bool verticalPreferred = (target.row == 1 || target.row == n);
    if (verticalPreferred) return (dr > 0 ? SOUTH : NORTH);
    return (dc > 0 ? EAST : WEST);
}

static Dir boundaryExitDir(int id, int n, int m) {
    if (id <= m) return NORTH;
    if (id <= m + n) return EAST;
    if (id <= 2 * m + n) return SOUTH;
    return WEST;
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
        Dir incoming = pointIncomingDir(e, n, m);
        Dir exitDir = boundaryExitDir(t, n, m);

        long long time = arrival + 1;
        while (!(cur.row == target.row && cur.col == target.col)) {
            time = nextGreen(time, incoming, k);
            Dir move = chooseMove(cur, target, n, m);
            if (move == NORTH) --cur.row;
            else if (move == SOUTH) ++cur.row;
            else if (move == WEST) --cur.col;
            else ++cur.col;
            time += 1;
            incoming = (move == NORTH ? SOUTH : move == SOUTH ? NORTH : move == WEST ? EAST : WEST);
        }

        if (exitDir == EAST) {
            time = nextGreen(time, incoming, k);
        }

        answer[idx] = time;
    }

    for (int i = 0; i < a; ++i) {
        cout << answer[i] << '\n';
    }
    return 0;
}