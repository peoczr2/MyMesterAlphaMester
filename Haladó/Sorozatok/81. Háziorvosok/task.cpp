/*
Megoldás lényege:
Az állások és az orvosok a városok sorrendjében vannak megadva, a városokhoz pedig ismert a valós
távolság. Ezért az állások tényleges pozícióját és az orvosok lakhelyének pozícióját ki tudjuk írni,
utána a feladat pontosan ugyanaz, mint két rendezett pontsorozat maximum párosítása egy K sugarú
megengedett távolsággal.

Két mutatóval greedyn párosítjuk a legbaloldalibb még fel nem használt kompatibilis állást és orvost.
*/
/*
Hint 1: || Először a várossorszámokat alakítsd át valódi kilométerpozíciókká. ||
Hint 2: || Ezután ugyanaz a probléma marad, mint két rendezett számsor maximum párosítása. ||
Hint 3: || Ha a bal oldali elem már túl messze van, azt később sem lehet megmenteni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int v, m, n;
    cin >> v >> m >> n;
    vector<int> cityPos(v + 1);
    for (int i = 1; i <= v; ++i) cin >> cityPos[i];

    vector<int> jobs(m), doctors(n);
    for (int i = 0; i < m; ++i) {
        int city;
        cin >> city;
        jobs[i] = cityPos[city];
    }
    for (int i = 0; i < n; ++i) {
        int city;
        cin >> city;
        doctors[i] = cityPos[city];
    }

    int k;
    cin >> k;

    int i = 0, j = 0, answer = 0;
    while (i < m && j < n) {
        if (jobs[i] < doctors[j] - k) {
            ++i;
        } else if (jobs[i] > doctors[j] + k) {
            ++j;
        } else {
            ++answer;
            ++i;
            ++j;
        }
    }

    cout << answer << '\n';
    return 0;
}