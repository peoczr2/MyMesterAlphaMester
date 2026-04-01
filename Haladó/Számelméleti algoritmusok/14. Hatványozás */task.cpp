/*
 * Nagy egész hatványozás cpp_int-tel.
 
Hint 1: || Az eredmény túl nagy lehet a beépített egész típusokhoz, ezért saját nagy szám vagy multiprecision kell. ||
Hint 2: || Mivel csak egy egész számmal kell sokszor szorozni, elég egy egyszerű nagy egész reprezentáció is, nem kell teljes nagy szám aritmetika. ||
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
