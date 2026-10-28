/*
Megoldás lényege:
A verseny teljes, ezért mindig létezik olyan sorrend, amelyben mindenki legyőzte a közvetlenül előtte állót, vagyis Hamilton-út a győzelmi gráfban. Ezt beszúrásos rendezéssel építjük: az új versenyzőt a sor végére tesszük, majd amíg legyőzi a bal szomszédját, vele cserél helyet. A megfordítás előtt így minden szomszédos párban a bal oldali győzte le a jobb oldalit; a sor megfordítása után mindenki legyőzte a közvetlenül előtte állót. Az időigény O(N^2), mert N beszúrás történik, és egy beszúrás legfeljebb N cserével jár.
*/
/*
Hint 1: || Keress olyan felsorolást, amelyben minden versenyző legyőzi a közvetlenül utána állót; ennek fordítottja már a feladat szerinti sorrend. Ilyen felsorolás mindig van, mert minden pár játszott. ||
Hint 2: || Tárold egy win[a][b] mátrixban, hogy a legyőzte-e b-t, így a csere feltétele egy összehasonlítás. Az új versenyzőt a sor végére tedd, majd amíg legyőzi a bal szomszédját, cseréljetek helyet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<char>> win(n + 1, vector<char>(n + 1, 0));
    for (int i = 0; i < n * (n - 1) / 2; ++i) {
        int a, b;
        cin >> a >> b;
        win[a][b] = 1;
    }

    vector<int> path;
    for (int v = 1; v <= n; ++v) {
        path.push_back(v);
        int pos = (int)path.size() - 1;
        while (pos > 0 && win[path[pos]][path[pos - 1]]) {
            swap(path[pos], path[pos - 1]);
            --pos;
        }
    }

    reverse(path.begin(), path.end());
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}