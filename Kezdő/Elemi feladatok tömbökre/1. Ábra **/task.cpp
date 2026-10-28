/*
Megoldás lényege:
Az ábra x- és y-tengelyre is szimmetrikus, ezért a középpontja a fehér pontok legkisebb és legnagyobb sor-, illetve oszlopindexének összegének a fele. Legyen R a sorindexek legkisebb és legnagyobb értékének összege, C pedig az oszlopindexeké. Az (r, c) pont tükörképei ekkor (R-r, c), (r, C-c) és (R-r, C-c), és ezek az eredeti ábrán mind ugyanolyan színűek, mint az (r, c) pont. A sérült képen ezért a négy (esetleg egybeeső) pont fehér darabszámából döntünk: legalább 3 fehér esetén az eredeti szín fehér, legfeljebb 1 esetén fekete, pontosan 2 esetén nem dönthető el (k). A befoglaló téglalapon kívüli pontok mindig feketék. Pontonként állandó munka van, így az összidő O(N*M).
*/
/*
Hint 1: || Keresd meg a sérült kép fehér pontjaiból a legkisebb és a legnagyobb sor- és oszlopindexet: ezek adják az ábra befoglaló téglalapját, és ennek közepe lesz a szimmetria középpontja. ||
Hint 2: || Egy (r, c) pont tükörképei a középpontra vett tükrözésekkel: (R-r, c), (r, C-c) és (R-r, C-c), ahol R és C a befoglaló téglalap sor-, illetve oszlopindexeinek összege. Ezek a pontok az eredeti ábrán ugyanolyan színűek, mint (r, c). ||
Hint 3: || Számold meg, hány fehér pont van a négy tükörkép között (az (r, c) pontot is beleértve). Legalább 3 fehér esetén az eredeti szín fehér, legfeljebb 1 esetén fekete, pontosan 2 esetén a kiírandó betű k. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (auto &sor : a) cin >> sor;

    // a fehér pontok befoglaló téglalapja
    int minR = n, maxR = -1, minC = m, maxC = -1;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            if (a[r][c] == '1') {
                minR = min(minR, r);
                maxR = max(maxR, r);
                minC = min(minC, c);
                maxC = max(maxC, c);
            }

    int R = minR + maxR;   // a sorok tükrözésének összege
    int C = minC + maxC;   // az oszlopok tükrözésének összege

    for (int r = 0; r < n; r++) {
        string kimenet(m, '0');
        for (int c = 0; c < m; c++) {
            // a befoglaló téglalapon kívül minden pont fekete
            if (r < minR || r > maxR || c < minC || c > maxC) continue;

            bool feher = a[r][c] == '1';
            int darab = (a[r][c] == '1') + (a[R - r][c] == '1')
                      + (a[r][C - c] == '1') + (a[R - r][C - c] == '1');
            if (darab == 2)
                kimenet[c] = 'k';
            else if (darab > 2)
                kimenet[c] = feher ? '1' : 'p';
            else
                kimenet[c] = feher ? 'z' : '0';
        }
        cout << kimenet << "\n";
    }
    return 0;
}
