/*
Megoldás lényege:
Az állások és az orvosok várossorszámként szerepelnek, de a városok helyzete ismert. Miután mindkét
listát átalakítottuk kilométerpozíciókká, a kérdés az lesz, hogy két rendezett ponthalmazból maximum
hány pár választható úgy, hogy a két pont távolsága legfeljebb K.

Erre ugyanaz a kétmutatós mohó eljárás jó, mint a dinnyeárusoknál: mindig a legbaloldalibb még
szóba jövő kompatibilis állást és orvost párosítjuk.
*/
/*
Hint 1: || A várossorszámokat előbb valódi távolságokra kell visszafejteni. ||
Hint 2: || Utána két rendezett számsor maximum párosítása marad. ||
Hint 3: || Ha az egyik oldal eleme már túl balra van, azt később sem lehet párosítani. ||
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