/*
Megoldás lényege:
Az időpontokat percre váltjuk, és a napváltást úgy kezeljük, hogy két állomás között a haladás ideje a két időpont különbsége modulo 1440 lesz, mert az út nem tart 24 óránál tovább.
Minden köztes állomáson 10 percet áll a vonat, így a megállások és a haladási szakaszok egy folytonos idővonalat adnak.
A leghosszabb megállás nélküli időszak a haladási szakaszok közül a leghosszabb.
Éjfélkor (minden 1440 perces többszörösnél) megnézzük, hogy a vonat éppen egy állomáson áll-e (zárt megállási intervallum), vagy két állomás között halad (nyílt haladási intervallum).
Az időigény O(N + a napok száma), ami nagyon kicsi.
*/
/*
Hint 1: || Az időpontokat alakítsd át napon belüli percekre, és a két egymás utáni időpont közti haladási időt számold modulo 1440 szerint. ||
Hint 2: || Minden köztes állomáson az érkezés után 10 perccel indul tovább a vonat: az indulási időt külön tárold, mert a következő szakasz onnan indul. A haladási szakaszok maximuma adja az A-kérdés választ. ||
Hint 3: || Az éjfélekre csak a 0, 1440, 2880, ... perceket kell megnézni. Ha az éppen aktuális perc egy megállás intervallumába esik, az állomás sorszámát írd ki, különben a két állomás közti haladást "k-(k+1)" alakban. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long DAY = 24 * 60; // a nap hossza percben
    const long long WAIT = 10;     // megállási idő minden köztes állomáson

    int n;
    cin >> n;

    // arr[i]: érkezés az i. állomásra, dep[i]: indulás onnan (abszolút percek, 0 a kezdő nap éjfele)
    vector<long long> arr(n + 1), dep(n + 1);

    int h, m;
    cin >> h >> m;
    arr[1] = dep[1] = h * 60LL + m;
    long long cur = dep[1];

    for (int i = 2; i <= n; ++i) {
        cin >> h >> m;
        long long t = h * 60LL + m;
        // a haladás ideje a napon belüli különbség, 24 óránál nem tart tovább
        long long travel = ((t - cur % DAY) % DAY + DAY) % DAY;
        arr[i] = cur + travel;
        dep[i] = (i < n) ? arr[i] + WAIT : arr[i]; // a végállomásról nincs indulás
        cur = dep[i];
    }

    // A: a leghosszabb haladási szakasz hossza
    long long longest = 0;
    for (int i = 2; i <= n; ++i) {
        longest = max(longest, arr[i] - dep[i - 1]);
    }

    // B: a vonat helyzete minden éjfélkor
    vector<string> events;
    for (long long midnight = 0; midnight <= arr[n]; midnight += DAY) {
        if (midnight < dep[1]) {
            continue;
        }
        bool done = false;
        for (int s = 1; s <= n && !done; ++s) {
            if (arr[s] <= midnight && midnight <= dep[s]) {
                events.push_back(to_string(s));
                done = true;
            }
        }
        for (int s = 1; s < n && !done; ++s) {
            if (dep[s] < midnight && midnight < arr[s + 1]) {
                events.push_back(to_string(s) + "-" + to_string(s + 1));
                done = true;
            }
        }
    }

    cout << longest << "\n";
    if (events.empty()) {
        cout << "0\n";
    } else {
        for (size_t i = 0; i < events.size(); ++i) {
            if (i > 0) {
                cout << ' ';
            }
            cout << events[i];
        }
        cout << "\n";
    }
    return 0;
}
