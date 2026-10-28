/*
Megoldás lényege: a főágat a zárójelek nélkül, végig lefúrjuk, utána sorban jönnek az elágazások (mindegyik teljesen, majd annak saját leágazásai), mindig a leágazási pontból indulva. Minden fúrt cellát az ág azonosítójával jegyzünk egy 201x201-es rácsban. Új cella fúrásakor megnézzük mind a 8 szomszédját (oldal- és sarokszomszéd): ha ott másik ághoz tartozó cella áll, az ágak összeértek, és az aktuális karakter sorszámát írjuk ki. Kivétel a leágazási pont maga és a szülőág leágazás utáni első cellája, mert ezekkel a leágazás természetesen érintkezik. A zárójelpárokat veremmel előre kiszámoljuk. Időigény: O(n), memória O(1) méretű rács.
*/
/*
Hint 1: || A zárójelek párját előre, egy veremmel határozd meg: így egy ág tartalmát és a folytatását is gyorsan megtalálod. ||
Hint 2: || Az ágakat külön fúrd: először a főág karakterei a zárójelek kihagyásával, utána egyesével a leágazások, mindegyik a saját indulópontjából és a leágazáskori irányból. ||
Hint 3: || Rácsban jegyezd, melyik ág fúrta az adott cellát. Új cella ellenőrzésénél a 8 szomszédját nézd, a sarkok is számítanak; a leágazási pontot és a szülőág folytatását ne tekintsd ütközésnek. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int DX[4] = {0, 1, 0, -1};
static const int DY[4] = {1, 0, -1, 0};
static const int OFF = 105;

struct Ctx {
    string s;
    vector<int> match;
    int owner[2 * OFF + 1][2 * OFF + 1];   // -1: üres
    int fromX[2 * OFF + 1][2 * OFF + 1];   // az előző cella koordinátái (a fúrás útján)
    int fromY[2 * OFF + 1][2 * OFF + 1];
    int nextId = 0;
    int answer = 0;
};

static bool drillPart(Ctx &c, int l, int r, int x, int y, int d, int id, int parentId) {
    struct Sub {
        int l, r, x, y, d;
    };
    vector<Sub> subs;
    int rootX = x, rootY = y;
    int steps = 0;  // ebben az ágban eddig fúrt cellák száma

    int i = l;
    while (i < r) {
        char ch = c.s[i];
        if (ch == '(') {
            subs.push_back({i + 1, c.match[i], x, y, d});
            i = c.match[i] + 1;
            continue;
        }
        if (ch == 'J') {
            d = (d + 1) % 4;
        } else if (ch == 'B') {
            d = (d + 3) % 4;
        } else if (ch == 'E') {
            int nx = x + DX[d], ny = y + DY[d];
            bool bad = false;
            for (int dx = -1; dx <= 1 && !bad; ++dx) {
                for (int dy = -1; dy <= 1 && !bad; ++dy) {
                    int qx = nx + dx, qy = ny + dy;
                    int o = c.owner[qx + OFF][qy + OFF];
                    if (o < 0 || o == id) continue;
                    if (id != 0 && steps < 2 && qx == rootX && qy == rootY) continue;  // a leágazási pont maga
                    if (id != 0 && steps < 1 && o == parentId && c.fromX[qx + OFF][qy + OFF] == rootX &&
                        c.fromY[qx + OFF][qy + OFF] == rootY) {
                        continue;  // a szülőág folytatása a leágazási pont után
                    }
                    bad = true;
                }
            }
            if (bad) {
                c.answer = i + 1;
                return true;
            }
            c.owner[nx + OFF][ny + OFF] = id;
            c.fromX[nx + OFF][ny + OFF] = x;
            c.fromY[nx + OFF][ny + OFF] = y;
            x = nx;
            y = ny;
            ++steps;
        }
        ++i;
    }

    for (const Sub &sb : subs) {
        int nid = ++c.nextId;
        if (drillPart(c, sb.l, sb.r, sb.x, sb.y, sb.d, nid, id)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    static Ctx c;
    cin >> c.s;
    int n = (int)c.s.size();

    c.match.assign(n, -1);
    vector<int> stk;
    for (int i = 0; i < n; ++i) {
        if (c.s[i] == '(') {
            stk.push_back(i);
        } else if (c.s[i] == ')' && !stk.empty()) {
            int open = stk.back();
            stk.pop_back();
            c.match[open] = i;
            c.match[i] = open;
        }
    }

    memset(c.owner, -1, sizeof(c.owner));
    c.owner[OFF][OFF] = 0;
    c.fromX[OFF][OFF] = INT_MIN;
    c.fromY[OFF][OFF] = INT_MIN;
    drillPart(c, 0, n, 0, 0, 0, 0, -1);

    cout << c.answer << '\n';
    return 0;
}
