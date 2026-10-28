/*
Megoldás lényege:
A síkság a szigeten belül legalább két egymás utáni, egyenlő pozitív mérésből álló szakasz, mert ott nem mutatható ki szintkülönbség. A szigeteket a 0-tól különböző mérések összefüggő szakaszai adják; az első és az utolsó szakasz a kontinenshez tartozik, ezeket kihagyjuk. Minden szigeten egy bejárással megkeressük az egyenlő értékek maximális futamait, és a legszélesebb futamot tartjuk meg (döntetlennél a balról első marad). A kiírás a síkság két szélét, majd a sziget két partját adja, 1-től számozva; ha nincs síkság szigeten, a válasz 0. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A síkság egyenlő, egymást követő pozitív mérések futama, amelynek hossza legalább 2. Ilyet csak a szigeteken belül keress: a kontinenshez érő első és utolsó szakaszt most is hagyd ki. ||
Hint 2: || Szigetenként egy ciklusban haladj balról jobbra: a futam végét az adja, ahol a szomszédos érték már nem egyenlő. Minden futamnál nézd meg a szélességét, és csak a szigorúan szélesebbnél írd felül az eddigi legjobbat, így a balról első marad. ||
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

    int legszelesebb = 0;                  // a legszélesebb síkság mérésszáma, 0: még nincs
    int sik_bal = 0, sik_jobb = 0;         // a síkság szélei (0-tól számozva)
    int sziget_bal = 0, sziget_jobb = 0;   // a síkságot tartalmazó sziget partjai (0-tól számozva)

    int i = 0;
    while (i < n) {
        if (m[i] == 0) {
            i++;
            continue;
        }
        int l = i;
        while (i < n && m[i] > 0) i++;
        int r = i - 1;  // a sziget [l..r] indexei (0-tól számozva)

        if (l == 0 || r == n - 1) continue;  // a kontinenshez érő szakasz nem sziget

        int j = l;
        while (j <= r) {
            int s = j;  // az egyenlő értékű futam kezdete
            while (j < r && m[j + 1] == m[j]) j++;
            int e = j;  // a futam vége
            int szelesseg = e - s + 1;
            if (szelesseg >= 2 && szelesseg > legszelesebb) {
                legszelesebb = szelesseg;
                sik_bal = s;
                sik_jobb = e;
                sziget_bal = l;
                sziget_jobb = r;
            }
            j++;
        }
    }

    if (legszelesebb == 0) {
        cout << 0 << "\n";
    } else {
        cout << sik_bal + 1 << ' ' << sik_jobb + 1 << "\n";
        cout << sziget_bal + 1 << ' ' << sziget_jobb + 1 << "\n";
    }
    return 0;
}
