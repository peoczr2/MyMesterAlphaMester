/*
Megoldás lényege:
A kikötők a körön vannak, így két szakasz pontosan akkor keresztezi egymást, ha végpontjaik a körön váltakozva következnek.
Egy szakasz a kört két ívre vágja, és az útvonal további része mindig csak az egyik ívre szorítkozhat, ezért a keresztezés
nélküli esetet ívekre épülő DP adja: R[s][L] az s kikötőből induló, L hosszú íven belül maradó leghosszabb útvonal,
Lf[e][L] pedig az ív végpontjából visszafelé ugyanez. Egy keresztezés esetén az első szakasz két oldalán az útvonal
egy-egy monoton láncból és egy ívbeli részből áll, ezeket az előre számolt táblázatokból a keresztező szakasz két végén
illesztjük össze. A kezdőkikötő és a második kikötő minden párjára O(N) munka jut, ezért az időigény O(N^3), a memória O(N^2).
*/
/*
Hint 1: || A kikötők körön vannak, így egy szakasz a körön lévő többi kikötőt két ívre bontja. Ha az útvonal később nem keresztez, a folytatása mindig csak az egyik íven maradhat. ||
Hint 2: || Készíts DP-t íveken: az s kikötőből induló, adott hosszúságú íven belül maradó leghosszabb útvonal értékét írd fel, és ugyanezt a végpontra illeszkedő ívre is. Az ívhossz szerint növekvő sorrendben számolhatók. ||
Hint 3: || Egy keresztezésnél az első szakasz két oldalán az útvonal egy-egy monoton láncból és egy ívbeli részből áll. A keresztező szakasz két végéhez tartozó értékeket külön-külön összegyűjtve a kezdőpont és a második kikötő rögzítése után egy lineáris bejárás elég. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int NEG = -1000000;
const int HALF = -500000;
const int BIG = 2000000;  // büntetés nem létező szakaszra (elágazás nélküli max)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, kType;
    cin >> n >> kType;
    const int P = 2 * n;

    // adjR[u][c] = 1, ha u-ból közvetlenül megy szakasz a (c mod n) kikötőbe; c a duplázott indexelés miatt [0, 2n)
    vector<vector<char>> adjR(n, vector<char>(P, 0));
    for (int i = 0; i < n; i++) {
        while (true) {
            int x;
            cin >> x;
            if (x == 0) break;
            adjR[i][x - 1] = 1;
            adjR[i][x - 1 + n] = 1;
        }
    }
    // AF[d][s]: s -> s+d, AB[d][s]: s -> s-d (a kör szerinti eltolással)
    vector<vector<char>> AF(n, vector<char>(n, 0)), AB(n, vector<char>(n, 0));
    for (int d = 1; d < n; d++) {
        for (int s = 0; s < n; s++) {
            AF[d][s] = adjR[s][s + d];
            AB[d][s] = adjR[s][s - d + n];
        }
    }

    // Az L hosszú íveket [len][kezdő vagy végpont] alakban tároljuk, a pozíciókat duplázva (0..2n-1).
    // R[len][p]:  p-ből induló útvonal, minden csúcs a p-től számított len hosszú íven belül
    // Lf[len][p]: p-ben végződő ív, az útvonal p-ből indul és az ív belsejében marad
    // ZD[len][p]: p-ből a len hosszú ív bal végéig tartó monoton csökkenő lánc (-inf, ha nincs)
    // ZI[len][p]: p-ből a len hosszú ív jobb végéig tartó monoton növekvő lánc (-inf, ha nincs)
    vector<vector<int>> R(n + 1, vector<int>(P, 0)), Lf(n + 1, vector<int>(P, 0));
    vector<vector<int>> ZD(n + 1, vector<int>(P, NEG)), ZI(n + 1, vector<int>(P, NEG));
    for (int p = 0; p < P; p++) {
        ZD[1][p] = 0;
        ZI[1][p] = 0;
    }
    vector<int> nR(n), nL(n), nD(n), nI(n);
    for (int L = 2; L <= n; L++) {
        fill(nR.begin(), nR.end(), 0);
        fill(nL.begin(), nL.end(), 0);
        fill(nD.begin(), nD.end(), NEG);
        fill(nI.begin(), nI.end(), NEG);
        for (int d = 1; d < L; d++) {
            const int* lfD = Lf[d].data();
            const int* rD = R[d].data();
            const int* rRem = R[L - d].data();
            const int* lfRem = Lf[L - d].data();
            const int* ziRem = ZI[L - d].data();
            const int* zdRem = ZD[L - d].data();
            const char* af = AF[d].data();
            const char* ab = AB[d].data();
            for (int s = 0; s < n; s++) {
                int w = s + d;      // előre lépés s -> w
                int v = s - d + n;  // hátra lépés s -> v
                int pf = (1 - af[s]) * BIG;
                int pb = (1 - ab[s]) * BIG;
                int cR = 1 + max(lfD[w], rRem[w]);
                nR[s] = max(nR[s], cR - pf);
                int cI = 1 + ziRem[w];
                nI[s] = max(nI[s], cI - pf);
                int cL = 1 + max(rD[v], lfRem[v]);
                nL[s] = max(nL[s], cL - pb);
                int cD = 1 + zdRem[v];
                nD[s] = max(nD[s], cD - pb);
            }
        }
        for (int s = 0; s < n; s++) {
            R[L][s] = R[L][s + n] = nR[s];
            Lf[L][s] = Lf[L][s + n] = nL[s];
            ZD[L][s] = ZD[L][s + n] = nD[s];
            ZI[L][s] = ZI[L][s + n] = nI[s];
        }
    }

    // K = 0: nincs keresztezés, a kezdőpont az összes kikötő közül bármelyik lehet
    int best0 = 0, start0 = 0;
    for (int s = 0; s < n; s++) {
        if (R[n][s] > best0) {
            best0 = R[n][s];
            start0 = s;
        }
    }
    if (kType == 0) {
        cout << best0 << '\n' << start0 + 1 << '\n';
        return 0;
    }

    // K = 1: az első S-T szakaszt legfeljebb egy másik szakasz metszi.
    // Eltolások T-hez képest: S = T + sg, az A2 = (T, S) ív pozíciói T+1..T+sg-1,
    // az A1 = (S, T) ív pozíciói T+sg+1..T+n-1.
    int best1 = best0, start1 = start0;
    vector<int> bestIn(n), bestOut(n);
    for (int T = 0; T < n; T++) {
        // a) A1-beli x-ből A2-beli y-ba megy a keresztező szakasz (az út T-ből monoton csökkenve jut x-be)
        fill(bestIn.begin(), bestIn.end(), NEG);
        for (int sg = n - 1; sg >= 1; sg--) {
            int S = T + sg;
            if (S >= n) S -= n;
            if (adjR[S][T]) {
                int m = NEG;
                for (int j = 1; j < sg; j++) {
                    int y = T + j;
                    m = max(m, bestIn[j] + max(Lf[j][y], R[sg - j][y]));
                }
                int c = 1 + max(R[sg][T], Lf[n - sg][T]);
                if (m > HALF) c = max(c, 2 + m);
                if (c > best1) {
                    best1 = c;
                    start1 = S;
                }
            }
            // az x = T + sg csúcs a következő (kisebb sg-jű) körökben már A1-beli lesz
            int x = T + sg;
            if (x >= n) x -= n;
            int zv = ZD[n - sg + 1][T];
            const vector<char>& rx = adjR[x];
            for (int j = 1; j < n; j++) {
                bestIn[j] = max(bestIn[j], zv - (1 - rx[T + j]) * BIG);
            }
        }

        // b) A2-beli y-ból A1-beli x-be megy a keresztező szakasz (az út T-ből monoton növekedve jut y-ba)
        fill(bestOut.begin(), bestOut.end(), NEG);
        for (int sg = 1; sg <= n - 1; sg++) {
            int S = T + sg;
            if (S >= n) S -= n;
            if (adjR[S][T]) {
                int m = NEG;
                for (int k = sg + 1; k < n; k++) {
                    int x = T + k;
                    m = max(m, bestOut[k] + max(Lf[k - sg][x], R[n - k][x]));
                }
                if (m > HALF && 2 + m > best1) {
                    best1 = 2 + m;
                    start1 = S;
                }
            }
            // az y = T + sg csúcs a következő körökben már A2-beli lesz
            int y = T + sg;
            if (y >= n) y -= n;
            int zv = ZI[sg + 1][T];
            const vector<char>& ry = adjR[y];
            for (int k = 1; k < n; k++) {
                bestOut[k] = max(bestOut[k], zv - (1 - ry[T + k]) * BIG);
            }
        }
    }

    cout << best1 << '\n' << start1 + 1 << '\n';
    return 0;
}
