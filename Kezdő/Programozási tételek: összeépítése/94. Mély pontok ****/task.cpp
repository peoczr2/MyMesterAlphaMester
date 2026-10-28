/*
Megoldás lényege:
Mély pont az a pont, amelynek mélysége nagyobb mind a négy oldalszomszédjánál, ezért minden belső
pontra O(1) ellenőrzéssel eldönthető, hogy mély pont-e; a rács szélén nincs ilyen pont. A mély
pontok jelölő tömbjéből kétdimenziós prefixösszeget építünk, így bármely téglalapban lévő mély
pontok száma négy tömbelem összegeként O(1) alatt lekérdezhető. A téglalap pontosan K pontot
tartalmaz, ezért a méretei a × b alakúak, ahol a · b = K; csak a K osztópárjai jönnek szóba, és
minden ilyen mérethez végigmegyünk az összes lehetséges bal felső sarkon. A legtöbb mély pontot
tartalmazó téglalapot tartjuk meg. Időigény O(N·M + d(K)·N·M), ahol d(K) a K osztóinak száma
(legfeljebb 32).
*/
/*
Hint 1: || Egy pont akkor mély pont, ha mélysége nagyobb a négy oldalszomszédjáénál; ezt minden belső pontra előre ki lehet számolni, a rács szélén viszont sosem lehet mély pont. ||
Hint 2: || A mély pontok jelölő tömbjéből érdemes 2D prefixösszeget építeni, így egy téglalapban lévő mély pontok száma négy tömbelem összegeként, konstans időben adódik. ||
Hint 3: || A téglalap pontosan K pontot tartalmaz, ezért a méretei a × b alakúak, ahol a · b = K; csak ezeket a méreteket kell végignézni, és mindegyiknél az összes lehetséges pozíciót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<int>> a(N, vector<int>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> a[i][j];

    // S[i][j]: a mély pontok száma az első i sor és első j oszlop által alkotott részen
    vector<vector<int>> S(N + 1, vector<int>(M + 1, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int deep = 0;
            if (i > 0 && i + 1 < N && j > 0 && j + 1 < M &&
                a[i][j] > a[i - 1][j] && a[i][j] > a[i + 1][j] &&
                a[i][j] > a[i][j - 1] && a[i][j] > a[i][j + 1])
                deep = 1;
            S[i + 1][j + 1] = S[i][j + 1] + S[i + 1][j] - S[i][j] + deep;
        }
    }

    int best = -1, r1 = 1, c1 = 1, r2 = 1, c2 = 1;
    for (int w = 1; w <= M; w++) {
        if (K % w != 0) continue;
        int h = K / w;
        if (h > N) continue;
        for (int r = 0; r + h <= N; r++) {
            for (int c = 0; c + w <= M; c++) {
                int cnt = S[r + h][c + w] - S[r][c + w] - S[r + h][c] + S[r][c];
                if (cnt > best) {
                    best = cnt;
                    r1 = r + 1;
                    c1 = c + 1;
                    r2 = r + h;
                    c2 = c + w;
                }
            }
        }
    }

    cout << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << '\n';
    return 0;
}
