/*
Megoldás lényege:
Minden munka legfeljebb egy másiknak előfeltétele, ezért a függőségek befelé irányuló erdőt alkotnak. Egy munka szintje
az a szám, ahány munka van a láncában a munkától a gyökérig (a munka is beleszámít). A minimális idő a legnagyobb szint,
hiszen a leghosszabb előfeltétel-láncot egymás után kell elvégezni. A minimális munkásszámot Hu algoritmusával keressük:
egy napon azokból a munkákból, amelyek előfeltételei már készen vannak, a legnagyobb szintűeket választjuk, legfeljebb P
darabot. Hu algoritmusa egységnyi idejű munkákra optimális, és a napok száma P növelésével nem nő, ezért a legkisebb
megfelelő P bináris kereséssel megtalálható. Az időigény O(N log^2 N).
*/
/*
Hint 1: || Mivel minden munkának legfeljebb egy közvetlen követője van, a feladat fákból áll: a minimális idő a leghosszabb előfeltétel-lánc hossza. Számold ki minden munkához, hány munka van a láncában a gyökérig. ||
Hint 2: || Egy napon csak olyan munkát végezhetsz, amelynek minden előfeltétele már az előző napon elkészült. Ha kevés a munkás, a gyökértől legtávolabbi (legnagyobb szintű) munkákat válaszd először. ||
Hint 3: || Több munkás sosem lassít, ezért a legkisebb olyan munkásszám bináris kereséssel megtalálható, amelynél a szimulált ütemezés még a minimális idő alatt végez. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> succ_;   // a munka közvetlen követője (-1, ha nincs)
vector<int> indeg0;  // a munka közvetlen előfeltételeinek száma
vector<int> level_;  // a munka és a gyökér közötti láncának hossza (a munka is beleszámít)

// Hu algoritmusa: P munkással hány nap alatt végeznek
int daysNeeded(int P) {
    vector<int> need = indeg0;
    priority_queue<pair<int, int>> pq;
    for (int v = 1; v <= n; ++v)
        if (need[v] == 0)
            pq.push({level_[v], v});

    int days = 0, done = 0;
    vector<int> finished;
    while (done < n && !pq.empty()) {
        ++days;
        finished.clear();
        for (int i = 0; i < P && !pq.empty(); ++i) {
            finished.push_back(pq.top().second);
            pq.pop();
        }
        for (int v : finished) {
            ++done;
            int s = succ_[v];
            if (s != -1 && --need[s] == 0)
                pq.push({level_[s], s});
        }
    }
    return days;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    succ_.assign(n + 1, -1);
    indeg0.assign(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        succ_[a] = b;
        ++indeg0[b];
    }

    // topologikus sorrend, majd a szintek a gyökerektől visszafelé
    vector<int> order, need = indeg0;
    queue<int> q;
    for (int v = 1; v <= n; ++v)
        if (need[v] == 0)
            q.push(v);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);
        if (succ_[v] != -1 && --need[succ_[v]] == 0)
            q.push(succ_[v]);
    }
    level_.assign(n + 1, 0);
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int v = order[i];
        level_[v] = (succ_[v] == -1) ? 1 : level_[succ_[v]] + 1;
    }
    int T = *max_element(level_.begin(), level_.end());

    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (daysNeeded(mid) <= T)
            hi = mid;
        else
            lo = mid + 1;
    }
    cout << T << " " << lo << "\n";
    return 0;
}
