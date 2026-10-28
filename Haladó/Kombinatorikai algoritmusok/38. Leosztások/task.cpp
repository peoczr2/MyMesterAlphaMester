/*
Megoldás lényege:
A lerakások lexikografikus sorrendje prefixfa-bejárásnak felel meg: egy szó közvetlenül a saját bővítései elé kerül. Ha a jelenlegi lerakás még bővíthető (van fel nem használt kártya), akkor a következő lerakás a szó végére írt legkisebb fel nem használt kártya. Ha nem bővíthető, a jobb végétől visszafelé keressük az első olyan pozíciót, ahol a még elérhető kártyák között van a jelenlegi betűnél nagyobb; ide a legkisebb ilyen betűt írjuk, a prefixet pedig megtartjuk. Ha ilyen pozíció nincs, a lerakás a lista utolsó eleme, és a kód ciklikusan a legkisebb betűt írja ki.
A prefixenként felhasznált kártyák darabszámát tömbben tároljuk, így az időigény O(N·ábécé), ami N ≤ 1000 mellett bőven belefér.
*/
/*
Hint 1: || A lerakások sorrendje prefixfa-bejárás: egy szó előbb áll, mint a bővítései. Először nézd meg, lehet-e a jelenlegi lerakást még egy kártyával bővíteni, és ha nem, honnan kell visszalépni. ||
Hint 2: || Tartsd nyilván betűnként, hány kártya van összesen, és a prefixekben hány van már felhasználva. Visszalépéskor a jobb végétől balra haladva az első olyan pozícióban, ahol még elérhető nagyobb betű van, a legkisebb ilyet írd a helyére, az előtte álló prefixet pedig tartsd meg. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    string cards;
    cin >> cards;

    if ((int)cards.size() != n) return 0;

    vector<char> cardList(cards.begin(), cards.end());

    int m;
    cin >> m;
    string cur;
    cin >> cur;

    if ((int)cur.size() != m) return 0;

    vector<char> values = cardList;
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    vector<int> total(values.size(), 0);
    for (char x : cardList) {
        int id = lower_bound(values.begin(), values.end(), x) - values.begin();
        ++total[id];
    }

    vector<vector<int>> pref(m + 1, vector<int>(values.size(), 0));
    for (int i = 0; i < m; ++i) {
        pref[i + 1] = pref[i];
        int id = lower_bound(values.begin(), values.end(), cur[i]) - values.begin();
        ++pref[i + 1][id];
    }

    string nxt;
    if (m < n) {
        vector<int> used = pref[m];
        for (int id = 0; id < (int)values.size(); ++id) {
            if (used[id] < total[id]) {
                nxt = cur;
                nxt.push_back(values[id]);
                break;
            }
        }
    } else {
        for (int i = m - 1; i >= 0; --i) {
            int curId = lower_bound(values.begin(), values.end(), cur[i]) - values.begin();
            for (int id = curId + 1; id < (int)values.size(); ++id) {
                if (total[id] - pref[i][id] > 0) {
                    nxt.assign(cur.begin(), cur.begin() + i);
                    nxt.push_back(values[id]);
                    goto next_done;
                }
            }
        }
        nxt.push_back(values[0]);
    }
next_done:
    cout << nxt.size() << '\n' << nxt << '\n';
    return 0;
}
