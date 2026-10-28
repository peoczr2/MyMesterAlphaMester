/*
Megoldás lényege:
Egy kutya a j. szempont szerint akkor esik ki, ha a j. pontja kisebb a j. szempont alsó ponthatáránál. Ezt szempontonként külön vizsgáljuk, és minden szempont kiesőit megszámoljuk. A legkevesebb kiesőt adó szempont sorszámát írjuk ki; egyenlőség esetén a kisebb sorszám marad, mert a minimumot csak szigorúan kisebb számláló írja felül. Minden (kutya, szempont) párt egyszer nézünk meg. Az időigény O(N·M), a memóriaigény O(M).
*/
/*
Hint 1: || Egy (kutya, szempont) párnál elég megnézni, hogy a pont kisebb-e a szempont alsó ponthatáránál. Ha igen, ezt a szempontot egy kieséssel terheld. ||
Hint 2: || Szempontonként tarts egy számlálót, és keress minimumot. Csak szigorúan kisebb számlálónál cseréld a legjobb indexet, így egyenlőségnél a kisebb sorszám marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<int> kieso(m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int p;
            cin >> p;
            if (p < minPont[j]) kieso[j]++;
        }

    int legjobb = 0;
    for (int j = 1; j < m; j++)
        if (kieso[j] < kieso[legjobb]) legjobb = j;

    cout << legjobb + 1 << '\n';
    return 0;
}
