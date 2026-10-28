/*
Megoldás lényege:
Az emelkedő kétféle lehet: az oda-úton balról jobbra szigorúan nő a sorozat, a visszaúton pedig balról jobbra szigorúan csökken (visszafelé olvasva ez már emelkedő). Mindkét esetben egyetlen balról jobbra haladó bejárással megkeressük a maximális hosszúságú, összefüggő, szigorúan monoton szakaszt. Holtverseny esetén az oda-úti emelkedő a korábbi, a visszaútiak között pedig a nagyobb sorszámú kezdőpontú az, amelyet a hegymászó előbb ér el. Ha a két irány leghosszabb emelkedője egyenlő hosszú, az oda-úti nyer. Az időigény O(N), a futamok hossza legalább 2.
*/
/*
Hint 1: || Két külön esetet kell kezelni: a szomszédos elemek szigorú növekedését az oda-úton, és a szigorú csökkenésüket a visszaúton. ||
Hint 2: || Elég egyszer végigmenni a sorozaton, és a szomszédos elemek összehasonlításával követni az aktuális futam hosszát. Ha a feltétel megszakad, új futam kezdődik. ||
Hint 3: || A visszaúti emelkedő kezdőpontja a nagyobb sorszámú szél, a végpontja a kisebb. Kiírás előtt döntsd el, melyik irány leghosszabb emelkedője a hosszabb. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> v(n);
    for (auto &x : v) cin >> x;

    // oda-út: szigorúan növekvő maximális futamok, a legkorábbi a leghosszabb
    int upLen = 0, upL = 0, upR = 0;
    int i = 0;
    while (i < n) {
        int j = i;
        while (j + 1 < n && v[j + 1] > v[j]) j++;
        if (j > i && j - i + 1 > upLen) {
            upLen = j - i + 1;
            upL = i + 1;
            upR = j + 1;
        }
        i = j + 1;
    }

    // visszaút: szigorúan csökkenő maximális futamok, a nagyobb sorszámú a leghosszabb
    int downLen = 0, downL = 0, downR = 0;
    i = 0;
    while (i < n) {
        int j = i;
        while (j + 1 < n && v[j + 1] < v[j]) j++;
        if (j > i && j - i + 1 >= downLen) {
            downLen = j - i + 1;
            downL = i + 1;
            downR = j + 1;
        }
        i = j + 1;
    }

    if (upLen == 0 && downLen == 0) {
        cout << -1 << "\n";
    } else if (upLen >= downLen) {
        cout << upL << " " << upR << "\n";
    } else {
        cout << downR << " " << downL << "\n";
    }
    return 0;
}
