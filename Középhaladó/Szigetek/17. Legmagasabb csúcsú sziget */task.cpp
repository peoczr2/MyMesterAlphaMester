/*
Megoldás lényege:
A szigetek a 0-tól különböző mérések összefüggő szakaszai, amelyek előtt és után is 0 áll. Az első és az utolsó mérés a kontinens fölött van, ezért az ezekhez érő szakasz nem sziget, ezeket kihagyjuk. Egy csúcs a sziget belső eleme: a középső mérés nagyobb a bal és a jobb szomszédjánál, és ezek a szomszédok a szigeten belül pozitívak. Egyetlen bejárással végigmegyünk a szigeteken, és minden szigeten megkeressük a csúcsokat; az eddigi legmagasabb csúcsnál szigorúan magasabbat a sziget bal és jobb partjával együtt megtartjuk, így döntetlen esetén a balról első sziget marad. Az időigény O(N), a memóriaigény O(1) a mérések tárolásán kívül.
*/
/*
Hint 1: || Egy csúcs a sziget belsejében van: a középső mérés nagyobb a két szomszédjánál. A kontinenshez érő első és utolsó szakasz nem sziget, ezeket hagyd ki. ||
Hint 2: || Egy szigeten belül a bal és a jobb part sorszámát a szakasz első és utolsó pozitív eleme adja. Tartsd nyilván az eddigi legmagasabb csúcs magasságát és a hozzá tartozó két partot, és csak szigorúan magasabb csúcsnál írd felül. ||
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

    int legmagasabb = 0;   // az eddigi legmagasabb csúcs magassága (0: még nincs csúcs)
    int bal = 0, jobb = 0; // a legmagasabb csúcsú sziget partjai (1-től számozva)

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

        for (int j = l + 1; j < r; j++) {
            if (m[j - 1] < m[j] && m[j] > m[j + 1] && m[j] > legmagasabb) {
                legmagasabb = m[j];
                bal = l + 1;
                jobb = r + 1;
            }
        }
    }

    if (legmagasabb == 0) {
        cout << 0 << "\n";
    } else {
        cout << bal << ' ' << jobb << "\n";
    }
    return 0;
}
