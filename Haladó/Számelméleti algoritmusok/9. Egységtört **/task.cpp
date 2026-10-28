/*
Megoldás lényege: az egyiptomi törtbontás klasszikus mohó algoritmusa.
Mindig a legkisebb olyan 1/d egységtörtet vesszük, amely nem nagyobb a maradék M/N törtnél, vagyis d = ceil(N/M).
Ezt levonjuk a maradékból: az új maradék (M*d - N)/(N*d), amit gcd-vel egyszerűsítünk, hogy a számok ne nőjenek feleslegesen.
A maradék számlálója minden lépésben szigorúan kisebb lesz, így legfeljebb M lépés van, és a kapott nevezők szigorúan növekvő sorrendben jönnek.
Mivel N <= 30, a számok mérete kicsi, az időigény pedig elhanyagolható.
*/
/*
Hint 1: || Az egyiptomi törtbontás klasszikus mohó ötlete: mindig a lehető legkisebb 1/x-et válaszd, ami még nem nagyobb a maradék tört értékénél. ||
Hint 2: || Ha kiválasztottad az 1/d tagot, vond ki a törtből, egyszerűsítsd a maradékot gcd-vel, és folytasd, amíg a számláló el nem fogy. ||
*/
#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long m, n;
    cin >> m >> n;
    vector<long long> denoms;
    while (m) {
        long long d = (n + m - 1) / m;
        denoms.push_back(d);
        m = m * d - n;
        n = n * d;
        long long g = gcdll(m, n);
        m /= g;
        n /= g;
    }
    for (int i = 0; i < (int)denoms.size(); ++i) {
        if (i) cout << ' ';
        cout << denoms[i];
    }
    cout << '\n';
    return 0;
}
