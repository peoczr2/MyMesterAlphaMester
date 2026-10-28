/*
Megoldás lényege:
Mivel a napi jövedelmek nemnegatívak, egy szakasz összege nő, ha hosszabbítjuk. Kétmutatós technikát használunk:
a jobb végpontot a napokon végigvisszük, és az aktuális szakasz összegét nyilvántartjuk. Ha a bal végpont
elhagyása után az összeg még eléri F-et, a bal végpontot előrébb léptetjük. Így minden jobb végpontra
a legrövidebb, F-et elérő szakasz adódik. A legrövidebb szakaszt szigorú összehasonlítással tartjuk meg, így
azonos hossz esetén az korábban kezdődő szakasz marad. Minden nap legfeljebb egyszer lép be és ki a szakaszból,
ezért az idő O(N).
*/
/*
Hint 1: || A jövedelmek nemnegatívak, ezért ha egy szakaszt meghosszabbítasz, az összege nem csökken. Ez elég ahhoz, hogy a bal végpontot csak előre mozgasd. ||
Hint 2: || Tartsd nyilván az aktuális szakasz összegét. Minden új jobb végpontnál add hozzá a jövedelmet, majd amíg a bal szél elhagyása után is eléri F-et az összeg, léptesd a bal végpontot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long f;
    cin >> n >> f;
    vector<long long> jov(n);
    for (long long& x : jov) cin >> x;

    int legrovidebb = INT_MAX, bal = -1, jobb = -1;
    long long osszeg = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        osszeg += jov[r];
        // Ha a bal szél elhagyása után is eléri F-et a szakasz, a bal végpont léphet előre.
        while (l < r && osszeg - jov[l] >= f) {
            osszeg -= jov[l];
            l++;
        }
        if (osszeg >= f) {
            int hossz = r - l + 1;
            if (hossz < legrovidebb) {
                legrovidebb = hossz;
                bal = l;
                jobb = r;
            }
        }
    }

    if (bal == -1) cout << "-1 -1\n";
    else cout << bal + 1 << " " << jobb + 1 << "\n";
    return 0;
}
