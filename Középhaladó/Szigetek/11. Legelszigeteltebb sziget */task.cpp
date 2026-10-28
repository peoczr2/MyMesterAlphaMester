/*
Megoldás lényege:
A szigetek a nullától különböző mérések összefüggő szakaszai, amelyek előtt és után is 0 áll. Az első és az utolsó szakasz a kontinens, ezért nem sziget. Két bejárással minden méréshez megjegyezzük a tőle balra és jobbra legközelebbi szárazföldi (pozitív) mérés sorszámát. Egy sziget távolsága a két oldali legközelebbi szárazföld közül a kisebbik távolság. Ezt maximalizáljuk, és döntetlen esetén a balról első szigetet tartjuk meg. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Szigeteket a pozitív mérések összefüggő szakaszai adnak. Ha egy ilyen szakasz az első vagy az utolsó méréssel kezdődik vagy végződik, az a kontinens, nem sziget. ||
Hint 2: || Tárold el minden mérésre a bal és a jobb oldali legközelebbi pozitív mérés sorszámát, két bejárással. Egy sziget két oldali távolsága ebből egy kivonással adódik, és a kisebbet kell maximalizálni. ||
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

    // bal_fold[i]: legnagyobb j <= i, amelyre m[j] > 0 (-1, ha nincs)
    // jobb_fold[i]: legkisebb j >= i, amelyre m[j] > 0 (-1, ha nincs)
    vector<int> bal_fold(n), jobb_fold(n);
    int utolso = -1;
    for (int i = 0; i < n; i++) {
        if (m[i] > 0) utolso = i;
        bal_fold[i] = utolso;
    }
    utolso = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (m[i] > 0) utolso = i;
        jobb_fold[i] = utolso;
    }

    int legjobb = 0;  // a legnagyobb elért távolság (0: nincs sziget)
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

        int tav_bal = l - bal_fold[l - 1];
        int tav_jobb = jobb_fold[r + 1] - r;
        int tav = min(tav_bal, tav_jobb);
        if (tav > legjobb) {
            legjobb = tav;
            bal_part = l;
            jobb_part = r;
        }
    }

    if (legjobb == 0) {
        cout << 0 << "\n";
    } else {
        cout << bal_part + 1 << ' ' << jobb_part + 1 << "\n";
    }
    return 0;
}
