/*
Megoldás lényege:
Egy járáson belül az áru ingyen eljut bármely városba, ezért a járás összes városát előre össze lehet kötni, így a járások összefüggő egységekké válnak.
A kereskedők ajánlatai ezek között az egységek között kerülnek költségbe, és az a cél, hogy az ország összefüggő legyen minimális összköltséggel: ez a minimális feszítőfa keresése.
Kruskal-algoritmussal az ajánlatokat költség szerint növekvően vesszük sorra, és azokat fogadjuk el, amelyek két még nem összekötött halmazt kötnek össze; a sorszámokat az elfogadás sorrendjében írjuk ki.
Ha a végén nem marad egyetlen összefüggő halmaz, a feladat nem oldható meg, és 0 a válasz.
Az időigény O(K log K), ami K ≤ 1 000 000 esetén belefér az időkorlátba.
*/
/*
Hint 1: || Az azonos járásban lévő városokat ingyen össze lehet kötni, így utána csak az ajánlatok közül kell minimális költségű összekötő halmazt választani. ||
Hint 2: || Rendezd az ajánlatokat költség szerint, és unió-keresés adatszerkezettel fogadd el azokat, amelyek két még nem összekötött halmazt kötnek össze; a végén ellenőrizd, hogy egyetlen halmaz maradt-e. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> szulo;

int keres(int x) {
    while (szulo[x] != x) {
        szulo[x] = szulo[szulo[x]];
        x = szulo[x];
    }
    return x;
}

bool egyesit(int a, int b) {
    int ra = keres(a), rb = keres(b);
    if (ra == rb) return false;
    szulo[ra] = rb;
    return true;
}

struct Ajanlat {
    int u, v, w, sorszam;
};

bool van_szam(const string& s) {
    return s.find_first_of("0123456789") != string::npos;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, k;
    cin >> m >> n >> k;

    szulo.resize(n + 1);
    iota(szulo.begin(), szulo.end(), 0);

    // A járások sorai: egy-egy sor egy járás településeinek sorszámait tartalmazza
    int komponens = n;
    string sor;
    getline(cin, sor);  // az első sor maradéka
    for (int j = 0; j < m; ++j) {
        do {
            if (!getline(cin, sor)) break;
        } while (!van_szam(sor));
        istringstream is(sor);
        int x, elso = -1;
        while (is >> x) {
            if (elso == -1) elso = x;
            else if (egyesit(elso, x)) --komponens;
        }
    }

    vector<Ajanlat> ajanlatok(k);
    for (int i = 0; i < k; ++i) {
        cin >> ajanlatok[i].u >> ajanlatok[i].v >> ajanlatok[i].w;
        ajanlatok[i].sorszam = i + 1;
    }

    sort(ajanlatok.begin(), ajanlatok.end(),
         [](const Ajanlat& x, const Ajanlat& y) { return x.w < y.w; });

    long long koltseg = 0;
    vector<int> elfogadott;
    for (const Ajanlat& a : ajanlatok) {
        if (komponens == 1) break;
        if (egyesit(a.u, a.v)) {
            --komponens;
            koltseg += a.w;
            elfogadott.push_back(a.sorszam);
        }
    }

    if (komponens != 1) {
        cout << 0 << '\n';
        return 0;
    }

    cout << koltseg << '\n';
    for (size_t i = 0; i < elfogadott.size(); ++i) {
        if (i) cout << ' ';
        cout << elfogadott[i];
    }
    cout << '\n';
    return 0;
}
