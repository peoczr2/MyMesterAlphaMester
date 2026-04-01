#include <bits/stdc++.h>
using namespace std;

/*
    A pontszámok csak 1..100 közé eshetnek, ezért minden új versenyzőnél elég
    a korábbi kisebb pontszámú versenyzők számát prefixösszeggel kiszámítani.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> freq(101, 0);
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        int ans = 0;
        for (int x = 1; x < p; ++x) ans += freq[x];
        cout << ans << '\n';
        ++freq[p];
    }
    return 0;
}
