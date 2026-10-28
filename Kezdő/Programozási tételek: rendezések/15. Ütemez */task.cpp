/*
Megoldás lényege:
Ez egy kétgépes folyamatütemezési feladat, amelyre a Johnson-szabály ad optimális sorrendet.
Az alkatrészek két csoportba kerülnek: az A_i <= B_i csoportba és az A_i > B_i csoportba.
Az első csoportot A_i szerint növekvő, a másodikat B_i szerint csökkenő sorrendbe rendezzük, és a két csoportot egymás után fűzzük.
Az összidőt úgy kapjuk, hogy követjük az első gép idejét (t1) és a második gép idejét (t2): egy alkatrész B művelete a max(t2, t1) időpontban kezdődik, így t2 = max(t2, t1) + B_i.
Mindkét gép ugyanazt a sorrendet követi, ez érvényes ütemezés, és a végső t2 lesz a legkisebb lehetséges teljes idő.
A rendezés miatt az időigény O(N log N).
*/
/*
Hint 1: || Az összes idő a második gépen végzett utolsó művelet befejezési ideje, és egy alkatrész B művelete csak az A művelete után kezdődhet. ||
Hint 2: || Minden alkatrészt aszerint sorolj két csoportba, hogy az A művelet nem hosszabb-e a B műveletnél (A_i <= B_i); az első csoport kerüljön az ütemezés elejére, a másik a végére. ||
Hint 3: || Az A_i <= B_i alkatrészek közül az A_i szerint növekvő, az A_i > B_i alkatrészek közül a B_i szerint csökkenő sorrend a jó; ezt a két csoportot egymás után fűzd össze, és szimuláld a két gép idejét. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (auto &v : a) cin >> v;
    for (auto &v : b) cin >> v;

    vector<int> g1, g2;  // g1: A_i <= B_i, g2: A_i > B_i
    for (int i = 0; i < n; i++) {
        if (a[i] <= b[i]) g1.push_back(i);
        else g2.push_back(i);
    }
    sort(g1.begin(), g1.end(), [&](int x, int y) { return a[x] < a[y]; });
    sort(g2.begin(), g2.end(), [&](int x, int y) { return b[x] > b[y]; });

    vector<int> order = g1;
    order.insert(order.end(), g2.begin(), g2.end());

    long long t1 = 0, t2 = 0;  // a két gép aktuális ideje
    for (int i : order) {
        t1 += a[i];
        t2 = max(t2, t1) + b[i];
    }

    cout << t2 << '\n';
    for (int i : order) cout << i + 1 << ' ';
    cout << '\n';
    for (int i : order) cout << i + 1 << ' ';
    cout << '\n';
    return 0;
}
