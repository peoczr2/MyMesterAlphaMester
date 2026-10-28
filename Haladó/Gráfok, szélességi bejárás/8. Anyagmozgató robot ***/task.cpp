/*
Megoldás lényege:
A robot állapota a rácspont (sor, oszlop) és az irány. Egy másodperc alatt vagy egy rácsvonalat lép előre
az aktuális irányba, vagy 90 fokot fordul, ezért az állapotgráf éleinek súlya egységnyi, és a legrövidebb
időt szélességi bejárással (BFS) kapjuk meg a kezdőállapotból (kezdetben felfelé néz). A rácspont akkor
járható, ha a hozzá csatlakozó négy négyzet egyike sincs akadállyal: a 1,6 m átmérőjű robot középpontja
legalább 0,8 m-re van az akadályoktól. A rácspontok egész koordinátán vannak, így egy rácspont vagy érinti
a négyzetet, vagy legalább 1 m-re van tőle; csak az első eset tiltott. A falon lévő vonalakon nincs járható pont, a szélső pályák 1 m-re vannak a faltól. Az időigény
és a memóriaigény O(N·M·4).
*/
/*
Hint 1: || Az állapot legyen a (sor, oszlop, irány) hármas. Mindkét művelet (előre lépés és fordulás) pontosan 1 másodpercig tart, így szélességi bejárás adja a minimális időt. ||
Hint 2: || Egy rácspont akkor használható, ha a körülötte lévő négy négyzet közül egyik sem akadály. A falon (0. és N. sor, illetve oszlop) nincs járható pont, az 1. és az (N-1). sor a szélső pálya. ||
Hint 3: || Az első alkalommal, amikor a célpont bármely irányban a sorba kerül, megkapod a minimális időt. Ha a sor kiürül a célpont előtt, a válasz -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // a teljes bemenet gyors beolvasása
    string in;
    {
        char tmp[1 << 16];
        size_t r;
        while ((r = fread(tmp, 1, sizeof tmp, stdin)) > 0) in.append(tmp, r);
    }
    size_t pos = 0;
    auto readInt = [&]() -> int {
        while (pos < in.size() && (in[pos] < '0' || in[pos] > '9') && in[pos] != '-') ++pos;
        bool neg = false;
        if (pos < in.size() && in[pos] == '-') {
            neg = true;
            ++pos;
        }
        int x = 0;
        while (pos < in.size() && in[pos] >= '0' && in[pos] <= '9') {
            x = x * 10 + (in[pos] - '0');
            ++pos;
        }
        return neg ? -x : x;
    };

    int n = readInt(), m = readInt();
    int sr = readInt(), sc = readInt(), tr = readInt(), tc = readInt();
    vector<char> g(n * m);
    for (int i = 0; i < n * m; ++i) g[i] = (char)readInt();

    // ok[i*m+j]: a (i, j) rácspont járható, ha belső pont és a körülötte lévő 4 négyzet nem akadály
    vector<char> ok(n * m, 0);
    for (int i = 1; i <= n - 1; ++i)
        for (int j = 1; j <= m - 1; ++j)
            ok[i * m + j] = !(g[(i - 1) * m + (j - 1)] || g[(i - 1) * m + j] || g[i * m + (j - 1)] || g[i * m + j]);

    auto isOk = [&](int i, int j) { return ok[i * m + j] != 0; };
    if (!isOk(sr, sc) || !isOk(tr, tc)) {
        cout << -1 << '\n';
        return 0;
    }

    // irányok: 0 = fel, 1 = jobbra, 2 = le, 3 = balra; kezdetben 0 (fel)
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};
    // állapot azonosítója: (i*m + j)*4 + d; a bejárás szintenként halad, így elég a látogatottság
    vector<unsigned char> vis(n * m * 4, 0);
    vector<int> qu(n * m * 4);
    size_t head = 0, tail = 0, levelEnd = 0;
    int targetPos = tr * m + tc;
    int startState = (sr * m + sc) * 4;
    vis[startState] = 1;
    qu[tail++] = startState;
    levelEnd = tail;
    int level = 0;
    while (head < tail) {
        if (head == levelEnd) {
            ++level;
            levelEnd = tail;
        }
        int cur = qu[head++];
        int d = cur & 3;
        int p2 = cur >> 2;
        if (p2 == targetPos) {
            cout << level << '\n';
            return 0;
        }
        int i = p2 / m, j = p2 - i * m;
        // fordulás jobbra és balra, 1 másodperc
        int turned[2] = {(d + 1) & 3, (d + 3) & 3};
        for (int nd : turned) {
            int nxt = cur - d + nd;
            if (!vis[nxt]) {
                vis[nxt] = 1;
                qu[tail++] = nxt;
            }
        }
        // előre lépés 1 m-t, 1 másodperc
        int ni = i + dr[d], nj = j + dc[d];
        if (ni >= 0 && ni < n && nj >= 0 && nj < m && isOk(ni, nj)) {
            int nxt = ((ni * m + nj) << 2) | d;
            if (!vis[nxt]) {
                vis[nxt] = 1;
                qu[tail++] = nxt;
            }
        }
    }
    cout << -1 << '\n';
    return 0;
}
