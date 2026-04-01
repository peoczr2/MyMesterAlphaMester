/*
 * Megkeressük azokat a számrendszer-alapokat, amelyekben az A szám számjegyösszege S.
 
Hint 1: || Egy adott alapban a számjegyösszeget egyszerűen megkapod, ha ismételten veszed a maradékot és osztasz az alappal. ||
Hint 2: || Mivel az alap legfeljebb `A+1`, a teljes keresési tartomány kicsi; végigpróbálhatod az összes lehetséges alapot. ||
*/

#include "../common.hpp"

static int digit_sum_base(int a, int base) {
    int sum = 0;
    while (a) {
        sum += a % base;
        a /= base;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, s;
    cin >> a >> s;
    vector<int> ans;
    for (int base = 2; base <= a + 1; ++base) {
        if (digit_sum_base(a, base) == s) ans.push_back(base);
    }
    if (ans.empty()) {
        cout << 0 << '\n';
    } else {
        for (int i = 0; i < (int)ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
