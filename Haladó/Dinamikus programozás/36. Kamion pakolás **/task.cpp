/*
Itt a tárgy súlya maga a haszon is, ezért a feladat klasszikus 0/1 hátizsák: azt a legnagyobb elérhető összsúlyt kell
megkeresni, ami nem haladja meg a kapacitást. Az egy dimenziós elérhetőségi DP mellett minden újonnan elért súlyhoz
elmentjük, melyik korábbi súlyból és melyik tárggyal jutottunk oda, így a kiválasztott tárgyak halmaza is visszafejthető.
*/
/*
Hint 1: || Mivel a súly az érték is, elég az elérhető összsúlyokat tárolni. ||
Hint 2: || A tárgyakat jobbról balra frissítsd, különben ugyanazt a tárgyat többször is felhasználnád. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }

    vector<char> reach(K + 1, 0);
    vector<int> parent_weight(K + 1, -1), parent_item(K + 1, -1);
    reach[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int s = K - w[i]; s >= 0; --s) {
            if (reach[s] && !reach[s + w[i]]) {
                reach[s + w[i]] = 1;
                parent_weight[s + w[i]] = s;
                parent_item[s + w[i]] = i;
            }
        }
    }

    int best = K;
    while (best >= 0 && !reach[best]) {
        --best;
    }

    vector<int> items;
    for (int cur = best; cur > 0; cur = parent_weight[cur]) {
        items.push_back(parent_item[cur]);
    }
    reverse(items.begin(), items.end());

    cout << best << '\n';
    cout << items.size() << '\n';
    for (int i = 0; i < (int)items.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << items[i];
    }
    cout << '\n';
    return 0;
}
