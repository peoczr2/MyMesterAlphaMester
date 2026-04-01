/*
Megoldás lényege:
A legrövidebb nyitó sorozat pontosan egy de Bruijn-sorozat: az összes N hosszú
szó pontosan egyszer fordul elő benne. Ezt a K ábécé feletti, N-1 hosszú csúcsokból
álló de Bruijn-gráf Euler-körével lehet előállítani.

Minden csúcsból K él indul, amelyek a következő karakter hozzáadását jelentik.
A gráf Euler-körét Hierholzer-algoritmussal, iteratív stókkal bejárjuk. A kapott
éllabelleket visszafelé kiírva, az elejére N-1 darab 0-t téve kapjuk a legrövidebb
nyitó sorozatot.
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