/*
Megoldási ötlet:
Ha egy körben a mostani létszám `n`, és Reni néni a listából a `k` számot választja,
akkor pontosan `floor(n / k)` darab `k` fős csoportot tud létrehozni. A bent maradó gyerekek száma

    k * floor(n / k)

lesz, vagyis a következő állapot a legnagyobb `n`-nél nem nagyobb `k`-többszörös. Ha `k > n`, akkor
egy csoport sem jön létre, tehát mindenki kiesik, azaz közvetlenül `0` lesz a létszám.

Sok lekérdezés van, ezért nem külön-külön keresünk utat, hanem visszafelé építjük fel a gráfot.
Ha egy `m` létszám elérhető, és `m` osztható `k`-val, akkor pontosan azokból az `n` állapotokból
lehet egy lépésben `m`-be jutni ezzel a `k` választással, amelyekre

    m < n < m + k

teljesül. Valóban, ezekre `floor(n / k) = m / k`, tehát a következő létszám `m` lesz.
Ezért a fordított gráfban egy `m` csúcsból minden olyan `k` mellett, amely osztja `m`-et,
elérjük az `(m, m + k)` intervallum összes egész számát.

Így szélességi bejárást futtatunk `0`-ból. A gond az, hogy ugyanazokra az intervallumokra sokszor
rákérdezünk. Ezt egy "következő még nem látogatott" DSU-val gyorsítjuk: ha egy teljes intervallumot
fel akarunk venni a BFS-be, akkor csak a még nem feldolgozott elemeket járjuk be, és egy elemet
legfeljebb egyszer veszünk fel. Azt is előre kiszitáljuk, hogy mely listabeli `k` értékek osztják
az egyes `m` számokat.

Az algoritmus összesen `O(X * sum(1 / k) + X * alpha(X))` nagyságrendű, ahol `X` a legnagyobb
lekérdezett csoportlétszám, és bőven elég a megadott korlátokra.
*/
/*
Hint 1: || Egy `k` választás után a bent maradók száma nem tetszőleges, hanem pontosan `k * floor(n / k)`. ||
Hint 2: || Sok lekérdezésnél érdemes visszafelé gondolkodni: mely `n` értékekből lehet egy lépésben egy adott `m` állapotba jutni? ||
Hint 3: || Ha `m` osztható `k`-val, akkor a fordított irányú elérhető tartomány egyszerű intervallum: `m + 1, ..., m + k - 1`. ||
Hint 4: || Az intervallumok bejárását DSU-val lehet gyorsítani úgy, hogy minden számot csak egyszer látogatsz meg. ||
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

namespace {

struct DisjointNext {
    vector<int> parent;

    explicit DisjointNext(int size) : parent(size + 1) {
        for (int i = 0; i <= size; ++i) {
            parent[i] = i;
        }
    }

    int find(int value) {
        if (parent[value] == value) {
            return value;
        }
        parent[value] = find(parent[value]);
        return parent[value];
    }

    void erase(int value) {
        parent[value] = find(value + 1);
    }
};

}  // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m = 0;
    int q = 0;
    cin >> m >> q;

    vector<int> lehetseges(m);
    for (int i = 0; i < m; ++i) {
        cin >> lehetseges[i];
    }

    vector<int> kerdesek(q);
    int maximum = 0;
    for (int i = 0; i < q; ++i) {
        cin >> kerdesek[i];
        maximum = max(maximum, kerdesek[i]);
    }

    sort(lehetseges.begin(), lehetseges.end());
    lehetseges.erase(unique(lehetseges.begin(), lehetseges.end()), lehetseges.end());
    lehetseges.erase(remove(lehetseges.begin(), lehetseges.end(), 1), lehetseges.end());

    vector<vector<int>> osztoi(maximum + 1);
    for (int k : lehetseges) {
        if (k > maximum) {
            continue;
        }
        for (int tobbszoros = k; tobbszoros <= maximum; tobbszoros += k) {
            osztoi[tobbszoros].push_back(k);
        }
    }

    vector<int> tav(maximum + 1, -1);
    DisjointNext kovetkezo(maximum + 1);
    queue<int> bfs;

    auto intervallum_bejar = [&](int bal, int jobb, int uj_tav) {
        if (bal > jobb) {
            return;
        }
        int aktualis = kovetkezo.find(bal);
        while (aktualis <= jobb) {
            tav[aktualis] = uj_tav;
            bfs.push(aktualis);
            kovetkezo.erase(aktualis);
            aktualis = kovetkezo.find(aktualis);
        }
    };

    tav[0] = 0;
    kovetkezo.erase(0);

    for (int k : lehetseges) {
        if (k <= 1) {
            continue;
        }
        intervallum_bejar(1, min(maximum, k - 1), 1);
    }

    while (!bfs.empty()) {
        int most = bfs.front();
        bfs.pop();

        int uj_tav = tav[most] + 1;
        for (int k : osztoi[most]) {
            int bal = most + 1;
            int jobb = min(maximum, most + k - 1);
            intervallum_bejar(bal, jobb, uj_tav);
        }
    }

    for (int n : kerdesek) {
        if (tav[n] < 0) {
            cout << 0 << '\n';
        } else {
            cout << tav[n] << '\n';
        }
    }

    return 0;
}