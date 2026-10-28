/*
Megoldás lényege:
Egy véletlenszerűen választott csavart az összes anyával összehasonlítunk, amíg meg nem találjuk a párját (q). Így az anyák a csavarnál kisebbekre és nagyobbakra oszlanak, majd a többi csavart a q anyához mérve a csavarok is két részre oszlanak. A két részprobléma független, ugyanazzal a módszerrel rekurzívan megoldható, és mivel a pivot véletlen, a várható összehasonlítás-szám O(n log n), a rekurzió mélysége pedig logaritmikus. Kis részproblémákon (16 elem alatt) a sima keresés kevesebb összehasonlítást ad: egy csavarhoz sorban keressük az anyát, az utolsó csavar párja pedig már biztosan a maradék anya, így arra nem kell összehasonlítás. A kiírást az eredmeny függvény végzi, a cs tömb i. eleme az (i+1). csavar anyájának sorszáma.
*/
/*
Hint 1: || Egy csavart és egy anyát összehasonlítva kiderül, melyik a nagyobb. Egy kiválasztott csavart az összes anyával összehasonlítva megtalálod a párját, és közben az anyákat is kettéosztod. ||
Hint 2: || Ha a megtalált anyával a többi csavart is összehasonlítod, a csavarok is két részre oszlanak. A két rész ugyanúgy oldható meg, ezért rekurzióval dolgozz. Válassz véletlen csavart, hogy a várható összehasonlításszám kicsi legyen. ||
Hint 3: || Ha a részprobléma mérete kicsi (például 16 alatt), egyszerű keresés is elég: minden csavarhoz addig keress anyát, amíg meg nem találod, az utolsó csavar párja pedig már biztosan a maradék anya. A végén a párokat az eredmeny függvénynek adott tömbben, a csavar sorszámának megfelelő indexre írd. ||
*/
#include "csavarok.h"
#include <bits/stdc++.h>
using namespace std;

// Véletlen pivot-alapú rekurzió: egy csavart választunk, és az összes anyával
// összehasonlítjuk; a párját megtaláljuk, majd a többi csavart az anyához mérjük.
// Kis részproblémákon (THR alatt) egyszerű keresés fut.
static const int THR = 16;
static mt19937 rng(20191205u);
static vector<int> pairOf;   // pairOf[csavar] = anya sorszáma (1-tõl)

static void solveSet(vector<int>& B, vector<int>& N) {
    int s = (int)B.size();
    if (s == 0) return;
    if (s <= THR) {
        // egyszerű keresés: minden csavarhoz sorban keressük az anyát
        for (int bi = 0; bi < s; ++bi) {
            int b = B[bi];
            int k = (int)N.size();
            if (k == 1) {                 // egy anya maradt: párja biztosan ez
                pairOf[b] = N[0];
                N.clear();
                break;
            }
            int found = -1;
            for (int j = 0; j < k - 1; ++j) {
                if (proba(b, N[j]) == 0) { found = j; break; }
            }
            if (found == -1) found = k - 1;   // az utolsó már biztosan ez
            pairOf[b] = N[found];
            N[found] = N.back();
            N.pop_back();
        }
        return;
    }

    // véletlen csavar, amelynek párját megkeressük
    int pi = (int)(rng() % s);
    int p = B[pi];
    vector<int> Ln, Gn;
    int q = -1;
    for (int nut : N) {
        int r = proba(p, nut);            // +1: a csavar nagyobb, az anya kisebb
        if (r == 0) q = nut;
        else if (r > 0) Ln.push_back(nut);
        else Gn.push_back(nut);
    }
    vector<int> Lb, Gb;
    for (int i = 0; i < s; ++i) {
        if (i == pi) continue;
        int b = B[i];
        int r = proba(b, q);              // -1: a csavar kisebb az q anyánál
        if (r < 0) Lb.push_back(b);
        else Gb.push_back(b);
    }
    pairOf[p] = q;
    solveSet(Lb, Ln);
    solveSet(Gb, Gn);
}

int main() {
    int n = kezdet();

    vector<int> B(n), N(n);
    for (int i = 0; i < n; ++i) { B[i] = i + 1; N[i] = i + 1; }
    shuffle(B.begin(), B.end(), rng);
    shuffle(N.begin(), N.end(), rng);

    pairOf.assign(n + 1, 0);
    solveSet(B, N);

    // a függvény 0-tól indexelt tömböt vár: cs[i] az (i+1). csavar anyája
    vector<int> cs(n);
    for (int i = 0; i < n; ++i) cs[i] = pairOf[i + 1];

    eredmeny(cs.data());
    return 0;
}
