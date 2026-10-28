/*
Megoldás lényege:
A téglalapok átfedhetnek egymást, ezért a területüket nem lehet egyszerűen összeadni. A minden téglalap minden pontját külön bejáró megoldás túl lassú az 1000 téglalap és a 0,1 mp-es időlimit mellett.
Helyette a 0..1000 koordinátájú rácson kétdimenziós differencia-tömböt használunk: minden téglalap sarkaiba négy módosítást írunk, majd a kétdimenziós prefixösszeg minden rácspontra megadja, hány téglalap fedi le.
A minta alapján a téglalap szélei is beleszámítanak, vagyis a [bfx..jax] x [bfy..jay] zárt tartomány minden egész pontja lefedett (a példában így 600 jön ki). Az időigény O(N + 1000^2), a tároláshoz kb. 4 MB kell.
*/
/*
Hint 1: || Egy téglalap minden pontját külön megjelölni 1000 téglalapnál már túl sok lépés lehet. Keress olyan módszert, amely minden téglalapot csak a sarkaiban módosít, és a végén egyszer végigmegy a rácson. ||
Hint 2: || Differencia-tömb: az [x1..x2] x [y1..y2] zárt tartományhoz a d[x1][y1] és a d[x2+1][y2+1] helyre +1, a d[x2+1][y1] és a d[x1][y2+1] helyre −1 kerül. Ezután a tömb kétdimenziós prefixösszegét véve minden cellában megkapod a lefedő téglalapok számát. ||
Hint 3: || A prefixösszeg után számold meg a 0..1000 koordinátájú cellákat, amelyekben a fedettség legalább 1. A tömb mérete legyen legalább 1002 x 1002, mert a jax+1 index 1001 lehet. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int MERET = 1002;
int d[MERET][MERET];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int bfx, bfy, jax, jay;
        cin >> bfx >> bfy >> jax >> jay;
        d[bfx][bfy]++;
        d[jax + 1][bfy]--;
        d[bfx][jay + 1]--;
        d[jax + 1][jay + 1]++;
    }
    for (int x = 0; x < MERET; x++) {
        for (int y = 0; y < MERET; y++) {
            if (x > 0) d[x][y] += d[x - 1][y];
            if (y > 0) d[x][y] += d[x][y - 1];
            if (x > 0 && y > 0) d[x][y] -= d[x - 1][y - 1];
        }
    }
    int terulet = 0;
    for (int x = 0; x <= 1000; x++) {
        for (int y = 0; y <= 1000; y++) {
            if (d[x][y] > 0) {
                terulet++;
            }
        }
    }
    cout << terulet << endl;
    return 0;
}
