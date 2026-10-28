/*
Megoldás lényege:
A kígyózó szavak fát alkotnak: a gyökérből az a..z betűkbe vezetnek élek, egy c betűs csúcsból pedig a c-1 és a c+1 betűs gyerekek érhetők el (ha léteznek). A szótár sorrendje ennek a fának az előrendes bejárása, ezért a K-adik szót nem kell felsorolni, elég lefelé haladni a fában. Előre kiszámoljuk cnt[r][c]-t: hány, c betűvel kezdődő, legfeljebb r+1 hosszú kígyózó szó van (a 2·10^9 fölötti értékeket levágjuk). Egy szinten a testvéreket betű szerint nézzük, és az első olyan testvérnél állunk meg, amelynek részfájában benne van a sorszám; az átugrott részfák méretét levonjuk a sorszámból. Egy lekérdezés legfeljebb H lépés, így az összes lekérdezés O(H·26 + N·H) időben fut.
*/
/*
Hint 1: || Rajzold fába a szavakat: a gyökér gyerekei az a..z betűk, egy c betűs csúcs gyerekei a c-1 és a c+1 betűs csúcsok. A szótár sorrendje ennek a fának az előrendes bejárása, tehát a szavakat nem kell egyenként felsorolni. ||
Hint 2: || Számold meg előre, hogy egy adott betűvel kezdődő részfában hány szó van, figyelembe véve, hogy a szavak hossza legfeljebb H. Ezekkel a számokkal eldönthető, melyik részfába esik a keresett sorszám, és a sorszámból levonható az átugrott részfák mérete. ||
Hint 3: || Lekérdezésenként haladj lefelé a fában: az aktuális szinten a testvéreket betű szerint nézd végig, és az első olyan testvérnél állj meg, amelynek részfájában benne van a sorszám. A megálló csúcs maga is egy szó, ezért a sorszámból előbb egyet le kell vonni, és csak utána térsz át a gyerekeire. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const long long CAP = 2000000000LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, N;
    cin >> H >> N;

    // cnt[r][c]: a c betűvel kezdődő, legfeljebb r+1 hosszú kígyózó szavak száma
    vector<vector<long long>> cnt(H, vector<long long>(26, 1));
    for (int r = 1; r < H; ++r)
        for (int c = 0; c < 26; ++c) {
            long long s = 1;
            if (c > 0) s += cnt[r - 1][c - 1];
            if (c < 25) s += cnt[r - 1][c + 1];
            cnt[r][c] = min(s, CAP);
        }

    while (N--) {
        long long k;
        cin >> k;
        string ans;
        int depth = 1, prev = -1;
        while (true) {
            // a testvérek: gyökérnél mind a 26 betű, egyébként a prev-1 és a prev+1
            int lo = (prev < 0) ? 0 : max(0, prev - 1);
            int hi = (prev < 0) ? 25 : min(25, prev + 1);
            int chosen = -1;
            for (int c = lo; c <= hi; ++c) {
                if (c == prev) continue;
                long long sz = cnt[H - depth][c];
                if (k <= sz) {
                    chosen = c;
                    break;
                }
                k -= sz;
            }
            ans.push_back(char('a' + chosen));
            --k;  // a megállt csúcs maga is egy szó
            if (k == 0) break;
            prev = chosen;
            ++depth;
        }
        cout << ans << '\n';
    }
    return 0;
}
