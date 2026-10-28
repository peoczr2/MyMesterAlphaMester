/*
Megoldás lényege:
A kezdőpont a fekete pontok közül az első soronként balról jobbra haladva, így a fölötte és balra lévő pontok fehérek.
A bejárás a folt külső peremén halad az óramutató járásával egyező irányban, és csak olyan fekete pontra léphet,
amelynek van fehér oldalszomszédja. Minden lépésnél a visszafelé mutató iránytól (az előző pontból jövő iránytól)
indulva az óramutató szerinti sorrendben nézzük a 8 szomszédot, és az első megfelelő perem pontra lépünk.
Amint visszaérünk a kezdőpontba, megállunk. Minden lépés állandó munka, a lépésszám a perem nagyságával arányos,
így a teljes futásidő O(N*M).
*/
/*
Hint 1: || Az első fekete pont a kezdőpont, és a bejárás csak a folt peremén haladhat: csak olyan fekete pontra léphetsz, aminek van fehér oldalszomszédja. ||
Hint 2: || Az irányokat tárold az ábra szerinti kódokkal, az óramutató járásával egyező sorrendben egy tömbben. Lépés után az új pontból a keresést az előző pont irányából (az ellentétes irányból) indítsd, és az első megfelelő szomszédra lépj; a kezdőpontba érve állj meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Fehér keret a kép körül, hogy a szomszédok mindig elérhetők legyenek.
    vector<string> g(n + 2, string(m + 2, '.'));
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j <= m && j <= (int)s.size(); ++j)
            g[i][j] = s[j - 1];
    }

    // Iránykódok (1..8) az ábra szerint: 1 fent, 2 bal-fent, 3 bal, 4 bal-lent, 5 lent, 6 jobb-lent, 7 jobb, 8 jobb-fent.
    const int dr[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
    const int dc[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
    // Az óramutató járásával egyező sorrend.
    const int cw[8] = {1, 8, 7, 6, 5, 4, 3, 2};
    int pos[9];
    for (int k = 0; k < 8; ++k)
        pos[cw[k]] = k;

    auto isBoundary = [&](int r, int c) {
        if (g[r][c] != 'X') return false;
        return g[r - 1][c] != 'X' || g[r + 1][c] != 'X' || g[r][c - 1] != 'X' || g[r][c + 1] != 'X';
    };

    int sr = -1, sc = -1;
    for (int i = 1; i <= n && sr < 0; ++i)
        for (int j = 1; j <= m; ++j)
            if (g[i][j] == 'X') {
                sr = i;
                sc = j;
                break;
            }

    if (sr < 0) {
        cout << "NINCS FOLT\n";
        return 0;
    }

    string code;
    int r = sr, c = sc;
    int back = 3; // a kezdőpont bal szomszédja fehér, innen indul a keresés
    const long long limit = 4LL * n * m + 8;
    while ((long long)code.size() < limit) {
        int found = 0;
        for (int k = 1; k <= 8; ++k) {
            int d = cw[(pos[back] + k) % 8];
            if (isBoundary(r + dr[d], c + dc[d])) {
                found = d;
                break;
            }
        }
        if (found == 0)
            break;
        code.push_back(char('0' + found));
        r += dr[found];
        c += dc[found];
        if (r == sr && c == sc)
            break;
        back = (found + 3) % 8 + 1; // az ellentétes irány
    }

    cout << sr << ' ' << sc << '\n' << code << '\n';
    return 0;
}
