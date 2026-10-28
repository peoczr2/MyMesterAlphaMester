/*
Megoldás lényege:
Egy állomáson az utasok száma pontosan akkor csökken, ha a leszállók száma nagyobb a felszállókénál.
A kérdés olyan kezdőállomás, ahonnan Székesfehérvárig minden állomáson csökken az utasszám, ezért Székesfehérvártól visszafelé haladunk, és megállunk az első olyan állomásnál, ahol már nem csökken.
A visszafelé haladás során utoljára talált csökkenő állomás sorszámát írjuk ki, vagyis a legkisebb olyan sorszámút, ahonnan a csökkenés végig tart; ha Székesfehérváron nem csökken az utasszám, nincs ilyen állomás, és 0-t írunk ki.
Az állomásokat egyszer olvassuk be, és legfeljebb egyszer dolgozzuk fel, így az időigény O(N).
*/
/*
Hint 1: || Egy állomáson akkor csökken az utasok száma, ha ott a leszállók száma nagyobb, mint a felszállóké. ||
Hint 2: || Nem kell elölről végigmenni: Székesfehérvártól visszafelé dolgozd fel az állomásokat, és ha egy állomáson már nem csökken az utasszám, a ciklus megállhat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> le(n + 1), fel(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> le[i] >> fel[i];
    }
    int eredmeny = 0;
    for (int i = n; i >= 1; i--) {
        if (le[i] <= fel[i]) break;
        eredmeny = i;
    }
    cout << eredmeny << endl;
    return 0;
}
