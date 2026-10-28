/*
Megoldás lényege:
Egy megállóban a villamos nem áll meg, ha az érkezési és az indulási idő egyenlő, ezt a feltételt számoljuk. A 0. állomás nincs a bemenetben, a végállomás (N.) pedig a példa szerint nem számít bele, ezért csak az 1-től N-1-ig tartó sorszámokat vizsgáljuk. A távolságok nem szerepelnek a döntésben. A megállókat egyszer olvassuk be és számoljuk, így az időigény O(N).
*/
/*
Hint 1: || Egy megálló akkor marad ki a megállásból, ha az érkezési és az indulási idő megegyezik. A távolság ehhez nem kell. ||
Hint 2: || Olvasd be a megállókat sorban, és minden 1-től N-1-ig tartó sorszámra ellenőrizd az egyenlőséget. Az egyenlő esetek darabszámát egy számlálóban tartsd, és a végén azt írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int count = 0;
    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (i < n && arr == dep) {
            count++;
        }
    }

    cout << count << '\n';
    return 0;
}
