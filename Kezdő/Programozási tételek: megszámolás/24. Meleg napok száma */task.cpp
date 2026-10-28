/*
Megoldás lényege:
Nincs szükség a mérések tárolására: az N mérést egyenként olvassuk be, és minden értéket azonnal összehasonlítunk K-val.
Ha a mérés nagyobb K-nál, növeljük a számlálót. A feltétel szigorú, így a K fokos napok nem számítanak bele.
Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell eltárolni a méréseket: minden érték beolvasás után azonnal megvizsgálható. ||
Hint 2: || A feltétel szigorú: csak a K-nál nagyobb értékek számítanak, az egyenlők nem. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int db = 0;
    for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        if (h > k) db++;
    }
    cout << db << endl;
    return 0;
}
