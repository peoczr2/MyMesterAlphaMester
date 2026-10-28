/*
Megoldás lényege:
A korongok nem különböztethetők meg, ezért az állapot a két korong mezőjének rendezett párja, így legfeljebb 36·36 állapot van. Ezen szélességi bejárást végzünk: egy állapotból minden korongra megvizsgáljuk a 8 irányt, és az érvényes lépések (üres célmező; átlós lépésnél a célmező valamelyik szomszédján a másik korong) új állapotba visznek. Minden lépés egységnyi költségű, így az első elérés adja a minimális lépésszámot. A szülőmutatókból visszafejtjük a lépéssorozatot, amely a feladat szerint bármelyik optimális megoldás lehet. Az időigény elhanyagolható.
*/
/*
Hint 1: || A korongok azonosíthatatlanok, ezért az állapotot a két mező rendezett párjaként tárold, így kevesebb állapotot kell kezelni. ||
Hint 2: || Egy lépés minden esetben 1 egység, ezért szélességi bejárás adja a minimumot; minden állapothoz mentsd el, melyik állapotból, melyik korongot és melyik irányba mozgatva értük el. ||
Hint 3: || A jelölés a 2. ábra szerint értendő: F fel, L le, B balra, J jobbra, a sarkok az átlós irányok (U bal-fel, V jobb-fel, Z bal-le, W jobb-le). ||
*/
#include <bits/stdc++.h>
using namespace std;

// Irányok a 2. ábra jelölése szerint; a sor nő lefelé, az oszlop jobbra.
struct Dir {
    int dr, dc;
    char sym;
};

// Előbb a négy merőleges, utána az átlós irányok (a bejárás sorrendje miatt).
static const Dir DIRS[8] = {
    {-1, 0, 'F'}, {1, 0, 'L'}, {0, -1, 'B'}, {0, 1, 'J'},
    {-1, -1, 'U'}, {-1, 1, 'V'}, {1, -1, 'Z'}, {1, 1, 'W'}
};

static int cellId(int r, int c) { return (r - 1) * 6 + (c - 1); }

static int stateKey(int a, int b) { return min(a, b) * 36 + max(a, b); }

// Léphet-e a (r,c) korong a (dr,dc) irányba, ha a másik korong (orr,oc)-n van.
static bool canStep(int r, int c, int dr, int dc, int orr, int oc) {
    int tr = r + dr, tc = c + dc;
    if (tr < 1 || tr > 6 || tc < 1 || tc > 6) return false;
    if (tr == orr && tc == oc) return false;
    if (dr != 0 && dc != 0) {
        // Átlós lépésnél a célmező valamelyik szomszédján a másik korongnak kell lennie.
        if (abs(tr - orr) + abs(tc - oc) != 1) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2;
    cin >> x3 >> y3 >> x4 >> y4;

    int start = stateKey(cellId(x1, y1), cellId(x2, y2));
    int goal = stateKey(cellId(x3, y3), cellId(x4, y4));

    vector<int> dist(36 * 36, -1), prev(36 * 36, -1), fromCell(36 * 36, -1), dirIdx(36 * 36, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty() && dist[goal] == -1) {
        int cur = q.front();
        q.pop();
        int a = cur / 36, b = cur % 36;
        for (int side = 0; side < 2; ++side) {
            int mv = side == 0 ? a : b;      // a mozgatott korong mezője
            int other = side == 0 ? b : a;   // a másik korong mezője
            int r = mv / 6 + 1, c = mv % 6 + 1;
            int orr = other / 6 + 1, oc = other % 6 + 1;
            for (int d = 0; d < 8; ++d) {
                if (!canStep(r, c, DIRS[d].dr, DIRS[d].dc, orr, oc)) continue;
                int nt = cellId(r + DIRS[d].dr, c + DIRS[d].dc);
                int nk = stateKey(nt, other);
                if (dist[nk] == -1) {
                    dist[nk] = dist[cur] + 1;
                    prev[nk] = cur;
                    fromCell[nk] = mv;
                    dirIdx[nk] = d;
                    q.push(nk);
                }
            }
        }
    }

    if (dist[goal] == -1) {
        cout << -1 << '\n';
        return 0;
    }

    // Visszafejtés a célállapotból a kezdőállapotig.
    vector<pair<int, int>> seq;   // (kiindulási mező, irány)
    for (int s = goal; s != start; s = prev[s]) {
        seq.push_back({fromCell[s], dirIdx[s]});
    }
    reverse(seq.begin(), seq.end());

    cout << seq.size() << '\n';
    for (auto [cell, d] : seq) {
        cout << cell / 6 + 1 << ' ' << cell % 6 + 1 << ' ' << DIRS[d].sym << '\n';
    }
    return 0;
}
