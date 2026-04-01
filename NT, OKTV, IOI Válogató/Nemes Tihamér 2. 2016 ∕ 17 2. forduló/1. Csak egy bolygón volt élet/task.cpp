#include <bits/stdc++.h>
using namespace std;

/*
    A két bolygó életszakaszai rendezett, zárt intervallumok. Azok a részek,
    ahol pontosan az egyik bolygón van élet, a két halmaz szimmetrikus
    különbségét adják. Ezt eseményekkel sweep line módszerrel számoljuk.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;
    vector<pair<long long, int>> esemenyek;

    auto beolvas = [&](int darab) {
        for (int i = 0; i < darab; ++i) {
            long long l, r;
            cin >> l >> r;
            esemenyek.push_back({l, 1});
            esemenyek.push_back({r + 1, -1});
        }
    };

    beolvas(a);
    beolvas(b);
    sort(esemenyek.begin(), esemenyek.end());

    vector<pair<long long, long long>> valasz;
    int aktiv = 0;
    long long kezdet = 0;
    for (size_t i = 0; i < esemenyek.size();) {
        long long x = esemenyek[i].first;
        int delta = 0;
        while (i < esemenyek.size() && esemenyek[i].first == x) {
            delta += esemenyek[i].second;
            ++i;
        }
        int uj = aktiv + delta;
        if (aktiv != 1 && uj == 1) kezdet = x;
        if (aktiv == 1 && uj != 1) valasz.push_back({kezdet, x - 1});
        aktiv = uj;
    }

    cout << valasz.size() << '\n';
    for (auto [l, r] : valasz) cout << l << ' ' << r << '\n';
    return 0;
}