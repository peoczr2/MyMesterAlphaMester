/*
Az N! végén álló nullák száma megegyezik azzal, hogy hány 10 = 2 * 5 szorzópár van a szorzatban.
A kettesből mindig több van, mint az ötösből, ezért elég az ötös prímtényezőket megszámolni.
Az ötösök száma a Legendre-formulából adódik: N/5 + N/25 + N/125 + ... (egész osztással), ami O(log N) lépésben kiszámolható.
*/
/*
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
