/*
Megoldás lényege:
Egy állapot a két kannában lévő víz mennyiségének párja: (a, b), ahol 0 ≤ a ≤ A és 0 ≤ b ≤ B. A kezdő állapot (0, 0), és a hat művelet mindegyike egy új állapotba visz. Mivel minden művelet egy lépésnek számít, a legkevesebb lépést szélességi bejárással (BFS) keressük: az első olyan állapot, ahol a második kannában N liter van, a legrövidebb műveletsor végpontja. Minden újonnan talált állapothoz eltároljuk az előző állapotot és a rajta használt műveletet, így a műveletsor a végétől visszafelé követve kiírható. Az állapotok száma legfeljebb (A+1)(B+1) ≤ 10^6, így az időigény és a memóriaigény is belefér a korlátokba.
*/
/*
Hint 1: || Egy állapot a két kanna aktuális vízmennyisége, vagyis egy (a, b) pár. Írd fel a hat műveletet úgy, hogy megmondod, melyik kanna mennyisége hogyan változik. ||
Hint 2: || Mivel minden művelet ugyanannyit ér, a legkevesebb lépés szélességi bejárással adódik. Az AB művelet annyit visz át, amennyi a második kannában még elfér: min(a, B-b). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int target, A, B;
    cin >> target >> A >> B;

    const int W = B + 1;
    const int total = (A + 1) * W;
    const char* names[6] = {"TA", "TB", "UA", "UB", "AB", "BA"};

    vector<int> dist(total, -1), prv(total, -1), how(total, -1);
    queue<int> q;
    dist[0] = 0;
    q.push(0);

    int found = -1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        int a = cur / W, b = cur % W;
        if (b == target) {
            found = cur;
            break;
        }

        int na[6], nb[6];
        na[0] = A;     nb[0] = b;          // TA
        na[1] = a;     nb[1] = B;          // TB
        na[2] = 0;     nb[2] = b;          // UA
        na[3] = a;     nb[3] = 0;          // UB
        int t = min(a, B - b);
        na[4] = a - t; nb[4] = b + t;      // AB
        t = min(b, A - a);
        na[5] = a + t; nb[5] = b - t;      // BA

        for (int k = 0; k < 6; ++k) {
            int nid = na[k] * W + nb[k];
            if (dist[nid] == -1) {
                dist[nid] = dist[cur] + 1;
                prv[nid] = cur;
                how[nid] = k;
                q.push(nid);
            }
        }
    }

    if (found == -1) {
        cout << "NINCS\n";
        return 0;
    }

    vector<int> ops;
    for (int cur = found; cur != 0; cur = prv[cur]) ops.push_back(how[cur]);
    reverse(ops.begin(), ops.end());

    cout << ops.size() << '\n';
    for (int k : ops) cout << names[k] << '\n';
    return 0;
}
