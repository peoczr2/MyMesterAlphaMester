/*
Megoldás lényege:
Nem kell tudni, melyik hallgató melyik hónapban született, csak azt, hogy minden hónap előfordul-e a bemenetben. A tizenkét hónapnevet ékezet nélkül, kisbetűkkel egy listában rögzítjük, a hallgatók hónapjait pedig egy halmazba gyűjtjük. A válasz akkor IGEN, ha a lista minden hónapneve benne van a halmazban, különben NEM. Az időigény N-nel arányos.
*/
/*
Hint 1: || Nem kell a hallgatók neveit tárolni: elég a hónapok neveit összegyűjteni, és megnézni, hány különböző hónap fordul elő. ||
Hint 2: || Használj set<string> halmazt a beolvasott hónapneveknek, majd ellenőrizd, hogy a tizenkét hónapnév (januar, februar, marcius, aprilis, majus, junius, julius, augusztus, szeptember, oktober, november, december) mindegyike benne van-e. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    set<string> honapok;
    for (int i = 0; i < n; i++) {
        string honap;
        cin >> honap;
        honapok.insert(honap);
    }

    vector<string> osszes = {"januar", "februar", "marcius", "aprilis", "majus", "junius",
                             "julius", "augusztus", "szeptember", "oktober", "november", "december"};
    bool mind = true;
    for (const string &h : osszes) {
        if (!honapok.count(h)) {
            mind = false;
        }
    }

    cout << (mind ? "IGEN" : "NEM") << '\n';
    return 0;
}
