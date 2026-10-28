/*
Megoldás lényege:
A szigeteket ugyanúgy találjuk meg, mint a legelszigeteltebb szigetnél: a pozitív mérések összefüggő szakaszai, amelyek nem érnek a kontinensekhez. Az óceán közepe az első és az utolsó tengeri (0 magasságú) mérés közepe, mert az óceán ezek között terül el. Ha f és u az első és utolsó tengeri mérés sorszáma, a közép (f+u)/2; a p-edik mérés kétszeres távolsága ettől |2p - (f+u)|, így törtek nélkül dolgozhatunk. Egy sziget távolsága a két partja közül a kisebb; ezt minimalizáljuk, döntetlennél a balról első szigetet tartjuk meg. Egyetlen bejárás: az időigény O(N), a memóriaigény O(N) a beolvasott tömb miatt.
*/
/*
Hint 1: || Egy sziget két partja a szakasz első és utolsó pozitív mérése. Az óceán közepét az első és az utolsó 0 magasságú mérés sorszámából kapod meg. ||
Hint 2: || Szorozd meg kettővel a távolságokat, hogy a középpont ne legyen törtszám: |2·p − (f+u)| egész. Keresd azt a szigetet, amelynél a két part közül a kisebb távolság a legkisebb. ||
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

    // az első és az utolsó tengeri (0) mérés sorszáma, 0-tól számozva
    int elso_tengeri = -1, utolso_tengeri = -1;
    for (int i = 0; i < n; i++) {
        if (m[i] == 0) {
            if (elso_tengeri < 0) elso_tengeri = i;
            utolso_tengeri = i;
        }
    }
    // a közép kétszerese, 1-től számozott sorszámokkal: (f+1) + (u+1)
    long long kozep2 = 0;
    if (elso_tengeri >= 0) kozep2 = (long long)(elso_tengeri + 1) + (utolso_tengeri + 1);

    long long legkisebb = LLONG_MAX;  // a legkisebb távolság (kétszeresben)
    int bal_part = -1, jobb_part = -1;

    int i = 0;
    while (i < n) {
        if (m[i] <= 0) {
            i++;
            continue;
        }
        int l = i;
        while (i + 1 < n && m[i + 1] > 0) i++;
        int r = i;
        i++;

        if (l == 0 || r == n - 1) continue;  // a kontinens szakasza nem sziget

        long long d_bal = llabs(2LL * (l + 1) - kozep2);
        long long d_jobb = llabs(2LL * (r + 1) - kozep2);
        long long d = min(d_bal, d_jobb);
        if (d < legkisebb) {
            legkisebb = d;
            bal_part = l;
            jobb_part = r;
        }
    }

    if (bal_part < 0) {
        cout << 0 << "\n";
    } else {
        cout << bal_part + 1 << ' ' << jobb_part + 1 << "\n";
    }
    return 0;
}
