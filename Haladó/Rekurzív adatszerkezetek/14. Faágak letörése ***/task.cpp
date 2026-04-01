/*
Megoldasi otlet:
A fa minden csomopontjanal megnezzuk, hogy a maradek bal es jobb oldali reszfa
merete kozott mekkora az elteres. A letores mindig a gyokertol legtavolabbi
egyensulytalan agaktol indul, ezert a szamolast alulrol felfele erdemes vegezni.

Egy csomopont eredmenye ket reszbol all: hany letores tortent az alatta levo
reszfan belul, es hany csomopont maradt meg az adott reszfabol. Ha a ket oldal
kozott az elteres nagyobb, mint E, akkor a nagyobb oldal teljes reszfatletorese
megtortenik, es addig ismételjuk, amig az egyensuly helyre nem all.

Hint 1: || A legmelyebb egyensulytalan agakat kell elobb levagni, ezert postorder bejaras kell. ||
Hint 2: || Egy csomopontnal csak a maradek bal es jobb reszfa merete szamit a tovabbi donteshez. ||
Hint 3: || Ha a kulonbseg tul nagy, mindig a nagyobb oldalt kell teljesen levagni, majd ujra ellenorizni. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Result {
    int breaks = 0;
    int size = 0;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, E, root;
    cin >> N >> E >> root;

    vector<int> leftChild(N + 1, 0), rightChild(N + 1, 0);
    vector<int> parent(N + 1, 0);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        char side;
        cin >> u >> v >> side;
        if (side == 'b') leftChild[u] = v;
        else rightChild[u] = v;
        parent[v] = u;
    }

    function<Result(int)> dfs = [&](int u) -> Result {
        Result left, right;
        if (leftChild[u] != 0) left = dfs(leftChild[u]);
        if (rightChild[u] != 0) right = dfs(rightChild[u]);

        Result cur;
        cur.breaks = left.breaks + right.breaks;
        int lsz = left.size;
        int rsz = right.size;
        while (abs(lsz - rsz) > E) {
            ++cur.breaks;
            if (lsz > rsz) lsz = 0;
            else rsz = 0;
        }
        cur.size = 1 + lsz + rsz;
        return cur;
    };

    Result ans = dfs(root);
    cout << ans.breaks << '\n' << ans.size << '\n';
    return 0;
}