/*
Megoldás lényege:
Az ajánlatokat egy N x M-es táblázatba írjuk: ar[cég][termék] az ár, a 0 jelöli, ha a cég nem kínálja a terméket. Az 1. részfeladatban a termékenként legnagyobb ajánlott árat vesszük, és ennek maximumát keressük, döntetlennél a kisebb sorszám marad. A 2. részfeladatban a cégek kínált termékeinek számát hasonlítjuk össze. A 3. részfeladatban termékenként megszámoljuk a beszállítókat: az egyetlen beszállítós termékek száma az első sor, sorszámuk növekvő sorrendben a második. A 4. részfeladatban a cégpárokat sorszám szerint járjuk be, és az első olyan pár kerül kiírásra, amelynek kínált termékhalmaza azonos; ha nincs ilyen, a válasz -1. Az 5. részfeladatban egy cég akkor felel meg, ha kínált termékei mindegyikénél más cégnek nincs azonos vagy olcsóbb ajánlata. Az időigény O(N^2 M), ami N, M <= 100 mellett bőven belefér.
*/
/*
Hint 1: || Az ajánlatokat tárold egy cég x termék táblázatban, ahol a nulla azt jelzi, hogy a cég nem kínálja a terméket. Így minden kérdés egyszerű ciklussal megválaszolható. ||
Hint 2: || A 3. részfeladatnál termékenként számold meg a beszállítókat, és csak a pontosan egy beszállítós termékeket vedd figyelembe. Az 5. részfeladatban egy cég minden kínált termékére külön ellenőrizd, hogy más cégnek van-e azonos vagy olcsóbb ajánlata. ||
Hint 3: || A 4. részfeladatban két cég akkor azonos, ha ugyanazokat a termékeket kínálják, az ár most nem számít. A párokat sorszámuk szerint növekvően vizsgáld, az első találatnál állj meg, és az üres kínálatú cégeket hagyd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a;
    cin >> n >> m >> a;

    vector<vector<int>> price(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < a; ++i) {
        int c, p, ar;
        cin >> c >> p >> ar;
        price[c][p] = ar;
    }

    vector<int> offerCount(n + 1, 0);
    for (int c = 1; c <= n; ++c)
        for (int p = 1; p <= m; ++p)
            if (price[c][p] > 0) ++offerCount[c];

    // 1. részfeladat: a legdrágább termék
    int dear = 1, dearPrice = 0;
    for (int p = 1; p <= m; ++p) {
        int mx = 0;
        for (int c = 1; c <= n; ++c) mx = max(mx, price[c][p]);
        if (mx > dearPrice) {
            dearPrice = mx;
            dear = p;
        }
    }
    cout << "#\n" << dear << "\n";

    // 2. részfeladat: a legtöbbféle terméket szállító cég
    int bestCo = 1;
    for (int c = 2; c <= n; ++c)
        if (offerCount[c] > offerCount[bestCo]) bestCo = c;
    cout << "#\n" << bestCo << "\n";

    // 3. részfeladat: az egyetlen beszállítótól beszerezhető termékek (a minta szerint a termék-sorszámokat írjuk ki)
    vector<int> sole;
    for (int p = 1; p <= m; ++p) {
        int suppliers = 0;
        for (int c = 1; c <= n; ++c)
            if (price[c][p] > 0) ++suppliers;
        if (suppliers == 1) sole.push_back(p);
    }
    cout << "#\n" << sole.size() << "\n";
    for (size_t i = 0; i < sole.size(); ++i) cout << sole[i] << (i + 1 < sole.size() ? " " : "\n");

    // 4. részfeladat: első olyan cégpár, amelynek kínált termékei azonosak
    int ra = -1, rb = -1;
    for (int x = 1; x <= n && ra < 0; ++x) {
        if (offerCount[x] == 0) continue;
        for (int y = x + 1; y <= n && ra < 0; ++y) {
            if (offerCount[y] == 0) continue;
            bool same = true;
            for (int p = 1; p <= m && same; ++p)
                if ((price[x][p] > 0) != (price[y][p] > 0)) same = false;
            if (same) {
                ra = x;
                rb = y;
            }
        }
    }
    cout << "#\n";
    if (ra < 0)
        cout << -1 << "\n";
    else
        cout << ra << " " << rb << "\n";

    // 5. részfeladat: azok a cégek, amelyek kínált termékeinél más cégnél nincs olcsóbb (a minta szerint azonos ár sem megengedett)
    vector<int> cheapest;
    for (int c = 1; c <= n; ++c) {
        if (offerCount[c] == 0) continue;
        bool ok = true;
        for (int p = 1; p <= m && ok; ++p) {
            if (price[c][p] == 0) continue;
            for (int y = 1; y <= n; ++y)
                if (y != c && price[y][p] > 0 && price[y][p] <= price[c][p]) {
                    ok = false;
                    break;
                }
        }
        if (ok) cheapest.push_back(c);
    }
    cout << "#\n" << cheapest.size() << "\n";
    for (size_t i = 0; i < cheapest.size(); ++i) cout << cheapest[i] << (i + 1 < cheapest.size() ? " " : "\n");

    return 0;
}
