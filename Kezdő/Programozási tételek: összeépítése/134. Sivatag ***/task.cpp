/*
Megoldás lényege:
Az esőzések téglalapjait kétdimenziós különbségi tömbben gyűjtjük: téglalaponként a bal alsó sarokba +1, a két szomszédos pontba −1, a jobb felső mező utáni pontba +1 kerül. A tömb 2D prefixösszege adja minden mező vízmennyiségét, ezt O(N·M + E) időben kapjuk meg. Újabb 2D prefixösszeggel bármely téglalap vízmennyisége O(1)-ben lekérdezhető, így a K×K vízgyűjtő négyzetek összege is O(1). Az összes lehetséges bal alsó sarkon végigmenve kiválasztjuk a maximumot. Az összegek akár 2,5·10^10 nagyságúak, ezért 64 bites egészeket használunk.
*/
/*
Hint 1: || Egy téglalap minden mezőjére egyszerre +1 írható be: a bal alsó sarokba +1, az (x2+1, y1) és (x1, y2+1) pontokba −1, az (x2+1, y2+1) pontba +1 kerül. ||
Hint 2: || A vízgyűjtő négyzet vízmennyisége a víz 2D prefixösszegéből négy tömbelem összegével és különbségével számolható ki. ||
Hint 3: || A bal alsó sarok (x, y) lehetséges értékei x ≤ N − K + 1 és y ≤ M − K + 1; mindegyiken végigmenve a szigorú > összehasonlítás az első maximumot tartja meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, e;
    cin >> n >> m >> k >> e;

    // d: 1-indexelt különbségi tömb; a 2D prefixösszeg után a mezők vízmennyisége
    vector<vector<long long>> d(n + 2, vector<long long>(m + 2, 0));
    for (int i = 0; i < e; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        d[x1][y1] += 1;
        d[x2 + 1][y1] -= 1;
        d[x1][y2 + 1] -= 1;
        d[x2 + 1][y2 + 1] += 1;
    }
    for (int x = 1; x <= n; ++x)
        for (int y = 1; y <= m; ++y)
            d[x][y] += d[x - 1][y] + d[x][y - 1] - d[x - 1][y - 1];

    // s: a vízmennyiség 2D prefixösszege; s[x][y] a (1..x) × (1..y) téglalap összege
    vector<vector<long long>> s(n + 1, vector<long long>(m + 1, 0));
    for (int x = 1; x <= n; ++x)
        for (int y = 1; y <= m; ++y)
            s[x][y] = d[x][y] + s[x - 1][y] + s[x][y - 1] - s[x - 1][y - 1];

    long long best = -1;
    int bx = 1, by = 1;
    for (int x = 1; x + k - 1 <= n; ++x)
        for (int y = 1; y + k - 1 <= m; ++y) {
            int x2 = x + k - 1, y2 = y + k - 1;
            long long sum = s[x2][y2] - s[x - 1][y2] - s[x2][y - 1] + s[x - 1][y - 1];
            if (sum > best) {
                best = sum;
                bx = x;
                by = y;
            }
        }

    cout << best << '\n' << bx << ' ' << by << '\n';
    return 0;
}
