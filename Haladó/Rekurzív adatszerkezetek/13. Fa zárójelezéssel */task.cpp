#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
A leírás bináris fa: vagy csak egy F áll, vagy egy belső csomópontot látunk
„(bal)F(jobb)” alakban. Egyetlen rekurzív bejárásban kiszámolható minden keresett
érték.

Egy levélre a magasság 1, a tömeg 1 és az elágazások száma 0. Egy belső csomópontnál
a magasság a két részfa magasságának maximuma plusz 1, a tömeg a két részfa tömegének
és az aktuális csomópontnak az összege, az elágazások száma pedig a két részfa
elágazásainak összege plusz 1.

Hint 1: || A levél egyszerűen az önmagában álló F. ||
Hint 2: || Az „(bal)F(jobb)” alakban a középső F az aktuális csomópont. ||
Hint 3: || Egy rekurzív parserrel egyszerre három mennyiséget is összeadhatsz: magasságot, tömeget és elágazásszámot. ||
*/

struct Res {
    int height = 0;
    int mass = 0;
    int branches = 0;
};

string s;
int pos;

Res parseTree() {
    if (s[pos] == 'F') {
        ++pos;
        return {1, 1, 0};
    }

    ++pos; // (
    Res left = parseTree();
    ++pos; // )
    ++pos; // F
    ++pos; // (
    Res right = parseTree();
    ++pos; // )

    Res cur;
    cur.height = 1 + max(left.height, right.height);
    cur.mass = 1 + left.mass + right.mass;
    cur.branches = 1 + left.branches + right.branches;
    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    pos = 0;
    Res ans = parseTree();
    cout << ans.height << '\n' << ans.mass << '\n' << ans.branches << '\n';
    return 0;
}