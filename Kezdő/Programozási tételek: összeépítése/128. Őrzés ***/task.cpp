/*
Megoldás lényege:
Egy szakaszban akkor van legalább egy olyan dolgozó, akivel nem találkoztunk őrként, ha a szakaszban M-nél kevesebb különböző dolgozó szerepel. Ha egy szakasz ilyen, minden részszakasza is az, ezért a bal végpont csak jobbra mozdulhat, miközben a jobb végpontot végigviszem a napokon (csúszóablak, két mutató). Egy számláló tömb tartja, hányszor szerepel az egyes dolgozók az ablakban, és egy változó a különböző dolgozók számát. Ha már mind az M dolgozó benne van, a bal végpontot addig léptetem jobbra, amíg valaki ki nem esik az ablakból. A legkorábbi leghosszabb szakaszt tartom meg, az időigény O(N), a memóriaigény O(M).
*/
/*
Hint 1: || Egy szakaszban akkor van hiányzó dolgozó, ha a benne szereplő különböző őrök száma kisebb M-nél. Ha egy szakasz ilyen, minden belőle kivágott részszakasza is az. ||
Hint 2: || Keress olyan leghosszabb szakaszt, amelyben M-nél kevesebb különböző szám van. A bal és a jobb végpontot is csak balról jobbra mozgasd, vagyis tarts egy csúszóablakot. ||
Hint 3: || Tarts egy számláló tömböt (hányszor szerepel az adott dolgozó az ablakban) és külön változót a különböző dolgozók számára. Ha ez eléri M-et, a bal szélt léptesd jobbra, amíg valaki ki nem esik, és minden jobb végpontnál csak szigorú növekedésnél írd felül a legjobb hosszt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    vector<int> cnt(m + 1, 0);
    int distinct = 0;
    int bestLen = 0, bestL = 0, bestR = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        if (cnt[s[r]]++ == 0) distinct++;
        while (distinct == m) {
            if (--cnt[s[l]] == 0) distinct--;
            l++;
        }
        if (r - l + 1 > bestLen) {
            bestLen = r - l + 1;
            bestL = l;
            bestR = r;
        }
    }
    cout << bestL + 1 << " " << bestR + 1 << "\n";
    return 0;
}
