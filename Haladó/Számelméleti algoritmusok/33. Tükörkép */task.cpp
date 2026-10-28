/*
Megoldás lényege:
Ha x számjegyei a_0 … a_{n-1}, akkor az x · tükörképe szorzat együtthatói a számjegypárok szorzatösszegei, és ezek szimmetrikusak a közepükre.
Ha minden együttható legfeljebb 9, nincs átvitel, így a szorzat számjegyei is szimmetrikusak lesznek, azaz palindrom.
Az együtthatók közül a legnagyobb az a_i^2 összeg, ezért elég, hogy a számjegyek négyzetösszege legfeljebb 9 legyen.
Az első és az utolsó számjegy nem lehet nulla, különben a szorzat végén vagy elején nulla állna, és nem lenne palindrom.
N ≤ 8 esetén a teljes keresés megerősíti, hogy ez a feltétel pontosan a jó számokat adja.
A számjegyek így 0, 1 vagy 2 lehetnek, és egy visszafelé számolt táblázat megmutatja, melyik maradék négyzetösszeg-keretből van még teljes kitöltés.
Ezzel a lexikografikus DFS zsákutca nélkül, növekvő sorrendben adja a számokat, és az M. találatnál megáll.
Időigény: O(N · M), gyakorlatilag azonnali.
*/
/*
Hint 1: || Vizsgáld meg, mi történik a szorzat együtthatóival, ha az összes számjegypár-szorzatösszeg legfeljebb 9: akkor nincs átvitel, és a szorzat palindrom lesz. ||
Hint 2: || Ebből következik, hogy a számjegyek négyzetösszege legfeljebb 9, az első és az utolsó számjegy nem nulla, a többi számjegy 0, 1 vagy 2. Ezt lexikografikus DFS-sel, a zsákutcákat egy egyszerű táblázattal kiszűrve járd be. ||
*/

#include "../common.hpp"

static int n, m;
static int found = 0;
// ok[pos][b]: a pos-tól kezdődő számjegyek kitölthetők-e úgy, hogy a négyzetösszeg legfeljebb b legyen
static vector<vector<bool>> ok;

static int first_digit(int pos) {
    return (pos == 0 || pos == n - 1) ? 1 : 0;
}

static void generate(int pos, int budget, string& cur) {
    if (found >= m) return;
    if (pos == n) {
        cout << cur << '\n';
        ++found;
        return;
    }
    for (int d = first_digit(pos); d <= 2; ++d) {
        int cost = d * d;
        if (cost > budget || !ok[pos + 1][budget - cost]) continue;
        cur.push_back(char('0' + d));
        generate(pos + 1, budget - cost, cur);
        cur.pop_back();
        if (found >= m) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    if (n == 1) {
        for (int x = 1; x <= min(m, 3); ++x) cout << x << '\n';
        return 0;
    }

    ok.assign(n + 1, vector<bool>(10, false));
    for (int b = 0; b <= 9; ++b) ok[n][b] = true;
    for (int pos = n - 1; pos >= 0; --pos) {
        for (int b = 0; b <= 9; ++b) {
            for (int d = first_digit(pos); d <= 2; ++d) {
                if (d * d <= b && ok[pos + 1][b - d * d]) ok[pos][b] = true;
            }
        }
    }

    string cur;
    generate(0, 9, cur);
    return 0;
}
