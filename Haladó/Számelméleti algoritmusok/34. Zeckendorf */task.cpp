/*
Megoldás lényege:
A Zeckendorf-tétel szerint minden természetes szám egyértelműen felírható nem szomszédos Fibonacci-számok összegeként.
Ezt mohó módszerrel kapjuk meg: mindig a legnagyobb, N-nél nem nagyobb Fibonacci-számot vesszük le, majd a maradékkal ugyanígy folytatjuk.
Ha F_k a legnagyobb N-nél nem nagyobb Fibonacci-szám, akkor a maradék kisebb F_{k-1}-nél, ezért a következő kiválasztott tag indexe legalább 2-vel kisebb lesz.
A Fibonacci-számok exponenciálisan nőnek, így N ≤ 10^7 esetén legfeljebb néhány tucat tagot kell kezelni.
A mohó sorrend miatt a tagokat csökkenő sorrendben kapjuk, ezért a kiírás előtt megfordítjuk őket.
Időigény: O(log N).
*/
/*
Hint 1: || Zeckendorf-felbontásnál mindig a legnagyobb, még elférő Fibonacci-számot érdemes levenni. ||
Hint 2: || Generáld le a Fibonacci-számokat N-ig, majd a legnagyobbtól kezdve válassz mohón, és a végén a felhasznált tagokat növekvő sorrendben írd ki. ||
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
    reverse(parts.begin(), parts.end());
    for (int i = 0; i < (int)parts.size(); ++i) {
        if (i) cout << ' ';
        cout << parts[i];
    }
    cout << '\n';
    return 0;
}
