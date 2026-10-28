/*
Megoldás lényege:
Egy közeli permutációban minden elem a helyén marad, vagy egy szomszédjával cserélődik
meg, ezért a sorozat egy- vagy kételemű blokkokra bomlik. A lexikografikusan következő
permutáció a jobb szélről az utolsó olyan i pozíción (i < N) változik, ahol p_i = i.
Minél későbbi pozíción növelünk, annál kisebb a kapott sorozat. Ezen a helyen az i. pozícióra
i+1 kerül, az i+1. pozícióra i, a maradék pozíciókat pedig növekvő sorrendben írjuk ki.
Ha nincs ilyen i, a sorozat az utolsó közeli permutáció, és a következő az 1 2 ... N.
A megoldás O(N) időigényű.
*/
/*
Hint 1: || Az i. pozícióra csak i-1, i vagy i+1 kerülhet, így minden elem vagy fix marad, vagy egy szomszédjával cserélődik. Ezért a sorozat egy- és kételemű blokkokra bontható, és egy p_i = i elem mindig önálló blokk. ||
Hint 2: || A lexikografikusan következő sorozat a lehető leghosszabb közös előtagot tartja meg az eredetivel, és azon a helyen nagyobb értéket tartalmaz. Melyik az a legkésőbbi pozíció, ahol a sorozatot még nagyobbra lehet állítani? ||
Hint 3: || Keresd a jobb szélről az első olyan i-t (i < N), amelyre p_i = i. Ha találsz ilyet, az i. helyre i+1, az i+1. helyre i kerül, a többi pozícióra pedig a számok növekvő sorrendben. Ha nincs ilyen i, a válasz 1 2 ... N. ||
*/
#include <bits/stdc++.h>
using namespace std;

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
