/*
Megoldás lényege:
Az azonosítókat egy összefüggő karaktertömbben tároljuk, és lexikografikusan rendezzük (indexekkel, memcmp-pel).
Rendezés után egy azonosító legrövidebb egyedi prefixe a két szomszédjával vett leghosszabb közös prefix + 1 hosszú,
legfeljebb H. Megegyező azonosítók esetén ez H, vagyis a teljes azonosító marad. Ezután a prefixet kiírjuk, a maradék
karaktereket pontokkal pótoljuk, és mellé írjuk a pontszámot. Az időigény O(N log N · H) legrosszabb esetben, a memóriaigény O(N·H).
*/
/*
Hint 1: || Egy azonosító akkor azonosítja be a versenyzőt, ha a prefixe más azonosítóban nem szerepel. Keresd meg a legrövidebb ilyen prefixet. ||
Hint 2: || Ha az azonosítókat lexikografikusan rendezed, egy azonosító egyedi prefixének hossza a két szomszédjával vett közös prefix hosszának maximumából számítható: max(előző, következő) + 1, legfeljebb H. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;

    vector<char> buf((size_t)n * h);
    vector<int> score(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s >> score[i];
        memcpy(&buf[(size_t)i * h], s.data(), h);
    }

    auto idp = [&](int i) { return buf.data() + (size_t)i * h; };
    auto lcp = [&](int a, int b) {
        int l = 0;
        while (l < h && idp(a)[l] == idp(b)[l]) l++;
        return l;
    };

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return memcmp(idp(a), idp(b), h) < 0;
    });

    vector<int> keep(n);
    for (int k = 0; k < n; k++) {
        int best = 0;
        if (k > 0) best = max(best, lcp(ord[k - 1], ord[k]));
        if (k + 1 < n) best = max(best, lcp(ord[k], ord[k + 1]));
        keep[ord[k]] = min(h, best + 1);
    }

    string dots(h, '.');
    for (int i = 0; i < n; i++) {
        cout.write(idp(i), keep[i]);
        cout.write(dots.data(), h - keep[i]);
        cout << ' ' << score[i] << '\n';
    }
    return 0;
}
