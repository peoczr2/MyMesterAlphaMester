/*
Megoldás lényege:
Havonként szimulálunk. Minden hónap elején megnézzük, hogy a bankban legalább 1000 Ft van-e: ha igen, a kamat S + P százalék, különben S százalék. A kamatot a bankban lévő összegből számoljuk, és az otthoni pénzhez adjuk. Ezután az otthoni pénzből annyi 100-ast teszünk a bankba, amennyi belefér, a maradék otthon marad. A bank összege mindig 100 többszöröse, így a kamat egész szám lesz. A számok nagyok lehetnek, ezért 64 bites egész típust használunk. Az időigény O(H).
*/
/*
Hint 1: || Minden hónap elején nézd meg, hogy a bankban legalább 1000 Ft van-e. Ebből dől el, hogy S vagy S + P százalék a kamat, és a kamatot a bankban lévő összegből számold. ||
Hint 2: || Az otthoni pénzből a 100-asokat átvisszük a bankba, a maradék otthon marad. A számok nagyok lehetnek, ezért használj 64 bites egészet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long bank, s, p, h;
    cin >> bank >> s >> p >> h;

    long long home = 0;
    for (long long month = 0; month < h; ++month) {
        long long rate = s + (bank >= 1000 ? p : 0);   // százalékban
        home += bank / 100 * rate;                     // bank száz többszöröse, így egész

        long long hundreds = home / 100;
        bank += 100 * hundreds;
        home %= 100;

        cout << bank << ' ' << home << '\n';
    }
    return 0;
}
