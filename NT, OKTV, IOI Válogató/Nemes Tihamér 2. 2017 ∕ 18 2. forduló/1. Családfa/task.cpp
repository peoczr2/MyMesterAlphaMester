/*
Megoldás lényege:
Az apa-gyerek kapcsolatokból gyerek-listát építünk: minden taghoz fejelemes, tömbökkel megvalósított láncolt listában tároljuk a gyermekeit, így az apa sorszáma nem kell, hogy kisebb legyen a gyermekénél. Ezután az 1-es tagtól szélességi bejárással számoljuk ki minden tag mélységét, mert egy tag mélysége a szülőjéé plusz egy. A legnagyobb mélységet egy végigmenéssel határozzuk meg, majd sorszám szerinti végigmenéssel írjuk ki a legmélyebb tagokat, így a kimenet automatikusan növekvő sorrendben lesz. Az időigény és a memóriaigény O(N).
*/
/*
Hint 1: || A mélység csak akkor számolható ki, ha a szülő mélysége már ismert. Mivel az apa sorszáma nem feltétlenül kisebb a gyermekénél, a sorszámok szerinti sorrend nem jó: a fát az 1-es tagtól kell bejárni. ||
Hint 2: || Építs gyerek-listát: például firstChild[apa] tárolja az egyik gyermeket, nextSibling[gyerek] a testvérét. Ezután sorban (queue) haladj a gyökértől lefelé, és a gyermek mélysége a szülő mélysége plusz egy. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> firstChild(n + 1, 0), nextSibling(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        nextSibling[i] = firstChild[p];
        firstChild[p] = i;
    }

    vector<int> depth(n + 1, 0), order;
    order.reserve(n);
    order.push_back(1);
    for (size_t h = 0; h < order.size(); ++h) {
        int v = order[h];
        for (int c = firstChild[v]; c != 0; c = nextSibling[c]) {
            depth[c] = depth[v] + 1;
            order.push_back(c);
        }
    }

    int bestDepth = 0;
    for (int i = 1; i <= n; ++i) bestDepth = max(bestDepth, depth[i]);

    int cnt = 0;
    for (int i = 1; i <= n; ++i) if (depth[i] == bestDepth) ++cnt;

    cout << cnt << ' ' << bestDepth << '\n';
    bool first = true;
    for (int i = 1; i <= n; ++i) {
        if (depth[i] != bestDepth) continue;
        if (!first) cout << ' ';
        cout << i;
        first = false;
    }
    cout << '\n';
    return 0;
}
