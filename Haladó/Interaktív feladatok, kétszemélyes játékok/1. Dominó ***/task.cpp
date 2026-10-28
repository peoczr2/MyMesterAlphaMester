/*
Megoldás lényege:
A választható sorból mindig a bal vagy a jobb szélső dominót vesszük el, ezért a maradék sor mindig egy összefüggő
szakasz [i..j] az eredeti sorból. A kirakott sor állapotát a két szélének értéke (L, R) írja le. Az F(i,j,L,R) függvény
azt adja meg, hogy az éppen lépő játékos optimális játék mellett mennyi büntetőponttal több lesz az ellenfelénél a
játék végéig: a lépő a legkisebb értéket, az ellenfél a legnagyobbat igyekszik elérni. Ha van illeszkedő dominó,
kötelező illeszteni (a büntetéses lépés nem választható), különben a két eltávolítás közül a jobb érték számít.
F memoizált rekurzióval számolható: legfeljebb 100 * 100 * 10 * 10 állapot, egy állapot O(1) időben. Az első
játékos akkor nyer, ha a kezdőállás értéke negatív. A program a jatek könyvtár Meret, D1, D2 műveletével olvassa be
a dominókat, az EnLep(kód) hívással közli a saját lépését (1..6), majd a TeLep() hívással kérdezi le az ellenfél
lépését (szintén 1..6); az utolsó lépés lekérdezésénél a könyvtár befejezi a játékot.
*/
/*
Hint 1: || Gondold át, hogy a választható sor mindig összefüggő szakasz marad-e, és mi határozza meg a kirakott sor illeszkedését: csak a két szélének értéke. ||
Hint 2: || Írj olyan rekurziót, amely egy (i, j, L, R) állapotra kiszámolja a lépő játékos büntetőpontjának és az ellenfél büntetőpontjának különbségét, és memoizáld. ||
Hint 3: || Ha van illeszkedő szélső dominó, a lépő ezek közül választ; ha nincs, a két eltávolítás közül azt, amelyik a különbséget a lépő számára a legjobban alakítja. ||
*/
#include "jatek.h"
#include <bits/stdc++.h>
using namespace std;

struct Dom {
    int x, y;
};

int N;
vector<Dom> d;                 // d[1..N]: a választható sor dominói, sorrendben
int memo[102][102][10][10];    // F(i, j, L, R) gyorsítótár
const int NINCS = INT_MIN;     // még nincs kiszámolva

bool illeszkedik(const Dom& p, int X) {
    return p.x == X || p.y == X;
}

int masik(const Dom& p, int X) {
    return p.x == X ? p.y : p.x;
}

// A lépő játékos (büntetőpont - ellenfél büntetőpontja) értéke optimális játékkal.
int F(int i, int j, int L, int R) {
    if (i > j) return 0;
    int& r = memo[i][j][L][R];
    if (r != NINCS) return r;

    const Dom a = d[i];
    const Dom b = d[j];
    int legjobb = INT_MAX;
    bool van = false;
    if (illeszkedik(a, L)) { van = true; legjobb = min(legjobb, -F(i + 1, j, masik(a, L), R)); }
    if (illeszkedik(a, R)) { van = true; legjobb = min(legjobb, -F(i + 1, j, L, masik(a, R))); }
    if (illeszkedik(b, L)) { van = true; legjobb = min(legjobb, -F(i, j - 1, masik(b, L), R)); }
    if (illeszkedik(b, R)) { van = true; legjobb = min(legjobb, -F(i, j - 1, L, masik(b, R))); }
    if (!van) {                        // nincs illeszkedő: büntetéses eltávolítás
        legjobb = min(1 - F(i + 1, j, L, R), 1 - F(i, j - 1, L, R));
    }
    return r = legjobb;
}

// A lépő játékos legjobb lépésének kódja (1..6).
int valasszLepes(int i, int j, int L, int R) {
    const Dom a = d[i];
    const Dom b = d[j];
    int legjobb = INT_MAX, kod = 0;
    auto probal = [&](int ertek, int k) {
        if (ertek < legjobb) { legjobb = ertek; kod = k; }
    };
    bool van = false;
    if (illeszkedik(a, L)) { van = true; probal(-F(i + 1, j, masik(a, L), R), 1); }
    if (illeszkedik(a, R)) { van = true; probal(-F(i + 1, j, L, masik(a, R)), 2); }
    if (illeszkedik(b, L)) { van = true; probal(-F(i, j - 1, masik(b, L), R), 3); }
    if (illeszkedik(b, R)) { van = true; probal(-F(i, j - 1, L, masik(b, R)), 4); }
    if (!van) {
        probal(1 - F(i + 1, j, L, R), 5);
        probal(1 - F(i, j - 1, L, R), 6);
    }
    return kod;
}

// Egy lépés (kód) alkalmazása az állapotra.
void lepes(int kod, int& i, int& j, int& L, int& R) {
    if (kod == 1) { int u = masik(d[i], L); i++; L = u; }
    else if (kod == 2) { int u = masik(d[i], R); i++; R = u; }
    else if (kod == 3) { int u = masik(d[j], L); j--; L = u; }
    else if (kod == 4) { int u = masik(d[j], R); j--; R = u; }
    else if (kod == 5) { i++; }
    else if (kod == 6) { j--; }
}

int main() {
    N = Meret();                       // a dominók száma (páros)
    d.assign(N + 2, Dom{0, 0});
    for (int t = 1; t <= N; t++) {
        d[t] = Dom{D1(t), D2(t)};      // a választható sor dominói, sorrendben
    }
    int a0 = D1(0), b0 = D2(0);        // a kezdő dominó két oldala
    fill(&memo[0][0][0][0], &memo[0][0][0][0] + sizeof(memo) / sizeof(int), NINCS);

    int i = 1, j = N, L = a0, R = b0;
    for (int t = 0; t < N / 2; t++) {
        int kod = valasszLepes(i, j, L, R);
        EnLep(kod);                    // a mi lépésünk
        lepes(kod, i, j, L, R);
        int ellen = TeLep();           // az ellenfél lépése (az utolsónál a könyvtár befejezi a játékot)
        lepes(ellen, i, j, L, R);
    }
    return 0;
}
