/*
Megoldási ötlet:
Minden folyó legfeljebb egy másikba ömlik, tehát a folyás irányában haladva minden indulási pontból egyetlen láncon
jutunk tovább. Ezért a két kérdés egyszerű szülőlánc-probléma.

Az első kérdéshez megjelöljük az első túra folyóit az indulási ponttól lefelé haladva. Ezután a második túra láncán
lépkedünk, és az első megjelölt folyó lesz az a hely, ahol először találkozhatnak. Ha nincs közös folyó, akkor az első
sor üres marad.

A második kérdéshez elég megnézni, hogy a második túra indulási folyója rajta van-e az első túra láncán. Ha igen,
akkor a minta szerinti számlálással az első túra odáig megtett úthosszát kell kiírni: azonos indulásnál ez 1,
különben az indulási folyótól a második indulási folyójáig vezető élút hossza.
Ha nincs rajta, akkor a válasz 0.
*/
/*
Hint 1: || A folyók „belefolyik” kapcsolata minden csúcsból legfeljebb egy kimenő él, tehát lefelé haladva mindig egy láncot kapsz. ||
Hint 2: || Az első közös pont megtalálásához jelöld meg az egyik lánc összes elemét, majd járd végig a másikat. ||
Hint 3: || A második kérdés csak azt vizsgálja, hogy az első lánc eléri-e a második indulási folyót, és ha igen, milyen hosszú az addigi út a minta szerinti számlálással. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, firstStart, secondStart;
    cin >> n >> m >> firstStart >> secondStart;

    vector<int> nextRiver(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        nextRiver[to] = from;
    }

    vector<int> position(n + 1, 0);
    int river = firstStart;
    int step = 1;
    while (river != 0 && position[river] == 0) {
        position[river] = step++;
        river = nextRiver[river];
    }

    int meeting = 0;
    river = secondStart;
    while (river != 0) {
        if (position[river] != 0) {
            meeting = river;
            break;
        }
        river = nextRiver[river];
    }

    if (meeting != 0) {
        cout << meeting;
    }
    cout << '\n';
    int waitDistance = 0;
    if (position[secondStart] != 0) {
        waitDistance = (firstStart == secondStart ? 1 : position[secondStart] - 1);
    }
    cout << waitDistance << '\n';
    return 0;
}