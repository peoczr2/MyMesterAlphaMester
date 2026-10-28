/*
Megoldási ötlet:
A fa minden csomópontjánál megnézzük, hogy a maradék bal- és jobboldali részfa mérete
között mekkora az eltérés. A letörés mindig a gyökértől legtávolabbi egyensúlytalan ágaktól
indul, ezért a számolást alulról felfelé érdemes végezni.

Egy csomópont eredménye két részből áll: hány letörés történt az alatta lévő részfán belül,
és hány csomópont maradt meg az adott részfából. Ha a két oldal mérete közötti eltérés nagyobb,
mint E, akkor a nagyobb oldal teljes részfáját letörjük (ez egy letörés), és ezt addig ismételjük,
amíg az egyensúly helyre nem áll. A megmaradt csomópontok száma a gyökér eredményéből adódik.
*/
/*
Hint 1: || A legmélyebb egyensúlytalan ágakat kell előbb levágni, ezért posztorder bejárásra van szükség. ||
Hint 2: || Egy csomópontnál a további döntéshez csak a maradék bal- és jobboldali részfa mérete számít. ||
Hint 3: || Ha az eltérés túl nagy, mindig a nagyobb oldalt kell teljesen levágni, majd újra ellenőrizni. ||
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
    while (cin.peek() != EOF && !isdigit(cin.peek())) cin.get();
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