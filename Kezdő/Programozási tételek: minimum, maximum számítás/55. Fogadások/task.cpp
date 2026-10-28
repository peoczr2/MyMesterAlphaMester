/*
Megoldás lényege:
Egy fogadás két ember pénzét változtatja meg: a nyerőé eggyel nő, a vesztesé eggyel csökken. Az egész
listát minden fogadás után bejárni túl lassú lenne (N = 10 000, M = 100 000), ezért az embereket egy
rendezett halmazban tartjuk (kulcs: -pénz, az utolsó változás ideje, sorszám). Így a halmaz első eleme
adja a legtöbb pénzt, és azt az embert, aki ezt legkorábban érte el. Külön tömbben számoljuk, hányan
vannak az egyes pénzösszegeken, így a maximumon lévők száma azonnal kiolvasható. Minden fogadás
O(log N) műveletet igényel, az összes fogadás O(M log N).
*/
/*
Hint 1: || Egy fogadás csak két ember pénzét változtatja: a nyertesét eggyel növeli, a vesztesét eggyel csökkenti. Így egy lépés után a legnagyobb pénzösszeg legfeljebb eggyel nőhet, és a teljes lista újrabejárása felesleges. ||
Hint 2: || Minden emberhez tárold a pénzét és azt az időpontot (a fogadás sorszámát), amikor legutóbb változott. Egy rendezett halmazban a kulcs legyen (-pénz, idő, sorszám): a halmaz első eleme a maximális pénzt és egy ilyen embert ad. ||
Hint 3: || Egy külön tömbben vezesd, hány embernek van az egyes pénzösszegekből, mert így a maximumon lévők száma egy lekérdezéssel megkapható. Fogadásonként a két érintett ember régi bejegyzését töröld a halmazból és az újat szúrd be. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> penz(n + 1, 0);       // penz[i]: az i. ember pénze (eltolás nélkül)
    vector<int> ido(n + 1, 0);        // ido[i]: mikor változott utoljára a pénze
    vector<int> db(2 * m + 1, 0);     // db[p + m]: hányan vannak p pénzzel
    db[m] = n;

    // rendezés: legtöbb pénz elöl, azonos pénznél a korábban ezt elérő, majd a kisebb sorszám
    set<tuple<int, int, int>> sor;    // (-pénz, idő, sorszám)
    for (int i = 1; i <= n; i++) sor.insert({0, 0, i});

    auto modosit = [&](int p, int delta, int t) {
        sor.erase({-penz[p], ido[p], p});
        db[penz[p] + m]--;
        penz[p] += delta;
        db[penz[p] + m]++;
        ido[p] = t;
        sor.insert({-penz[p], ido[p], p});
    };

    for (int t = 1; t <= m; t++) {
        int a, b;                     // A nyerte B-vel szemben
        cin >> a >> b;
        modosit(a, +1, t);
        modosit(b, -1, t);

        auto [negPenz, idoElso, sorszam] = *sor.begin();
        int legtobb = -negPenz;
        cout << db[legtobb + m] << ' ' << sorszam << '\n';
    }
    return 0;
}
