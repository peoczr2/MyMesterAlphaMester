/*
 * A nyitva maradó cellák a tökéletes négyzetek.
 
Hint 1: || Egy cella pontosan annyiszor változik, ahány osztója van az indexének. ||
Hint 2: || Csak a tökéletes négyzeteknek van páratlan számú osztójuk, ezért végül pontosan azok maradnak nyitva. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    bool first = true;
    for (int i = 1; 1LL * i * i <= n; ++i) {
        if (!first) cout << ' ';
        first = false;
        cout << 1LL * i * i;
    }
    cout << '\n';
    return 0;
}
