/*
 * Az lkktSzamlalo(n) értékek összege megegyezik azzal, hogy hány rendezett
 * párra teljesül lcm(a,b) <= N. Az egyes n-ek lcm-párszámát prímhatványos
 * faktorizálással számítjuk.
 
Hint 1: || Egy fix N-re a `lcm(a,b)=N` párok száma a prímtényezők kitevőiből külön-külön számolható. ||
Hint 2: || Ha `N = p1^e1 * ... * pk^ek`, akkor minden prímtényezőre `(2*ei+1)` lehetőség adódik, és ezeket össze kell szorozni. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> spf(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            if (1LL * i * i <= n) {
                for (int j = i * i; j <= n; j += i) if (!spf[j]) spf[j] = i;
            }
        }
    }
    vector<long long> ways(n + 1);
    ways[1] = 1;
    for (int x = 2; x <= n; ++x) {
        int y = x;
        long long value = 1;
        while (y > 1) {
            int p = spf[y] ? spf[y] : y;
            int e = 0;
            while (y % p == 0) {
                y /= p;
                ++e;
            }
            value *= (2 * e + 1);
        }
        ways[x] = value;
    }
    long long answer = 0;
    for (int x = 1; x <= n; ++x) answer += ways[x];
    cout << answer << '\n';
    return 0;
}
