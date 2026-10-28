/*
Megoldás lényege:
Minden számhoz nyilvántartjuk az utolsó kisorsolásának napját, így minden ismétlődésnél megkapjuk a két egymást követő előfordulás közötti szakasz hosszát és kezdőnapját.
A hossz szerinti darabszám-tömbben számoljuk, hányszor fordult elő az egyes hosszúságú szakasz, és minden hosszhoz feljegyezzük az első ilyen szakasz kezdőnapját.
Mivel a napokat időrendben dolgozzuk fel, ugyanolyan hosszúságú szakaszok között a korábbi kezdőnap van előbb, így az első előfordulás adja a legkorábbit.
A válasz első sora a legnagyobb darabszám, a második sorba pedig a legkorábbi kezdőnap kerül azok közül a hosszúságok közül, amelyek ezt a darabszámot érik el.
Ha nem volt ismétlődés, csak a 0 kerül ki.
Az időigény O(N + M), ami az 0,1 mp-es limitbe bőven belefér.
*/
/*
Hint 1: || Minden számhoz tartsd nyilván az utolsó kisorsolásának napját. Egy ismétlődésnél a két nap különbsége adja a szakasz hosszát, ezt egy hossz szerinti darabszám-tömbben számold. ||
Hint 2: || Ha egy hosszúság első előfordulását észleled, jegyezd fel a szakasz kezdőnapját is. A napok időrendi feldolgozása miatt így az első előfordulás a legkorábbi kezdőnapot adja az adott hosszra. ||
Hint 3: || A végén keresd meg a legnagyobb darabszámot, majd a leggyakoribb hosszúságok közül a legkorábbi kezdőnapot. Ha a legnagyobb darabszám 0, csak a 0-t írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> last(m + 1, 0);
    vector<int> cnt(n + 1, 0);
    vector<int> firstStart(n + 1, 0);

    for (int day = 1; day <= n; ++day) {
        int x;
        cin >> x;
        if (last[x] != 0) {
            int d = day - last[x];
            if (cnt[d] == 0) firstStart[d] = last[x];
            ++cnt[d];
        }
        last[x] = day;
    }

    int best = 0;
    for (int d = 1; d <= n; ++d) {
        best = max(best, cnt[d]);
    }

    if (best == 0) {
        cout << 0 << '\n';
        return 0;
    }

    int start = INT_MAX;
    for (int d = 1; d <= n; ++d) {
        if (cnt[d] == best) start = min(start, firstStart[d]);
    }

    cout << best << '\n' << start << '\n';
    return 0;
}
