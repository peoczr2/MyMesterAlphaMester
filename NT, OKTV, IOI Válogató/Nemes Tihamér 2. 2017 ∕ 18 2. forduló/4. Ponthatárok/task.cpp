#include <bits/stdc++.h>
using namespace std;

/*
    Egy ponthatárt addig lehet lejjebb tolni, amíg az alatta levő pontszámok
    egy összefüggő, legfeljebb L hosszú blokkot alkotnak. Ha a blokk ennél hosszabb,
    akkor a ponthatár marad a helyén.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, l;
    cin >> n >> k >> l;
    int kh, hh, nh, oh;
    cin >> kh >> hh >> nh >> oh;
    vector<char> seen(k + 1, 0);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        seen[x] = 1;
    }

    auto javit = [&](int t) {
        int cnt = 0;
        while (t - cnt - 1 >= 0 && seen[t - cnt - 1]) ++cnt;
        if (cnt > 0 && cnt <= l) return t - cnt;
        return t;
    };

    cout << javit(kh) << '\n' << javit(hh) << '\n' << javit(nh) << '\n' << javit(oh) << '\n';
    return 0;
}