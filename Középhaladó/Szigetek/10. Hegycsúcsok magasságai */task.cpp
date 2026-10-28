/*
Megoldás lényege:
Minden B mérésre, a második és az utolsó előtti között, megvizsgáljuk a két szomszédját: A a bal oldali, C a jobb oldali. A hegycsúcs feltétele B > 500, 0 < A < B és B > C > 0. A feltételt teljesítő B értékeket sorrendben eltároljuk. A kiírásban először a darabszám szerepel, majd ha van csúcs, a magasságaik egy sorban, abban a sorrendben, ahogy a mérések során következtek. Egyetlen bejárás, így az időigény O(N), a tárolt csúcsok száma legfeljebb N.
*/
/*
Hint 1: || A B mérés feltétele a két szomszédjától függ: A a bal oldali, C a jobb oldali szomszéd. A szélső méréseknek nincs mindkét szomszédja, ezért csak a második és az utolsó előtti mérés között kell vizsgálni. ||
Hint 2: || A három feltétel (B > 500, 0 < A < B és B > C > 0) egyszerre legyen igaz. A kiírásnál először a darabszám jön, a magasságokat pedig csak akkor írd ki, ha volt legalább egy csúcs. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> m(n);
    for (auto &x : m) cin >> x;

    vector<int> csucsok;
    for (int i = 1; i + 1 < n; i++) {
        int a = m[i - 1], b = m[i], c = m[i + 1];
        if (b > 500 && 0 < a && a < b && b > c && c > 0) {
            csucsok.push_back(b);
        }
    }

    cout << csucsok.size() << "\n";
    for (size_t i = 0; i < csucsok.size(); i++) {
        if (i > 0) cout << ' ';
        cout << csucsok[i];
    }
    if (!csucsok.empty()) cout << "\n";
    return 0;
}
