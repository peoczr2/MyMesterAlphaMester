/*
Időjárási csúcsok (= Nemes Tihamér 2018/19, 2. forduló, 2. korcsoport, 1. feladat)

Feladat: N nap déli hőmérséklete alapján meg kell számolni, hány olyan [l,r] időszak van, amelyben
pontosan K lokálisan meleg és L lokálisan hideg nap van.

Megoldás lényege:
A meleg és hideg napokat egyszer, a teljes sorozaton jelöljük meg: egy nap meleg, ha mindkét
szomszédjánál melegebb, hideg, ha mindkettőnél hidegebb (az első és az utolsó nap egyik sem).
Az időszak végpontjai is számítanak, ha a teljes sorozatban csúcsok: a mintában például [1,8] jó,
pedig a 8. nap hideg.
Így elég két 0/1 sorozat: hot[i] és cold[i]. Ha prefHot és prefCold ezek prefixösszegei, akkor
[l,r] pontosan akkor jó, ha prefHot[r]-prefHot[l-1] = K és prefCold[r]-prefCold[l-1] = L, azaz
(prefHot[l-1], prefCold[l-1]) = (prefHot[r]-K, prefCold[r]-L). Az r-rel balról jobbra haladva egy
hash map tárolja, melyik prefixpár hányszor fordult elő eddig (az üres prefix (0,0) is), és minden
r-nél hozzáadjuk a keresett pár darabszámát. A pár egyetlen 64 bites kulcsba van kódolva.
A válasz akár ~N^2/2 is lehet, ezért long long.

Időigény: O(N), memória: O(N).
*/
/*
Hint 1: || Először jelöld meg az egész sorozatban, mely napok melegek és melyek hidegek – ez nem függ a vizsgált időszaktól (a végpontok is számítanak, lásd a mintában az [1,8] időszakot). Hogyan kapod meg O(1)-ben egy [l,r] időszak meleg napjainak számát? ||
Hint 2: || Prefixösszeg: [l,r] pontosan akkor jó, ha a meleg napok prefixösszegének különbsége K, a hidegeké pedig L, vagyis rögzített r-hez olyan l−1 kell, amelynek prefixpárja (prefHot[r] − K, prefCold[r] − L). ||
Hint 3: || Menj végig r-rel 1-től N-ig, és egy hash map-ben számold, melyik prefixpár hányszor fordult elő eddig (kezdetben a (0,0) egyszer); minden r-nél add a válaszhoz a keresett pár darabszámát. A válasz long long! ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, needHot, needCold;
    cin >> n >> needHot >> needCold;
    vector<int> h(n + 1);
    for (int i = 1; i <= n; ++i) cin >> h[i];

    vector<int> hot(n + 1, 0), cold(n + 1, 0);
    for (int i = 2; i <= n - 1; ++i) {
        hot[i] = (h[i] > h[i - 1] && h[i] > h[i + 1]);
        cold[i] = (h[i] < h[i - 1] && h[i] < h[i + 1]);
    }

    vector<int> prefHot(n + 1, 0), prefCold(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prefHot[i] = prefHot[i - 1] + hot[i];
        prefCold[i] = prefCold[i - 1] + cold[i];
    }

    unordered_map<unsigned long long, long long> count;
    count.reserve(2 * n + 1);
    // a (meleg, hideg) párt egy 64 bites kulcsba kódoljuk; előjel nélkül, mert a W[r]-K negatív is lehet
    auto encode = [](int a, int b) -> unsigned long long {
        return (static_cast<unsigned long long>(static_cast<unsigned int>(a)) << 32) | static_cast<unsigned int>(b);
    };

    long long answer = 0;
    count[encode(0, 0)] = 1;
    for (int right = 1; right <= n; ++right) {
        unsigned long long key = encode(prefHot[right] - needHot, prefCold[right] - needCold);
        auto it = count.find(key);
        if (it != count.end()) answer += it->second;
        count[encode(prefHot[right], prefCold[right])]++;
    }

    cout << answer << '\n';
    return 0;
}