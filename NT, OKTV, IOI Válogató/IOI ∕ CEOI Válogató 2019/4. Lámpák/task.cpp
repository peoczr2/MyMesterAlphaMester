/*
Megoldás lényege:
Minden négyzethez egy 0/1 változó tartozik: 1, ha ott kapcsolunk. Egy lámpa végállapota a kezdeti állapotának és a rá ható kapcsolások összegének (mod 2) együttese, ezért minden négyzetre egy egyenlet írható fel: a négyzet és a szomszédai kapcsolás-változóinak összege mod 2 egyenlő a négyzet kezdeti értékével. Így N² egyenlet és N² ismeretlen adódik, ami GF(2) felett lineáris egyenletrendszer. Ezt bitmaszkos Gauss-eliminációval oldjuk meg; ha ellentmondásra jutunk, nincs megoldás (-1). A megoldások egy eltolt altér elemei: a szabad változók minden kombinációját végigpróbáljuk, és a legkevesebb kapcsolást adó megoldást írjuk ki. A szabad változók száma kicsi, ezért ez gyorsan lefut.
*/
/*
Hint 1: || Rendelj minden négyzethez egy változót: 1, ha ott kapcsolsz, 0, ha nem. Két kapcsolás ugyanazon a helyen kiejti egymást, így minden helyet elég legfeljebb egyszer figyelembe venni. ||
Hint 2: || Egy négyzet végállapota a kezdeti értékéből és a saját meg a szomszédai kapcsolásaiból áll össze, és ennek 0-nak kell lennie. Így minden négyzethez egy XOR-egyenlet tartozik: a négyzet és a szomszédai változóinak XOR-ja egyenlő a kezdeti értékkel. ||
Hint 3: || Az N² egyenletet bitmaszkokkal oldd meg Gauss-eliminációval (sorok XOR-olásával). Ha egy egyenlet bal oldala csupa 0, de jobb oldala 1, nincs megoldás. Ha vannak szabad változók, a megoldások a szabad változók kombinációival állnak elő: próbáld ki mindet, és a legkevesebb 1-est tartalmazó megoldást írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<string> a(n);
        for (auto &s : a) cin >> s;

        int v = n * n;
        // sor: a változók (v bit), utolsó bit a jobb oldal
        vector<bitset<226>> eq(v);
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++) {
                int e = r * n + c;
                eq[e][e] = 1;
                if (r > 0) eq[e][e - n] = 1;
                if (r + 1 < n) eq[e][e + n] = 1;
                if (c > 0) eq[e][e - 1] = 1;
                if (c + 1 < n) eq[e][e + 1] = 1;
                eq[e][v] = (a[r][c] == '1');
            }

        // Gauss-Jordan-elimináció GF(2) felett
        vector<int> pivotRow(v, -1);
        int rank = 0;
        for (int col = 0; col < v; col++) {
            int sel = -1;
            for (int i = rank; i < v; i++)
                if (eq[i][col]) { sel = i; break; }
            if (sel < 0) continue;
            swap(eq[sel], eq[rank]);
            for (int i = 0; i < v; i++)
                if (i != rank && eq[i][col]) eq[i] ^= eq[rank];
            pivotRow[col] = rank;
            rank++;
        }

        bool possible = true;
        for (int i = rank; i < v; i++)
            if (eq[i][v]) possible = false;
        if (!possible) {
            cout << -1 << "\n";
            continue;
        }

        // partikuláris megoldás: a szabad változók 0-k
        bitset<225> base;
        vector<int> freeCols;
        for (int col = 0; col < v; col++) {
            if (pivotRow[col] < 0) freeCols.push_back(col);
            else if (eq[pivotRow[col]][v]) base[col] = 1;
        }

        // a homogén rendszer megoldásainak bázisa
        vector<bitset<225>> basis;
        for (int f : freeCols) {
            bitset<225> x;
            x[f] = 1;
            for (int col = 0; col < v; col++)
                if (pivotRow[col] >= 0 && eq[pivotRow[col]][f]) x[col] = 1;
            basis.push_back(x);
        }

        // a szabad változók minden kombinációja (Gray-kóddal)
        int k = basis.size();
        bitset<225> cur = base, best = base;
        int bestCnt = (int)cur.count();
        for (int i = 1; i < (1 << k); i++) {
            cur ^= basis[__builtin_ctz(i)];
            int cnt = (int)cur.count();
            if (cnt < bestCnt) {
                bestCnt = cnt;
                best = cur;
            }
        }

        cout << bestCnt;
        for (int e = 0; e < v; e++)
            if (best[e]) cout << " " << e / n + 1 << " " << e % n + 1;
        cout << "\n";
    }
    return 0;
}
