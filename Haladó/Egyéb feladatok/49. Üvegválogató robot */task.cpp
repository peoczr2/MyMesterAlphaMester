/*
Megoldás lényege:
Mozgatott üvegek száma = az összes üveg száma mínusz azoknak az üvegeknek a száma, amelyek már a helyes ládában vannak. Az összes üveg száma fix, így azt kell maximalizálni, hogy a három kijelölt láda saját fajtájú tartalma összesen mennyi legyen: F_i + Z_j + B_k, ahol i, j, k páronként különbözőek. Mindhárom fajtához elég a három legnagyobb értékű ládát figyelembe venni, mert a különbözőség miatt az optimális megoldásban egy-egy listából legfeljebb két láda ütközhet, így mindig marad a listában szabad választás. A 27 kombinációt végigpróbáljuk. Az időigény O(N).
*/
/*
Hint 1: || Számold ki, hány üveget kell mozgatni: az összes üvegből le kell vonni azt, ami már a helyes ládában van. Mit kell ezek után maximalizálni? ||
Hint 2: || Három különböző ládát kell választani a fehérnek, zöldnek és barnának, és az összegük legyen maximális. Mindhárom fajtára elég a három legnagyobb értékű ládát figyelembe venni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> f(n), z(n), b(n);
    for (int i = 0; i < n; ++i) cin >> f[i] >> z[i] >> b[i];

    // Fajtánként a három legnagyobb értékű láda indexei
    auto top3 = [&](const vector<long long>& v) {
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        partial_sort(idx.begin(), idx.begin() + 3, idx.end(),
                     [&](int a, int c) { return v[a] > v[c]; });
        return vector<int>(idx.begin(), idx.begin() + 3);
    };
    vector<int> tf = top3(f), tz = top3(z), tb = top3(b);

    long long best = -1;
    int bi = -1, bj = -1, bk = -1;
    for (int i : tf)
        for (int j : tz)
            for (int k : tb) {
                if (i == j || j == k || i == k) continue;
                long long s = f[i] + z[j] + b[k];
                if (s > best) {
                    best = s;
                    bi = i;
                    bj = j;
                    bk = k;
                }
            }
    cout << bi + 1 << ' ' << bj + 1 << ' ' << bk + 1 << '\n';
    return 0;
}
