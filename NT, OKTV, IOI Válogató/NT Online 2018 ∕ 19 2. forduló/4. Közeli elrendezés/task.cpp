#include <bits/stdc++.h>
using namespace std;

/*
    Egy közeli permutációban az i. pozícióban vagy i, vagy i+1 állhat. A
    lexikografikusan következő permutációhoz a jobb szélről keressük azt a helyet,
    ahol még i áll, és ezt i+1, i alakra cseréljük; a maradékot a legkisebb
    lehetséges sorrendben írjuk ki.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) cin >> p[i];

    int hely = -1;
    for (int i = n - 1; i >= 1; --i) {
        if (p[i] == i) {
            hely = i;
            break;
        }
    }

    if (hely == -1) {
        for (int i = 1; i <= n; ++i) {
            if (i > 1) cout << ' ';
            cout << i;
        }
        cout << '\n';
        return 0;
    }

    for (int i = 1; i < hely; ++i) cout << p[i] << ' ';
    cout << hely + 1 << ' ' << hely;
    for (int i = hely + 2; i <= n; ++i) cout << ' ' << i;
    cout << '\n';
    return 0;
}
