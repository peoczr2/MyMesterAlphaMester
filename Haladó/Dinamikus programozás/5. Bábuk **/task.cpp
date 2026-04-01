/*
Egy bábu pontosan akkor tud eljutni egy mezőre K időegység alatt, ha a Manhattan-távolsága legfeljebb K.
Az |r-r0|+|c-c0|<=K feltétel az u=r+c és v=r-c transzformációban tengelyekkel párhuzamos téglalappá válik:
|u-u0|<=K és |v-v0|<=K. Minden bábuhoz ezért egy téglalapot adunk hozzá egy 2D differenciatáblához,
majd prefixösszeggel kiszámítjuk, hogy az egyes valódi mezőpontokon hány téglalap fedi egymást. A maximum
lesz a keresett válasz.
*/
/*
Hint 1: || A rombusz alakú elérési tartományt érdemes koordinátatranszformációval téglalappá alakítani. ||
Hint 2: || Az r+c és r-c koordinátákban a Manhattan-gömb tengelyekkel párhuzamos négyzet lesz. ||
Hint 3: || Nem kell minden bábuhoz minden mezőt bejárni: elég differenciatáblával téglalap-hozzáadásokat végezni. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, b;
    cin >> n >> m >> k >> b;

    int max_u = n + m;
    int max_v = n + m - 1;
    vector<vector<int>> diff(max_u + 3, vector<int>(max_v + 3, 0));

    for (int i = 0; i < b; ++i) {
        int r, c;
        cin >> r >> c;
        int u = r + c;
        int v = r - c + m;
        int u1 = max(2, u - k);
        int u2 = min(max_u, u + k);
        int v1 = max(1, v - k);
        int v2 = min(max_v, v + k);
        ++diff[u1][v1];
        --diff[u2 + 1][v1];
        --diff[u1][v2 + 1];
        ++diff[u2 + 1][v2 + 1];
    }

    for (int u = 1; u <= max_u + 1; ++u) {
        for (int v = 1; v <= max_v + 1; ++v) {
            diff[u][v] += diff[u - 1][v] + diff[u][v - 1] - diff[u - 1][v - 1];
        }
    }

    int answer = 0;
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= m; ++c) {
            int u = r + c;
            int v = r - c + m;
            answer = max(answer, diff[u][v]);
        }
    }

    cout << answer << '\n';
    return 0;
}