/*
Megoldás lényege:
A prímosztókat próbaosztással keressük: d = 2-től kezdve, amíg d·d nem nagyobb a maradéknál, ha d osztója a maradéknak, akkor d-t teljesen kiosztjuk belőle, így minden osztó csak egyszer kerül a listába.
Mivel a kisebb osztókat már kivettük, a talált d osztók mind prímek, és növekvő sorrendben kerülnek elő.
Ha a próbaosztás végén a maradék 1-nél nagyobb, az egy újabb, a legnagyobb prímosztó, amely csak egyszer szerepel.
Mivel N legfeljebb 10^8, a próbaosztás legfeljebb 10^4 lépésben véget ér, az időigény O(sqrt(N)).
*/
/*
Hint 1: || A különböző prímosztókhoz nem kell semmi extra: elég a szokásos próbaosztásos faktorizálás. ||
Hint 2: || Amikor találsz egy osztó prímet, oszd ki teljesen a számból, hogy ugyanaz a prímosztó csak egyszer kerüljön a kimenetbe. ||
*/
#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 n;
    cin >> n;
    auto factors = factorize_int(n);
    for (int i = 0; i < (int)factors.size(); ++i) {
        if (i) cout << ' ';
        cout << factors[i].first;
    }
    cout << '\n';
    return 0;
}
