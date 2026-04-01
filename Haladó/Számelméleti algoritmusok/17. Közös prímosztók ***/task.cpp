/*
 * Két szám közös prímosztóinak meghatározása prímfaktorizálással.
 
Hint 1: || A közös prímosztók a két szám prímtényezős felbontásának közös elemei. ||
Hint 2: || Faktorizáld mindkét számot növekvő prímsorrendben, aztán kétmutatósan szedd ki a közös prímtényezőket. ||
*/

#include "../common.hpp"

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
