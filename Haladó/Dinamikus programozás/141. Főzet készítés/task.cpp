/*
Megoldási ötlet:
Az a:b arány csak akkor különbözik egy másiktól, ha a tört egyszerűsített alakja különbözik. Ezért a kérdés pontosan az,
hány olyan (a,b) pár van 1≤a≤A, 1≤b≤B mellett, amelyre gcd(a,b)=1.

A és B legfeljebb 500, ezért előre kiszámítjuk minden rácspontban, hogy relatív prím-e, majd erre 2D prefixösszeget
építünk. Így egy kérdésre a válasz O(1)-ben kiolvasható.
*/
/*
Hint 1: || Azonos arányt ad például a 2:4 és az 1:2, tehát az egyszerűsített alak a lényeg. ||
Hint 2: || Pontosan azok az arányok különbözőek, ahol a két szám relatív prím. ||
Hint 3: || A kis korlát miatt előre fel lehet tölteni az összes 500×500 állapotot és prefixösszegezni. ||
*/

#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int limit = 500;
    vector<vector<int>> pref(limit + 1, vector<int>(limit + 1, 0));
    for (int a = 1; a <= limit; ++a) {
        for (int b = 1; b <= limit; ++b) {
            pref[a][b] = pref[a - 1][b] + pref[a][b - 1] - pref[a - 1][b - 1] + (gcd(a, b) == 1 ? 1 : 0);
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << pref[a][b] << '\n';
    }
    return 0;
}