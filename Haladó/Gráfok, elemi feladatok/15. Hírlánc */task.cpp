/*
Megoldás lényege:
A hírek nem járnak körbe, ezért az átadások gráfja körmentes, tehát van topologikus sorrend: mire egy tanuló sorra kerül, minden tőle hírt kapó ember hitét már ismerjük.
Mindenki megszámolja a bejövő élek forrásainál lévő híreket, és azt a hírt fogadja el, amelyet szigorúan többen mondtak, mint bármely mást. A kitalálók, ha nincs ilyen egyértelmű többségű hír, a saját hírüket tartják igaznak.
Ha több hír is a legtöbb szavazatot kapja (döntetlen), vagy nem kap senki hírt, az ember a NINCS választ adja.
A topologikus sorrendet Kahn-algoritmussal kapjuk meg, a számolás a sorrendben egy menetben elvégezhető.
Időigény: O(N + M log M), ami a megadott korlátok mellett bőven elég.
*/
/*
Hint 1: || Mivel a hírek nem járnak körbe, az átadások irányított körmentes gráfot adnak. Ha a tanulókat a hír-átadás sorrendjében dolgozod fel, mire rájuk kerül a sor, már ismered a tőlük kapott híreket. ||
Hint 2: || Topologikus sorrend: Kahn-algoritmus, a bejövő fok 0 csúcsokkal indulva, a kimenő élek mentén csökkentve a fokszámokat. A sorrend megadja, melyik ember előbb, melyik később dönthet. ||
Hint 3: || Minden tanulónál számold meg (például map-pel) a bejövő élek forrásainál lévő híreket. Ha a legtöbbször előforduló hír egyedi maximum, az lesz a hite; döntetlennél és üres listánál NINCS. Ha nincs egyértelmű többségű hír, a kitalálónak a saját hírét kell megtartania. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> from(n + 1), to(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        to[a].push_back(b);
        from[b].push_back(a);
        indeg[b]++;
    }

    vector<string> invented(n + 1);
    vector<bool> isInventor(n + 1, false);
    for (int i = 0; i < k; i++) {
        int s;
        string h;
        cin >> s >> h;
        invented[s] = h;
        isInventor[s] = true;
    }

    // Topologikus sorrend (Kahn)
    vector<int> order;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);
        for (int u : to[v])
            if (--indeg[u] == 0)
                q.push(u);
    }

    // Az üres string jelenti, hogy az ember nem tart igaznak egy hírt sem
    vector<string> belief(n + 1);
    for (int v : order) {
        map<string, int> cnt;
        for (int u : from[v])
            if (!belief[u].empty())
                cnt[belief[u]]++;

        int best = 0;
        bool tie = false;
        string bestNews;
        for (const auto &[news, c] : cnt) {
            if (c > best) {
                best = c;
                bestNews = news;
                tie = false;
            } else if (c == best) {
                tie = true;
            }
        }
        if (best > 0 && !tie)
            belief[v] = bestNews;
        else if (isInventor[v])
            belief[v] = invented[v];
    }

    for (int i = 1; i <= n; i++)
        cout << (belief[i].empty() ? string("NINCS") : belief[i]) << "\n";
    return 0;
}
