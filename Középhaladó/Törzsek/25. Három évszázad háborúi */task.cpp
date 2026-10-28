/*
Megoldás lényege:
A háborúkat századonként külön számoljuk. Egy háború egy századhoz tartozik, ha a kezdő- vagy a befejező éve benne van a század évtartományában (XVII.: 1601–1700, XVIII.: 1701–1800, XIX.: 1801–1900). Egy háború egy századhoz legfeljebb egyszer számít, akkor is, ha a kezdő- és a befejező éve ugyanabba a századba esik. Az időigény O(3·K), ami messze belefér az időkorlátba.
*/
/*
Hint 1: || Egy háború egy századba akkor is csak egyszer számít, ha a kezdő- és a befejező éve ugyanabba a századba esik. Ezért háborúnként és századonként elég egyetlen „benne van-e?” ellenőrzés. ||
Hint 2: || Tarts három számlálót, és minden háborúnál azokat a századokat növeld, amelyek tartományába a kezdő- vagy a befejező év esik: XVII. 1601–1700, XVIII. 1701–1800, XIX. 1801–1900. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 4>> haboru(k);
    for (auto &h : haboru)
        cin >> h[0] >> h[1] >> h[2] >> h[3];

    // Az évszázadok évtartománya: XVII., XVIII., XIX.
    const int kezd[3] = {1601, 1701, 1801};
    const int vege[3] = {1700, 1800, 1900};

    int szamlalo[3] = {0, 0, 0};
    for (const auto &h : haboru) {
        for (int c = 0; c < 3; ++c) {
            bool belep = (h[2] >= kezd[c] && h[2] <= vege[c]) || (h[3] >= kezd[c] && h[3] <= vege[c]);
            if (belep)
                ++szamlalo[c];
        }
    }
    cout << szamlalo[0] << " " << szamlalo[1] << " " << szamlalo[2] << "\n";
    return 0;
}
