/*
Megoldás lényege:
Az i-edik cellát pontosan annyi börtönőr kapcsolja, ahány osztója i-nek, így az állapota a kapcsolások számának paritásától függ. Kezdetben minden cella zárt, ezért nyitva az marad, amelyiknek páratlan sok osztója van. Az osztók párokba állíthatók (d és i/d), páratlan számuk csak akkor lehet, ha van olyan osztó, amelynek párja önmaga, vagyis i tökéletes négyzet. Ezért a program az 1, 4, 9, … négyzeteket írja ki: i = 1, 2, … sorban, amíg i² ≤ N. Az időigény O(√N), ami N ≤ 1 000 000 esetén bőven belefér az időkorlátba.
*/
/*
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
