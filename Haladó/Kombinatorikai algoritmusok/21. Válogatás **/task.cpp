/*
Megoldás lényege:
N legfeljebb 8, ezért az összes permutációt kipróbálhatjuk.
Egy permutáció megmondja, hogy az I. ládába melyik üvegfajtát gyűjtjük.
Az optimális megoldás az, ahol a helyben maradó üvegek száma maximális.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> a(n, vector<int>(n));
    long long total = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            total += a[i][j];
        }
    }

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);

    long long bestKeep = -1;
    vector<int> bestPerm;
    do {
        long long keep = 0;
        for (int i = 0; i < n; ++i) keep += a[i][perm[i] - 1];
        if (keep > bestKeep) {
            bestKeep = keep;
            bestPerm = perm;
        }
    } while (next_permutation(perm.begin(), perm.end()));

    cout << total - bestKeep << '\n';
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << bestPerm[i];
    }
    cout << '\n';
    return 0;
}