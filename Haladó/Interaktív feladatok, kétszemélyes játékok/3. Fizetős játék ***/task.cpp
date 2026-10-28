/*
Megoldás lényege:
Minden kérdés ára fix, P(x), függetlenül a választól, Éva pedig mindig a drágább ágat adja. Ezért az [a,b] intervallumban rejtőző szám megtalálásának legrosszabb költsége f(a,b) = min_{a<=x<b} ( P(x) + max( f(a,x), f(x+1,b) ) ), ahol f(a,a) = 0. Ez egy minimax-rekurzió, amelyet a rövid intervallumoktól a hosszabbak felé haladva töltünk ki táblázatban. A játékban mindig a táblázat szerint optimális x-et kérdezzük, és a válasz alapján szűkítjük az intervallumot; egy elemű intervallumnál Megoldas-szal válaszolunk. Az idő O(N^3), a memória O(N^2). Az I/O az eva modulon keresztül történik, nem cin/cout-tal.
*/
/*
Hint 1: || Figyelj arra, hogy minden kérdés ára fix, és a válasz nem befolyásolja, mennyibe kerül; Éva viszont mindig a két lehetséges ág közül a drágábbat választja. Így a feladat minimax jellegű. ||
Hint 2: || Legyen f(a,b) annak a legrosszabb összköltsége, amikor a szám az [a,b] intervallumban van. Ekkor f(a,a)=0, és egy x-kérdés után az intervallum [a,x] vagy [x+1,b] lesz. ||
Hint 3: || Az f táblázatot az intervallum hossza szerint növekvő sorrendben töltsd ki két egymásba ágyazott ciklussal. A játékban minden lépésnél válaszd azt az x-et, amely P(x)+max(f(a,x), f(x+1,b)) minimumát adja. ||
*/
#include "eva.h"
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n = GetN();
    vector<int> cost(n + 1, 0);
    for (int x = 1; x <= n; x++)
        cost[x] = P(x);

    // f[a][b]: az [a,b] intervallumban rejtőző szám megtalálásának legrosszabb költsége
    vector<vector<int>> f(n + 2, vector<int>(n + 2, 0));
    for (int len = 2; len <= n; len++)
        for (int a = 1; a + len - 1 <= n; a++) {
            int b = a + len - 1;
            int best = 1000000000;
            for (int x = a; x < b; x++)
                best = min(best, cost[x] + max(f[a][x], f[x + 1][b]));
            f[a][b] = best;
        }

    int a = 1, b = n;
    while (a < b) {
        int bestX = a, bestVal = 1000000000;
        for (int x = a; x < b; x++) {
            int v = cost[x] + max(f[a][x], f[x + 1][b]);
            if (v < bestVal) {
                bestVal = v;
                bestX = x;
            }
        }
        if (Kerdes(bestX) == 1)
            b = bestX;
        else
            a = bestX + 1;
    }
    Megoldas(a);
    return 0;
}
