/*
Megoldás lényege: egy összefüggő láncot (útvonalat) építünk a molekulában, és ennek végeihez csatoljuk az új atomokat. A Kozte(p,t) hívás szomszédság-vizsgálatra is használható: ha p és t szomszédos, az eredmény p vagy t, így a csatolás biztos. Ha a válasz egy lánc-kívüli atom, az új, a lánchoz közelebbi célpont lesz; ha a válasz a láncban lévő atom, a t csatlakozási pontja a lánc azon részében van, amelyre a válasz mutat, ezért a pivotot oda visszük, és a csatlakozási pontot intervallum-szűkítéssel (bináris kereséssel) határozzuk meg. Ha a csatlakozási pont a lánc belső pontja, akkor ez a pont a központ, mert a láncban már két szomszédja van, és a t atom a harmadik. Minden atomot kb. egy elhelyezési hívás és néhány segédhívás követ, ezért az összes Kozte-hívás száma kb. 2N, ami a 2N+10 határon belül marad.
*/
/*
Hint 1: || Ne kérdezz minden atompárt: tarts fenn egy összefüggő láncot, és a lánc egyik végéről kérdezz egy még nem elhelyezett atomra. A válasz vagy a két atom valamelyike (akkor szomszédosak), vagy egy köztes atom, amely a lánchoz közelebb visz. ||
Hint 2: || Ha a válasz a lánc egy belső csúcsa, a csatlakozási pont a lánc abban a részében van, amelyre a válasz mutat; ezt az intervallumot minden lépésben felezd. Ha egy belső láncpont szomszédos egy új atommal, az a pont a központ, mert már két lánc-szomszédja van. ||
*/
#include "muszer.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = Atomszam();
    const int OFF = n + 2;                  // a lánc kezdőpozíciója a tömb közepén
    vector<int> ch(2 * n + 6, 0);           // ch[p]: a lánc p. pozíciójában lévő atom
    vector<int> pos(n + 1, -1);             // pos[v]: v pozíciója a láncban, -1 ha nincs benne
    int L = OFF, R = OFF;                   // a lánc bal és jobb vége
    ch[OFF] = 1;
    pos[1] = OFF;
    vector<int> stk;                        // még nem elhelyezett célpontok (lehetnek elavultak)
    for (int v = 2; v <= n; v++) stk.push_back(v);
    int pv = OFF;                           // a pivot: a lánc utolsó végpontja
    while (true) {
        while (!stk.empty() && pos[stk.back()] >= 0) stk.pop_back();
        if (stk.empty()) return 0;          // nem fordulhat elő
        int cur = stk.back();               // aktuális célpont
        int lo = L, hi = R;                 // a csatlakozási pont pozíciójának intervalluma
        int x = pv;                         // a lánc pivotja (pozícióban)
        bool switched = false;              // a másik végre már átváltottunk-e
        while (true) {
            int px = ch[x];
            int z = Kozte(px, cur);
            if (z == px || z == cur) {      // cur szomszédos px-szel
                if (x > L && x < R) Kozpont(px);   // belső láncpont harmadik szomszéddal: ez a központ
                if (x == R) { R++; ch[R] = cur; pos[cur] = R; }
                else        { L--; ch[L] = cur; pos[cur] = L; }
                pv = pos[cur];
                break;
            }
            if (pos[z] >= 0) {              // z a láncban van: a csatlakozási pont szűkül
                int y = pos[z];
                if (y < x) hi = min(hi, y);
                else       lo = max(lo, y);
                if (!switched && (x == L || x == R)) {
                    switched = true;        // először a másik végről kérdezünk
                    x = (x == R) ? L : R;
                } else {
                    x = (lo + hi) / 2;      // ezután felezés
                }
            } else {                        // z lánc-kívüli: közelebbi, új célpont
                stk.push_back(z);
                cur = z;
            }
        }
    }
}
