/*
Megoldás lényege:
Egy szakasz az előző megálló indulásától a következő megálló érkezéséig tart, így az ideje az érkezési idő mínusz az előző indulási idő (a 0. állomás indulási ideje 0). A szakasz sebessége a távolság osztva ezzel az idővel. A legkisebb sebességű szakasz megkereséséhez a törteket nem osztással, hanem keresztbe szorzással hasonlítjuk össze egész számokkal, így nincs lebegőpontos pontatlanság. A szigorú < összehasonlítás miatt egyenlőség esetén a korábbi szakasz marad meg. Egy menetben, O(N) időben megoldható.
*/
/*
Hint 1: || Egy szakasz ideje az adott megálló érkezési ideje mínusz az előző megálló indulási ideje. Az induló állomásról a 0. percben indul a villamos. ||
Hint 2: || A sebesség távolság osztva idővel. Két szakasz sebességét úgy vesd össze, hogy a első távolságot a második idővel, a második távolságot az első idővel szorzod, és így a kisebb sebességet egész számokkal eldöntöd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long prevDep = 0;  // a 0. állomásról a 0. percben indul a villamos
    long long bestDist = 0, bestTime = 0;
    int bestFrom = 0, bestTo = 0;
    for (int i = 1; i <= n; i++) {
        long long dist, arr, dep;
        cin >> dist >> arr >> dep;
        long long time = arr - prevDep;
        // dist/time < bestDist/bestTime  <=>  dist*bestTime < bestDist*time
        if (i == 1 || dist * bestTime < bestDist * time) {
            bestDist = dist;
            bestTime = time;
            bestFrom = i - 1;
            bestTo = i;
        }
        prevDep = dep;
    }

    cout << bestFrom << ' ' << bestTo << '\n';
    return 0;
}
