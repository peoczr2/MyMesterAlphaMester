/*
Megoldás lényege:
Egy k-adik pillanatban érkező diák a k-tól kezdődő szakaszt hallja, és akkor hall minden évszámot, ha az összes különböző évszám ebben a szakaszban legalább egyszer szerepel. Egy évszám akkor szerepel a k-tól kezdődő szakaszban, ha utolsó előfordulása legalább k. Ezért k-nak minden évszámnál legfeljebb az adott évszám utolsó előfordulásáig szabad lennie, tehát a legkésőbbi jó kezdési pillanat az évszámok utolsó előfordulási indexeinek minimuma. Mivel az évszámok nagyok lehetnek, az (évszám, sorszám) párokat rendezzük: így az azonos évszámok egymás mellé kerülnek, és csoportonként az utolsó elem adja az utolsó előfordulást. Az időigény O(N log N), a memóriaigény O(N).
*/
/*
Hint 1: || A késve érkező diák a megérkezése utáni órarészt hallja. Azt kell megnézni, hogy ebben a szakaszban minden különböző évszám előfordul-e legalább egyszer. ||
Hint 2: || Egy évszám akkor van benne a k-tól kezdődő szakaszban, ha az utolsó előfordulása k-nál nem korábbi. Ezért a keresett k nem lehet nagyobb, mint az évszámok utolsó előfordulásainak minimuma. ||
Hint 3: || Az évszámok 10^9-ig mehetnek, ezért ne tömbben indexeld őket. Rendezd az (évszám, sorszám) párokat, csoportonként vedd az utolsó sorszámot, és írd ki ezek minimumát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> e(n);  // (évszám, időpillanat)
    for (int i = 0; i < n; i++) {
        cin >> e[i].first;
        e[i].second = i + 1;
    }
    sort(e.begin(), e.end());

    // minden évszám utolsó előfordulásának minimuma: ez a legkésőbbi jó kezdés
    int legkesobb = INT_MAX;
    for (int i = 0; i < n;) {
        int j = i;
        while (j + 1 < n && e[j + 1].first == e[i].first) j++;
        legkesobb = min(legkesobb, e[j].second);
        i = j + 1;
    }

    cout << legkesobb << "\n";
    return 0;
}
