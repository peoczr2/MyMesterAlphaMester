/*
Megoldás lényege:
A tej összmennyisége állandó, ezért egy állapotot elég az A- és B-kannában lévő mennyiséggel leírni, így legfeljebb (A+1)·(B+1) állapot van.
Egy öntögetés mindig teljesen tölt: a forrásból annyit öntünk, amennyi benne van, vagy amennyi a célba még belefér. Ennek ideje
a kiöntött mennyiség, vagyis az él súlya, így a legrövidebb utat keresünk az állapotok között (Dijkstra-típusú keresés).
Minden A-beli mennyiséghez a hozzá tartozó állapotok közül a legkisebb idő kell. Ezek közül azt a mennyiséget választjuk,
amelynek a kimérése a legtovább tart, és ha több ilyen van, a legkisebbet. Mivel az élsúlyok legfeljebb a legnagyobb kanna
űrtartalma, a prioritási sor helyett az időpontokat vödrökbe soroljuk (körkörös vödörsor), így a futás O(A·B) körüli.
*/
/*
Hint 1: || Egy öntögetés addig tart, amíg a forrás ki nem ürül, vagy a cél meg nem telik. Így minden lépés egyértelmű: a kiöntött mennyiség a két kanna aktuális tartalmából számolható. ||
Hint 2: || A tej összmennyisége nem változik, ezért egy állapot az A- és B-kannában lévő mennyiséggel leírható. Az élsúly az öntött mennyiség, minden A-beli mennyiséghez pedig a hozzá tartozó legkisebb időt kell megtalálnod. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cap[3], cur[3];
    cin >> cap[0] >> cap[1] >> cap[2];
    cin >> cur[0] >> cur[1] >> cur[2];

    const int A = cap[0], B = cap[1];
    const int total = cur[0] + cur[1] + cur[2];
    const int W = B + 1;                                   // állapot indexe: a * W + b
    const int K = max(cap[0], max(cap[1], cap[2])) + 1;    // egy öntés legfeljebb ennyi, ezért K vödör elég

    vector<long long> dist((size_t)(A + 1) * W, -1);
    vector<vector<int>> bucket(K);
    const int start = cur[0] * W + cur[1];
    dist[start] = 0;
    bucket[0].push_back(start);
    long long pending = 1;

    for (long long d = 0; pending > 0; ++d) {
        vector<int> &list = bucket[d % K];
        for (size_t k = 0; k < list.size(); ++k) {
            int s = list[k];
            --pending;
            if (dist[s] != d) continue;                    // elavult bejegyzés

            int x[3] = {s / W, s % W, 0};
            x[2] = total - x[0] - x[1];
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (i == j || x[i] == 0 || x[j] == cap[j]) continue;
                    int t = min(x[i], cap[j] - x[j]);
                    int y[3] = {x[0], x[1], x[2]};
                    y[i] -= t;
                    y[j] += t;
                    int ns = y[0] * W + y[1];
                    long long nd = d + t;
                    if (dist[ns] == -1 || nd < dist[ns]) {
                        dist[ns] = nd;
                        bucket[nd % K].push_back(ns);
                        ++pending;
                    }
                }
            }
        }
        list.clear();
    }

    // Minden A-beli mennyiséghez a legkisebb idő.
    vector<long long> best(A + 1, -1);
    for (size_t s = 0; s < dist.size(); ++s) {
        if (dist[s] < 0) continue;
        int a = (int)(s / W);
        if (best[a] < 0 || dist[s] < best[a]) best[a] = dist[s];
    }

    // A leghosszabb mérés; egyenlőség esetén a kisebb mennyiség (a ciklus növekvő a-val fut).
    int ansX = -1;
    long long ansT = -1;
    for (int a = 0; a <= A; ++a) {
        if (best[a] > ansT) {
            ansT = best[a];
            ansX = a;
        }
    }

    cout << ansX << ' ' << ansT << '\n';
    return 0;
}
