/*
Megoldás lényege:
Legyen μ_j a j-edik faj átlagos előfordulása az M helységben. Egy i-edik helységre az eltérések összege Σ_j (E_ij − μ_j) = (a helység összes madárszáma) − Σ_j μ_j. A Σ_j μ_j tag minden helységnél ugyanaz, ezért elég azt a helységet keresni, ahol a madarak összege a legnagyobb. Soronként összegezünk, és a maximumot választjuk (egyenlőségnél a legkisebb sorszámút). Az időigény O(M·N).
*/
/*
Hint 1: || Írd fel az eltérések összegét képlettel: az átlagok levonása minden helységre ugyanazt a konstanst adja. ||
Hint 2: || A konstans elhagyható, így elég minden helység madárszámát kiszámolni és a legnagyobbat kiválasztani. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    long long bestSum = -1;  // a madárszámok nemnegatívak, így -1 biztosan kisebb
    int bestRow = 0;
    for (int i = 0; i < m; i++) {
        long long s = 0;
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            s += x;
        }
        if (s > bestSum) {
            bestSum = s;
            bestRow = i;
        }
    }
    cout << bestRow + 1 << "\n";
    return 0;
}
