/*
Megoldás lényege:
Legyen x_v=1, ha a v. üzlet az első részhez tartozik. Egy csúcs belső fokszáma
akkor és csak akkor páros, ha a szomszédai között a saját színéből páros sok van.
Ez a feltétel GF(2)-ben lineáris egyenletrendszerré alakítható:

  (A + D) x = deg mod 2,

ahol A az illesztési mátrix, D a fokszámparitások átlós mátrixa. A teljes rendszerre
Gauss-eliminációt végzünk bitműveletekkel. Ha az alapmegoldás csak 0-kból vagy csak 1-esekből áll,
egy szabad változót egyenként 1-re állítva keresünk nemtriviális megoldást, amely mindkét részt nem üresen hagyja.
Az időigény O(N^3 / 64), ami N ≤ 200 mellett bőven elég.
*/
/*
Hint 1: || Minden üzlethez egy 0/1 változót rendelünk: x_v = 1, ha az első részbe kerül. Egy üzlet saját részbeli partnereinek száma akkor páros, ha a szomszédaira összegezve az 1 + x_u + x_v értékek összege (mod 2) nulla. ||
Hint 2: || Így minden üzletre GF(2)-beli lineáris egyenlet adódik: (A + D) x = d (mod 2), ahol A a szomszédsági mátrix, D a főátlóban az üzletek fokszámparitását tartalmazó diagonális mátrix, d pedig ugyanez a paritásvektor. Ezt a rendszert bitmaszkos Gauss-eliminációval oldd meg. ||
Hint 3: || Ha az eredmény csak 0-kból vagy csak 1-esekből áll, nem jó, mert mindkét rész nem lehet üres. Ilyenkor a szabad változók egyenkénti 1-re állításával próbálkozz; a feladat garantálja, hogy legalább az egyik nemtriviális megoldást ad. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 205;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<bitset<MAXN>> mat(n);
    vector<int> degParity(n, 0);
    vector<vector<int>> adj(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int v;
            cin >> v;
            --v;
            if (!adj[i][v]) {
                adj[i][v] = adj[v][i] = 1;
                degParity[i] ^= 1;
                degParity[v] ^= 1;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adj[i][j]) mat[i][j] = 1;
        }
        if (degParity[i]) mat[i][i] = 1;
        mat[i][n] = degParity[i];
    }

    vector<int> where(n, -1);
    int row = 0;
    for (int col = 0; col < n && row < n; ++col) {
        int sel = -1;
        for (int i = row; i < n; ++i) {
            if (mat[i][col]) {
                sel = i;
                break;
            }
        }
        if (sel == -1) continue;
        swap(mat[sel], mat[row]);
        where[col] = row;
        for (int i = 0; i < n; ++i) {
            if (i != row && mat[i][col]) mat[i] ^= mat[row];
        }
        ++row;
    }

    vector<int> freeCols;
    for (int col = 0; col < n; ++col) if (where[col] == -1) freeCols.push_back(col);

    auto buildSolution = [&](const vector<int>& freeOn) {
        vector<int> x(n, 0);
        for (int col = n - 1; col >= 0; --col) {
            if (where[col] == -1) continue;
            int r = where[col];
            int val = mat[r][n];
            for (int f : freeOn) if (mat[r][f]) val ^= 1;
            x[col] = val;
        }
        for (int f : freeOn) x[f] = 1;
        return x;
    };

    auto isTrivial = [&](const vector<int>& x) {
        bool all0 = true, all1 = true;
        for (int v : x) {
            if (v) all0 = false;
            else all1 = false;
        }
        return all0 || all1;
    };

    vector<int> ans = buildSolution({});
    if (isTrivial(ans)) {
        bool found = false;
        for (int f : freeCols) {
            vector<int> trial = buildSolution({f});
            if (!isTrivial(trial)) {
                ans = move(trial);
                found = true;
                break;
            }
        }
        if (!found) {
            // A feladat garantálja, hogy van megoldás.
            ans = buildSolution(freeCols.empty() ? vector<int>{} : vector<int>{freeCols[0]});
        }
    }

    vector<int> side;
    for (int i = 0; i < n; ++i) if (ans[i]) side.push_back(i + 1);

    cout << side.size() << '\n';
    for (int i = 0; i < (int)side.size(); ++i) {
        if (i) cout << ' ';
        cout << side[i];
    }
    cout << '\n';
    return 0;
}