/*
Megoldás lényege:
Minden egyéni versenyen megkeressük a legnagyobb elért pontszámot, és a vele egyenlő pontot elérő résztvevők mindegyike győztes, ezért mindegyiküknek jár egy győzelem. Az összetett versenyre vonatkozó szűrés itt nem alkalmazandó: a győzelmeket minden egyéni versenyen külön számoljuk, amit a minta is igazol. A győzelmek számát tanulónként tároljuk, majd megkeressük a legnagyobb értéket. Végül azok sorszámát írjuk ki növekvő sorrendben, akik ezt a maximumot elérték, a darabszámukkal együtt. Minden versenyt egyszer dolgozunk fel, így az időigény O(N·M), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Egy versenyen a legnagyobb pontszámot elérők nyernek, ezért versenyenként elég a maximumot megkeresni. ||
Hint 2: || Ha több résztvevő is ugyanazt a maximális pontot éri el, mindannyian győztesek, tehát mindegyikük győzelmi számlálóját növeld meg. Minden tanulóhoz tartsd nyilván a győzelmei számát. ||
Hint 3: || A számlálók maximumát keresd meg, majd a sorszámokat 1-től N-ig bejárva gyűjtsd ki azokat, akiknek ez a maximum a számlálója. Így a sorszámok már növekvő sorrendben lesznek. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int minimum;  // ebben a feladatban nincs rá szükség
        cin >> minimum;
    }

    vector<int> wins(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        vector<int> who(ind), score(ind);
        for (int j = 0; j < ind; j++) {
            cin >> who[j] >> score[j];
        }

        int top = *max_element(score.begin(), score.end());
        for (int j = 0; j < ind; j++) {
            if (score[j] == top) {
                wins[who[j]]++;
            }
        }
    }

    int best = *max_element(wins.begin(), wins.end());
    vector<int> ans;
    for (int s = 1; s <= n; s++) {
        if (wins[s] == best) {
            ans.push_back(s);
        }
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
