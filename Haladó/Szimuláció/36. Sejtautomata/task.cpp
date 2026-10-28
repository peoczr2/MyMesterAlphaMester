/*
A sejtautomata minden lépésben az előző tábla alapján frissül, ezért a következő állapotot egy külön tömbbe számoljuk. Egy cella sorsát az 5 hosszú környezete mintázata dönti el: ezt egy 5 bites számmá alakítjuk, és a 32 elemű szabálytáblában nézzük meg, hogy zöld lesz-e. A szélső 2-2 cella mindig fehér marad. Egy lépés O(N) munka, így az összes lépés O(N·K).
*/
/*
Hint 1: || A szabály minden cellára ugyanaz, ezért a következő állapotot az előző tábla másolatából számold. ||
Hint 2: || A cella új állapotát a balra és jobbra legfeljebb 2-2 sejt együttes mintázata dönti el, nem csak a zöldek száma: ezt egy 5 bites számmal kódolhatod. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    string a;
    cin >> a;
    int m;
    cin >> m;
    vector<int> rule(32, 0);
    for (int i = 0; i < m; ++i) {
        string p;
        cin >> p;
        int mask = 0;
        for (char c : p) mask = (mask << 1) | (c == 'Z');
        rule[mask] = 1;
    }

    for (int step = 0; step < k; ++step) {
        string b(n, 'F');
        for (int i = 2; i < n - 2; ++i) {
            int mask = 0;
            for (int j = i - 2; j <= i + 2; ++j) mask = (mask << 1) | (a[j] == 'Z');
            if (rule[mask]) b[i] = 'Z';
        }
        a.swap(b);
    }

    cout << count(a.begin(), a.end(), 'Z') << '\n';
    return 0;
}