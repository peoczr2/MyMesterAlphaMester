/*
Megoldás lényege:
Az i-edik fal az i-edik és az (i+1)-edik őrhely között húzódik. Ez a fal akkor védett, ha mindkét végén van őrség, vagyis az i-edik és az (i+1)-edik érték is 1.
Ezért egy lineáris bejárással végigmegyünk az N-1 szomszédos páron, és megszámoljuk azokat, ahol mindkét érték 1.
Az időigény O(N), a tárigény O(N), mert az őrségek leírását egy tömbben tároljuk.
*/
/*
Hint 1: || Egy fal akkor védett, ha a két végén is van őrség. Ezt két szomszédos őrhelyre nézve kell ellenőrizni, nem a teljes listára. ||
Hint 2: || Minden i-re, ahol 1 és N-1 közötti, nézd meg az i-edik és az (i+1)-edik őrhelyet. Ha mindkettőn van őrség, a védett falak számát növeld eggyel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> orseg(n);
    for (int i = 0; i < n; i++) {
        cin >> orseg[i];
    }
    int vedett = 0;
    for (int i = 0; i + 1 < n; i++) {
        if (orseg[i] == 1 && orseg[i + 1] == 1) {
            vedett++;
        }
    }
    cout << vedett << endl;
    return 0;
}
