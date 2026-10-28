/*
Megoldás lényege:
Jelöljük x_v-vel, hogy a v üzlet melyik részbe kerül (0 vagy 1). Mivel [x_u = x_v] ≡ 1 + x_u + x_v (mod 2), a v üzletnek pontosan akkor páros számú azonos részbeli partnere van, ha Σ x_u + deg(v)·x_v ≡ deg(v) (mod 2), ahol az összeg a v partnereire fut. Ez N ismeretlenes lineáris egyenletrendszer a kettes maradékosztályban, amelynek a feladat szerint van megoldása (ez Gallai tétele). A Gauss-eliminációt bitenként végezzük, a szabad ismeretleneket 0-nak véve kapunk egy megoldást. Ha ez csupa 0 vagy csupa 1, a homogén rendszer megoldásai közül egy nem konstans vektort adunk hozzá, így mindkét rész nem üres lesz. Az időigény O(N^3), N ≤ 200 esetén ez bőven gyors.
*/
/*
Hint 1: || Jelöld x_v-vel, hogy a v üzlet melyik részbe kerül. Két üzlet akkor azonos részbeli, ha x_u = x_v, és ez modulo 2 az 1 + x_u + x_v összefüggéssel írható fel. ||
Hint 2: || Írd fel minden v üzletre a „páros számú azonos részbeli partner” feltételt. Ez egyenként lineáris egyenlet a kettes maradékosztályban, így a teljes feltétel egy N ismeretlenes egyenletrendszer. ||
Hint 3: || Oldd meg az egyenletrendszert Gauss-eliminációval modulo 2. Ha a kapott megoldás csupa 0 vagy csupa 1, adj hozzá egy olyan magvektort, amely nem konstans. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> partner(n);
    for (int i = 0; i < n; ++i) {
        int ki;
        cin >> ki;
        partner[i].resize(ki);
        for (auto &p : partner[i]) {
            cin >> p;
            --p;
        }
    }

    // Egyenletrendszer modulo 2: minden v-re Σ_{u ∈ N(v)} x_u + deg(v)·x_v = deg(v).
    // Az utolsó oszlop a jobb oldal.
    vector<vector<char>> A(n, vector<char>(n + 1, 0));
    for (int v = 0; v < n; ++v) {
        int deg = partner[v].size();
        for (int u : partner[v]) A[v][u] = 1;
        A[v][v] = deg % 2;
        A[v][n] = deg % 2;
    }

    // Gauss-elimináció (redukált alak), modulo 2.
    vector<int> pivotCol;
    vector<char> isPivot(n, 0);
    int r = 0;
    for (int c = 0; c < n && r < n; ++c) {
        int p = -1;
        for (int i = r; i < n; ++i)
            if (A[i][c]) {
                p = i;
                break;
            }
        if (p < 0) continue;
        swap(A[p], A[r]);
        for (int i = 0; i < n; ++i)
            if (i != r && A[i][c])
                for (int j = c; j <= n; ++j) A[i][j] ^= A[r][j];
        pivotCol.push_back(c);
        isPivot[c] = 1;
        ++r;
    }

    auto isConst = [&](const vector<char> &v) {
        for (int i = 1; i < n; ++i)
            if (v[i] != v[0]) return false;
        return true;
    };

    // Egy megoldás: a szabad ismeretlenek 0-k.
    vector<char> x(n, 0);
    for (int i = 0; i < r; ++i) x[pivotCol[i]] = A[i][n];

    // Ha csupa 0 vagy csupa 1, egy nem konstans magvektorral toljuk el.
    if (isConst(x)) {
        for (int f = 0; f < n; ++f) {
            if (isPivot[f]) continue;
            vector<char> kv(n, 0);
            kv[f] = 1;
            for (int i = 0; i < r; ++i) kv[pivotCol[i]] = A[i][f];
            if (!isConst(kv)) {
                for (int i = 0; i < n; ++i) x[i] ^= kv[i];
                break;
            }
        }
    }

    vector<int> half;
    for (int i = 0; i < n; ++i)
        if (x[i]) half.push_back(i + 1);
    cout << half.size() << "\n";
    for (size_t i = 0; i < half.size(); ++i) {
        if (i) cout << ' ';
        cout << half[i];
    }
    cout << "\n";
    return 0;
}
