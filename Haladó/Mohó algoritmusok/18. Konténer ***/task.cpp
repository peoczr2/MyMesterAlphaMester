/*
Megoldás lényege:
A konténereket balról jobbra haladva szigorúan növekvő láncokba rendezzük: minden konténert a legnagyobb, nála kisebb láncvégre fűzünk, ha nincs ilyen, új láncot nyitunk. A láncok minimális száma a Dilworth-tétel szerint a leghosszabb nem növekvő részsorozat hossza, a felszabadítható helyek száma pedig N mínusz a láncok száma. A láncvégek multihalmazában a keresés és a módosítás O(log N), így az időigény O(N log N).
*/
/*
Hint 1: || Egy láncban a méreteknek balról jobbra növekedniük kell. ||
Hint 2: || Mindig a legnagyobb még kisebb láncvégre tedd az aktuális konténert. ||
Hint 3: || A felszabadítható helyek száma a konténerek száma mínusz a láncok száma. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    multiset<int> tails;
    for (int x : a) {
        auto it = tails.lower_bound(x);
        if (it == tails.begin()) {
            tails.insert(x);
        } else {
            --it;
            tails.erase(it);
            tails.insert(x);
        }
    }

    cout << n - (int)tails.size() << '\n';
    return 0;
}