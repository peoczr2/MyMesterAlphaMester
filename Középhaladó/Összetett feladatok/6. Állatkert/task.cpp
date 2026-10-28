/*
Megoldás lényege:
A K rekordot egy N x M-es táblázatba írjuk: cnt[állatkert][fajta] az ott található darabszám. Az 1. részfeladatban az állatkertek sorösszegeinek maximumát keressük, döntetlennél a kisebb sorszám marad. A 2. részfeladatban fajtánként megszámoljuk, hány állatkertben van belőle legalább egy, és a valahol előforduló fajták közül a minimumhoz tartozókat írjuk ki. A 3. részfeladatban azokat az állatkerteket számoljuk, ahol minden jelen lévő fajtából legalább két állat van. A 4. részfeladatban a párokat sorszám szerint növekvő sorrendben vizsgáljuk, és az első olyan párt írjuk ki, amelynek nincs közös fajtája; ha nincs ilyen, -1 a válasz. Az 5. részfeladatban egy állatkertet akkor számolunk, ha minden általa tartott fajtából többet tart, mint bármely más állatkert. Az összidő O(N^2 M), ami N, M <= 100 mellett bőven belefér.
*/
/*
Hint 1: || Az állatkert-fajta darabszámokat írd egy N x M-es táblázatba: a bemenet minden sora egy cella, így az összes kérdés egyszerű ciklusokkal megválaszolható. ||
Hint 2: || A 4. részfeladatnál két állatkertnek akkor nincs közös fajtája, ha a táblázatuk soraiban nincs olyan oszlop, ahol mindkettő pozitív. A párokat sorszámuk szerint növekvő sorrendben járd be, és az első megfelelőnél állj meg. ||
Hint 3: || Az 5. részfeladatban minden fajtára külön hasonlítsd össze az állatkert darabszámát a többi állatkertével, és csak akkor szigorú a feltétel, ha minden fajtára teljesül. Az állatok nélküli állatkertekre a feltétel üresen teljesül, ezt a ciklusoknál tartsd szem előtt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> cnt(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < k; ++i) {
        int z, a, d;
        cin >> z >> a >> d;
        cnt[z][a] += d;
    }

    // 1. részfeladat: a legtöbb állatot tartó állatkert
    vector<int> total(n + 1, 0);
    for (int z = 1; z <= n; ++z)
        for (int a = 1; a <= m; ++a) total[z] += cnt[z][a];
    int mostZoo = 1;
    for (int z = 2; z <= n; ++z)
        if (total[z] > total[mostZoo]) mostZoo = z;
    cout << "#\n" << mostZoo << "\n";

    // 2. részfeladat: a legkevesebb állatkertben látható fajták
    vector<int> where(m + 1, 0);
    for (int a = 1; a <= m; ++a)
        for (int z = 1; z <= n; ++z)
            if (cnt[z][a] > 0) ++where[a];
    int minWhere = INT_MAX;
    for (int a = 1; a <= m; ++a)
        if (where[a] > 0) minWhere = min(minWhere, where[a]);
    vector<int> rare;
    for (int a = 1; a <= m; ++a)
        if (where[a] == minWhere) rare.push_back(a);
    cout << "#\n" << minWhere << "\n";
    for (size_t i = 0; i < rare.size(); ++i) cout << rare[i] << (i + 1 < rare.size() ? " " : "\n");

    // 3. részfeladat: azok az állatkertek, ahol minden fajtából legalább egy pár van
    int pairZoos = 0;
    for (int z = 1; z <= n; ++z) {
        bool ok = true;
        for (int a = 1; a <= m; ++a)
            if (cnt[z][a] > 0 && cnt[z][a] < 2) ok = false;
        if (ok) ++pairZoos;
    }
    cout << "#\n" << pairZoos << "\n";

    // 4. részfeladat: első olyan állatkertpár, amelyekben nincs azonos fajta
    int ra = -1, rb = -1;
    for (int x = 1; x <= n && ra < 0; ++x)
        for (int y = x + 1; y <= n && ra < 0; ++y) {
            bool disjoint = true;
            for (int a = 1; a <= m && disjoint; ++a)
                if (cnt[x][a] > 0 && cnt[y][a] > 0) disjoint = false;
            if (disjoint) {
                ra = x;
                rb = y;
            }
        }
    cout << "#\n";
    if (ra < 0)
        cout << -1 << "\n";
    else
        cout << ra << " " << rb << "\n";

    // 5. részfeladat: azok az állatkertek, amelyek minden fajtájukból többet tartanak, mint a többiek
    vector<int> best;
    for (int z = 1; z <= n; ++z) {
        bool ok = true;
        for (int a = 1; a <= m && ok; ++a) {
            if (cnt[z][a] == 0) continue;
            for (int y = 1; y <= n; ++y)
                if (y != z && cnt[y][a] >= cnt[z][a]) {
                    ok = false;
                    break;
                }
        }
        if (ok) best.push_back(z);
    }
    cout << "#\n" << best.size() << "\n";
    for (size_t i = 0; i < best.size(); ++i) cout << best[i] << (i + 1 < best.size() ? " " : "\n");

    return 0;
}
