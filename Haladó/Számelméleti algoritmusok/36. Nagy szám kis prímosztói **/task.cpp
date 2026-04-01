/*
 * A 2 és 40 közötti prímszámok közül kiválogatjuk azokat, amelyek osztják a
 * megadott hatalmas számot.
 
Hint 1: || Csak a 2 és 40 közötti prímszámokat kell vizsgálni, ez nagyon kevés jelölt. ||
Hint 2: || A hatalmas számot ne alakítsd át beépített típussá; minden jelölt prímre külön számold ki a maradékát karakterenként. ||
*/

#include "../common.hpp"

static bool divisible(const string& s, int mod) {
    int r = 0;
    for (char c : s) r = (r * 10 + (c - '0')) % mod;
    return r == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    vector<int> primes = {2,3,5,7,11,13,17,19,23,29,31,37};
    vector<int> ans;
    for (int p : primes) if (divisible(s, p)) ans.push_back(p);
    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
