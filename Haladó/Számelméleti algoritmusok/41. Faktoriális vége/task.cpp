/*
 * A faktorális végén álló nullák száma.
 
Hint 1: || Egy zérus a végén egy `10 = 2*5` párból jön, és az `N!`-ben mindig több a 2-es, mint az 5-ös. ||
Hint 2: || Ezért elég megszámolni, hány darab 5-ös prímtényező van `N!`-ben: `N/5 + N/25 + N/125 + ...`. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int ans = 0;
    while (n) {
        n /= 5;
        ans += n;
    }
    cout << ans << '\n';
    return 0;
}
