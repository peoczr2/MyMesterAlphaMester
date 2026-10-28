/*
Megoldás lényege:
Az a vonat indul Székesfehérvárról, amelynek a Székesfehérvár-sorában nincs érkezési ideje (-1), vagyis a vonat itt kezdi az útját. Egy átmenő vonat, amely csak megáll a városban, nem számít, még akkor sem, ha ott is van indulási ideje. A sorokat sorban olvassuk, és az első ilyen, érvényes indulási idejű sornál megállunk. Mivel az adatok indulási idő szerint vannak rendezve, ez a legkorábbi indulás. Ha nincs ilyen sor, a -1 marad a válasz. Az időigény O(N), N ≤ 100.
*/
/*
Hint 1: || Nem minden Székesfehérvárral kapcsolatos sor jó: a keresett vonat ott kezdi az útját, vagyis ott nincs érkezési ideje. ||
Hint 2: || Az adatok indulási idő szerint vannak rendezve, így az első megfelelő sornál megállhatsz. Ha nincs megfelelő sor, a -1-et írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int answer = -1;
    for (int i = 0; i < n; i++) {
        string city;
        int arrival, departure;
        cin >> city >> arrival >> departure;
        if (answer == -1 && city == "Szekesfehervar" && arrival == -1 && departure != 9999) {
            answer = departure;
        }
    }
    cout << answer << "\n";
    return 0;
}
