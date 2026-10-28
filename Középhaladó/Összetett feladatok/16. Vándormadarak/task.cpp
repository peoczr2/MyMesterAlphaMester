/*
Megoldás lényege:
Az 1. részfeladatban minden megfigyelés-párra megnézzük, van-e ugyanazon a napon, ugyanazon a helyen más madárfajt megfigyelő rekord; az adatsorozat sorrendjében az első ilyen megfigyelés helye a válasz, különben „-1 -1”. A 2. részfeladatban a nyári (151..242) napokra eső, a központtól T-nél közelebbi megfigyeléseket gyűjtjük, a sorszámukkal együtt.
A 3. részfeladatban a megfigyelési napok közül próbáljuk minden kezdőnapra a [s, s + H - 1] időszak megfigyelésszámát, és az első legnagyobbat tartjuk meg. A 4. részfeladatban a különböző helyek párjai közül a legnagyobb távolságút keressük a megadott képlettel, az 5. részfeladatban pedig a különböző madárfajokat összegyűjtjük, rendezve.
Az időigény O(N^2) az 1. részfeladatnál és O(N^2) a többinél is, N <= 100 esetén villámgyors.
*/
/*
Hint 1: || Az 1. részfeladatban két megfigyelés „egy időben” akkor van, ha ugyanaz a nap és ugyanaz a hely; ha ezek madárfaja eltér, a hely a válasz. Az adatsorozat sorrendjében az első ilyen helyet kell kiírni. ||
Hint 2: || A 3. részfeladatban csak a megfigyelések napjait kezdőnapnak tekintsd (a napok növekvő sorrendjében), és minden kezdőnapra számold meg, hány megfigyelés esik a [s, s + H - 1] napokra; a legnagyobb számnál az első, legkisebb kezdőnapot tartsd meg. ||
Hint 3: || A 4. részfeladatban a különböző helyek párjait próbáld végig a megadott távolságképlettel, a legnagyobb távolságú párt őrizd meg (a helyek sorrendje az első előfordulásuk szerinti legyen); a 5. részfeladatban a madárfajokat egy halmazba gyűjtsd, a halmaz mérete a darabszám, és a halmaz bejárása adja a rendezett sorozatot. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Obs {
    int day;
    int no;
    int ea;
    int species;
};

int gpsDist(int no1, int ea1, int no2, int ea2) {
    int dn = abs(no1 - no2);
    int de = abs(ea1 - ea2);
    return dn + min(de, 360 - de);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t, h;
    int kno, kea;
    cin >> n >> t >> h >> kno >> kea;

    vector<Obs> ob(n);
    for (auto &x : ob) cin >> x.day >> x.no >> x.ea >> x.species;

    // 1. részfeladat: az első hely, ahol egy időben többféle madarat figyeltek meg
    int ansNo = -1, ansEa = -1;
    bool found = false;
    for (int i = 0; i < n && !found; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j != i && ob[j].day == ob[i].day && ob[j].no == ob[i].no && ob[j].ea == ob[i].ea &&
                ob[j].species != ob[i].species) {
                found = true;
                ansNo = ob[i].no;
                ansEa = ob[i].ea;
                break;
            }
        }
    }

    // 2. részfeladat: nyári (151..242) és a központtól T-nél közelebbi megfigyelések sorszámai
    vector<int> near;
    for (int i = 0; i < n; ++i) {
        if (ob[i].day >= 151 && ob[i].day <= 242 &&
            gpsDist(ob[i].no, ob[i].ea, kno, kea) < t) {
            near.push_back(i + 1);
        }
    }

    // 3. részfeladat: a legtöbb megfigyelést tartalmazó H napos időszak legkisebb kezdőnapja
    vector<int> days;
    for (const auto &x : ob) days.push_back(x.day);
    sort(days.begin(), days.end());
    days.erase(unique(days.begin(), days.end()), days.end());

    int bestCnt = -1, bestStart = days[0];
    for (int s : days) {
        int c = 0;
        for (const auto &x : ob) {
            if (x.day >= s && x.day <= s + h - 1) c++;
        }
        if (c > bestCnt) {
            bestCnt = c;
            bestStart = s;
        }
    }

    // 4. részfeladat: a két legtávolabbi különböző hely (első előfordulás sorrendjében)
    vector<pair<int, int>> places;
    set<pair<int, int>> placeSet;
    for (const auto &x : ob) {
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

    // 5. részfeladat: a különböző madárfajok száma és sorszámai növekvően
    set<int> species;
    for (const auto &x : ob) species.insert(x.species);

    cout << "#\n";
    if (found) {
        cout << ansNo << ' ' << ansEa << "\n";
    } else {
        cout << "-1 -1\n";
    }
    cout << "#\n";
    cout << near.size();
    for (int idx : near) cout << ' ' << idx;
    cout << "\n";
    cout << "#\n" << bestStart << "\n";
    cout << "#\n";
    cout << A.first << ' ' << A.second << ' ' << B.first << ' ' << B.second << "\n";
    cout << "#\n";
    cout << species.size();
    for (int s : species) cout << ' ' << s;
    cout << "\n";

    return 0;
}
