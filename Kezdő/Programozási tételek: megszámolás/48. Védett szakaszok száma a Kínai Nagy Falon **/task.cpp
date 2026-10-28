/*
Megoldás lényege:
Az j-edik fal (az j-edik és a (j+1)-edik őrhely között) akkor védett, ha mindkét végén van őrség. Az őrségek helyét logikai tömbben tároljuk, így a falak állapota egyszerűen lekérdezhető.
Egy védett szakasz első falánál a szomszédos előző fal már nem védett (vagy nincs is), ezért elég azokat a védett falakat megszámolni, amelyek előtt a szomszédos fal nem védett.
Egy balról jobbra haladó bejárásban az előző fal állapotát egy logikai változóban követjük.
Az időigény O(N), a tárigény O(N).
*/
/*
Hint 1: || Minden védett szakasz legalább egy védett fallal kezdődik. A szakaszok számát úgy kapod meg, ha megszámolod a kezdő falakat: azokat a védett falakat, amelyek előtt a szomszédos fal nem védett. ||
Hint 2: || Egy fal (az j-edik és a (j+1)-edik őrhely között) akkor védett, ha mindkét végén van őrség. Az őrségek helyét logikai tömbben tárold, hogy a falak állapotát gyorsan le tudd kérdezni. ||
Hint 3: || A bejárás közben elég egy logikai változóban megjegyezni, hogy az előző fal védett volt-e. Ha az aktuális fal védett, de az előző nem, új szakasz kezdődött. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<bool> orseg(n + 2, false);
    for (int i = 0; i < m; i++) {
        int hely;
        cin >> hely;
        orseg[hely] = true;
    }
    int szakaszok = 0;
    bool elozo_vedett = false;
    for (int j = 1; j < n; j++) {
        bool vedett = orseg[j] && orseg[j + 1];
        if (vedett && !elozo_vedett) {
            szakaszok++;
        }
        elozo_vedett = vedett;
    }
    cout << szakaszok << endl;
    return 0;
}
