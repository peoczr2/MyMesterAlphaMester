/*
Megoldás lényege:
Az autókat a rendszámuk alapján az első előfordulásuk sorrendjében nyilvántartjuk, és minden kölcsönzésnél növeljük az autó kölcsönzésszámát és a kölcsönzött napok számát (U - E + 1). Az 1. és 2. részfeladat ezekből az összegekből közvetlenül adódik: az összes napot az autók napjainak összege adja, a legtöbb napra kölcsönzött autó pedig a napok összegének maximuma.
A hónap napjai (1..30) kevesen vannak, ezért minden autóhoz egy 31 elemű logikai tömböt vezetünk, ami jelzi, mely napokon volt kölcsönben. Ebből a d. napon kölcsönben lévő autók száma (cnt[d]) összegzéssel kapható meg, a 3. részfeladatban pedig a legnagyobb cnt[d] első napja a válasz.
A 4. részfeladatban a napokat 2-től 30-ig végigjárjuk, és azokat írjuk ki, ahol cnt[d] szigorúan nagyobb az addigi maximumnál; az 1. nap nem kerülhet a listába, mert előtte nincs más nap.
Az időigény O(N * 30) plusz a rendszám-kereséshez szükséges O(N log N), így N <= 1000 esetén ezredmásodpercek alatt lefut.
*/
/*
Hint 1: || Nem kell minden kölcsönzést külön vizsgálni a napokra: a napok száma kicsi (1..30), ezért elég a napokat egy tömbben nyilvántartani, és naponként összeszámolni, hány autó volt kölcsönben. ||
Hint 2: || Minden autóhoz tarts nyilván egy 31 elemű logikai tömböt, és a kölcsönzés [E, U] napjait állítsd igazra; így egy autó egy napon is csak egyszer számít be. A cnt[d] érték az igaz értékek összege a d. napon az összes autóra. ||
Hint 3: || A 4. részfeladatnál futtasd végig a napokat 2-től 30-ig, és tartsd nyilván az eddigi legnagyobb cnt értéket (kezdetben cnt[1]): ha az aktuális cnt[d] nagyobb, a d-t írd ki, és frissítsd a maximumot. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> plates;          // az autók rendszáma, első előfordulás sorrendjében
    map<string, int> id;            // rendszám -> sorszám a plates-ben
    vector<int> rentals;            // hányszor kölcsönözték az adott autót
    vector<int> days;               // az autó kölcsönzött napjainak összege
    vector<array<bool, 31>> busy;   // busy[a][d]: az a. autó kölcsönben volt-e a d. napon

    for (int i = 0; i < n; ++i) {
        string plate;
        int e, u;
        cin >> plate >> e >> u;

        int a;
        auto it = id.find(plate);
        if (it == id.end()) {
            a = (int)plates.size();
            id[plate] = a;
            plates.push_back(plate);
            rentals.push_back(0);
            days.push_back(0);
            busy.push_back({});
        } else {
            a = it->second;
        }

        rentals[a]++;
        days[a] += u - e + 1;
        for (int d = e; d <= u; ++d) busy[a][d] = true;
    }

    // 1. részfeladat: az összes kölcsönzött nap
    long long total = 0;
    for (int a = 0; a < (int)plates.size(); ++a) total += days[a];

    // 2. részfeladat: a legtöbb napra kölcsönzött autó (döntetlennél az első)
    int bestCar = 0;
    for (int a = 1; a < (int)plates.size(); ++a) {
        if (days[a] > days[bestCar]) bestCar = a;
    }

    // naponkénti kölcsönben lévő autók száma
    vector<int> cnt(31, 0);
    for (int a = 0; a < (int)plates.size(); ++a) {
        for (int d = 1; d <= 30; ++d) {
            if (busy[a][d]) cnt[d]++;
        }
    }

    // 3. részfeladat: a legtöbb autó kölcsönben lévő napja (döntetlennél az első)
    int bestDay = 1;
    for (int d = 2; d <= 30; ++d) {
        if (cnt[d] > cnt[bestDay]) bestDay = d;
    }

    // 4. részfeladat: azok a napok, amikor több autó volt kölcsönben, mint előtte bármikor
    vector<int> records;
    int mx = cnt[1];
    for (int d = 2; d <= 30; ++d) {
        if (cnt[d] > mx) {
            records.push_back(d);
            mx = cnt[d];
        }
    }

    // 5. részfeladat: autónként a kölcsönzések száma és a kölcsönzött napok száma
    cout << "#\n" << total << "\n";
    cout << "#\n" << plates[bestCar] << "\n";
    cout << "#\n" << bestDay << "\n";
    cout << "#\n";
    if (records.empty()) {
        cout << 0 << "\n";
    } else {
        for (size_t i = 0; i < records.size(); ++i) {
            if (i) cout << ' ';
            cout << records[i];
        }
        cout << "\n";
    }
    cout << "#\n";
    for (int a = 0; a < (int)plates.size(); ++a) {
        cout << plates[a] << ' ' << rentals[a] << ' ' << days[a] << "\n";
    }

    return 0;
}
