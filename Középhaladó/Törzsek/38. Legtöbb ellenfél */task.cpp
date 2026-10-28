/*
Megoldás lényege:
A kérdés a különböző ellenfelek száma, nem a háborúk száma: ugyanazzal a törzzsel vívott több háború egynek számít.
Minden törzshez egy halmazban gyűjtjük az ellenfeleit; minden háborúnál mindkét résztvevő halmazába bekerül a másik sorszáma.
A halmazok mérete adja a különböző ellenfelek számát, és az 1-től N-ig tartó végigmenésben a legnagyobbat keressük.
Szigorú összehasonlításnál egyenlőség esetén a kisebb sorszámú törzs marad. Az idő O(K log K), a memória O(N + K).
*/
/*
Hint 1: || Minden háborúban két törzs vesz részt, és mindkettőnek ellenfele a másik. Az ismétlődő párokat ne számold többször. ||
Hint 2: || Tartsd törzsenként egy halmazban az ellenfelek sorszámait: a halmaz mérete a különböző ellenfelek száma. A végén a legnagyobb halmazméretű törzset keresd, és egyenlőségnél a kisebbet tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<set<int>> enemies(n + 1);
    for (int i = 0; i < k; i++) {
        int a, b, s, e;
        cin >> a >> b >> s >> e;
        enemies[a].insert(b);
        enemies[b].insert(a);
    }

    int bestTribe = 1;
    size_t bestCount = 0;
    for (int t = 1; t <= n; t++) {
        if (enemies[t].size() > bestCount) {
            bestCount = enemies[t].size();
            bestTribe = t;
        }
    }
    cout << bestTribe << " " << bestCount << "\n";
    return 0;
}
