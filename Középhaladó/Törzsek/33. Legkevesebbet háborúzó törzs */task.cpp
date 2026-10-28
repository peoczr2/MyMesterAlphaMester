/*
Megoldás lényege:
Minden háború két résztvevőt érint, ezért törzsenként megszámoljuk, hányszor szerepel a háborúk sorai között támadóként vagy védőként. A békés törzsek száma nulla, ezeket kihagyjuk. A nem békés törzsek közül keressük a legkevesebb háborúval rendelkezőt, egyenlőség esetén a kisebb sorszámút. A kiírás a törzs sorszáma és a háborúinak száma. Az időigény O(K + N), a memória O(N).
*/
/*
Hint 1: || Egy háború mindkét résztvevőt érinti, ezért egy törzs háborúinak száma azt adja meg, hányszor szerepel a sorokban támadóként vagy védőként. ||
Hint 2: || Számláló tömbbel számold a háborúkat törzsenként, majd a nulla számlálójú (békés) törzsek kihagyásával keresd a minimumot; egyenlőségnél a kisebb sorszám marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 2>> wars(k); // támadó, védő (a dátumokra nincs szükség)
    int maxId = n;
    for (auto &w : wars) {
        int s, e;
        cin >> w[0] >> w[1] >> s >> e;
        maxId = max({maxId, w[0], w[1]});
    }

    vector<int> cnt(maxId + 1, 0);
    for (const auto &w : wars) {
        cnt[w[0]]++;
        cnt[w[1]]++;
    }

    int best = -1;
    for (int t = 1; t <= maxId; t++) {
        if (cnt[t] == 0) continue; // békés törzs
        if (best == -1 || cnt[t] < cnt[best]) best = t;
    }

    cout << best << " " << cnt[best] << "\n";
    return 0;
}
