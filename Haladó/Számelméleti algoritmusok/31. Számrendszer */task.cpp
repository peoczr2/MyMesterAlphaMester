/*
Megoldás lényege:
Az A szám b alapú számjegyösszegét úgy kapjuk, hogy ismételten vesszük az aktuális szám b-vel való osztási maradékát, majd A-t b-vel osztjuk, amíg A nulla nem lesz.
Mivel az alapszám legfeljebb A+1 lehet, a 2 és A+1 közötti összes alapot végigpróbáljuk, és kiírjuk azokat, amelyekben a számjegyösszeg pontosan S.
Az alapokat növekvő sorrendben vizsgáljuk, így a kiírás is növekvő lesz; ha nincs találat, 0-t írunk.
Az időigény O(A log A), ami A ≤ 32767 esetén bőven belefér az időlimitbe.
*/
/*
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
