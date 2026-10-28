/*
Megoldás lényege:
A hír csak az ismert telefonszámokon halad, így irányított gráfot kapunk: az i-ből j-be vezet él, ha az i. tanuló ismeri a j. tanuló telefonszámát. Minden tanulóból egy szélességi bejárással (BFS) megszámoljuk, hány másik tanulóhoz jut el a hír. Mivel N legfeljebb 250, az N bejárás belefér az időkorlátba. A legtöbb tanulóhoz eljutó tanulók közül a legkisebb sorszámút írjuk ki, így a kimenet egyértelmű.
*/
/*
Hint 1: || A hír csak az ismert telefonszámokon halad, tehát irányított gráfot kapsz: az i-ből j-be akkor megy él, ha i ismeri j telefonszámát. ||
Hint 2: || Mivel N kicsi, minden tanulóból indíts egy szélességi bejárást, és számold meg, hány másik tanulót ér el. A legtöbbet elérő tanulók közül a legkisebb sorszámút írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> knows(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        while (cin >> x && x != 0) knows[i].push_back(x);
    }

    int bestStudent = 1, bestReach = -1;
    for (int s = 1; s <= n; s++) {
        vector<char> seen(n + 1, 0);
        queue<int> q;
        seen[s] = 1;
        q.push(s);
        int reached = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : knows[v]) {
                if (!seen[u]) {
                    seen[u] = 1;
                    reached++;
                    q.push(u);
                }
            }
        }
        if (reached > bestReach) {
            bestReach = reached;
            bestStudent = s;
        }
    }

    cout << bestStudent << "\n";
    return 0;
}
