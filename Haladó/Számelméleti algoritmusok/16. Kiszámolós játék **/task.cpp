/*
 * Josephus-jellegű kiszámolós játék. A kivált gyerekeket sorban kiírjuk, majd
 * a végén a megmaradt gyerek sorszámát.
 
Hint 1: || Ez a klasszikus Josephus-szimuláció: mindig az aktuális körben kell a K-adik gyereket kivenni. ||
Hint 2: || Tarts egy listát vagy vektort az életben maradtakról, és az indexet léptesd `(idx+K-1) mod méret` szerint minden kiesésnél. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> k >> n;
    vector<int> children(n);
    iota(children.begin(), children.end(), 1);
    vector<int> eliminated;
    int idx = 0;
    while (children.size() > 1) {
        idx = (idx + k - 1) % (int)children.size();
        eliminated.push_back(children[idx]);
        children.erase(children.begin() + idx);
    }
    for (int i = 0; i < (int)eliminated.size(); ++i) {
        if (i) cout << ' ';
        cout << eliminated[i];
    }
    cout << '\n' << children[0] << '\n';
    return 0;
}
