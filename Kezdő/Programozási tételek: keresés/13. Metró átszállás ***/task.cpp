/*
Megoldás lényege:
A metróhálózatot gráfként kezeljük: egy csomópont egy (vonal, állomás) pár. Ugyanazon a vonalon a szomszédos állomások között 1 megálló a távolság, az azonos nevű állomások (átszállási pontok) között pedig 0. Mivel az élek súlya csak 0 vagy 1, egy kétvégű sorral (0-1 BFS) meghatározzuk minden csomópont legkevesebb megállós távolságát, az induló állomás minden példányából indulva. A célállomás legközelebbi példányából visszakövetjük az előző csomópontokat, így megkapjuk az utat. Az utat vonalanként szakaszokba fogjuk össze: egy vonalon folyamatosan haladva a szakasz hossza a kezdő és záró állomás indexének különbsége, iránya pedig az a végállomás, amely felé haladunk. A szakaszokat a bejárás sorrendjében írjuk ki, az átszállás miatti nulla hosszú részeket kihagyva. A gráf legfeljebb 60 csomópontos, így az időigény elhanyagolható.
*/
/*
Hint 1: || Gondolj a hálózatra gráfként: a csomópont egy (vonal, állomás) pár, két csomópont között pedig él van, ha egy vonalon egymás mellett állnak (1 megálló), vagy ha ugyanazon nevű állomáson találkoznak (átszállás, 0 megálló). ||
Hint 2: || Mivel az élek súlya csak 0 vagy 1, nem kell általános Dijkstra: egy kétvégű sorral minden csomópont legkevesebb megállós távolsága meghatározható. Minden csomópontnál jegyezd fel, honnan érkeztél, hogy vissza tudd követni az utat. ||
Hint 3: || A célállomás legjobb példányától visszafelé haladva összegyűjtheted az útvonalat. Ezt vonalanként szakaszokba fogd össze: a szakasz hossza a kezdő és a záró állomás indexének különbsége, a végállomás pedig az a szélső állomás, amely felé haladsz (növekvő index: az utolsó, csökkenő index: az első). ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Szakasz {
    int vonal, honnan, hova;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string indulo, cel;
    cin >> indulo >> cel;

    const int VONALAK = 3;
    vector<vector<string>> allomas(VONALAK);
    for (int l = 0; l < VONALAK; ++l) {
        int db;
        cin >> db;
        allomas[l].resize(db);
        for (auto &nev : allomas[l]) cin >> nev;
    }

    // Csomópont: (vonal, állomás) pár, sorszáma base[l] + i
    vector<int> base(VONALAK + 1, 0);
    for (int l = 0; l < VONALAK; ++l)
        base[l + 1] = base[l] + (int)allomas[l].size();
    int n = base[VONALAK];

    vector<int> vonalOf(n), poz(n);
    vector<string> nev(n);
    for (int l = 0; l < VONALAK; ++l)
        for (int i = 0; i < (int)allomas[l].size(); ++i) {
            int v = base[l] + i;
            vonalOf[v] = l;
            poz[v] = i;
            nev[v] = allomas[l][i];
        }

    // Élek: szomszédos megálló súlya 1, átszállás súlya 0
    vector<vector<pair<int, int>>> adj(n);
    for (int v = 0; v < n; ++v) {
        int l = vonalOf[v], i = poz[v];
        if (i > 0) adj[v].push_back({v - 1, 1});
        if (i + 1 < (int)allomas[l].size()) adj[v].push_back({v + 1, 1});
        for (int u = 0; u < n; ++u)
            if (vonalOf[u] != l && nev[u] == nev[v]) adj[v].push_back({u, 0});
    }

    // 0-1 BFS, az induló állomás összes példányából indulva
    const int INF = INT_MAX;
    vector<int> tav(n, INF), elozo(n, -1);
    deque<int> sor;
    for (int v = 0; v < n; ++v)
        if (nev[v] == indulo) {
            tav[v] = 0;
            sor.push_back(v);
        }
    while (!sor.empty()) {
        int v = sor.front();
        sor.pop_front();
        for (auto [u, w] : adj[v])
            if (tav[v] + w < tav[u]) {
                tav[u] = tav[v] + w;
                elozo[u] = v;
                if (w == 0) sor.push_front(u);
                else sor.push_back(u);
            }
    }

    // A célállomás legközelebbi példánya
    int celV = -1;
    for (int v = 0; v < n; ++v)
        if (nev[v] == cel && tav[v] < INF && (celV == -1 || tav[v] < tav[celV]))
            celV = v;
    if (celV == -1) return 0;

    // Az út visszakövetése az induló csomópontig
    vector<int> ut;
    for (int v = celV; v != -1; v = elozo[v]) ut.push_back(v);
    reverse(ut.begin(), ut.end());

    // Folytonos haladás vonalanként egy szakaszba
    vector<Szakasz> szakaszok;
    for (size_t k = 0; k + 1 < ut.size(); ++k) {
        int a = ut[k], b = ut[k + 1];
        if (vonalOf[a] != vonalOf[b]) continue;  // átszállás
        int l = vonalOf[a];
        if (!szakaszok.empty() && szakaszok.back().vonal == l && szakaszok.back().hova == poz[a])
            szakaszok.back().hova = poz[b];
        else
            szakaszok.push_back({l, poz[a], poz[b]});
    }

    for (const auto &sz : szakaszok) {
        int l = sz.vonal;
        string vegallomas = (sz.hova > sz.honnan) ? allomas[l].back() : allomas[l].front();
        cout << l + 1 << ". metrovonal " << vegallomas << " fele "
             << abs(sz.hova - sz.honnan) << " allomas\n";
    }
}
