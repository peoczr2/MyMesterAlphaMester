/*
A ritka számok azok a nemnegatív egészek, amelyek kettes alakjában nincs két egymás melletti 1-es; a 0 is ritka szám, ő a sorozat első eleme.
Ezért az N-edik ritka szám megkereséséhez az (N-1)-edik pozitív ritka számot állítjuk elő, az N = 1 esetben a válasz 0.
Az L bites, 1-gyel kezdődő ritka számok darabszáma Fibonacci-számokat követ, így az előtag-összegekből meghatározható, hány bites a keresett szám.
A számot ezután bitenként építjük fel: ha az előző bit 1, a következő csak 0 lehet; ha az előző bit 0, akkor a 0-val folytatható változatok darabszáma alapján döntjük el, hogy a sorszám melyik ágba esik.
Az időigény O(log N), ami a korlátok mellett messze belefér a 0,3 mp-es limitbe.
*/
/*
Hint 1: || Számold meg, hány L bites szám van, amely 1-gyel kezdődik és nincs benne két egymás melletti 1-es; ez Fibonacci-szerű rekurziót követ. ||
Hint 2: || Bitenként építsd a számot: ha az előző bit 1, a következő csak 0 lehet; ha az előző bit 0, akkor a 0-val folytatott, még szabad helyek számából látszik, hogy a sorszám a 0-s vagy az 1-es ágba esik. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }
    --n;

    vector<long long> exact(65, 0), pref(65, 0);
    exact[1] = 1;
    exact[2] = 1;
    for (int len = 3; len <= 64; ++len) exact[len] = exact[len - 1] + exact[len - 2];
    for (int len = 1; len <= 64; ++len) pref[len] = pref[len - 1] + exact[len];

    int len = 1;
    while (pref[len] < n) ++len;
    long long rank = n - pref[len - 1];

    string bits(len, '0');
    bits[0] = '1';
    int prev = 1;
    for (int pos = 1; pos < len; ++pos) {
        int rem = len - pos - 1;
        long long count_if_zero = exact[rem + 2];
        if (prev == 1) {
            bits[pos] = '0';
            prev = 0;
        } else {
            if (rank <= count_if_zero) {
                bits[pos] = '0';
                prev = 0;
            } else {
                rank -= count_if_zero;
                bits[pos] = '1';
                prev = 1;
            }
        }
    }

    long long value = 0;
    for (char c : bits) value = value * 2 + (c - '0');
    cout << value << '\n';
    return 0;
}
