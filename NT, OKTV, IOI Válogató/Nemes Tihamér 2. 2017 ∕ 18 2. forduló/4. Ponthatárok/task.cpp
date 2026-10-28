/*
Megoldás lényege:
A ponthatár alatti, közvetlenül egymás után következő előforduló pontszámokat nézzük az első hiányzó pontszámig. Ha ez a blokk legfeljebb L hosszú, a ponthatár a blokk legalacsonyabb pontszámára csökken, különben a régi ponthatár marad. A pontszámok előfordulását egy jelölőtömbben tároljuk, és minden ponthatárnál lefelé megszámoljuk a blokk hosszát. Az időigény O(K + N).
*/
/*
Hint 1: || Az egyes ponthatároknál csak a közvetlenül alattuk lévő pontszámokat kell megnézni: a ponthatártól lefelé haladva az első hiányzó pontszámnál meg lehet állni. ||
Hint 2: || Jelöld be egy tömbben (0-tól K-ig), melyik pontszám fordul elő. Minden ponthatárnál számold meg a jelölt, egymást követő pontszámokat lefelé; ha ez a szám legfeljebb L, az új határ a legalacsonyabb ilyen pontszám. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, l;
    cin >> n >> k >> l;
    int kh, hh, nh, oh;
    cin >> kh >> hh >> nh >> oh;
    vector<char> seen(k + 1, 0);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        seen[x] = 1;
    }

    auto javit = [&](int t) {
        int cnt = 0;
        while (t - cnt - 1 >= 0 && seen[t - cnt - 1]) ++cnt;
        if (cnt > 0 && cnt <= l) return t - cnt;
        return t;
    };

    cout << javit(kh) << '\n' << javit(hh) << '\n' << javit(nh) << '\n' << javit(oh) << '\n';
    return 0;
}
