/*
Egy cella új állapota a saját állapotától és a balra, jobbra legfeljebb L sejtnyi szomszédjától függ, ezért a szabályt a 2L+1 hosszú környezetek mintázataként kezeljük. Minden lépésben a régi tábláról készítünk új táblát, és minden belső cellánál a környezetét egy 2L+1 bites maszkká alakítjuk, amely a 2^(2L+1) méretű szabálytáblában megmutatja, lesz-e zöld. A szélső L-L cella mindig fehér marad. Egy lépés O(N·L), így az összes lépés O(N·K·L) munka.
*/
/*
Hint 1: || A cella új állapota csak a 2L+1 hosszú környezetétől függ, ezért minden lépésben a régi tábla alapján új táblát készíts. ||
Hint 2: || A környezet bitjeit balról jobbra egy számba fűzve megkapod a szabálytábla indexét, így minden cellára egyetlen tömbelemet kell megnézni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, l;
    cin >> n >> k >> l;
    string a;
    cin >> a;
    int m;
    cin >> m;
    int rule_size = 2 * l + 1;
    vector<int> rule(1 << rule_size, 0);
    for (int i = 0; i < m; ++i) {
        string p;
        cin >> p;
        int mask = 0;
        for (char c : p) mask = (mask << 1) | (c == 'Z');
        rule[mask] = 1;
    }

    for (int step = 0; step < k; ++step) {
        string b(n, 'F');
        for (int i = l; i < n - l; ++i) {
            int mask = 0;
            for (int j = i - l; j <= i + l; ++j) mask = (mask << 1) | (a[j] == 'Z');
            if (rule[mask]) b[i] = 'Z';
        }
        a.swap(b);
    }

    cout << count(a.begin(), a.end(), 'Z') << '\n';
    return 0;
}