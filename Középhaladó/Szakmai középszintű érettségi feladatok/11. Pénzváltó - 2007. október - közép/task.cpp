/*
Megoldás lényege:
A valuták azonosítóit (három kisbetű) és forint-értékeit egy asszociatív tömbbe (map) tesszük, így bármelyik azonosító árfolyama O(log N) idő alatt megtalálható. Minden tranzakciónál kikeressük a valuta árfolyamát, és megszorozzuk az átváltandó mennyiséggel; a kiírás a bemenet sorrendjében történik. Egy szorzat legfeljebb 1000 * 1 000 000 = 10^9, a biztonság kedvéért long long típust használunk. Az időigény O(N log N + M log N), ahol N legfeljebb 10 és M legfeljebb 5000, a memóriaigény O(N).
*/
/*
Hint 1: || Minden tranzakcióhoz a valuta azonosítója alapján kell megkeresni a forintértékét. Olyan adatszerkezetet válassz, amelyben szöveges kulcs alapján lehet keresni. ||
Hint 2: || Használj map<string, long long>-ot: az N valuta beolvasása után az M tranzakciónál a kulcs alapján kérd le az árfolyamot, és szorozd meg a mennyiséggel. A szorzat már egy sorban kiírható. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    map<string, long long> rate;
    for (int i = 0; i < n; i++) {
        string code;
        long long e;
        cin >> code >> e;
        rate[code] = e;
    }

    for (int j = 0; j < m; j++) {
        string code;
        long long t;
        cin >> code >> t;
        cout << rate[code] * t << "\n";
    }

    return 0;
}
