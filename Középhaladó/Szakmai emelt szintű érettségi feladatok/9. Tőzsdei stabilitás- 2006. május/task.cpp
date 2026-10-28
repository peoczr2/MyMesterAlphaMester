/*
Megoldás lényege:
Egy cég stabilitásösszege a szomszédos napok záróárfolyam-különbségei abszolút értékeinek összege, vagyis az M-1 darab |p[j] - p[j-1]| érték összege. A bemenetet cégenként olvassuk: beolvassuk a cég nevét, majd az árfolyamokat egyesével, és közben már számoljuk a stabilitásösszeget úgy, hogy csak az előző napi árat tartjuk meg, a teljes árfolyamsort nem. A neveket és a stabilitásösszegeket egy vektorba tesszük; az első részfeladat eredménye ezek minimuma. A második részfeladatban a legkisebb összeget elérő cégek kerülnek a kimenetbe a bemenet sorrendjében: előbb a darabszámuk, majd a nevük szóközzel elválasztva. Az időigény O(N * M), ami legfeljebb 150 * 750 beolvasott szám, a memóriaigény pedig O(N).
*/
/*
Hint 1: || Az első részfeladathoz nem kell az egész árfolyamtáblázatot tárolni: cégenként a szomszédos napok különbségeit egyetlen ciklusban összegezheted, miközben olvasod az árakat. ||
Hint 2: || Egy vektorban tartsd a cégneveket és a hozzájuk tartozó összegeket, keresd meg a legkisebb összeget, majd egy újabb végigmenéssel gyűjtsd ki azokat a neveket, amelyek összege ugyanennyi. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> names(n);
    vector<long long> sums(n, 0);

    for (int i = 0; i < n; i++) {
        cin >> names[i];
        long long prev;
        cin >> prev;
        for (int j = 1; j < m; j++) {
            long long cur;
            cin >> cur;
            sums[i] += abs(cur - prev);
            prev = cur;
        }
    }

    long long best = *min_element(sums.begin(), sums.end());

    cout << "#\n" << best << "\n";

    vector<string> winners;
    for (int i = 0; i < n; i++) {
        if (sums[i] == best) winners.push_back(names[i]);
    }

    cout << "#\n" << winners.size() << "\n";
    for (size_t i = 0; i < winners.size(); i++) {
        if (i > 0) cout << ' ';
        cout << winners[i];
    }
    cout << "\n";

    return 0;
}
