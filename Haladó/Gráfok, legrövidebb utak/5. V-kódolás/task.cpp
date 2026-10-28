/*
Megoldás lényege:
A V-alakban a sorok sorszáma periodikusan, fel-le járva ismétlődik: az i. karakter sorszámát az i mod 2·(V-1) maradékból kapjuk úgy, hogy ha a maradék r < V, akkor a sor r, különben 2·(V-1) - r. Egyetlen balról jobbra haladó menetben minden karaktert a hozzá tartozó sor végéhez fűzünk, majd a V sort felülről lefelé egymás után írjuk ki. Az időigény O(N), N <= 10 000 esetén ez elhanyagolható.
*/
/*
Hint 1: || Figyeld meg, hogy a sorszámok 0-tól V-1-ig tartó fel-le mozgással ismétlődnek: a periódus 2·(V-1) hosszú. ||
Hint 2: || Az i. karakter sorát az i és a periódus maradékából határozhatod meg: ha a maradék legfeljebb V-1, az a sor maga, különben a periódus és a maradék különbsége. ||
Hint 3: || Készíts V darab üres karaktersorozatot, a bemeneti szöveget balról jobbra haladva a megfelelő sorhoz fűzd, végül a sorokat sorrendben írd ki egymás után. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, v;
    cin >> n >> v;
    string s;
    cin >> s;

    int period = 2 * (v - 1);
    vector<string> rows(v);
    int len = static_cast<int>(s.size());
    for (int i = 0; i < len; i++) {
        int r = i % period;
        int row = r < v ? r : period - r;
        rows[row] += s[i];
    }

    string result;
    for (const auto &row : rows) result += row;
    cout << result << '\n';
    return 0;
}
