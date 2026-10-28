/*
Megoldás lényege:
A végzési évekhez azt kell tudni, melyik végzett a legidősebb. A pontos végzési dátum nincs megadva, ezért a végzés évében
betöltött kor mindig a végzési év és a születési év különbsége. Így minden évhez elég a legkisebb születési évet tárolni,
a születési hónap és nap a kor értékén nem változtat. A végzési éveket map-ban tároljuk, így a kiíráskor a kulcsok már
rendezve vannak, és visszafelé, csökkenő sorrendben írhatjuk ki őket. Az időigény O(N log N).
*/
/*
Hint 1: || A kor csak a végzési évtől és a születési évtől függ, így minden végzési évhez elég a legkisebb születési évet megtalálni. ||
Hint 2: || Használj map-et: a kulcs a végzési év, az érték a legkisebb születési év. A map kulcsai rendezve maradnak, a kiíráskor visszafelé járd be. ||
Hint 3: || Először az évek számát írd ki, utána évenként a végzési évet és a legidősebb korát. A hónap és a nap ebben a feladatban nem változtatja a kiírt kort. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // végzési év -> a legidősebb végzett születési éve
    map<int, int> oldestBorn;
    for (int i = 0; i < n; i++) {
        int bornYear, bornMonth, bornDay, startYear, gradYear;
        cin >> bornYear >> bornMonth >> bornDay >> startYear >> gradYear;
        if (!oldestBorn.count(gradYear) || bornYear < oldestBorn[gradYear]) {
            oldestBorn[gradYear] = bornYear;
        }
    }

    cout << oldestBorn.size();
    // csökkenő sorrend: a map végétől indulunk
    for (auto it = oldestBorn.rbegin(); it != oldestBorn.rend(); ++it) {
        cout << ' ' << it->first << ' ' << it->first - it->second;
    }
    cout << '\n';
    return 0;
}
