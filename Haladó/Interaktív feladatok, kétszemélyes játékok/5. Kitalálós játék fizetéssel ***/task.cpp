/*
Megoldás lényege:
Éva csalfa, ezért Ádámnak minden válaszágon elég zsetont kell tartania. Legyen need(a,b) az a legkevesebb zseton, amellyel az [a,b] intervallumban biztosan kitalálható a szám. Ekkor need(a,a)=0, és need(a,b) = min_{a<=x<b} max( need(x+1,b)+1 , need(a,x)+1-GetP(x) ), mert egy kérdés 1 zsetonba kerül, az igen válasz pedig GetP(x) zsetont ad. A játékban mindig azt az x-et kérdezzük, amely a minimumot adja; így a zsetonok száma végig legalább a need érték marad, tehát a program akkor találja ki a számot, ha a kezdő zsetonok száma legalább need(1,N). Az idő O(N^3). Az I/O az eva modulon keresztül történik, nem cin/cout-tal.
*/
/*
Hint 1: || Egy kérdés mindig 1 zsetonba kerül, a nem válasz nem ad vissza semmit, az igen válasz viszont GetP(x) zsetont. Számold ki, hogy egy intervallumhoz legalább hány zseton kell a biztos sikerhez. ||
Hint 2: || Legyen need(a,b) ez a szám. Ekkor need(a,a)=0, és egy x-kérdésnél a nem ág az [x+1,b], az igen ág az [a,x] intervallumot adja, így need(a,b) = min over x of max(need(x+1,b)+1, need(a,x)+1-GetP(x)). ||
Hint 3: || A need táblázatot az intervallum hossza szerint növekvő sorrendben töltsd ki, a játékban pedig mindig azt az x-et válaszd, amely a minimumot adja. Így a zsetonok száma végig elég marad. ||
*/
#include "eva.h"
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n = GetN();
    vector<int> f(n + 1, 0);
    for (int x = 1; x <= n; x++)
        f[x] = GetP(x);

    // need[a][b]: a legkevesebb zseton, amellyel az [a,b] intervallum biztosan kitalálható
    vector<vector<int>> need(n + 2, vector<int>(n + 2, 0));
    for (int len = 2; len <= n; len++)
        for (int a = 1; a + len - 1 <= n; a++) {
            int b = a + len - 1;
            int best = 1000000000;
            for (int x = a; x < b; x++)
                best = min(best, max(need[x + 1][b] + 1, need[a][x] + 1 - f[x]));
            need[a][b] = best;
        }

    int a = 1, b = n;
    while (a < b) {
        int bestX = a, bestVal = 1000000000;
        for (int x = a; x < b; x++) {
            int v = max(need[x + 1][b] + 1, need[a][x] + 1 - f[x]);
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
