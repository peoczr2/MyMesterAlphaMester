/*
Megoldás lényege:
A legrövidebb nyitó sorozat pontosan egy de Bruijn-sorozat: az összes N hosszú
szó pontosan egyszer fordul elő benne. Ezt a K ábécé feletti, N-1 hosszú csúcsokból
álló de Bruijn-gráf Euler-körével lehet előállítani.

Minden csúcsból K él indul, amelyek a következő karakter hozzáadását jelentik.
A gráf Euler-körét Hierholzer-algoritmussal, veremmel bejárjuk. A kapott
éllabelleket visszafelé kiírva, az elejére N-1 darab 0-t téve kapjuk a legrövidebb
nyitó sorozatot. Az időigény és a memóriaigény O(K^N).
*/
/*
Hint 1: || Modellezd gráffal: a csúcsok az N-1 hosszú karaktersorozatok, és minden N hosszú kódhoz pontosan egy él tartozik. Ennek kezdőcsúcsa a kód első N-1 karaktere, végpontja az utolsó N-1 karakter, címkéje az utolsó karakter. Így a feladat: olyan bejárást keresni, amely minden élt pontosan egyszer használ. ||
Hint 2: || Minden csúcsnak K kimenő és K bemenő éle van, így a gráfban létezik Euler-kör. Ha a bejárást a csupa nulla csúcsból indítjuk, az élcímkék elé N-1 nullát írva a legrövidebb nyitó sorozatot kapjuk, hossza K^N + N-1. ||
Hint 3: || Az Euler-kört Hierholzer-algoritmussal, veremmel (rekurzió nélkül) építsd meg: amíg a verem tetejének van kihasználatlan kimenő éle, lépj rajta; ha nincs, vedd le a csúcsot, és írd ki a hozzá vezető él címkéjét. A kiírt címkék fordított sorrendje adja a bejárás sorrendjét. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    if (!(cin >> k >> n)) return 0;

    if (n == 1) {
        for (int i = 0; i < k; ++i) cout << i;
        cout << '\n';
        return 0;
    }

    int nodes = 1;
    for (int i = 0; i < n - 1; ++i) nodes *= k;

    vector<int> nextDigit(nodes, 0);
    vector<int> stNodes;
    vector<int> stDigits;
    vector<int> ans;
    stNodes.push_back(0);

    while (!stNodes.empty()) {
        int v = stNodes.back();
        if (nextDigit[v] < k) {
            int d = nextDigit[v]++;
            int to = (v * k + d) % nodes;
            stNodes.push_back(to);
            stDigits.push_back(d);
        } else {
            stNodes.pop_back();
            if (!stDigits.empty()) {
                ans.push_back(stDigits.back());
                stDigits.pop_back();
            }
        }
    }

    for (int i = 0; i < n - 1; ++i) cout << 0;
    for (int i = (int)ans.size() - 1; i >= 0; --i) cout << ans[i];
    cout << '\n';
    return 0;
}