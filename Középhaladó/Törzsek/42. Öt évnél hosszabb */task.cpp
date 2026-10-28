/*
Megoldás lényege:
Egy háború hosszát a kezdő- és a befejező év alapján számoljuk, és mindkét évet beleszámítjuk: a háború hossza befejező év - kezdőév + 1 év. Ez a szabály illeszkedik a mintához: az 1770-1775 közötti háború 6 évnyi, ezért O = 5 mellett már számít. Egyetlen menetben végigmegyünk a K háborún, és megszámoljuk azokat, amelyek hossza nagyobb O-nál. Az időigény O(K), ami K <= 2000 mellett elhanyagolható.
*/
/*
Hint 1: || Egy háború hosszához csak a kezdő- és a befejező évre van szükség, a törzsek sorszámai a számoláshoz nem kellenek. ||
Hint 2: || A háború hossza a befejező év és a kezdő év különbsége plusz egy, mert mindkét év része a háborús időszaknak. Ezt kell összehasonlítani O-val. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 4>> haboru(k);
    for (auto &h : haboru)
        cin >> h[0] >> h[1] >> h[2] >> h[3];
    int o;
    cin >> o;

    int db = 0;
    for (const auto &h : haboru) {
        int hossz = h[3] - h[2] + 1;
        if (hossz > o) db++;
    }
    cout << db << "\n";
    return 0;
}
