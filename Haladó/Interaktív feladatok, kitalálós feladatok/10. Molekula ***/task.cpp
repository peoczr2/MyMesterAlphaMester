/*
Megoldás lényege:
A Kozte(x,y) művelet mindig a két atom közül a sorrendben balra lévő atom jobb szomszédját adja vissza. Rögzítjük az 1-es atomot, és mindegyik másik atommal lekérdezzük a Kozte(1,b) értéket (N-1 kérdés). Ha f(b)=b, akkor b az 1-es jobb szomszédja (R), és a jobb oldali atomok válasza mindig R. A bal oldali atomoknál f(b) a b jobb szomszédja, így a bal oldali láncot a válaszokból kiolvashatjuk: a láncot abban az atomban kezdjük, amelyre nem mutat másik bal oldali atom, és az 1-esnél fejezzük be. A jobb oldali atomok sorrendjét úgy kapjuk meg, hogy az utolsó ismert atomot és egy még el nem helyezett atomot kérdezünk: minden még el nem helyezett atom jobbra van, ezért a válasz mindig a következő atom. Összesen legfeljebb 2N-3 kérdés, ami a 2N-as határon belül van. A kiírás a Sorrend művelettel történik, sorban i=1..N-re, tükörkép is elfogadott.
*/
/*
Hint 1: || Rögzíts egy atomot (például az 1-est), és kérdezd le minden másik atommal a Kozte műveletet: a válasz mindig a két atom közül a bal oldalinak a jobb szomszédja. ||
Hint 2: || A rögzített atom jobb oldalán lévő atomok mind ugyanazt a választ adják, a bal oldaliak viszont a saját jobb szomszédjukat: ebből a bal oldali lánc sorrendje kiolvasható. ||
Hint 3: || Ha már ismert a sorrend egy vége, minden még ismeretlen atommal kérdezve a válasz a következő atom: egy kérdés egy új atomot ad. ||
*/
#include <bits/stdc++.h>
#include "muszer.h"
using namespace std;

int main() {
    int n = Atomszam();
    const int a = 1;                       // rögzített atom
    vector<int> f(n + 1, 0);
    for (int b = 2; b <= n; b++)
        f[b] = Kozte(a, b);

    // A jobb szomszéd R: az a atom, amelyre a válasz saját magát adja.
    int R = -1;
    for (int b = 2; b <= n; b++)
        if (f[b] == b) { R = b; break; }

    vector<int> left, right;               // bal oldal (az a-tól balra), jobb oldal (halmazként)
    for (int b = 2; b <= n; b++) {
        if (R != -1 && f[b] == R) right.push_back(b);
        else left.push_back(b);
    }

    // Bal oldali lánc: f[b] a b jobb szomszédja. Kezdő atom: aki senkinek nem jobb szomszédja.
    vector<int> order;
    if (!left.empty()) {
        vector<char> isSucc(n + 1, 0);
        for (int b : left) isSucc[f[b]] = 1;
        int cur = -1;
        for (int b : left)
            if (!isSucc[b]) { cur = b; break; }
        while (cur != a) {
            order.push_back(cur);
            cur = f[cur];
        }
    }
    order.push_back(a);

    // Jobb oldal: R a rögzített atom jobb szomszédja, utána egy kérdés egy új atomot ad.
    if (R != -1) {
        order.push_back(R);
        set<int> rest(right.begin(), right.end());
        rest.erase(R);
        int cur = R;
        while (!rest.empty()) {
            int y = *rest.begin();        // bármely még el nem helyezett atom: jobbra van
            int nxt = Kozte(cur, y);      // a cur jobb szomszédja
            order.push_back(nxt);
            rest.erase(nxt);
            cur = nxt;
        }
    }

    for (int i = 1; i <= n; i++)
        Sorrend(i, order[i - 1]);
    return 0;
}
