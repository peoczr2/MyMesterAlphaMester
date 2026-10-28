/*
Megoldás lényege:
A^N akár 8001 jegyű is lehet (a legnagyobb eset 10^8 ezredik hatványa), ezért nem fér bele a beépített egész típusba. A nagy számot 10^9 alapú számjegyek vektorában tároljuk, és N-szer megszorozzuk A-val. Egy szorzásnál végigmegyünk a számjegyeken, és minden számjeggyel a szorzatot az előző átvitellel együtt 64 bites egészben számoljuk, így az átvitel azonnal kezelhető. N = 0 esetén az eredmény 1, ezt a kezdőérték adja. Az időigény O(N · jegyek száma / 9), vagyis legfeljebb kb. 1000 · 900 lépés, a memória a jegyek számával arányos.
*/
/*
Hint 1: || Az eredmény túl nagy lehet a beépített egész típusokhoz, ezért saját nagy szám vagy multiprecision kell. ||
Hint 2: || Tárold a számot 10^9 alapú számjegyekből álló vektorban, és minden lépésben szorozd meg A-val úgy, hogy az átvitelt a következő számjegy felé viszed. ||
*/

#include "../common.hpp"

struct BigInt {
    static const int BASE = 1000000000;
    vector<int> a;

    BigInt(long long value = 0) {
        if (value == 0) return;
        while (value > 0) {
            a.push_back((int)(value % BASE));
            value /= BASE;
        }
    }

    void mul(int64 value) {
        int64 carry = 0;
        for (int& digit : a) {
            int64 cur = 1LL * digit * value + carry;
            digit = (int)(cur % BASE);
            carry = cur / BASE;
        }
        while (carry > 0) {
            a.push_back((int)(carry % BASE));
            carry /= BASE;
        }
    }

    string str() const {
        if (a.empty()) return "0";
        string s = to_string(a.back());
        for (int i = (int)a.size() - 1; i-- > 0;) {
            string part = to_string(a[i]);
            s += string(9 - part.size(), '0') + part;
        }
        return s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, n;
    cin >> a >> n;
    BigInt result(1);
    while (n-- > 0) {
        result.mul(a);
    }
    cout << result.str() << '\n';
    return 0;
}
