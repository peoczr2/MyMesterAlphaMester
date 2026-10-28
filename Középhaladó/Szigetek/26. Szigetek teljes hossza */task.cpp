/*
Megoldás lényege:
A szigetek a 0-tól különböző mérések összefüggő szakaszai; az első és az utolsó szakasz a kontinenshez tartozik, ezeket kihagyjuk. Egy sziget hossza a benne lévő nem nulla mérések száma, vagyis a szakasz hossza, és a kérdés ezeknek az összege. Egy bejárással szakaszonként megnézzük, hogy a szakasz éri-e az első vagy az utolsó mérést, és ha nem, a hosszát hozzáadjuk az összeghez. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A szigetek hosszainak összege ugyanannyi, mint a szigeteken lévő nem nulla mérések száma. Csak a kontinenshez nem tartozó szakaszokat számold bele. ||
Hint 2: || Egy bejárásban jegyezd meg a szakasz kezdő és záró indexét; a hossz ebből r - l + 1. Ha a szakasz nem éri el sem az első, sem az utolsó mérést, adj hozzá az összeghez. ||
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

    int osszeg = 0;  // a szigetek hosszainak összege

    int i = 0;
    while (i < n) {
        if (m[i] == 0) {
            i++;
            continue;
        }
        int l = i;
        while (i < n && m[i] > 0) i++;
        int r = i - 1;  // a szakasz [l..r] indexei (0-tól számozva)

        if (l == 0 || r == n - 1) continue;  // a kontinenshez érő szakasz nem sziget

        osszeg += r - l + 1;
    }

    cout << osszeg << "\n";
    return 0;
}
