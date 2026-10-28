/*
Megoldás lényege:
Egy részsorozat akkor mutáns, ha valamelyik betű darabszáma legalább a hosszának a fele, vagyis 2·darab − hossz ≥ 0. Legyen b_i = 2·(a vizsgált betű darabja az első i karakterben) − i, ekkor az (l, r] részsorozat pontosan akkor mutáns, ha b_r ≥ b_l. A b sorozat b_0 = 0 értékről indul, és minden lépésben pontosan ±1-et változik. Ezért r-hez a legkisebb jó l: ha b_r ≥ 0, akkor l = 0, különben b_r értékének első előfordulása. Ezt az első előfordulásokat tömbben tároljuk, így a négy betűre O(N) összidővel megoldható.
*/
/*
Hint 1: || Egy részsorozat mutáns, ha egy betű darabszámát a hosszhoz képest nézzük: 2·darab − hossz nem lehet negatív. ||
Hint 2: || Prefixekre vezess be b_i = 2·(a betű darabja az első i karakterben) − i értéket; az (l, r] részsorozat pontosan akkor jó, ha b_r ≥ b_l. ||
Hint 3: || A b_i sorozat ±1 lépésekkel halad b_0 = 0-ról, így b_r < 0 esetén a legkisebb jó l az első olyan index, ahol b_l = b_r; ezt tömbben minden értékre tárold. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    const int n = static_cast<int>(s.size());
    const string letters = "ACGT";

    int best = 0;
    vector<int> first(2 * n + 1);  // first[b + n]: b első előfordulásának indexe, vagy -1
    for (char c : letters) {
        fill(first.begin(), first.end(), -1);
        first[n] = 0;  // b_0 = 0
        int b = 0;
        for (int r = 1; r <= n; ++r) {
            b += (s[r - 1] == c) ? 1 : -1;
            if (first[b + n] == -1) first[b + n] = r;
            int l = (b >= 0) ? 0 : first[b + n];
            best = max(best, r - l);
        }
    }
    cout << best << '\n';
    return 0;
}
