/*
 * Nagyonprímek keresése DFS-sel. Minden prefixnek prímnek kell lennie.
 
Hint 1: || Nagyonprím számot balról jobbra lehet felépíteni, mert minden prefixnek is prímnek kell maradnia. ||
Hint 2: || Indulj az egyjegyű prímekből, és DFS-sel csak olyan számjegyet fűzz mögéjük, amely után az új prefix is prím marad. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    auto primes = sieve_primes(100000);
    vector<int> first = {2, 3, 5, 7};
    vector<int> digits = {1, 3, 7, 9};

    function<void(int,string)> dfs = [&](int len, string cur) {
        if ((int)cur.size() == len) {
            for (int i = 1; i <= len; ++i) {
                if (i > 1) cout << ' ';
                cout << cur.substr(0, i);
            }
            cout << '\n';
            return;
        }
        for (int d : digits) {
            string nxt = cur + char('0' + d);
            if (is_prime_int(stoll(nxt), primes)) dfs(len, nxt);
        }
    };

    if (n == 1) {
        for (int p : first) cout << p << '\n';
        return 0;
    }
    for (int p : first) {
        string start = to_string(p);
        dfs(n, start);
    }
    return 0;
}
