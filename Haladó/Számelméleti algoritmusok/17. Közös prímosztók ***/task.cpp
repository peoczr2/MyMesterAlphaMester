/*
Megoldás lényege: mindkét számot próbaosztással prímtényezőkre bontjuk, p*p <= n mellett, ami 10^8-ig legfeljebb
10^4 osztást jelent. A kapott prímtényezők listája már növekvő sorrendben van, ezért két mutatóval egy menetben
kiválogathatók a közös prímek. Ha nincs közös prím, a válasz -1. Az időigény O(sqrt(N)).
*/
/*
Hint 1: || A közös prímosztók a két szám prímtényezős felbontásának közös prímjei; nem kell a teljes osztólistát előállítanod. ||
Hint 2: || Faktorizáld mindkét számot növekvő prímsorrendben (próbaosztással, amíg p*p <= n), majd két mutatóval haladva szedd ki a közös prímeket. ||
*/

#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

vector<pair<int64, int>> factorize_int(int64 n) {
    vector<pair<int64, int>> result;
    for (int64 p = 2; p * p <= n; ++p) {
        if (n % p != 0) continue;
        int exponent = 0;
        while (n % p == 0) {
            n /= p;
            ++exponent;
        }
        result.push_back({p, exponent});
    }
    if (n > 1) result.push_back({n, 1});
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 a, b;
    cin >> a >> b;
    auto fa = factorize_int(a);
    auto fb = factorize_int(b);
    vector<int64> common;
    size_t i = 0, j = 0;
    while (i < fa.size() && j < fb.size()) {
        if (fa[i].first == fb[j].first) {
            common.push_back(fa[i].first);
            ++i; ++j;
        } else if (fa[i].first < fb[j].first) {
            ++i;
        } else {
            ++j;
        }
    }
    if (common.empty()) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i < (int)common.size(); ++i) {
        if (i) cout << ' ';
        cout << common[i];
    }
    cout << '\n';
    return 0;
}
