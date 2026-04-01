#include <bits/stdc++.h>
using namespace std;

/*
    Minden faj egy intervallumot fed le az évek tengelyén. A legtöbb fajtól
    érintett év a lefedések maximális pontja; az évszámok közül a legnagyobbat
    kell megadni.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<int> diff(m + 3, 0);
    for (int i = 0; i < n; ++i) {
        int u, e;
        cin >> u >> e;
        if (u > e) swap(u, e);
        ++diff[u];
        --diff[e + 1];
    }

    int akt = 0, best = -1, kor = 1;
    for (int i = 1; i <= m; ++i) {
        akt += diff[i];
        if (akt > best || (akt == best && i > kor)) {
            best = akt;
            kor = i;
        }
    }

    cout << best << '\n' << kor << '\n';
    return 0;
}