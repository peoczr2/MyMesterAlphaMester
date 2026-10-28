/*
Megoldás lényege:
Az 1. részfeladatban azt a helyet keressük, amelyet az utazó legalább kétszer is meglátogatott: ha egy hely második előfordulása a bemenetben a legkorábbi, az a válasz; ha nincs ilyen, „-1 -1” a kimenet. A helyeket a GPS-koordinátájuk (No, Ea) azonosítja, a számlálást egy map-pel végezzük.
A 2. részfeladatban minden lehetséges kezdőnapra (0..1000) megszámoljuk, hány esemény esik a [kezdőnap, kezdőnap + H - 1] időszakba, és az első, legnagyobb értékhez tartozó kezdőnapot írjuk ki; a 1000 kezdőnap és N <= 100 esemény miatt ez gyorsan lefut.
A 3. részfeladatban a különböző helyek közül minden párra kiszámoljuk a feladatban megadott távolságot, és a legnagyobbat választjuk; a 4. részfeladatban az eseményszavakat az első előfordulásuk sorrendjében, egyszer írjuk ki.
Az időigény O(1000 * N + P^2), ahol P a különböző helyek száma, így N <= 100 esetén villámgyors.
*/
/*
Hint 1: || Egy hely akkor „visszatérés”, ha ugyanazokkal a koordinátákkal legalább kétszer szerepel a bemenetben; ezt egy map<pair<int,int>, int> alkalmas számlálóval gyorsan lehet követni. ||
Hint 2: || A 2. részfeladatban a H hosszú időszak kezdőnapját próbáld ki minden 0..1000 közötti napra: az adott [s, s + H - 1] intervallumba eső események számát egyszerű bejárással megkapod, és a legnagyobb számú esemény első kezdőnapját tartod meg. ||
Hint 3: || A 3. részfeladatban a különböző helyek összes párját végigpróbálod, a távolság képletét (|No1-No2| + min(|Ea1-Ea2|, 360-|Ea1-Ea2|)) minden párra kiszámolod, és a legnagyobb értékű párt őrzöd; ha csak egy hely van, azt kell kétszer kiírni. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Event {
    int day;
    int no;
    int ea;
    string word;
};

int gpsDist(int no1, int ea1, int no2, int ea2) {
    int dn = abs(no1 - no2);
    int de = abs(ea1 - ea2);
    return dn + min(de, 360 - de);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;

    vector<Event> ev(n);
    for (auto &x : ev) cin >> x.day >> x.no >> x.ea >> x.word;

    // 1. részfeladat: a legkorábbi "visszatérés" (egy hely második előfordulása)
    map<pair<int, int>, int> visits;
    int ansNo = -1, ansEa = -1;
    bool found = false;
    for (const auto &x : ev) {
        int c = ++visits[{x.no, x.ea}];
        if (c == 2 && !found) {
            found = true;
            ansNo = x.no;
            ansEa = x.ea;
        }
    }

    // 2. részfeladat: a legtöbb eseményt tartalmazó H napos időszak legkisebb kezdőnapja
    int bestCnt = -1, bestStart = 0;
    for (int s = 0; s <= 1000; ++s) {
        int c = 0;
        for (const auto &x : ev) {
            if (x.day >= s && x.day <= s + h - 1) c++;
        }
        if (c > bestCnt) {
            bestCnt = c;
            bestStart = s;
        }
    }

    // 3. részfeladat: a két legtávolabbi különböző hely (első előfordulás sorrendjében)
    vector<pair<int, int>> places;
    set<pair<int, int>> placeSet;
    for (const auto &x : ev) {
        pair<int, int> p{x.no, x.ea};
        if (!placeSet.count(p)) {
            placeSet.insert(p);
            places.push_back(p);
        }
    }
    pair<int, int> A = places[0], B = places[0];
    if (places.size() > 1) {
        int bestD = -1;
        for (size_t i = 0; i < places.size(); ++i) {
            for (size_t j = i + 1; j < places.size(); ++j) {
                int d = gpsDist(places[i].first, places[i].second, places[j].first, places[j].second);
                if (d > bestD) {
                    bestD = d;
                    A = places[i];
                    B = places[j];
                }
            }
        }
    }

    // 4. részfeladat: a különböző események szavai első előfordulás sorrendjében
    vector<string> words;
    set<string> wordSet;
    for (const auto &x : ev) {
        if (!wordSet.count(x.word)) {
            wordSet.insert(x.word);
            words.push_back(x.word);
        }
    }

    cout << "#\n";
    if (found) {
        cout << ansNo << ' ' << ansEa << "\n";
    } else {
        cout << "-1 -1\n";
    }
    cout << "#\n" << bestStart << "\n";
    cout << "#\n";
    cout << A.first << ' ' << A.second << "\n";
    cout << B.first << ' ' << B.second << "\n";
    cout << "#\n" << words.size() << "\n";
    for (const auto &w : words) cout << w << "\n";

    return 0;
}
