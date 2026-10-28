/*
Megoldás lényege:
A három kérdést külön, egy-egy bejárással oldjuk meg. Fagyos az a nap, amelynek maximális hőmérséklete 0 fok alatt van: a futó számlálóval
az első olyan K hosszú szakaszt keressük, amelyben minden nap fagyos. Két szomszédos nap változását a napi minimumok és a napi
maximumok különbségének nagyobbikával mérjük, és a legnagyobb változású párt keressük (döntetlennél a korábbi pár nyer).
A harmadik kérdésnél az átlagos napi hőmérsékletek átlaga az összes minimum és maximum összegének 2N-ed része, ezért a
hasonlítás egész számokkal, a 2N-szeres szorzással elvégezhető. Az időigény O(N).
*/
/*
Hint 1: || Három külön kérdés van, mindegyiket egy bejárással meg lehet oldani; a fagyos nap a napi maximumtól függ, és egy futó számláló követi az egymást követő fagyos napokat. ||
Hint 2: || A B résznél minden szomszédos napi párt a minimumok és a maximumok különbségével hasonlíts össze, és a legnagyobb változású párt keresd (egyenlőségnél a korábbit). ||
Hint 3: || A C résznél először számold ki az összes napi minimum és maximum összegét: az átlagos hőmérsékletek átlaga ennek a 2N-ed része, így a minimumot 2N-szeresével hasonlítsd ehhez az összeghez. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<long long> mn(n), mx(n);
    for (int i = 0; i < n; ++i) {
        cin >> mn[i] >> mx[i];
    }

    // A: az első K hosszú szakasz, amelyben minden nap maximuma 0 alatt van
    int startA = -1;
    int run = 0;
    for (int i = 0; i < n && startA == -1; ++i) {
        if (mx[i] < 0) {
            ++run;
            if (run == k) {
                startA = i - k + 1;
            }
        } else {
            run = 0;
        }
    }

    if (startA == -1) {
        cout << "NINCS\n";
    } else {
        cout << startA + 1 << " " << startA + k << "\n";
    }

    // B: két szomszédos nap közötti legnagyobb változás (minimumok vagy maximumok különbsége)
    long long bestChange = -1;
    int bestI = 0;
    for (int i = 0; i + 1 < n; ++i) {
        long long change = max(llabs(mn[i + 1] - mn[i]), llabs(mx[i + 1] - mx[i]));
        if (change > bestChange) {
            bestChange = change;
            bestI = i;
        }
    }
    cout << bestI + 1 << " " << bestI + 2 << "\n";

    // C: azok a napok, ahol a napi minimum nagyobb az átlagos napi hőmérsékletek átlagánál
    long long total = 0;
    for (int i = 0; i < n; ++i) {
        total += mn[i] + mx[i];
    }
    vector<int> days;
    for (int i = 0; i < n; ++i) {
        if (2LL * n * mn[i] > total) {
            days.push_back(i + 1);
        }
    }
    if (days.empty()) {
        cout << "NINCS\n";
    } else {
        for (size_t i = 0; i < days.size(); ++i) {
            if (i > 0) {
                cout << ' ';
            }
            cout << days[i];
        }
        cout << "\n";
    }
    return 0;
}
