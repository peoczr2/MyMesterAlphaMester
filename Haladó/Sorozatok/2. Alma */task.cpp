/*
Megoldás lényege:
Az időegységeket egyenként szimuláljuk. Minden bábu a saját irányába lép; ha a következő mező kívülre esne,
a bábu iránya mindkét koordinátában megfordul, és az új irányba lép egyet, így visszafelé lép, ahonnan jött.
Minden lépést előbb kiszámolunk, és csak utána vizsgáljuk az ütközést: ütközés van, ha két bábu ugyanarra
a mezőre lép, vagy valamelyik bábu egy másik bábu jelenlegi mezőjére lép (a két minta ezt a szabályt igazolja).
Az első ütközés időpontját írjuk ki; ha K időegységen belül nincs ütközés, a válasz -1.
Egy időegységben O(L^2) ellenőrzés van, így az összidő O(K * L^2).
*/
/*
Hint 1: || Egy időegységben minden bábu mozgása külön kiszámítható; a tábla szélén az irányt mindkét koordinátában meg kell fordítani. ||
Hint 2: || Az ütközésnél nemcsak az azonos célmezőt kell nézni, hanem azt is, hogy egy bábu a másik bábu jelenlegi mezőjére lép-e. ||
Hint 3: || Az összes lépést előbb számold ki, és csak utána ellenőrizd az ütközéseket a régi pozíciók alapján; a páronkénti ellenőrzés az L és K korlátok mellett belefér. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Piece {
    int x, y, dx, dy;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, l, k;
    cin >> n >> m >> l >> k;

    map<string, pair<int, int>> dir = {{"EN", {-1, -1}}, {"EK", {-1, 1}}, {"DN", {1, -1}}, {"DK", {1, 1}}};
    vector<Piece> p(l);
    for (int i = 0; i < l; ++i) {
        string s;
        cin >> p[i].x >> p[i].y >> s;
        p[i].dx = dir[s].first;
        p[i].dy = dir[s].second;
    }

    for (int t = 1; t <= k; ++t) {
        vector<pair<int, int>> next(l);
        for (int i = 0; i < l; ++i) {
            int nx = p[i].x + p[i].dx;
            int ny = p[i].y + p[i].dy;
            if (nx < 1 || nx > n || ny < 1 || ny > m) {
                p[i].dx = -p[i].dx;
                p[i].dy = -p[i].dy;
                nx = p[i].x + p[i].dx;
                ny = p[i].y + p[i].dy;
            }
            next[i] = {nx, ny};
        }

        bool collision = false;
        for (int i = 0; i < l && !collision; ++i) {
            for (int j = 0; j < l && !collision; ++j) {
                if (i == j) continue;
                if (next[i] == next[j] || next[i] == make_pair(p[j].x, p[j].y)) collision = true;
            }
        }
        if (collision) {
            cout << t << '\n';
            return 0;
        }

        for (int i = 0; i < l; ++i) {
            p[i].x = next[i].first;
            p[i].y = next[i].second;
        }
    }

    cout << -1 << '\n';
    return 0;
}
