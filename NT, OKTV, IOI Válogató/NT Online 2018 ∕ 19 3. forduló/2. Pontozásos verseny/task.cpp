/*
Megoldás lényege:
Minden versenyzőnél azt kell megadni, hány korábbi versenyzőnél volt az ő pontszáma
magasabb, azaz hányan kaptak nála kevesebb pontot. A pontszámok 1 és 100 közé esnek,
ezért a korábbi pontszámok gyakoriságát egy tömbben tartjuk (freq[p] = hányan kaptak
p pontot). Egy új p pontos versenyzőnél az 1..p-1 pontszámok gyakoriságait összegezzük,
majd freq[p]-t eggyel növeljük. Versenyzőnként legfeljebb 99 összeadás van, így az
időigény O(N · 100).
*/
/*
Hint 1: || Egy versenyzőnél azt kell megszámolni, hány korábbi versenyzőnél volt az övé magasabb pontszám. Ehhez nem kell minden korábbi versenyzőt külön-külön vizsgálni: elég a pontszámok szerinti darabszámokat nyilvántartani. ||
Hint 2: || Mivel a pontszámok csak 1 és 100 között lehetnek, tárolj egy freq tömböt: freq[p] azt adja meg, hányan kaptak eddig p pontot. Egy új p pontos versenyzőnél a válasz a freq[1] + ... + freq[p-1] összeg, utána freq[p]-t növeld. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> freq(101, 0);
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        int ans = 0;
        for (int x = 1; x < p; ++x) ans += freq[x];
        cout << ans << '\n';
        ++freq[p];
    }
    return 0;
}
