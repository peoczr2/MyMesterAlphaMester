/*
Megoldás lényege:
A két vágányt egy-egy (célállomás, kocsiszám) párral nyilvántartjuk, az üres vágány kocsiszáma 0.
Minden érkező kocsinál előbb azt nézzük, van-e olyan nem tele vágány, amely ugyanarra a célállomásra gyűjt;
ha igen, a kocsi oda kerül. Ha nincs, és van üres vágány, a kocsi arra kerül. Csak akkor kell szerelvényt
indítani, ha a kocsi sehova nem fér el: ekkor a két szerelvény közül a hosszabbat (azonos hossznál az
1. vágányt) azonnal kiírjuk, és az érkező kocsi a helyére kerül. Az utolsó kocsi után a maradék
szerelvényeket is kiírjuk, a hosszabbal kezdve. Minden kocsi állandó munkát igényel, így az időigény O(N).
*/
/*
Hint 1: || Egy vágányt elég egy párral nyilvántartani: a célállomás neve és a rajta álló kocsik száma, az üres vágány kocsiszáma pedig 0. ||
Hint 2: || Egy érkező kocsit először arra a vágányra tedd, amely ugyanarra a célállomásra gyűjt és nincs tele, ha nincs ilyen, egy üres vágányra; csak ha ez sem megy, kell valamelyik szerelvényt útnak indítani. ||
Hint 3: || A végén a még álló szerelvényeket is ki kell írni, előbb a hosszabbat, azonos hossznál az 1. vágányt; a közbenső indításnál is ugyanígy döntsünk. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Vagany {
    string cel;     // a vágányon álló szerelvény célállomása
    int db = 0;     // a vágányon álló kocsik száma (0 = üres vágány)
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> cel(n);
    for (auto &c : cel) cin >> c;

    Vagany v[2];

    auto indit = [&](int k) {
        cout << v[k].cel << ' ' << v[k].db << '\n';
        v[k].cel.clear();
        v[k].db = 0;
    };

    for (int i = 0; i < n; i++) {
        const string &d = cel[i];

        // 1. nem tele vágány, amely ugyanarra a célra gyűjt
        int k = -1;
        for (int t = 0; t < 2; t++) {
            if (v[t].db > 0 && v[t].cel == d && v[t].db < m) {
                k = t;
                break;
            }
        }
        if (k != -1) {
            v[k].db++;
            continue;
        }

        // 2. üres vágány
        for (int t = 0; t < 2; t++) {
            if (v[t].db == 0) {
                k = t;
                break;
            }
        }
        if (k != -1) {
            v[k].cel = d;
            v[k].db = 1;
            continue;
        }

        // 3. mindkét vágány foglalt: a hosszabb szerelvény indul (azonos hossznál az 1. vágány)
        int longer = (v[1].db > v[0].db) ? 1 : 0;
        indit(longer);
        v[longer].cel = d;
        v[longer].db = 1;
    }

    // a maradék szerelvények: előbb a hosszabb (azonos hossznál az 1. vágány)
    int first = (v[1].db > v[0].db) ? 1 : 0;
    int second = 1 - first;
    if (v[first].db > 0) indit(first);
    if (v[second].db > 0) indit(second);
    return 0;
}
