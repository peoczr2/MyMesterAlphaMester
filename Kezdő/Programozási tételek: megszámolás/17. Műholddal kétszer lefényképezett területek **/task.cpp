/*
Megoldás lényege:
Minden fénykép egy téglalap, amelyet a bal felső és a jobb alsó sarka ír le, a határ-koordináták is benne vannak.
A teljes terület 1001×1001 cellából áll, ezért egy kétdimenziós különbségi tömbbel dolgozunk: egy téglalap minden
sarkánál +1 vagy -1 értéket írunk be. A tömb kétszeri prefixösszegzése után minden cella értéke azt adja meg, hány
fénykép fedi le az adott cellát. Az eredmény a 2 értékű cellák száma. Az időigény O(N + 1001²), ami körülbelül 10^6
művelet, így az időlimitet bőven tartja.
*/
/*
Hint 1: || Egy cellát akkor kell számolni, ha pontosan két téglalap fedi. Ne a téglalapok páronkénti metszeteit vizsgáld, hanem keress olyan módszert, amellyel minden cella fedettsége egyszerre megkapható. ||
Hint 2: || Használj 2D különbségi tömböt: egy (x1,y1)–(x2,y2) téglalaphoz d[x1][y1] += 1, d[x2+1][y1] -= 1, d[x1][y2+1] -= 1, d[x2+1][y2+1] += 1 értékeket írj. A tömb mérete legalább 1002 × 1002 legyen. ||
Hint 3: || Ezután a tömbön kétszer prefixösszeget kell számolni (soronként, majd oszloponként, vagy a 2D képlettel), végül a 0..1000 tartományban megszámolod a 2-es értékű cellákat. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXC = 1000;

int main() {
    int n;
    cin >> n;
    // A koordináták 0..1000 közöttiek, a különbségi tömbhöz x2+1 = 1001 index is kell
    static int d[MAXC + 2][MAXC + 2];
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        d[x1][y1] += 1;
        d[x2 + 1][y1] -= 1;
        d[x1][y2 + 1] -= 1;
        d[x2 + 1][y2 + 1] += 1;
    }
    // 2D prefixösszeg: utána d[x][y] az adott cellát fedő fényképek száma
    for (int x = 0; x <= MAXC + 1; x++) {
        for (int y = 0; y <= MAXC + 1; y++) {
            int up = (x > 0) ? d[x - 1][y] : 0;
            int left = (y > 0) ? d[x][y - 1] : 0;
            int diag = (x > 0 && y > 0) ? d[x - 1][y - 1] : 0;
            d[x][y] += up + left - diag;
        }
    }
    int ans = 0;
    for (int x = 0; x <= MAXC; x++) {
        for (int y = 0; y <= MAXC; y++) {
            if (d[x][y] == 2) ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}
