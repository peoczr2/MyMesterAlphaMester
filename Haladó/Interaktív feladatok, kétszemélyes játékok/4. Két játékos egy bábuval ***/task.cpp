/*
Megoldás lényege:
A játék állapotát a bábu helye és az határozza meg, hogy melyik játékos következik. A bábu csak jobbra vagy lefelé mozog, ezért az állapotokat a jobb alsó sarokból kiindulva, visszafelé lehet kiszámolni. Legyen A(i,j) az első játékos legjobb jövőbeli pontszáma, ha a bábu az (i,j) mezőn áll és ő lép, B(i,j) pedig ugyanez, ha a második játékos lép. Az első játékos a jobbra vagy lefelé eső mezők közül azt választja, ahol a mező értéke plusz B értéke a nagyobb; a második játékos a két jelölt közül azt, ahol A kisebb. A jobb alsó sarokban az érték 0. A táblázat O(N^2) idő alatt kiszámolható, a játékban pedig mindig a táblázat szerint jobb lépést tesszük, az ellenfél válaszát a GepLep adja. Az I/O a gep modulon keresztül történik, nem cin/cout-tal.
*/
/*
Hint 1: || A játék állapotát a bábu helye és az határozza meg, hogy melyik játékos következik. A bábu csak jobbra vagy lefelé mozog, így a végállapotokból visszafelé lehet számolni. ||
Hint 2: || Két tömb kell: A[i][j] és B[i][j]. Az első játékos lépése után a célmező értékéhez a B érték adódik, a második játékos lépése után pedig az A érték a célmezőn; a jobb alsó sarokban mindkettő 0. ||
Hint 3: || A tömböket i és j szerint csökkenő sorrendben töltsd ki, a játékban pedig mindig azt a lépést válaszd, ahol a célmező értéke plusz B értéke a legnagyobb. Az ellenfél lépését a GepLep adja, azt kövesd nyilván. ||
*/
#include "gep.h"
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n = Kezd();
    vector<vector<int>> v(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            v[i][j] = Mezo(i, j);

    // A[i][j]: az első játékos jövőbeli pontszáma, ha a bábu (i,j)-n áll és ő lép
    // B[i][j]: ugyanez, ha a második játékos lép
    vector<vector<int>> A(n, vector<int>(n, 0)), B(n, vector<int>(n, 0));
    for (int i = n - 1; i >= 0; i--)
        for (int j = n - 1; j >= 0; j--) {
            if (i == n - 1 && j == n - 1)
                continue;
            bool canDown = i + 1 < n, canRight = j + 1 < n;

            int bestA = -1000000000;
            if (canDown)
                bestA = max(bestA, v[i + 1][j] + B[i + 1][j]);
            if (canRight)
                bestA = max(bestA, v[i][j + 1] + B[i][j + 1]);
            A[i][j] = bestA;

            int bestB = 1000000000;
            if (canDown)
                bestB = min(bestB, A[i + 1][j]);
            if (canRight)
                bestB = min(bestB, A[i][j + 1]);
            B[i][j] = bestB;
        }

    int i = 0, j = 0;
    while (!(i == n - 1 && j == n - 1)) {
        bool canDown = i + 1 < n, canRight = j + 1 < n;
        char lep = 'L';
        int bestVal = -1000000000;
        if (canDown) {
            int c = v[i + 1][j] + B[i + 1][j];
            if (c > bestVal) {
                bestVal = c;
                lep = 'L';
            }
        }
        if (canRight) {
            int c = v[i][j + 1] + B[i][j + 1];
            if (c > bestVal) {
                bestVal = c;
                lep = 'J';
            }
        }
        Lep(lep);
        if (lep == 'L')
            i++;
        else
            j++;
        char masik = GepLep();
        if (masik == 'L')
            i++;
        else
            j++;
    }
    return 0;
}
