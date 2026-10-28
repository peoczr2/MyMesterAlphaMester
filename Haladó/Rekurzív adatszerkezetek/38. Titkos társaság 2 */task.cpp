/*
Megoldási ötlet:
Minden tagnak legfeljebb K sorszámozott közvetlen beosztottja lehet. Az új tag minden olyan helyre kerülhet,
ahol valamelyik csúcs egy közvetlen beosztotti helye még üres. Egy csúcs saját üres helyeinek száma `K - gyerekszám`.

Számoljuk ki minden részfára az összes üres hely számát, a gyerekeket a szülő előtt feldolgozva
(a bejárási sorrend fordítottját használva, mert a sorszámok nem feltétlenül követik a főnök sorrendjét). Ekkor:
- az első kérdés válasza a főnök üres helyeinek száma;
- a második kérdés i-edik válasza a főnök i-edik közvetlen beosztottjának részfájában levő összes üres hely,
  vagy 0, ha ilyen i-edik beosztott nincs.
*/
/*
Hint 1: || Az új tag mindig valamelyik meglévő tag közvetlen beosztottja lesz, tehát ismét az üres gyerekhelyeket kell számolni. ||
Hint 2: || Egy csúcs részfájának válasza = saját üres helyei + a gyerekrészfák válaszai. ||
Hint 3: || A második sorban K számot kell kiírni, ezért a főnök minden sorszámozott közvetlen helyéhez külön tartsd meg, ki ül ott. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> children(n + 1);
    vector<vector<int>> slotChild(n + 1, vector<int>(k + 1, 0));
    vector<int> childCount(n + 1, 0);
    for (int node = 2; node <= n; ++node) {
        int boss, index;
        cin >> boss >> index;
        slotChild[boss][index] = node;
        children[boss].push_back(node);
        ++childCount[boss];
    }

    vector<int> order = {1};
    for (size_t i = 0; i < order.size(); ++i) {
        for (int child : children[order[i]]) {
            order.push_back(child);
        }
    }

    vector<int> subtreeFree(n + 1, 0);
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int node = order[i];
        subtreeFree[node] = k - childCount[node];
        for (int child : children[node]) {
            subtreeFree[node] += subtreeFree[child];
        }
    }

    cout << (k - childCount[1]) << '\n';
    for (int index = 1; index <= k; ++index) {
        if (index > 1) {
            cout << ' ';
        }
        int child = slotChild[1][index];
        cout << (child ? subtreeFree[child] : 0);
    }
    cout << '\n';
    return 0;
}
