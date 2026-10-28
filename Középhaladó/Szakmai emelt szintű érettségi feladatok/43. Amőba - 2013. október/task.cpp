/*
Megoldás lényege:
A pályát egy 16x16-os tömbben tároljuk, a bemenet két blokkját (az első betű jelzi a kezdő játékost) egyszerűen beolvassuk, és közben számoljuk, hány lépést tett mindkét játékos. A játékosok felváltva lépnek, a kezdő először, ezért ha a két lépésszám egyenlő, a kezdő következik, különben a másik. A soron következő játékos jeleinek leghosszabb vízszintes szakaszát soronként egy végigmenéssel keressük: az aktuális futás hosszát számoljuk, és csak szigorúan hosszabb szakasznál frissítünk, így döntetlen esetén a bal oldali marad. Az időigény konstans, hiszen a pálya mérete rögzített, 16x16.
*/
/*
Hint 1: || A játékosok felváltva lépnek és a kezdő lép először, így a soron következő játékos megállapításához elég a két lépésszámot összehasonlítani: egyenlő számnál a kezdő következik, különben a másik. ||
Hint 2: || A leghosszabb szakaszt soronként egy végigmenéssel keresd: számold a soron következő játékos egymás melletti jeleit, és ha a futás hossza nagyobb az eddigi legjobbnál, jegyezd fel a kezdő- és végoszlopot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    char g[17][17];
    for (int i = 1; i <= 16; i++)
        for (int j = 1; j <= 16; j++)
            g[i][j] = '.';

    string tok;
    cin >> tok;
    char starter = tok[0];
    char other = (starter == 'O') ? 'X' : 'O';
    char cur = starter;
    int cntStart = 0, cntOther = 0;

    while (cin >> tok) {
        if (tok == "O" || tok == "X") {
            cur = tok[0];
            continue;
        }
        int r = stoi(tok);
        int c;
        cin >> c;
        g[r][c] = cur;
        if (cur == starter) cntStart++;
        else cntOther++;
    }
    char nextP = (cntStart == cntOther) ? starter : other;

    // 1. részfeladat: a pálya kirajzolása
    cout << "#\n";
    for (int i = 1; i <= 16; i++) {
        for (int j = 1; j <= 16; j++) cout << g[i][j];
        cout << '\n';
    }

    // 2. részfeladat: a kezdő és a soron következő játékos
    cout << "#\n" << starter << ' ' << nextP << '\n';

    // 3. részfeladat: a soron következő játékos leghosszabb vízszintes szakasza soronként
    cout << "#\n";
    for (int i = 1; i <= 16; i++) {
        int bestLen = 0, bestS = 0, bestE = 0, run = 0;
        for (int j = 1; j <= 16; j++) {
            if (g[i][j] == nextP) {
                run++;
                if (run > bestLen) {
                    bestLen = run;
                    bestE = j;
                    bestS = j - run + 1;
                }
            } else {
                run = 0;
            }
        }
        if (bestLen > 0) cout << i << ' ' << bestS << ' ' << bestE << ' ' << bestLen << '\n';
    }
    return 0;
}
