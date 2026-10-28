/*
Megoldás lényege:
A szavak kezdőbetűi egyediek, és a lánc minden szava az előző szó utolsó betűjével kezdődik. Az első szó kezdőbetűjére egyetlen szó sem végződik, ezért azt az O(N^2) ellenőrzéssel megtaláljuk. Innen kezdve minden lépésben megkeressük azt a még nem használt szót, amelynek kezdőbetűje az aktuális szó utolsó betűje, és kiírjuk. Mivel N legfeljebb 25, az időigény O(N^2), ami bőven elég.
*/
/*
Hint 1: || Minden szó kezdőbetűje különböző, és a lánc minden szava az előző szó utolsó betűjével kezdődik. Így a szavak egy láncot alkotnak a betűk között. ||
Hint 2: || Az első szó kezdőbetűjét egyik szó utolsó betűje sem adja. Keresd meg azt a szót, amelynek kezdőbetűjére egyetlen másik szó sem végződik. ||
Hint 3: || A kezdő szótól indulva minden lépésben válaszd azt a még ki nem írt szót, amelynek kezdőbetűje az aktuális szó utolsó betűjével egyezik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> szavak(n);
    for (auto& s : szavak) cin >> s;

    // kezdőszó: amelynek kezdőbetűjére egyetlen szó sem végződik
    int kezdo = 0;
    for (int i = 0; i < n; i++) {
        bool vegzodik = false;
        for (int j = 0; j < n; j++) {
            if (szavak[j].back() == szavak[i][0]) {
                vegzodik = true;
                break;
            }
        }
        if (!vegzodik) {
            kezdo = i;
            break;
        }
    }

    vector<bool> felhasznalt(n, false);
    int akt = kezdo;
    felhasznalt[akt] = true;
    cout << szavak[akt] << "\n";

    for (int k = 1; k < n; k++) {
        int kov = -1;
        for (int j = 0; j < n && kov < 0; j++) {
            if (!felhasznalt[j] && szavak[j][0] == szavak[akt].back()) kov = j;
        }
        if (kov < 0) break;
        felhasznalt[kov] = true;
        akt = kov;
        cout << szavak[akt] << "\n";
    }
    return 0;
}
