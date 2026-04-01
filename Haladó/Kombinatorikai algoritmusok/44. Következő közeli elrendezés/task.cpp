/*
   Következő közeli elrendezés: az i és i+1 helyeken álló számok felcserélhetők,
   és a permutáció pontosan az egymást nem fedő cserék halmaza. Ezért a feladat
   egy 0/1 sorozat lexikografikus következőjére vezethető vissza, ahol az 1 azt
   jelenti, hogy az adott szomszédos pár fel van cserélve.
*/
#include <bits/stdc++.h>
using namespace std;

static vector<int> buildPermutation(int n, const vector<int>& bits) {
    vector<int> ans;
    for (int i = 0; i < n - 1; ) {
        if (bits[i]) {
            ans.push_back(i + 2);
            ans.push_back(i + 1);
            i += 2;
        } else {
            ans.push_back(i + 1);
            ++i;
        }
    }
    if ((int)ans.size() < n) ans.push_back(n);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    vector<int> bits(max(0, n - 1), 0);
    for (int i = 0; i + 1 < n; ) {
        if (p[i] == i + 1) {
            bits[i] = 0;
            ++i;
        } else {
            bits[i] = 1;
            i += 2;
        }
    }

    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }

    bool found = false;
    for (int i = n - 2; i >= 0; --i) {
        if (bits[i] == 0 && (i == 0 || bits[i - 1] == 0)) {
            bits[i] = 1;
            for (int j = i + 1; j < n - 1; ++j) bits[j] = 0;
            found = true;
            break;
        }
    }
    if (!found) fill(bits.begin(), bits.end(), 0);

    auto ans = buildPermutation(n, bits);
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}