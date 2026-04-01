/*
Megoldas lenyege:
Ket kepet keresunk, amelyek arainak osszege pontosan P. Elmentjuk, hogy egy adott ar eddig
melyik indexen szerepelt, es minden uj arhoz megnezzuk, hogy a komplementere mar megjelent-e.

Mivel barmelyik jo par megfelel, az elso talalt pontos par kiirhato. Ha a teljes bejaras alatt
nem talalunk ilyet, akkor nincs megoldas.
*/
/*
Hint 1: || Az aktualis arhoz a P-ar komplementert keresd. ||
Hint 2: || Egy hash mapben eleg az egyik korabbi indexet eltarolni minden arhoz. ||
Hint 3: || A par barmely sorrendje jo, de a kisebb indexet erdemes elore irni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;

    unordered_map<int, int> firstPos;
    firstPos.reserve(2 * n + 1);

    for (int i = 1; i <= n; ++i) {
        int price;
        cin >> price;
        auto it = firstPos.find(target - price);
        if (it != firstPos.end()) {
            cout << it->second << ' ' << i << '\n';
            return 0;
        }
        if (!firstPos.count(price)) firstPos[price] = i;
    }

    cout << -1 << '\n';
    return 0;
}