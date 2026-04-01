#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
Az F-láncokkal leírt fát ugyanúgy lehet rekurzívan feldolgozni, mint a korábbi
zárójelezéses feladatokat: egy részfa elején álló F-ek egy láncot adnak, majd a
lánc végén a gyermekek következnek zárójelben.

Egy részfára elég két értéket számolni:
1. a magasságot,
2. a teljes tömeget.

A magasság a saját F-lánc hossza plusz a legnagyobb gyermekmagasság. A teljes tömeg
pedig a saját részfa magassága és a gyermekek teljes tömegének összege. Ez pontosan
illik a mintákra, ahol az egységnyi legalsó ágakból felfelé haladva minden szint egy
egységgel növeli a súlyt.

Hint 1: || Először a lánc hosszát számold meg, és utána dolgozd fel a gyerekeket zárójelekben. ||
Hint 2: || A magasság a lánc hosszából és a legnagyobb gyermekmagasságból áll össze. ||
Hint 3: || A teljes tömeghez add hozzá a saját magasságot is, majd minden gyermek teljes tömegét. ||
*/

struct Res {
    long long height = 0;
    long long total = 0;
};

string s;
int pos;

Res parseTree() {
    long long chain = 0;
    while (pos < (int)s.size() && s[pos] == 'F') {
        ++chain;
        ++pos;
    }

    long long bestChildHeight = 0;
    long long childTotal = 0;
    while (pos < (int)s.size() && s[pos] == '(') {
        ++pos;
        Res child = parseTree();
        bestChildHeight = max(bestChildHeight, child.height);
        childTotal += child.total;
        if (pos < (int)s.size() && s[pos] == ')') ++pos;
    }

    Res cur;
    cur.height = chain + bestChildHeight;
    cur.total = cur.height + childTotal;
    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    pos = 0;
    Res ans = parseTree();
    cout << ans.height << '\n' << ans.height << '\n' << ans.total << '\n';
    return 0;
}