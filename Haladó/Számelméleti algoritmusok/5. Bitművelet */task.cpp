/*
 * Az (X,Y) párok sorozata a diagonális felsorolás alapján adott. Az N-edik párt
 * visszafejtjük, majd kiszámítjuk az AND és OR értéket kettes és tízes alakban.
 
Hint 1: || Az (X,Y) párok nem véletlen sorrendben jönnek: átlókon vannak felsorolva, ahol X+Y állandó. ||
Hint 2: || Ha megtaláltad, melyik átlón van az N-edik elem és az átlón belüli pozícióját is, már csak ki kell számolni az AND és OR értékeket binárisan is. ||
*/

#include "../common.hpp"

static pair<long long,long long> pair_at(long long n) {
    long long diag = 0;
    while ((diag + 1) * (diag + 2) / 2 <= n) ++diag;
    long long start = diag * (diag + 1) / 2;
    long long offset = n - start;
    return {offset, diag - offset};
}

static string bin(long long x) {
    if (x == 0) return "0";
    string s;
    while (x) {
        s.push_back(char('0' + (x & 1)));
        x >>= 1;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    auto [x, y] = pair_at(n);
    cout << x << ' ' << y << '\n';
    long long a = x & y;
    long long o = x | y;
    cout << bin(a) << ' ' << a << '\n';
    cout << bin(o) << ' ' << o << '\n';
    return 0;
}
