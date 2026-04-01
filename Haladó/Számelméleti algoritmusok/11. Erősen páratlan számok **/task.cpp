/*
 * A számjegyösszegek láncában az első páros értéket kell megadni, vagy IGEN-t,
 * ha a lánc végül egyjegyű páratlan számhoz fut.
 
Hint 1: || Itt csak a számjegyösszeg-láncot kell követni, nem a teljes nagy számot feldolgozni mindenféle bonyolult módon. ||
*/

#include "../common.hpp"

static long long sum_digits(const string& s) {
    long long sum = 0;
    for (char c : s) sum += c - '0';
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    while (s.size() > 1) {
        long long sum = sum_digits(s);
        if (sum % 2 == 0) {
            cout << "NEM\n" << sum << '\n';
            return 0;
        }
        s = to_string(sum);
    }
    cout << "IGEN\n";
    return 0;
}
