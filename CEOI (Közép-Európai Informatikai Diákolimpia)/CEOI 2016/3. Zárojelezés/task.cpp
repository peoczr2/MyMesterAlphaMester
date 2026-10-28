/*
Megoldás lényege:
Egy zárójelezés akkor felel meg S-nek, ha a párba tartozó zárójelek azonos betűn állnak, és a párok nem keresztezik egymást.
Egy pár (i, j) pontosan akkor lehetséges, ha S_i = S_j, és az (i, j) közötti rész redukálható üres szöveggé, azaz
a szó "szabad redukciója" (egymás mellett álló azonos betűk törlése) ugyanott áll i után és j-1 után.
A redukció lépéseit egy fában (a redukált prefixek trie-jában) követjük: minden lépés egy élt jár be,
és a pár két tagja ugyanazt az élt járja be ellentétes irányban. Ha az S redukciója nem üres, a válasz -1.
Lexikografikusan minimális zárójelezéshez a nyitó zárójel párját a belső rész utolsó, még ugyanazon
élen át vezető lépéséhez kell rendelni, így a nyitás a lehető leghosszabb egymásba ágyazást adja.
A feladatot intervallumokra bontva, verem segítségével, a bejárás minden lépésénél egy bináris kereséssel
találjuk meg a párt. Az időigény O(N log N).
*/
/*
Hint 1: || A zárójelek párjai csak akkor lehetnek, ha a közöttük lévő szakasz felsorolt betűi kiesnek
a szomszédos azonos betűk törlésével. Ez a feltétel nem függ a pár választásától. ||
Hint 2: || Tekintsd az S betűit lépéseknek egy fában: a betű elhagyása (ha az utolsó betű azonos) lépés
a szülő felé, egyébként új gyerekre lépés. Egy pár két tagja ugyanazt az élt járja be, az egyik irányban,
majd a másikban. ||
Hint 3: || A lexikografikusan legkisebb megoldáshoz mindig az adott nyitás utolsó visszalépését válaszd
párnak az aktuális intervallumon belül, és a belső illetve a külső részre ugyanígy rekurzívan folytasd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = (int)s.size();

    // Trie a redukált prefixekhez: parent, betű, gyerekek
    vector<int> parent(1, -1);
    vector<int> letter(1, -1);
    vector<array<int, 26>> child(1);
    child[0].fill(-1);

    vector<int> edge(n + 1, 0);  // az i-edik lépés által bejárt él (a gyermek csúcs azonosítója)
    int cur = 0;
    for (int i = 1; i <= n; ++i) {
        int c = s[i - 1] - 'a';
        if (cur != 0 && letter[cur] == c) {
            // visszalépés a szülőre: az élt a gyermek csúcs azonosítja
            edge[i] = cur;
            cur = parent[cur];
        } else {
            if (child[cur][c] == -1) {
                child[cur][c] = (int)parent.size();
                parent.push_back(cur);
                letter.push_back(c);
                array<int, 26> empty;
                empty.fill(-1);
                child.push_back(empty);
            }
            cur = child[cur][c];
            edge[i] = cur;
        }
    }
    if (cur != 0) {
        cout << -1 << "\n";
        return 0;
    }

    // Egy élhez tartozó lépések időpontjai, növekvő sorrendben
    int nodes = (int)parent.size();
    vector<vector<int>> times(nodes);
    for (int i = 1; i <= n; ++i) times[edge[i]].push_back(i);

    string res(n, ')');
    vector<pair<int, int>> stk;
    stk.push_back({1, n});
    while (!stk.empty()) {
        auto [l, r] = stk.back();
        stk.pop_back();
        if (l > r) continue;
        const vector<int> &tl = times[edge[l]];
        // az utolsó, r-nél nem későbbi bejárás ugyanazon az élen
        int idx = (int)(upper_bound(tl.begin(), tl.end(), r) - tl.begin()) - 1;
        int q = tl[idx];
        res[l - 1] = '(';
        res[q - 1] = ')';
        stk.push_back({l + 1, q - 1});
        stk.push_back({q + 1, r});
    }

    cout << res << "\n";
    return 0;
}
