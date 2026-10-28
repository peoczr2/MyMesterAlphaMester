/*
Megoldás lényege:
Kezdetben minden hely pontosan egy konténert tartalmaz, és az N+1. hely üres. Az üres helyet egyetlen átrakással egy mezővel odébb lehet vinni, így a konténerek sorrendje nem változik, és az üres hely tetszőleges helyre eljuttatható. Két egymás melletti, fordított sorrendű konténer (a bal oldali a nagyobb, mint a jobb oldali b) cseréje az üres hely segítségével négy lépésben megoldható: b átmegy az üres helyre, a átmegy a most üres helyre, b ráteszi magát a-ra (mert a > b), végül b balra lép a helyére. Ezt buborékrendezéssel ismételjük: a konténereket sorrendben tartjuk nyilván, és minden cseréhez az üres helyet a csere két konténere mögé visszük. Az üres hely mozgatása egy-egy lépés, így egy menet O(N) lépés, a cserék száma legfeljebb N*(N-1)/2, az időigény és a kimenet hossza O(N^2).
*/
/*
Hint 1: || Kezdetben minden hely egy konténert tartalmaz, és az N+1. hely üres. Egy átrakással az üres helyet egy mezővel odébb lehet vinni, így a konténerek sorrendje változatlan marad, de az üres hely bárhová eljuttatható. ||
Hint 2: || Ha a bal oldali a konténer nagyobb, mint a jobb oldali b, akkor a két konténer cseréje az üres hely segítségével megoldható. A cserénél b csak olyan konténerre rakható, amelynek mérete nagyobb nála, ezért a két konténer cseréjéhez éppen a > b kell. ||
Hint 3: || A két konténer legyen közvetlenül egymás mellett, az üres hely pedig a jobb oldali b után. Ekkor b jobbra az üres helyre, a jobbra, b visszafelé ráteszi magát a-ra, végül b balra kerül a helyére. Buborékrendezésnél a párokat balról jobbra haladva vizsgáld, és az üres helyet mindig a következő pár mögé vidd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // seq: a konténerek mérete a helyek sorrendjében (az üres helyet nem tartalmazza)
    // h: az üres hely a seq első h eleme után van, azaz az üres hely sorszáma h+1
    vector<int> seq(n);
    for (int i = 0; i < n; i++) cin >> seq[i];
    int h = n;

    vector<pair<int, char>> ops;  // egy művelet: (hely, irány)

    // Az üres helyet a target pozícióba viszi: minden lépésben egy szomszédos konténer átkerül
    auto holeTo = [&](int target) {
        while (h < target) {
            // a seq[h] konténer (hely: h+2) balra lép az üres helyre (h+1)
            ops.push_back({h + 2, 'B'});
            h++;
        }
        while (h > target) {
            // a seq[h-1] konténer (hely: h) jobbra lép az üres helyre (h+1)
            ops.push_back({h, 'J'});
            h--;
        }
    };

    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int k = 0; k + 1 < n; k++) {
            if (seq[k] < seq[k + 1]) continue;
            // a = seq[k] > b = seq[k+1]: a helyei k+1 és k+2, az üres hely a k+3. hely
            holeTo(k + 2);
            int i = k + 1;  // a helye
            ops.push_back({i + 1, 'J'});  // b az üres helyre (i+2 -> i+3)
            ops.push_back({i, 'J'});      // a az i+1. helyre
            ops.push_back({i + 2, 'B'});  // b a-ra kerül (a > b)
            ops.push_back({i + 1, 'B'});  // b az i. helyre
            swap(seq[k], seq[k + 1]);
            swapped = true;
        }
    }

    // végül az üres hely a sor végére kerül
    holeTo(n);

    for (auto& op : ops) {
        cout << op.first << ' ' << op.second << '\n';
    }
    return 0;
}
