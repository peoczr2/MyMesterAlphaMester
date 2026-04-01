/*
Ez a feladat egy klasszikus szekvenciaillesztés, ahol az egyezés költsége 0, az átírásé 1, a beszúrásé 2.
Ha egy pozícióban a két DNS karakter különbözik, akkor a közös ős-szekvencia adott helyén elég az egyiket
választani, és a másikat átírni, ezért a diagonális lépés költsége ilyenkor 1. A DP tábla kiszámítja a minimális
költséget, a szülőirányokból pedig visszaállítható az optimális S szekvencia és a két műveletsor is.
*/
/*
Hint 1: || Írd fel a szokásos szerkesztési távolság DP-t, de a résművelet költsége 2, a karaktercsere költsége 1. ||
Hint 2: || A visszafejtéskor három eset van: párosítás két karakter között, vagy az egyik oldalon rés. ||
Hint 3: || Különböző karakterek diagonális párosításánál a közös ősbetűt választhatod például az első szekvencia betűjének. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;
    int n = (int)a.size();
    int m = (int)b.size();

    int cols = m + 1;
    vector<unsigned short> dp((n + 1) * (m + 1), 0);
    vector<unsigned char> parent((n + 1) * (m + 1), 0);

    auto id = [cols](int i, int j) {
        return i * cols + j;
    };

    for (int i = 1; i <= n; ++i) {
        dp[id(i, 0)] = (unsigned short)(2 * i);
        parent[id(i, 0)] = 1;
    }
    for (int j = 1; j <= m; ++j) {
        dp[id(0, j)] = (unsigned short)(2 * j);
        parent[id(0, j)] = 2;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            unsigned short best = (unsigned short)(dp[id(i - 1, j - 1)] + (a[i - 1] == b[j - 1] ? 0 : 1));
            unsigned char dir = 3;
            unsigned short cand = (unsigned short)(dp[id(i - 1, j)] + 2);
            if (cand < best) {
                best = cand;
                dir = 1;
            }
            cand = (unsigned short)(dp[id(i, j - 1)] + 2);
            if (cand < best) {
                best = cand;
                dir = 2;
            }
            dp[id(i, j)] = best;
            parent[id(i, j)] = dir;
        }
    }

    string s, pa, pb;
    int i = n, j = m;
    while (i > 0 || j > 0) {
        unsigned char dir = parent[id(i, j)];
        if (dir == 3) {
            s.push_back(a[i - 1]);
            pa.push_back(a[i - 1]);
            pb.push_back(a[i - 1] == b[j - 1] ? b[j - 1] : 'X');
            --i;
            --j;
        } else if (dir == 1) {
            pa.push_back('_');
            --i;
        } else {
            pb.push_back('_');
            --j;
        }
    }

    reverse(s.begin(), s.end());
    reverse(pa.begin(), pa.end());
    reverse(pb.begin(), pb.end());

    cout << dp[id(n, m)] << '\n';
    cout << s << '\n';
    cout << pa << '\n';
    cout << pb << '\n';
    return 0;
}