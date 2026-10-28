/*
Megoldás lényege:
Legfeljebb 5 ember van, akinek kettőnél több ismerőse van, ezért ezek közül kiválasztott részhalmazainak
mind (legfeljebb 32) kipróbálása gyors. Egy részhalmaz csak akkor lehet jó, ha tagjai között nincs ismeretség;
a kiválasztott emberek ismerősei ezután nem választhatók. A maradék emberek fokszáma legfeljebb 2, így az
általuk alkotott gráf utakból és körökből áll. Egy k csúcsú úton ⌈k/2⌉, egy k csúcsú körön ⌊k/2⌋ független
csúcs választható, ezeket komponensenként összeadjuk. A legnagyobb így kapott érték a megoldás.
Az időigény O(2^5 · (N + M)).
*/
/*
Hint 1: || Csak az ötnél kevesebb „sok ismerősű” embert kell külön kezelni: ezekre próbáld ki az összes döntést. ||
Hint 2: || Egy kiválasztott ember ismerősei nem kerülhetnek a halmazba, a többi ember már csak utakat és köröket alkot. ||
Hint 3: || Egy k csúcsú úton ⌈k/2⌉, egy k csúcsú körön ⌊k/2⌋ elemet választhatsz függetlenül; a komponensek összegét add hozzá a kiválasztott emberek számához. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int v = 1; v <= n; ++v) {
        sort(adj[v].begin(), adj[v].end());
        adj[v].erase(unique(adj[v].begin(), adj[v].end()), adj[v].end());
    }

    vector<int> high;
    for (int v = 1; v <= n; ++v) {
        if (adj[v].size() > 2) high.push_back(v);
    }
    int h = high.size();

    int best = 0;
    for (int mask = 0; mask < (1 << h); ++mask) {
        vector<char> chosen(n + 1, 0);
        int cnt = 0;
        for (int i = 0; i < h; ++i) {
            if (mask >> i & 1) {
                chosen[high[i]] = 1;
                ++cnt;
            }
        }

        bool ok = true;
        for (int i = 0; i < h && ok; ++i) {
            if (!(mask >> i & 1)) continue;
            for (int u : adj[high[i]]) {
                if (chosen[u]) {
                    ok = false;
                    break;
                }
            }
        }
        if (!ok) continue;

        // Szabad alacsony fokú csúcsok: nem nagy fokú, és nem szomszédja egy kiválasztottnak
        vector<char> freeV(n + 1, 0);
        for (int v = 1; v <= n; ++v) {
            if (adj[v].size() <= 2) freeV[v] = 1;
        }
        for (int i = 0; i < h; ++i) {
            if (!(mask >> i & 1)) continue;
            for (int u : adj[high[i]]) freeV[u] = 0;
        }

        // A szabad csúcsok komponensei utak vagy körök
        vector<char> seen(n + 1, 0);
        int total = cnt;
        for (int s = 1; s <= n; ++s) {
            if (!freeV[s] || seen[s]) continue;
            vector<int> stack{s};
            seen[s] = 1;
            long long comp = 0, degSum = 0;
            while (!stack.empty()) {
                int v = stack.back();
                stack.pop_back();
                ++comp;
                for (int u : adj[v]) {
                    if (!freeV[u]) continue;
                    ++degSum;
                    if (!seen[u]) {
                        seen[u] = 1;
                        stack.push_back(u);
                    }
                }
            }
            long long edges = degSum / 2;
            if (edges == comp - 1) {
                total += (comp + 1) / 2;  // út
            } else {
                total += comp / 2;  // kör
            }
        }
        best = max(best, total);
    }

    cout << best << '\n';
    return 0;
}
