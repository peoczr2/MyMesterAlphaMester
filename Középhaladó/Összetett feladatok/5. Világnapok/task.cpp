/*
Megoldás lényege:
Az eseményeket a bemenet sorrendjében tároljuk: hónap, nap, évszám és a teljes szöveges sor. Az 1. részfeladatban a lekérdezett hónap-nap párra illeszkedő események teljes sorát írjuk ki. A 2. részfeladatban az első 13-dikára eső esemény sorszámát keressük, 0-t hagyva, ha nincs ilyen. A 3. részfeladatban hónaponként a különböző napok számát halmazzal számoljuk, mert egy napon több esemény is lehet. A 4. részfeladatban az események darabszámát számoljuk hónaponként, és szigorú összehasonlítással keressük a maximumot, így döntetlennél a korábbi hónap marad. Az 5. részfeladatban a legkisebb évszámú esemény első előfordulását választjuk. Az összidő O(E log 31), ami E <= 1000 mellett elhanyagolható.
*/
/*
Hint 1: || Az évszám az esemény sorának első száma, a teljes sort pedig változatlanul kell kiírni. A szöveg szóközöket is tartalmazhat, ezért getline-nal olvasd. ||
Hint 2: || Hónaponként két különböző számot kell tudni: a különböző napok számát (set vagy jelölő tömb) és az események összes számát (sima számláló). Ezek eltérhetnek, mert egy napon több esemény is lehet. ||
Hint 3: || A hónapneveket fix tömbből indexeld, a maximumkeresésnél csak szigorú > összehasonlítást használj. Az 5. részfeladatban akkor cserélj jelöltet, ha az új évszám szigorúan kisebb. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Event {
    int month, day, year;
    string text;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int e;
    cin >> e;
    string line;
    getline(cin, line);

    vector<Event> ev(e);
    for (int i = 0; i < e; ++i) {
        cin >> ev[i].month >> ev[i].day;
        getline(cin, line);
        getline(cin, ev[i].text);
        while (!ev[i].text.empty() && ev[i].text.back() == '\r') ev[i].text.pop_back();
        istringstream ss(ev[i].text);
        ss >> ev[i].year;
    }

    int qm, qd;
    cin >> qm >> qd;

    // 1. részfeladat: a megadott dátumhoz tartozó események
    cout << "#\n";
    for (const auto& x : ev)
        if (x.month == qm && x.day == qd) cout << x.text << "\n";

    // 2. részfeladat: az első 13-dikára eső esemény sorszáma (0, ha nincs)
    int first13 = 0;
    for (int i = 0; i < e; ++i)
        if (ev[i].day == 13) {
            first13 = i + 1;
            break;
        }
    cout << "#\n" << first13 << "\n";

    // 3. részfeladat: hónaponként a különböző napok száma, amelyeken van esemény
    vector<set<int>> days(13);
    for (const auto& x : ev) days[x.month].insert(x.day);
    cout << "#\n";
    for (int m = 1; m <= 12; ++m) cout << days[m].size() << (m < 12 ? " " : "\n");

    // 4. részfeladat: a legtöbb eseményt tartalmazó hónap neve
    vector<int> cnt(13, 0);
    for (const auto& x : ev) ++cnt[x.month];
    int best = 1;
    for (int m = 2; m <= 12; ++m)
        if (cnt[m] > cnt[best]) best = m;
    static const char* names[13] = {"", "JANUAR", "FEBRUAR", "MARCIUS", "APRILIS", "MAJUS", "JUNIUS",
                                    "JULIUS", "AUGUSZTUS", "SZEPTEMBER", "OKTOBER", "NOVEMBER", "DECEMBER"};
    cout << "#\n" << names[best] << "\n";

    // 5. részfeladat: a legkisebb évszámú esemény leírása
    int youngest = 0;
    for (int i = 1; i < e; ++i)
        if (ev[i].year < ev[youngest].year) youngest = i;
    cout << "#\n" << ev[youngest].text << "\n";

    return 0;
}
