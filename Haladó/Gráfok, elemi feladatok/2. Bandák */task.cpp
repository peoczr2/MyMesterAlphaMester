/*
Megoldás lényege:
A bűnözőket csúcsoknak, a közös bűncselekményeket éleknek tekintjük; a bandák a legalább kételemű összefüggő komponensek, a magányosak az izolált csúcsok.
A bandánként a legtöbb kapcsolattal rendelkező tag a legnagyobb fokszámú csúcs (egyenlőség esetén a kisebb sorszám), a legnagyobb banda mérete pedig a komponensek maximuma.
A kulcsembert úgy keressük, hogy minden tagot kihagyva megszámoljuk a maradék komponenseinek számát; a legtöbb részre bontó tag lesz a kulcsember (egyenlőségnél a kisebb sorszám).
A biztonságos banda olyan (legalább 3 tagú) banda, amelynek egyetlen tagjának letartóztatása sem bontja szét több részre, a kockázatos banda egy főnökből áll, akinek kiesése minden más tagot magányossá tesz, a totálisan szervezett banda pedig teljes gráf.
A bandákon belül minden lépés O(k^2) körüli, ahol k a banda mérete, így az időkorlát bőven teljesül.
*/
/*
Hint 1: || A kapcsolatokat szomszédsági listában tárold, a bandákat pedig összefüggő komponensekként (legalább két taggal) keresd meg egy bejárással. ||
Hint 2: || Egy tag letartóztatása után a banda maradékának komponenseit úgy számold meg, hogy a bejárást az adott tag kihagyásával futtatod; ebből derül ki a kulcsember és a biztonság is. ||
Hint 3: || A kockázatos és a totálisan szervezett bandák fokszám-feltételekkel eldönthetők: teljes gráfnál minden tag fokszáma a banda mérete mínusz egy, a főnökös bandánál a többi tag csak a főnökhöz kapcsolódik. ||
*/
#include <bits/stdc++.h>
using namespace std;

void printList(const vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        if (i) cout << ' ';
        cout << v[i];
    }
    cout << '\n';
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> edges;
    int a, b;
    while (cin >> a >> b) {
        if (a == 0 && b == 0) break;
        edges.push_back({a, b});
    }

    int V = n;
    for (auto& e : edges) V = max({V, e.first, e.second});

    vector<vector<int>> g(V + 1);
    vector<vector<char>> adj(V + 1, vector<char>(V + 1, 0));
    for (auto& e : edges) {
        int x = e.first, y = e.second;
        if (x == y || adj[x][y]) continue;
        adj[x][y] = adj[y][x] = 1;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    // A: magányos bűnözők
    vector<int> loners;
    for (int v = 1; v <= V; v++)
        if (g[v].empty()) loners.push_back(v);

    // bandák: legalább kételemű komponensek
    vector<int> comp(V + 1, -1);
    vector<vector<int>> gangs;
    for (int v = 1; v <= V; v++) {
        if (g[v].empty() || comp[v] != -1) continue;
        int id = gangs.size();
        vector<int> members;
        queue<int> q;
        q.push(v);
        comp[v] = id;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            members.push_back(x);
            for (int y : g[x])
                if (comp[y] == -1) {
                    comp[y] = id;
                    q.push(y);
                }
        }
        sort(members.begin(), members.end());
        gangs.push_back(members);
    }

    // a banda tagjainak kihagyásával kapott komponensek száma
    auto partsWithout = [&](const vector<int>& mem, int removed) {
        vector<char> in(V + 1, 0), seen(V + 1, 0);
        for (int x : mem)
            if (x != removed) in[x] = 1;
        int cnt = 0;
        for (int x : mem) {
            if (x == removed || seen[x]) continue;
            cnt++;
            queue<int> q;
            q.push(x);
            seen[x] = 1;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int y : g[u])
                    if (in[y] && !seen[y]) {
                        seen[y] = 1;
                        q.push(y);
                    }
            }
        }
        return cnt;
    };

    vector<int> bestConn, keyPersons;
    int maxSize = 0;
    int safeCnt = 0, riskyCnt = 0, totalCnt = 0;
    for (auto& mem : gangs) {
        int s = mem.size();
        maxSize = max(maxSize, s);

        // C: legtöbb kapcsolattal rendelkező tag
        int bestDeg = -1, bestV = -1;
        for (int x : mem)
            if ((int)g[x].size() > bestDeg) {
                bestDeg = g[x].size();
                bestV = x;
            }
        bestConn.push_back(bestV);

        // E: kulcsember (a legtöbb részre bontó tag)
        int bestParts = -1, keyV = -1;
        bool fragile = false;
        for (int x : mem) {
            int p = partsWithout(mem, x);
            if (p > bestParts) {
                bestParts = p;
                keyV = x;
            }
            if (s - 1 <= 1 || p >= 2) fragile = true;
        }
        keyPersons.push_back(keyV);

        // F: biztonságos banda (egy letartóztatás sem bontja szét)
        if (!fragile) safeCnt++;

        // G: kockázatos banda (van olyan tag, akinek kiesése után mindenki magányos)
        bool risky = false;
        for (int x : mem) {
            bool allLoners = true;
            for (int y : mem) {
                if (y == x) continue;
                if (g[y].size() != 1 || g[y][0] != x) {
                    allLoners = false;
                    break;
                }
            }
            if (allLoners) {
                risky = true;
                break;
            }
        }
        if (risky) riskyCnt++;

        // H: totálisan szervezett banda (teljes gráf)
        bool complete = true;
        for (int x : mem)
            if ((int)g[x].size() != s - 1) {
                complete = false;
                break;
            }
        if (complete) totalCnt++;
    }

    sort(bestConn.begin(), bestConn.end());
    sort(keyPersons.begin(), keyPersons.end());

    printList(loners);
    cout << gangs.size() << '\n';
    printList(bestConn);
    cout << maxSize << '\n';
    printList(keyPersons);
    cout << safeCnt << '\n';
    cout << riskyCnt << '\n';
    cout << totalCnt << '\n';
    return 0;
}
