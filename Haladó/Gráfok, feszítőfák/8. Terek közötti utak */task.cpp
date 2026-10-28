/*
Megoldás lényege:
A már meglévő utakat előre összevonjuk egy DSU-ban, így azok ingyen kötik össze a tereket. Ezután Kruskal-algoritmussal az építhető utakat költség szerint növekvő sorrendben dolgozzuk fel, és csak azt az utat építjük meg, amely két még különálló tércsoportot köt össze. Mivel minden térről el kell jutni minden térre, a meglévő és a megépített utak együtt pontosan egy feszítőfát adnak, amelynek építési költsége minimális. Az utak költség szerinti rendezése számlálórendezéssel történik (költség legfeljebb 1000), egyenlő költségnél a nagyobb sorszámú út kerül előre. Több minimális költségű megoldás is létezhet, a program ezek egyikét adja. Az időigény O(M + N + 1000), a DSU-műveletek gyakorlatilag állandó idejűek.
*/
/*
Hint 1: || A meglévő utak ingyen kapcsolják össze a tereket: tekintsd őket már megépítettnek, és csak a hiányzó összeköttetésekre számolj költséget. ||
Hint 2: || Dolgozd fel az építhető utakat költség szerint növekvő sorrendben (Kruskal), és egy utat akkor építs meg, ha két még különálló részt köt össze; a részeket uniós-megtalálós (DSU) struktúrával kezeld, a rendezést pedig a költségek kis értéke miatt számlálórendezéssel is megoldhatod. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> dsu;

int findSet(int x) {
    while (dsu[x] != x) {
        dsu[x] = dsu[dsu[x]];
        x = dsu[x];
    }
    return x;
}

bool unite(int x, int y) {
    x = findSet(x);
    y = findSet(y);
    if (x == y) return false;
    dsu[x] = y;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(m + 1), b(m + 1), s(m + 1);
    for (int i = 1; i <= m; i++) cin >> a[i] >> b[i] >> s[i];

    vector<char> built(m + 1, 0);
    for (int i = 0; i < k; i++) {
        int idx;
        cin >> idx;
        built[idx] = 1;
    }

    dsu.resize(n + 1);
    iota(dsu.begin(), dsu.end(), 0);
    for (int i = 1; i <= m; i++) {
        if (built[i]) unite(a[i], b[i]);
    }

    // Számlálórendezés költség szerint; azonos költségen a nagyobb sorszám kerül előre.
    vector<vector<int>> bucket(1001);
    for (int i = m; i >= 1; i--) {
        if (!built[i]) bucket[s[i]].push_back(i);
    }

    long long total = 0;
    vector<int> chosen;
    for (int c = 1; c <= 1000; c++) {
        for (int i : bucket[c]) {
            if (unite(a[i], b[i])) {
                total += c;
                chosen.push_back(i);
            }
        }
    }

    cout << total << '\n' << chosen.size() << '\n';
    for (size_t j = 0; j < chosen.size(); j++) {
        if (j) cout << ' ';
        cout << chosen[j];
    }
    cout << '\n';
    return 0;
}
