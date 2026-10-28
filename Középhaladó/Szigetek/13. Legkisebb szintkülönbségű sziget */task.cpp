/*
Megoldás lényege:
A szigetek a pozitív mérések összefüggő szakaszai, amelyek előtt és után is 0 áll. Az első és az utolsó mérés a kontinens fölött van, ezért a szakasz, amely az első vagy az utolsó méréssel kezdődik vagy végződik, nem sziget. Egy egyszeri bejárással minden szigeten megkeressük a legmagasabb és a legalacsonyabb mérést, és a különbségüket számoljuk. A legkisebb szintkülönbségű szigetet tartjuk meg; döntetlennél a balról első szigetet. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Egy sziget a pozitív mérések olyan összefüggő szakasza, amelynek előtte és utána is 0 áll. Az első és az utolsó szakasz a kontinens, ezeket hagyd ki. ||
Hint 2: || Egy szakaszon belül egyetlen végigmenéssel megkapod a legmagasabb és a legalacsonyabb értéket. Tartsd nyilván az eddigi legkisebb szintkülönbséget és a hozzá tartozó bal és jobb partot. ||
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

    int legkisebb = INT_MAX;  // az eddigi legkisebb szintkülönbség
    int bal_part = 0, jobb_part = 0;  // 1-től számozott partok, 0: nincs sziget

    int i = 0;
    while (i < n) {
        if (m[i] == 0) {
            i++;
            continue;
        }
        int l = i;
        int min_ertek = m[i], max_ertek = m[i];
        while (i < n && m[i] > 0) {
            min_ertek = min(min_ertek, m[i]);
            max_ertek = max(max_ertek, m[i]);
            i++;
        }
        int r = i - 1;

        if (l == 0 || r == n - 1) continue;  // a kontinens szakasza nem sziget

        if (max_ertek - min_ertek < legkisebb) {
            legkisebb = max_ertek - min_ertek;
            bal_part = l + 1;
            jobb_part = r + 1;
        }
    }

    if (bal_part == 0) {
        cout << 0 << "\n";
    } else {
        cout << bal_part << ' ' << jobb_part << "\n";
    }
    return 0;
}
