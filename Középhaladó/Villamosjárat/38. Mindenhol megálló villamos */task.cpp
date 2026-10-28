/*
Megoldás lényege:
Egy villamos egy állomáson akkor nem áll meg, ha az érkezési és az indulási idő egyenlő. Ezért a villamos akkor áll meg minden állomáson, ha minden megállóban az érkezési idő kisebb az indulási időnél. Egyetlen beolvasási ciklusban egy logikai változóba gyűjtjük, volt-e olyan megálló, ahol nem állt meg, majd ennek megfelelően 1-et vagy 0-t írunk ki. Az időigény O(N).
*/
/*
Hint 1: || Egy villamos akkor nem áll meg egy állomáson, ha az érkezési és az indulási idő egyenlő. ||
Hint 2: || Olvasd be a megállókat, és egy logikai változóval jegyezd meg, volt-e közöttük olyan, ahol nem állt meg. A végén a változó értéke alapján írj ki 1-et vagy 0-t. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    bool allStop = true;
    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (arr == dep) {
            allStop = false;
        }
    }

    cout << (allStop ? 1 : 0) << '\n';
    return 0;
}
