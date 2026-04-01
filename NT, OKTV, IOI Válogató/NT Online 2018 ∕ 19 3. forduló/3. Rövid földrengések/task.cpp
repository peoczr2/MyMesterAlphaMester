#include <bits/stdc++.h>
using namespace std;

/*
    Az összes földrengés időpontját összegyűjtjük, rendezzük, és a szomszédos
    időpontok közötti legnagyobb üres részt keressük. A kezdő és záró határidőket
    is figyelembe kell venni.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, m;
    cin >> k >> m;
    vector<int> idopontok;
    while (k--) {
        int f;
        cin >> f;
        for (int i = 0; i < f; ++i) {
            int r;
            cin >> r;
            idopontok.push_back(r);
        }
    }

    sort(idopontok.begin(), idopontok.end());
    idopontok.erase(unique(idopontok.begin(), idopontok.end()), idopontok.end());

    int ans = 0;
    int prev = 0;
    for (int x : idopontok) {
        ans = max(ans, x - prev - 1);
        prev = x;
    }
    ans = max(ans, m - prev);

    cout << ans << '\n';
    return 0;
}
