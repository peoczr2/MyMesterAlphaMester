/*
Megoldas lenyege:
A könyvek egy permutációt alkotnak. Egy csere csak a ciklusok számát csökkenti
1-gyel, ezért egy ciklus hossza k darab elem esetén pontosan k-1 csere kell a
helyre rendezéséhez. Így elég a permutáció ciklusait megszámolni, majd az
összes szükséges csere száma N - ciklusok_száma.
*/
/*
Hint 1: || Nézd meg, melyik könyv melyik helyre akar kerülni: ez egy permutációs ciklusfelbontás. ||
Hint 2: || Egy k hosszú ciklus belső rendezéséhez pontosan k-1 csere kell. ||
Hint 3: || Az összes szükséges csere a ciklusok hozzájárulásainak összege, vagyis N - ciklusok száma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) cin >> p[i];

    vector<char> vis(n + 1, 0);
    int cycles = 0;
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        ++cycles;
        int v = i;
        while (!vis[v]) {
            vis[v] = 1;
            v = p[v];
        }
    }

    cout << n - cycles << '\n';
    return 0;
}
