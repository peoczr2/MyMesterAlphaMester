/*
Megoldás lényege:
A ház mezőit rácsként kezeljük: a szobák koordinátái mezőket jelölnek, a jobb alsó sarok mezője is a szoba része, így a szélesség és a magasság a koordináták különbsége plusz egy.
Egy kétdimenziós különbségtömbbel minden szoba négy sarkába ±1 kerül, majd két irányú összegzéssel megkapjuk, mely mezők foglaltak.
A szabad mezőkből soronként hisztogramot építünk: minden oszlopban azt számoljuk, hány egymás alatti szabad mező van.
Minden sorban egy veremmel megkeressük a hisztogram legnagyobb téglalapját, és ezek közül a legnagyobb területet írjuk ki.
A legnagyobb szabad téglalap minden oldalán szobába vagy a ház falába ütközik, különben nagyobb lenne, ezért az oldalakra vonatkozó szomszédsági feltétel automatikusan teljesül.
Az időigény O(W·H), ahol W és H a ház mezőinek száma két irányban (legfeljebb 10^6), a memóriaigény szintén O(W·H).
*/
/*
Hint 1: || Rajzold le a házat mezőnként: minden mezőről döntsd el, szabad-e vagy egy szobához tartozik. A szoba koordinátái mind a két sarok mezőjét tartalmazzák, ezért a mezők száma a különbség plusz egy. ||
Hint 2: || Minden sorban számold meg, hány egymás alatti szabad mező van az egyes oszlopokban. Így a sor egy hisztogramot alkot, és a feladat a hisztogram legnagyobb téglalapjának keresése. ||
Hint 3: || A szobák foglalt mezőit gyorsan megjelölheted egy kétdimenziós különbségtömbbel: minden szoba sarkaiba ±1 kerül, majd a tömbön két irányú összegzést végzel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, fx, fy, ax, ay;
    cin >> n >> fx >> fy >> ax >> ay;
    int w = ax - fx + 1;
    int h = ay - fy + 1;

    // különbségtömb: a szobák mezőinek megjelölése (a sarkok a szoba részei)
    vector<vector<int>> d(h + 1, vector<int>(w + 1, 0));
    for (int i = 0; i < n; i++) {
        int bfx, bfy, jax, jay;
        cin >> bfx >> bfy >> jax >> jay;
        int x1 = bfx - fx, y1 = bfy - fy;
        int x2 = jax - fx, y2 = jay - fy;
        d[y1][x1] += 1;
        d[y1][x2 + 1] -= 1;
        d[y2 + 1][x1] -= 1;
        d[y2 + 1][x2 + 1] += 1;
    }

    // kétdimenziós összegzés: d[y][x] > 0 esetén a mező foglalt
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (y > 0) d[y][x] += d[y - 1][x];
            if (x > 0) d[y][x] += d[y][x - 1];
            if (y > 0 && x > 0) d[y][x] -= d[y - 1][x - 1];
        }
    }

    vector<int> magassag(w, 0);
    vector<int> verem;
    long long legnagyobb = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            magassag[x] = (d[y][x] == 0) ? magassag[x] + 1 : 0;
        }
        // legnagyobb téglalap a hisztogramban, veremmel
        verem.clear();
        for (int x = 0; x <= w; x++) {
            int aktualis = (x == w) ? 0 : magassag[x];
            while (!verem.empty() && magassag[verem.back()] >= aktualis) {
                int magas = magassag[verem.back()];
                verem.pop_back();
                int bal = verem.empty() ? -1 : verem.back();
                long long terulet = (long long)magas * (x - bal - 1);
                legnagyobb = max(legnagyobb, terulet);
            }
            if (x < w) {
                verem.push_back(x);
            }
        }
    }

    cout << legnagyobb << endl;
    return 0;
}
