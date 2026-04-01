/*
 * Zeckendorf-felbontás: a legnagyobb lehetséges Fibonacci-számokat választjuk.
 
Hint 1: || Zeckendorf-felbontásnál mindig a legnagyobb, még elférő Fibonacci-számot érdemes levenni. ||
Hint 2: || Generáld le a Fibonacci-számokat N-ig, majd hátulról greedyn válassz, és a végén növekvő sorrendben írd ki a felhasznált tagokat. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> fib = {1, 2};
    while (fib.back() <= n) fib.push_back(fib[fib.size()-1] + fib[fib.size()-2]);
    vector<int> parts;
    for (int i = (int)fib.size()-1; i >= 0; --i) {
        if (fib[i] <= n) {
            parts.push_back(fib[i]);
            n -= fib[i];
        }
    }
    for (int i = 0; i < (int)parts.size(); ++i) {
        if (i) cout << ' ';
        cout << parts[i];
    }
    cout << '\n';
    return 0;
}
