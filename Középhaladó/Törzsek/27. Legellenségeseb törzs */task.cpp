/*
Megoldás lényege:
Minden törzshöz gyűjtjük a különböző ellenséges törzsek sorszámát: minden háborúnál mindkét törzs halmazába felvesszük a másikat. Ezután megkeressük azt a törzset, amelynek a halmaza a legnagyobb, egyenlőség esetén a kisebb sorszámút tartjuk meg. A halmaz miatt ugyanazzal a törzzsel többször vívott háború sem növeli a számot. Az időigény O(K log N), ami az időkorláton (0,3 mp) bőven belül van.
*/
/*
Hint 1: || A kérdés a különböző ellenséges törzsek számára vonatkozik, nem a háborúk számára. Ha ugyanazzal a törzsel többször is háborúztak, azt egyszer kell számolni. ||
Hint 2: || Törzsenként tarts egy halmazt, amelybe az ellenségek sorszámát mindkét irányban beteszed. Ezután keresd meg a legnagyobb méretű halmazú törzset úgy, hogy egyenlőségnél a kisebb sorszám maradjon. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<set<int>> ellensegek(n + 1);
    for (int i = 0; i < k; ++i) {
        int a, b, s, e;
        cin >> a >> b >> s >> e;
        ellensegek[a].insert(b);
        ellensegek[b].insert(a);
    }

    int legjobb = 1;
    for (int t = 2; t <= n; ++t)
        if (ellensegek[t].size() > ellensegek[legjobb].size())
            legjobb = t;

    cout << legjobb << "\n";
    return 0;
}
