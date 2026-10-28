/*
Megoldás lényege:
Visszavonó határozat mindig egy korábbi törvényt érvényteleníthet, ezért egy törvény állapota csak a nála későbbi törvényektől függ. Ezért a törvényeket végétől az elejéig dolgozzuk fel: ha egy törvényt még nem érvénytelenített később aktív törvény, akkor aktív, és ha visszavonó határozat, akkor a j. törvényt érvénytelenítettnek jelöljük. A törvények sorszámait így csökkenő sorrendben kapjuk, a kiíráshoz megfordítjuk a listát. A megoldás O(N) idejű.
*/
/*
Hint 1: || Egy V j típusú törvény csak a j-edik törvényt érvényteleníti, és j mindig kisebb a saját sorszámánál. Így egy törvény aktivitását csak a nála nagyobb sorszámú törvények határozzák meg, ezért érdemes a bemenetet fordított sorrendben feldolgozni. ||
Hint 2: || Tarts nyilván egy logikai tömböt, amely azt jegyzi meg, hogy egy törvényt már érvénytelenített-e későbbi aktív törvény. Ha az i. törvény nincs érvénytelenítve, akkor aktív, és ha V j típusú, akkor a j. törvényt jelöld érvénytelennek. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<char> tipus(n + 1);
    vector<int> j(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> tipus[i];
        if (tipus[i] == 'V') cin >> j[i];
    }

    // a törvényeket végétől az eleje felé dolgozzuk fel
    vector<char> ervenytelen(n + 1, 0);
    vector<int> aktiv;
    for (int i = n; i >= 1; i--) {
        if (ervenytelen[i]) continue;
        aktiv.push_back(i);
        if (tipus[i] == 'V') ervenytelen[j[i]] = 1;
    }
    reverse(aktiv.begin(), aktiv.end());

    cout << aktiv.size() << '\n';
    for (size_t k = 0; k < aktiv.size(); k++) {
        if (k) cout << ' ';
        cout << aktiv[k];
    }
    cout << '\n';
    return 0;
}
