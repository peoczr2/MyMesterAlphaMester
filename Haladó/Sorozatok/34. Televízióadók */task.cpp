/*
Megoldas lenyege:
A napi időt 24 egyórás szakaszra bontjuk. Minden adás egy félopen [kezdet,vég)
intervallum, ezért diff-tömbbel könnyen kiszámítható, hogy az egyes órákban hány
adás érhető el. Az első sorba azok az órák kerülnek, ahol ez a szám maximális,
a második sorba pedig a leghosszabb, legkorábbi nulla lefedésű szakasz.
*/
/*
Hint 1: || A nap csak 24 órából áll, ezért elég óránként számolni. ||
Hint 2: || Az első sorhoz a maximális lefedettségű órákat kell kiírni. ||
Hint 3: || A második sor a leghosszabb olyan egybefüggő szakasz, ahol egyetlen adás sem fut. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> diff(25, 0);
    for (int i = 0; i < n; ++i) {
        int id, l, r;
        cin >> id >> l >> r;
        ++diff[l];
        --diff[r];
    }

    vector<int> cover(24, 0);
    int cur = 0;
    for (int h = 0; h < 24; ++h) {
        cur += diff[h];
        cover[h] = cur;
    }

    int best = *max_element(cover.begin(), cover.end());
    bool first = true;
    for (int h = 0; h < 24; ++h) {
        if (cover[h] == best) {
            if (!first) cout << ' ';
            first = false;
            cout << h << '-' << h + 1;
        }
    }
    if (!first) cout << ' ';
    cout << '\n';

    int bestLen = 0, bestL = -1, bestR = -1;
    int i = 0;
    while (i < 24) {
        if (cover[i] != 0) {
            ++i;
            continue;
        }
        int j = i;
        while (j < 24 && cover[j] == 0) ++j;
        if (j - i > bestLen) {
            bestLen = j - i;
            bestL = i;
            bestR = j;
        }
        i = j;
    }

    if (bestLen == 0) cout << 0 << '\n';
    else cout << bestL << '-' << bestR << '\n';
    return 0;
}
