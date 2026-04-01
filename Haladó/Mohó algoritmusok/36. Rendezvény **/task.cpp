/*
Feladat: A lehető legtöbb előadást kell megtartani két teremben úgy, hogy egy teremben ne legyen ütközés.
Ötlet: Sorban, befejezési idő szerint nézve mindig azt az előadást tesszük be, amelyik az egyik szabad teremre még ráfér. Ha mindkét terem foglalt, akkor az aktuális előadást kihagyjuk.
Hint 1: || A legkorábban befejeződő előadások hagyják meg a legtöbb lehetőséget. ||
Hint 2: || Egy előadás csak akkor mehet egy terembe, ha az előző ott már befejeződött. ||
Hint 3: || Két terem esetén elég két utolsó befejezési időt nyomon követni. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Event {
    int s, e, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Event> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].s >> a[i].e;
        a[i].id = i + 1;
    }
    sort(a.begin(), a.end(), [](const Event &x, const Event &y) {
        if (x.e != y.e) return x.e < y.e;
        if (x.s != y.s) return x.s < y.s;
        return x.id < y.id;
    });

    int endA = 0, endB = 0;
    vector<int> roomA, roomB;
    for (const auto &ev : a) {
        if (ev.s > endA) {
            endA = ev.e;
            roomA.push_back(ev.id);
        } else if (ev.s > endB) {
            endB = ev.e;
            roomB.push_back(ev.id);
        }
    }

    cout << roomA.size() << ' ' << roomB.size() << '\n';
    for (int i = 0; i < (int)roomA.size(); ++i) {
        if (i) cout << ' ';
        cout << roomA[i];
    }
    cout << '\n';
    for (int i = 0; i < (int)roomB.size(); ++i) {
        if (i) cout << ' ';
        cout << roomB[i];
    }
    cout << '\n';
    return 0;
}