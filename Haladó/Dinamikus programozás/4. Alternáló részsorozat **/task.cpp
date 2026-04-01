/*
Ez a klasszikus leghosszabb alternáló részsorozat, amelyre a mohó csúcspont-völgypont kiválasztás
optimális. Folyamatosan fenntartunk egy már jó alternáló részsorozatot indexekkel; ha az új elem a
jelenlegi irányt folytatja, akkor a legutolsó indexet egy szélsőségesebb elemre cseréljük, mert ez csak
javítja a későbbi folytatás esélyét. Ha irányváltás történik, akkor az új indexet hozzáfűzzük. Így O(N)
időben kapunk maximális hosszúságú részsorozatot, és az indexeket közvetlenül ki is tudjuk írni.
*/
/*
Hint 1: || Egy optimális alternáló részsorozatban a belső elemek helyi csúcsok vagy völgyek. ||
Hint 2: || Ha két egymás utáni különbség azonos előjelű, akkor a középső elem felesleges. ||
Hint 3: || Nem kell négyzetes DP: elég egy mohó sorozatot karbantartani a fordulópontokkal. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        if (ans.empty()) {
            ans.push_back(i);
            continue;
        }
        if (a[i] == a[ans.back()]) {
            ans.back() = i;
            continue;
        }
        if (ans.size() == 1) {
            ans.push_back(i);
            continue;
        }
        long long x = a[ans[ans.size() - 2]];
        long long y = a[ans.back()];
        long long z = a[i];
        if ((x < y && y < z) || (x > y && y > z)) {
            ans.back() = i;
        } else {
            ans.push_back(i);
        }
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}