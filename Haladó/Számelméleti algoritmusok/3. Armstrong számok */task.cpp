/*
 * N-jegyű Armstrong-számok keresése. Az összes N hosszúságú számjegy-multihalmazt
 * végigpróbáljuk, és ellenőrizzük, hogy a számjegyek N-edik hatványainak összege
 * visszaadja-e ugyanazt a számot.
 
Hint 1: || A számjegyek N-edik hatványait érdemes előre kiszámolni 0..9-re, mert sokszor kell majd őket összeadni. ||
Hint 2: || Nem muszáj az összes N-jegyű számot végignézni: elég a számjegy-multihalmazokat vizsgálni, és megnézni, visszakapod-e ugyanazt a számjegyeloszlást. ||
*/

#include "../common.hpp"

static long long pow_digit(int d, int n) {
    long long result = 1;
    for (int i = 0; i < n; ++i) result *= d;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> p(10);
    for (int d = 0; d <= 9; ++d) p[d] = pow_digit(d, n);

    vector<long long> answers;
    vector<int> cnt(10);

    function<void(int,int)> dfs = [&](int digit, int left) {
        if (digit == 10) {
            if (left != 0) return;
            long long sum = 0;
            for (int d = 0; d <= 9; ++d) sum += 1LL * cnt[d] * p[d];
            string s = to_string(sum);
            if ((int)s.size() != n || s[0] == '0') return;
            vector<int> got(10);
            for (char c : s) got[c - '0']++;
            if (got == cnt) answers.push_back(sum);
            return;
        }
        for (int take = 0; take <= left; ++take) {
            cnt[digit] = take;
            dfs(digit + 1, left - take);
        }
        cnt[digit] = 0;
    };

    dfs(0, n);
    sort(answers.begin(), answers.end());
    answers.erase(unique(answers.begin(), answers.end()), answers.end());
    for (long long x : answers) cout << x << '\n';
    return 0;
}
