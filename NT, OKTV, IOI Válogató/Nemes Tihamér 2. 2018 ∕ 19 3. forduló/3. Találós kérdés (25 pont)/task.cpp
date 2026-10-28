/*
Megoldás lényege:
A kérdések egy bináris fát alkotnak: a kérdések a belső csúcsok, a kitalálandók a levelek. A fát DFS-sel (veremmel) járjuk be, és menet közben számoljuk az út IGEN és NEM válaszainak számát. A levélben a címke az IGEN-ek és NEM-ek számának különbsége, ennek előfordulását hash-táblában gyűjtjük. A végén a legtöbbször előforduló címkét választjuk, döntetlennél a legkisebbet. Mivel N belső csúcs és N+1 levél van, az időigény O(N) (hash-táblával átlagosan).
*/
/*
Hint 1: || Nem kell tudni, melyik kérdéseken át jutottunk el egy kitalálandóhoz, csak az út IGEN és NEM válaszainak száma számít. Ezt a két számlálót bejárás közben, minden lépésnél növeld a megfelelő ágon. ||
Hint 2: || Ha egy sorszám N-nél nagyobb, az már kitalálandó: ott nem megyünk tovább, hanem a címke (IGEN-szám mínusz NEM-szám) gyakoriságát növeljük. Az eredményben a leggyakoribb címke kell; döntetlennél a kisebb címke. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> yes(2 * n + 2), no(2 * n + 2);
    for (int i = 1; i <= n; ++i) cin >> yes[i] >> no[i];

    unordered_map<int, int> freq;
    vector<tuple<int, int, int>> st;
    st.push_back({1, 0, 0});
    while (!st.empty()) {
        auto [u, y, nn] = st.back();
        st.pop_back();
        if (u > n) {
            ++freq[y - nn];
            continue;
        }
        st.push_back({yes[u], y + 1, nn});
        st.push_back({no[u], y, nn + 1});
    }

    int bestLabel = 0, bestCnt = -1;
    for (auto [lab, cnt] : freq) {
        if (cnt > bestCnt || (cnt == bestCnt && lab < bestLabel)) {
            bestCnt = cnt;
            bestLabel = lab;
        }
    }

    cout << bestLabel << ' ' << bestCnt << '\n';
    return 0;
}