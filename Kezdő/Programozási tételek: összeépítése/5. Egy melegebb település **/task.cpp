/*
Megoldás lényege:
Egy X település akkor jó, ha van olyan Y település, amelynél minden napon szigorúan alacsonyabb a hőmérséklet, mint X-nél. Ezt páronként ellenőrizzük: X és Y minden napját összevetjük, és az első olyan napnál abbahagyjuk, ahol Y nem hidegebb. A településeket sorszám szerint járjuk be, így az első megfelelő X adja a legkisebb sorszámot, különben –1 a válasz. N és M legfeljebb 100, így legfeljebb 100·100·100 = 10^6 összehasonlítás történik, ez bőven belefér az időkorlátba. A K korlát a feltételben nem szerepel, ezért nem használjuk fel.
*/
/*
Hint 1: || Egy település akkor jó, ha van nála minden napon hidegebb másik település. Ez két település összehasonlítását jelenti, a napokra nézve egyszerre. ||
Hint 2: || Két ciklus kell: a külső végigmegy a településeken (X), a belső az összes más Y településen, és egy logikai változó mutatja, hogy minden napon hidegebb-e. Ha egy napon Y nem hidegebb, a napciklust azonnal félbe lehet hagyni, és az első jó X-nél meg lehet állni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> h(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> h[i][j];

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (y == x) continue;
            bool mindenNapHidegebb = true;
            for (int d = 0; d < m && mindenNapHidegebb; d++)
                if (h[y][d] >= h[x][d]) mindenNapHidegebb = false;
            if (mindenNapHidegebb) {
                cout << x + 1 << endl;
                return 0;
            }
        }
    }
    cout << -1 << endl;
    return 0;
}
