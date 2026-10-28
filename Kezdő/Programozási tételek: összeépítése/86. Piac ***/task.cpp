/*
Megoldás lényege:
A kereskedőnkénti bevételt úgy kapjuk, hogy minden tételnél összeszorozzuk az egységárat az eladott mennyiséggel, és ezeket összegezzük. Az átlagosnál nagyobb bevételű kereskedőt úgy ismerjük fel, hogy a bevételét N-nel szorozva összevetjük az összes bevétellel, így nincs szükség osztásra. A termékenkénti összes eladott mennyiséget összegezzük, majd csökkenő sorrendbe rendezzük a termékeket; a K. helyen álló termék a keresett. A harmadik kérdésnél termékenként megkeressük a legmagasabb eladási árat, és egy tétel akkor felel meg, ha a kereskedő ezzel az árral szerepel; kereskedőnként megszámoljuk az ilyen tételeket, és a legtöbbet elérő (legkisebb sorszámú) kereskedőt írjuk ki. Az időigény O(N·F + M·log M), ami a korlátok mellett bőven elég.
*/
/*
Hint 1: || Az átlagos bevételhez nem kell osztani: egy kereskedő bevétele akkor átlag feletti, ha a bevételét szorozva N-nel nagyobb az összes bevételnél. ||
Hint 2: || A K. legnagyobb mennyiségű áruhoz termékenként külön-külön add össze az eladott mennyiségeket, majd rendezd a termékek sorszámait a mennyiségük szerint csökkenő sorrendbe. ||
Hint 3: || A harmadik kérdésnél először termékenként keresd meg a legmagasabb egységárat az összes kereskedő között, majd kereskedőnként számold meg, hányszor szerepel benne a saját tétele ezzel a maximális áron. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Tetel {
    int kereskedo;
    int termek;
    int ar;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<long long> bevetel(n, 0);
    vector<long long> mennyiseg(m + 1, 0);
    vector<int> maxAr(m + 1, 0);
    vector<Tetel> tetelek;

    for (int i = 0; i < n; ++i) {
        int f;
        cin >> f;
        for (int j = 0; j < f; ++j) {
            int s, ea, me;
            cin >> s >> ea >> me;
            bevetel[i] += (long long)ea * me;
            mennyiseg[s] += me;
            maxAr[s] = max(maxAr[s], ea);
            tetelek.push_back({i, s, ea});
        }
    }

    // A: az átlagosnál nagyobb bevételű kereskedők (növekvő sorrendben)
    long long osszes = accumulate(bevetel.begin(), bevetel.end(), 0LL);
    vector<int> atlagFeletti;
    for (int i = 0; i < n; ++i) {
        if (bevetel[i] * n > osszes) atlagFeletti.push_back(i + 1);
    }
    cout << atlagFeletti.size();
    for (int x : atlagFeletti) cout << ' ' << x;
    cout << '\n';

    // B: a K. legnagyobb mennyiségben fogyó áru sorszáma
    vector<int> termekek(m);
    iota(termekek.begin(), termekek.end(), 1);
    sort(termekek.begin(), termekek.end(), [&](int a, int b) {
        if (mennyiseg[a] != mennyiseg[b]) return mennyiseg[a] > mennyiseg[b];
        return a < b;
    });
    cout << termekek[k - 1] << '\n';

    // C: kereskedőnként a "legmagasabb áron árult" tételek száma
    vector<int> db(n, 0);
    for (const Tetel &t : tetelek) {
        if (t.ar == maxAr[t.termek]) ++db[t.kereskedo];
    }
    int legjobb = 0;
    for (int i = 1; i < n; ++i) {
        if (db[i] > db[legjobb]) legjobb = i;
    }
    cout << legjobb + 1 << '\n';

    return 0;
}
