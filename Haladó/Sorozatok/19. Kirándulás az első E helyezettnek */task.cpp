/*
Megoldas lenyege:
Minden versenyben az elso E helyezett jogosult a kirandulasra. Ezert eleg
minden verseny eredmenylistajabol az elso E sorszamat egy halmazba tenni, majd
a vegen a halmaz elemeit novekvo sorrendben kiirni.
*/
/*
Hint 1: || Egy versenybol csak az elso E helyezett szamit. ||
Hint 2: || Egy halmazban gyujtsd ossze az osszes ilyen tanulot. ||
Hint 3: || A kimenet a halmaz rendezett elemlistaja lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, N, E;
    cin >> T >> N >> E;

    set<int> eligible;
    for (int t = 0; t < T; ++t) {
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int x;
            cin >> x;
            if (i < E) eligible.insert(x);
        }
    }

    cout << eligible.size() << '\n';
    bool first = true;
    for (int x : eligible) {
        if (!first) cout << ' ';
        first = false;
        cout << x;
    }
    cout << '\n';
    return 0;
}
