/*
Megoldás lényege:
Minden territórium tengelyekkel párhuzamos négyzet, amelynek középpontja a madár fészke.
Két négyzet akkor fed át, ha a középpontjaik vízszintes és függőleges távolsága is legfeljebb
a két sugár összege. Minden madárra megnézzük az összes többi madarat, és ha talál átfedőt,
a madár nem kerül a kimenetbe. A sorszámok a bemeneti sorrendben, tehát növekvő sorrendben
kerülnek ki. Az időigény O(M*M), ami M legfeljebb 1000 mellett, mintegy 10^6 művelettel belefér.
*/
/*
Hint 1: || Két négyzet pontosan akkor fed át, ha a vízszintes és a függőleges irányban is átfednek. Egy irányban két szakasz átfed, ha a középpontjaik távolsága nem nagyobb a sugarak összegénél. ||
Hint 2: || Két madárnál legyen |X1 - X2| <= R1 + R2 és |Y1 - Y2| <= R1 + R2. Minden madárnál nézd végig az összes többit, és az első átfedésnél már nem kell tovább keresni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;

    vector<int> x(m), y(m), r(m);
    for (int i = 0; i < m; i++) {
        cin >> x[i] >> y[i] >> r[i];
    }

    vector<int> nemVerekedo;
    for (int i = 0; i < m; i++) {
        bool atfedes = false;
        for (int j = 0; j < m && !atfedes; j++) {
            if (i == j) {
                continue;
            }
            int osszeg = r[i] + r[j];
            if (abs(x[i] - x[j]) <= osszeg && abs(y[i] - y[j]) <= osszeg) {
                atfedes = true;
            }
        }
        if (!atfedes) {
            nemVerekedo.push_back(i + 1);
        }
    }

    for (size_t i = 0; i < nemVerekedo.size(); i++) {
        if (i > 0) {
            cout << " ";
        }
        cout << nemVerekedo[i];
    }
    cout << "\n";
    return 0;
}
