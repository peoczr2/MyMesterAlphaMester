/*
Megoldás lényege:
Minden kérdésnél végigmegyünk az összes személyen, és kiválasztjuk azokat, akik megfelelnek a kategória (SZAKACS, CUKRASZ vagy BARMILYEN) és a szakképzettségi szint relációjának (<, >, =, <=, >=) együttes feltételének. A megfelelők közül a MIN kérdésnél a legfiatalabb, a MAX kérdésnél a legidősebb személy kell; ha ebből több is van ugyanolyan életkorral, az ábécé szerint első nevet adjuk meg. Ha nincs megfelelő személy, a válasz NINCS. A korlátok (legfeljebb 1000 személy, 500 kérdés) miatt az egyszerű végigjárás O((N+M)·K) időben gyorsan lefut.
*/
/*
Hint 1: || A korlátok (legfeljebb 1000 személy és 500 kérdés) megengedik, hogy minden kérdésnél végignézd az összes személyt. Előbb a kategóriát és a szintet ellenőrizd, és csak a megfelelő személyekből válassz. ||
Hint 2: || A MIN és a MAX kérdésnél a kiválasztott életkor a megfelelő személyek minimuma vagy maximuma. Azonos életkor esetén a név szerinti kisebbet tartsd meg, így a végén az ábécé szerint első név marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Person {
    int category;  // 0: szakács, 1: cukrász
    int level;     // szakképzettségi szint (1 a legjobb)
    int age;
    string name;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<Person> people(n + m);
    for (int i = 0; i < n + m; ++i) {
        Person& p = people[i];
        p.category = (i < n) ? 0 : 1;
        cin >> p.level >> p.age;
        // Az életkor utáni szóköz elválasztó, a név ez utáni rész (szóközöket is tartalmazhat).
        getline(cin, p.name);
        if (!p.name.empty() && p.name[0] == ' ') p.name.erase(0, 1);
        if (!p.name.empty() && p.name.back() == '\r') p.name.pop_back();
    }

    for (int q = 0; q < k; ++q) {
        string s;
        cin >> s;

        // Alak: xxxx:yyyy:zzzz
        size_t c1 = s.find(':');
        size_t c2 = s.find(':', c1 + 1);
        string cat = s.substr(0, c1);
        string rel = s.substr(c1 + 1, c2 - c1 - 1);
        string which = s.substr(c2 + 1);

        // A reláció jele és a szám (a szám az első számjegynél kezdődik).
        size_t d = rel.find_first_of("0123456789");
        string op = rel.substr(0, d);
        int target = stoi(rel.substr(d));

        auto levelOk = [&](int lv) {
            if (op == "<") return lv < target;
            if (op == ">") return lv > target;
            if (op == "=") return lv == target;
            if (op == "<=") return lv <= target;
            return lv >= target;  // ">="
        };

        bool wantMin = (which == "MIN");
        bool found = false;
        int bestAge = 0;
        string bestName;
        for (const Person& p : people) {
            bool catOk = (cat == "BARMILYEN") || (cat == "SZAKACS" && p.category == 0) ||
                         (cat == "CUKRASZ" && p.category == 1);
            if (!catOk || !levelOk(p.level)) continue;

            bool better;
            if (!found) {
                better = true;
            } else if (p.age != bestAge) {
                better = wantMin ? (p.age < bestAge) : (p.age > bestAge);
            } else {
                better = (p.name < bestName);
            }
            if (better) {
                found = true;
                bestAge = p.age;
                bestName = p.name;
            }
        }

        cout << (found ? bestName : string("NINCS")) << '\n';
    }
    return 0;
}
