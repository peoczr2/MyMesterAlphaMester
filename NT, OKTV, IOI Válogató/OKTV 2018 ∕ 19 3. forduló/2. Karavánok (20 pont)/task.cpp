/*
Megoldás lényege:
Az oázisokat csúcsoknak, a karavánokat irányított éleknek tekintjük. Egy oázisból akkor juttatható el az áru minden másikba, ha onnan minden csúcs elérhető. Az erősen összefüggő komponensekre bontás (Kosaraju-algoritmus) után a komponensek egy körmentes gráfot adnak. Ha ebben pontosan egy olyan komponens van, amelybe másik komponensből nem vezet él, akkor annak csúcsai a megoldások: onnan minden más csúcs elérhető, és a többi csúcsból ez a komponens nem érhető el. Ha ilyen komponens több van, egyik csúcsból sem érhető el minden, ezért a válasz -1. Az időigény O(N + M).
*/
/*
Hint 1: || Egy erősen összefüggő komponens minden csúcsa ugyanazt tudja elérni, ezért a komponensekkel érdemes dolgozni: a komponenseket egy-egy csúcsnak tekintve körmentes gráfot kapsz. ||
Hint 2: || Egy komponens csúcsairól akkor érhető el minden más csúcs, ha a komponensbe más komponensből nem vezet él. Számold meg az ilyen „bejövő él nélküli” komponenseket: pontosan egy lehet, különben a válasz -1. ||
Hint 3: || A komponensek megtalálásához használd a Kosaraju-algoritmust: az első DFS a befejezési sorrendet adja, a fordított élekből álló gráfon a sorrend fordítottjában futtatott DFS-ek pedig a komponenseket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> ki, vissza;
vector<pair<int, int>> elek;
vector<bool> latogatott;
vector<int> befejezes;
vector<int> komp;

void elso_bejaras(int u) {
    latogatott[u] = true;
    for (int v : ki[u]) {
        if (!latogatott[v]) elso_bejaras(v);
    }
    befejezes.push_back(u);
}

void masodik_bejaras(int u, int c) {
    komp[u] = c;
    for (int v : vissza[u]) {
        if (komp[v] == -1) masodik_bejaras(v, c);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    ki.assign(n + 1, {});
    vissza.assign(n + 1, {});
    elek.reserve(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        ki[a].push_back(b);
        vissza[b].push_back(a);
        elek.push_back({a, b});
    }

    latogatott.assign(n + 1, false);
    for (int u = 1; u <= n; u++) {
        if (!latogatott[u]) elso_bejaras(u);
    }

    komp.assign(n + 1, -1);
    int kc = 0;
    for (int i = int(befejezes.size()) - 1; i >= 0; i--) {
        int u = befejezes[i];
        if (komp[u] == -1) {
            masodik_bejaras(u, kc);
            kc++;
        }
    }

    // bejovo_el[c]: van-e a c komponensbe más komponensből vezető él
    vector<bool> bejovo_el(kc, false);
    for (auto [a, b] : elek) {
        if (komp[a] != komp[b]) bejovo_el[komp[b]] = true;
    }

    int forras = -1, forrasok = 0;
    for (int c = 0; c < kc; c++) {
        if (!bejovo_el[c]) {
            forras = c;
            forrasok++;
        }
    }

    if (forrasok != 1) {
        cout << -1 << "\n";
        return 0;
    }

    bool elso = true;
    for (int u = 1; u <= n; u++) {
        if (komp[u] == forras) {
            if (!elso) cout << " ";
            cout << u;
            elso = false;
        }
    }
    cout << "\n";
    return 0;
}
