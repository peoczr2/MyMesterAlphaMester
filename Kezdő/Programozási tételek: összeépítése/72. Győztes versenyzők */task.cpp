/*
Megoldás lényege:
A kérdés az, kik nyertek legalább egy versenyen. Egy versenyen a győztes az 1-es helyezést elért versenyző, a 0 pedig azt jelenti, hogy nem indult, így nem nyerhet. A pontozási szabály (az első K helyezett pontot kap) a versenyek összesített sorrendjéhez kellene, de a kérdéshez nem szükséges, ezért nem használjuk. Az eredményeket soronként olvassuk be, és ha egy érték 1, a hozzá tartozó versenyzőt egy logikai tömbben megjelöljük. Végül a megjelölt sorszámokat növekvő sorrendben kiírjuk a darabszámmal együtt. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A kérdés csak arra vonatkozik, ki nyert legalább egy versenyt, vagyis a pontozást és a K értéket a megoldásban nem kell figyelembe venni. ||
Hint 2: || Egy logikai tömbben jelöld meg azokat a versenyzőket, akik valamelyik versenyen 1-es helyezést értek el, és a végén a megjelöltek sorszámait írd ki növekvő sorrendben. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<bool> nyert(n, false);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            int helyezes;
            cin >> helyezes;
            if (helyezes == 1) {
                nyert[i] = true;
            }
        }
    }

    int darab = 0;
    for (int i = 0; i < n; i++) {
        if (nyert[i]) darab++;
    }

    cout << darab << "\n";
    bool elso = true;
    for (int i = 0; i < n; i++) {
        if (nyert[i]) {
            if (!elso) cout << " ";
            cout << i + 1;
            elso = false;
        }
    }
    cout << "\n";

    return 0;
}
