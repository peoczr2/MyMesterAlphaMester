/*
Megoldás lényege:
Egy kő színét csak a két utolsó festése határozza meg. Ha még nem festették, fehér marad. Ha csak egyszer festették, a szín az a szín, amire festették. Ha legalább kétszer festették, és az utolsó két festés azonos színű, akkor a kő olyan színű lesz; ha különböző, akkor barna. Kőnként eltároljuk az utolsó és az utolsó előtti festés színét, a festéseket sorrendben feldolgozzuk, majd a végén megszámoljuk a piros és zöld köveket. Az időigény O(K * M * N), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Egy kő végső színét csak az utolsó két festése dönti el. Ha az utolsó két festés színe különbözik, a kő barna lesz. ||
Hint 2: || Kőnként tárold az utolsó és az utolsó előtti festés színét, és minden festésnél a téglalap kövein frissítsd őket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n, k;  // m: a fal hossza (oszlop), n: magassága (sor), k: emberek száma
    cin >> m >> n >> k;

    // 0: nincs festés, 1: piros (P), 2: zöld (Z)
    vector<vector<int>> last(n + 2, vector<int>(m + 2, 0));
    vector<vector<int>> prev(n + 2, vector<int>(m + 2, 0));

    for (int t = 0; t < k; ++t) {
        char c;
        int r1, c1, r2, c2;
        cin >> c >> r1 >> c1 >> r2 >> c2;
        int code = (c == 'P') ? 1 : 2;
        for (int i = r1; i <= r2; ++i)
            for (int j = c1; j <= c2; ++j) {
                prev[i][j] = last[i][j];
                last[i][j] = code;
            }
    }

    long long red = 0, green = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            if (last[i][j] == 0) continue;
            // egyszeri festésnél a festés színe, kétszeri (vagy több) festésnél akkor lesz
            // tiszta szín, ha az utolsó két festés azonos
            if (prev[i][j] == 0 || prev[i][j] == last[i][j]) {
                if (last[i][j] == 1) ++red;
                else ++green;
            }
        }

    cout << red << " " << green << "\n";
    return 0;
}
