/*
Megoldás lényege:
Azokon a kérdéseken, ahol a két válasz megegyezik, a két pontszám együtt nő vagy marad, és ezek közül
x darabon mindketten jól válaszoltatok. A különböző válaszú kérdések számát d jelöli: ezeken pontosan az
egyikőtök lehetett jól, így a barátod y darab ilyen kérdésen kapott pontot, a tiéd pedig d − y darabon.
A barátod pontszáma így x + y = P, a tiéd pedig x + (d − y) = 2x + d − P. Az x értéke csak az egyező
kérdések számával (s) és a feltételekkel korlátozott: 0 ≤ x ≤ s és 0 ≤ P − x ≤ d. A minimumot és a maximumot
a két szélső x értékből számoljuk ki. Az időigény O(N), ami a bemenet beolvasásából adódik.
*/
/*
Hint 1: || Vizsgáld külön azokat a kérdéseket, ahol a két válasz megegyezik, és azokat, ahol különböznek. Egy különböző válaszú kérdésen pontosan az egyikőtök kaphatott pontot. ||
Hint 2: || Jelölje x azoknak az egyező válaszú kérdéseknek a számát, amelyeken mindketten jól válaszoltatok, y pedig azoknak a különböző válaszú kérdéseknek a számát, amelyeken a barátod jól válaszolt. Ekkor a barátod pontja x + y, a tiéd pedig a különböző kérdések maradék részével együtt adódik. ||
Hint 3: || Az x-re két korlát adódik: nem lehet nagyobb az egyező kérdések számánál, és y = P − x nem lehet negatív vagy nagyobb a különböző kérdések számánál. A két szélső x értékből számold ki a minimumot és a maximumot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    cin >> n >> p;
    string bob, mine;
    cin >> bob >> mine;

    int same = 0, diff = 0;
    for (int i = 0; i < n; i++) {
        if (bob[i] == mine[i]) {
            same++;
        } else {
            diff++;
        }
    }

    // x: az egyező válaszú kérdések közül azok száma, amelyeken mindketten jól válaszoltatok.
    int xMin = max(0, p - diff);
    int xMax = min(same, p);

    int minScore = 2 * xMin + diff - p;
    int maxScore = 2 * xMax + diff - p;

    cout << minScore << ' ' << maxScore << '\n';
    return 0;
}
