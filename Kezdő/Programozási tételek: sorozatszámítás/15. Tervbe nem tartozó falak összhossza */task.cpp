/*
Megoldás lényege:
A ház külső fala a téglalap négy oldala, együttes hossza a kerület: 2 · (szélesség + magasság). Egy szoba csak akkor érinti a külső falat, ha a széle pontosan a ház szélén van: a bal oldali falat a BFX = FX, a felső falat a BFY = FY, a jobb oldalt a JAX = AX, az alsót a JAY = AY feltétel jelzi. Az oldalakat külön kezeljük: minden oldalhoz egy különbségtömböt vezetünk, amely a lefedett mezők intervallumait jelöli. A különbségtömb prefixösszegeiből megkapjuk, hány mező van lefedve az adott oldalon, így az átfedő szobák sem számolódnak kétszer. Ezt a kerület mezőinek számából kivonva kapjuk a tervbe nem tartozó falhosszt. Az időigény O(N + szélesség + magasság), a memóriaigény O(szélesség + magasság).
*/
/*
Hint 1: || A falak külön kezelhetők: a ház négy oldalát külön kell megnézni. Egy szoba akkor fedi le az adott oldal egy részét, ha a széle pontosan a ház ugyanazon széléhez esik. ||
Hint 2: || Minden oldalra tarts egy segédtömböt, amelybe a szobák szakaszait különbségként írod (kezdetnél +1, a végénél utána -1). A prefixösszegek megmutatják, mely mezők vannak lefedve, a lefedett mezők számát pedig vond ki a ház kerületéből. ||
*/
#include <bits/stdc++.h>
using namespace std;

int coveredCells(const vector<int>& diff, int len) {
    int cnt = 0;
    int cur = 0;
    for (int i = 0; i < len; i++) {
        cur += diff[i];
        if (cur > 0) {
            cnt++;
        }
    }
    return cnt;
}

int main() {
    int n, fx, fy, ax, ay;
    cin >> n >> fx >> fy >> ax >> ay;

    int w = ax - fx + 1;
    int h = ay - fy + 1;

    vector<int> topDiff(w + 1, 0), bottomDiff(w + 1, 0);
    vector<int> leftDiff(h + 1, 0), rightDiff(h + 1, 0);

    for (int i = 0; i < n; i++) {
        int bfx, bfy, jax, jay;
        cin >> bfx >> bfy >> jax >> jay;

        int x1 = bfx - fx, x2 = jax - fx;
        int y1 = bfy - fy, y2 = jay - fy;

        if (bfy == fy) {
            topDiff[x1]++;
            topDiff[x2 + 1]--;
        }
        if (jay == ay) {
            bottomDiff[x1]++;
            bottomDiff[x2 + 1]--;
        }
        if (bfx == fx) {
            leftDiff[y1]++;
            leftDiff[y2 + 1]--;
        }
        if (jax == ax) {
            rightDiff[y1]++;
            rightDiff[y2 + 1]--;
        }
    }

    long long perimeter = 2LL * (w + h);
    long long covered = coveredCells(topDiff, w) + coveredCells(bottomDiff, w)
                      + coveredCells(leftDiff, h) + coveredCells(rightDiff, h);

    cout << perimeter - covered << "\n";
    return 0;
}
