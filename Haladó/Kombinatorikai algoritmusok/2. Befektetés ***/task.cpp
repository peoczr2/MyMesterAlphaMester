/*
   Befektetés: a befektetési összegek Zeckendorf-szerű felbontása kell.
   A kiválasztott évek a Fibonacci-sorozat indexei, a következő évre tolva
   pedig azonnal megkapjuk a második kért összeget.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long A;
    if (!(cin >> A)) return 0;

    vector<long long> fib = {1, 1};
    while (fib.back() <= A) fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);

    long long rem = A;
    vector<int> years;
    long long shifted = 0;
    for (int i = (int)fib.size() - 2; i >= 0; --i) {
        if (fib[i] <= rem) {
            rem -= fib[i];
            years.push_back(i + 1);
            shifted += fib[i + 1];
        }
    }

    reverse(years.begin(), years.end());
    for (int i = 0; i < (int)years.size(); ++i) {
        if (i) cout << ' ';
        cout << years[i];
    }
    cout << '\n' << shifted << '\n';
    return 0;
}