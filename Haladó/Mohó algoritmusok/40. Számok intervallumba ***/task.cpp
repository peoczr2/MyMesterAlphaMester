/*
Feladat: A megadott számokat olyan intervallumokra kell bontani, hogy mindegyikbe legalább két szám essen, és az összhossz minimális legyen.
Ötlet: A rendezett számok között kiválasztjuk a legnagyobb hézagokat, de két vágás nem lehet egymás mellett, különben egyelemű csoport keletkezne. Ez egy súlyozott független halmaz a láncon.
Hint 1: || Az összhossz az első és utolsó szám különbségéből a kivágott hézagok összegével csökken. ||
Hint 2: || Olyan hézagokat válassz, amelyek között legalább egy szám marad. ||
Hint 3: || Dinamikával vagy a path-maximum egyszerű változatával vissza lehet fejteni az intervallumokat. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());

    if (n == 2) {
        cout << a[1] - a[0] << '\n' << a[0] << ' ' << a[1] << '\n';
        return 0;
    }

    int m = n - 1;
    vector<long long> gap(m, 0);
    for (int i = 0; i < m; ++i) gap[i] = a[i + 1] - a[i];

    vector<long long> dp(m, 0);
    vector<int> choose(m, 0);
    for (int i = 1; i <= m - 2; ++i) {
        long long take = gap[i] + (i >= 2 ? dp[i - 2] : 0);
        long long skip = dp[i - 1];
        if (take > skip) {
            dp[i] = take;
            choose[i] = 1;
        } else {
            dp[i] = skip;
        }
    }

    vector<int> cuts;
    for (int i = m - 2; i >= 1;) {
        long long take = gap[i] + (i >= 2 ? dp[i - 2] : 0);
        long long skip = dp[i - 1];
        if (take >= skip) {
            cuts.push_back(i);
            i -= 2;
        } else {
            --i;
        }
    }
    sort(cuts.begin(), cuts.end());

    long long total = a.back() - a.front();
    for (int c : cuts) total -= gap[c];

    cout << total << '\n';
    int start = 0;
    for (int c : cuts) {
        cout << a[start] << ' ' << a[c] << '\n';
        start = c + 1;
    }
    cout << a[start] << ' ' << a.back() << '\n';
    return 0;
}