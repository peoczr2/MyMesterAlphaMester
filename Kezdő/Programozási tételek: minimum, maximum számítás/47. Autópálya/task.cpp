/*
Megoldás lényege:
Minden autó egyszer, összefüggően és egy irányban halad át a helyeken, ezért két egymás melletti helyen észlelt autó az adott szakaszt megtette; a szakasz irányát az észlelések sorrendje adja. Az észleléseket autónként gyűjtjük, helyenként eltároljuk az időpontot percben (óra·60 + perc). Szakaszonként és irányonként külön tartjuk nyilván a legkisebb menetidőt; holtverseny esetén a bemenetben korábban először észlelt autó nyer, ezért az autókat első előfordulásuk sorrendjében járjuk be, és csak szigorúan kisebb menetidőnél írjuk felül a jelöltet. Az időigény O(M + A·N), ahol A az autók száma, a memóriaigény O(A·N).
*/
/*
Hint 1: || Egy autó egyszer, összefüggően halad át a helyeken, ezért két egymás melletti helyen észlelt autó az adott szakaszt megtette; a szakasz irányát az észlelések sorrendje adja. ||
Hint 2: || Gyűjtsd autónként a helyekhez tartozó időpontokat (percben), és minden szakaszra, irányonként külön tartsd nyilván az eddigi legkisebb menetidőt és a hozzá tartozó rendszámot. ||
Hint 3: || Holtverseny esetén a bemenetben korábban először észlelt autó nyer: az autókat abban a sorrendben dolgozd fel, ahogy először megjelentek, és a jelöltet csak szigorúan kisebb menetidőnél írd felül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    map<int, int> carIndex;     // rendszám -> autó sorszáma (az első előfordulás sorrendjében)
    vector<int> plate;          // autó sorszáma -> rendszám
    vector<vector<int>> tm;     // tm[autó][hely]: észlelés ideje percben, -1 ha nincs
    vector<vector<int>> ord;    // ord[autó][hely]: az észlelés sorszáma a bemenetben

    for (int k = 0; k < m; k++) {
        int r, h, o, p;
        cin >> r >> h >> o >> p;
        auto it = carIndex.find(r);
        int c;
        if (it == carIndex.end()) {
            c = (int)plate.size();
            carIndex[r] = c;
            plate.push_back(r);
            tm.push_back(vector<int>(n + 2, -1));
            ord.push_back(vector<int>(n + 2, -1));
        } else {
            c = it->second;
        }
        tm[c][h] = o * 60 + p;
        ord[c][h] = k;
    }

    // d = 0: az i -> i+1 irány, d = 1: az i+1 -> i irány
    const int INF = INT_MAX;
    vector<array<int, 2>> bestDur(n + 1, array<int, 2>{INF, INF});
    vector<array<int, 2>> bestPlate(n + 1, array<int, 2>{0, 0});

    for (int c = 0; c < (int)plate.size(); c++) {
        for (int i = 1; i < n; i++) {
            if (tm[c][i] < 0 || tm[c][i + 1] < 0) continue;
            int d, dur;
            if (ord[c][i] < ord[c][i + 1]) {
                d = 0;
                dur = tm[c][i + 1] - tm[c][i];
            } else {
                d = 1;
                dur = tm[c][i] - tm[c][i + 1];
            }
            if (dur < bestDur[i][d]) {
                bestDur[i][d] = dur;
                bestPlate[i][d] = plate[c];
            }
        }
    }

    for (int d = 0; d < 2; d++) {
        for (int i = 1; i < n; i++) {
            cout << bestPlate[i][d] << (i + 1 < n ? ' ' : '\n');
        }
    }
    return 0;
}
