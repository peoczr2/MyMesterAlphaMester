/*
Megoldás lényege:
Minden egyenletet külön, O(1) időben vizsgálunk. Ha a ≠ 0, a valós megoldások számát a D = b² − 4ac diszkrimináns előjele adja: D > 0 esetén 2, D = 0 esetén 1, D < 0 esetén 0 megoldás van. Ha a = 0, az egyenlet elsőfokú: b ≠ 0 esetén pontosan 1 megoldás van. Ha a = 0 és b = 0, akkor c = 0 esetén végtelen sok megoldás van (-1 kiírása), különben nincs megoldás. A D abszolút értéke legfeljebb 4·10^12 lehet, ezért long long típust használunk. Az összes egyenlet feldolgozása O(N) időben megoldható.
*/
/*
Hint 1: || Először vizsgáld meg, hogy az x² együttható (a) nulla-e. Ha igen, az egyenlet nem másodfokú, ezért külön esetként kell kezelni. ||
Hint 2: || Ha a nem nulla, a megoldások számát a D = b² − 4ac előjele határozza meg. A b² és a 4ac értéke akár 4·10^12 is lehet, ezért 64 bites egész típust használj. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        int ans;
        if (a != 0) {
            long long d = b * b - 4 * a * c;
            if (d > 0) ans = 2;
            else if (d == 0) ans = 1;
            else ans = 0;
        } else if (b != 0) {
            ans = 1;
        } else if (c == 0) {
            ans = -1;
        } else {
            ans = 0;
        }
        cout << ans << "\n";
    }
    return 0;
}
