/*
Megoldás lényege:
A termés a készített mennyiség (M), az ár (Á) az eredményt nem befolyásolja. Az éveket sorban olvassuk, és az eddigi legkisebb mennyiséget és a hozzá tartozó év sorszámát tartjuk nyilván. Szigorú „<” összehasonlítással holtverseny esetén a korábbi, azaz kisebb sorszámú év marad. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Az eredmény csak a mennyiségtől függ: az ár ebben a feladatban nem számít. ||
Hint 2: || Minimumkiválasztás egy menetben: tartsd nyilván az eddigi legkisebb mennyiséget és az év sorszámát, és csak szigorúan kisebb érték esetén frissíts. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestYear = 0;
    int bestAmount = INT_MAX;
    for (int i = 1; i <= n; i++) {
        int m, a;
        cin >> m >> a;
        if (m < bestAmount) {
            bestAmount = m;
            bestYear = i;
        }
    }

    cout << bestYear << "\n";
    return 0;
}
