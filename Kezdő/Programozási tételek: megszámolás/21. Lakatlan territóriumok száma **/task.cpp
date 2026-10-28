/*
Megoldás lényege:
A rács minden (x, y) pontjára (1 ≤ x, y ≤ N) megnézzük, hogy van-e olyan madár, amelynek territóriumába a pont beletartozik.
Az (X, Y) fészektől R távolságra lévő territórium pontosan akkor tartalmazza az (x, y) pontot, ha |x − X| ≤ R és |y − Y| ≤ R.
A territórium a rács szélén túlra is nyúlhat, de csak a rácson belüli pontokat számoljuk. Ha egy pontot egyik madár sem fed le, növeljük a számlálót.
Az összes pontot és az összes madarat végigpróbáljuk, így az időigény O(N² · M), ami N ≤ 100 és M ≤ 32 mellett néhány százezer lépés.
*/
/*
Hint 1: || Nem kell a territóriumok területét összeadni vagy metszeni: elég a rács minden pontjáról külön eldönteni, hogy le van-e fedve. ||
Hint 2: || Egy pont akkor fedett, ha valamelyik madárra igaz, hogy a pont x-koordinátája és a madár X koordinátája legfeljebb R-rel tér el, és ugyanez igaz az y koordinátákra is. Ezt egy belső ciklussal ellenőrizd minden madárra. ||
Hint 3: || Két egymásba ágyazott ciklus (x és y, 1-től N-ig) járja be a rácsot, a fedetlen pontokat egy számlálóban gyűjtsd. A rácson kívüli pontokat ne vedd figyelembe. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<int> x(m), y(m), r(m);
    for (int i = 0; i < m; i++) {
        cin >> x[i] >> y[i] >> r[i];
    }

    int db = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            bool covered = false;
            for (int k = 0; k < m && !covered; k++) {
                if (abs(i - x[k]) <= r[k] && abs(j - y[k]) <= r[k]) {
                    covered = true;
                }
            }
            if (!covered) {
                db++;
            }
        }
    }
    cout << db << endl;
    return 0;
}
