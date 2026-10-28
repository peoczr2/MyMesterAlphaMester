/*
Megoldás lényege:
Az emberek egyetlen közös sorban állnak, és a sor elejéről csak akkor engedjük be az
embert, ha az ő ügyének ügyintézője szabad. Ezért ha a sor elején álló embernek várnia
kell, a mögötte állók is várnak, akkor is, ha az ő ügyintézőjük szabad. Az eseményeket
időrendben dolgozzuk fel: a következő érkezés vagy a következő ügyintézés vége közül a
korábbi időpontra ugrunk. Minden időpontban előbb a befejezett ügyintézőket szabadítjuk
fel, utána az érkezőket soroljuk be, végül a sor elejéről addig engedünk be, amíg az
első ember ügyintézője foglalt. A várakozási időt a beengedés pillanatában, a sor
hosszát minden feldolgozás után mérjük. A befejezési idők prioritási sorban vannak,
így az összes művelet logaritmikus, a teljes futás N log N.
*/
/*
Hint 1: || Egyetlen közös sor van, és csak a sor elejét nézzük: ha annak az ügyintézője foglalt, a mögötte állók is várnak, akkor is, ha az ő ügyintézőjük szabad. ||
Hint 2: || Eseményalapú léptetés: a következő érkezés vagy a következő ügyintézés vége közül a korábbi időpontra ugorva, minden időpontban a sor elejét próbáljuk beengedni. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Person {
    long long arrival;
    int type;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> service(k + 1);
    for (int i = 1; i <= k; ++i) cin >> service[i];

    vector<Person> people(n);
    for (int i = 0; i < n; ++i) cin >> people[i].arrival >> people[i].type;

    queue<Person> waiting;
    vector<bool> deskFree(k + 1, true);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> busy;

    long long bestWait = 0;
    long long maxQueue = 0;
    int idx = 0;
    long long time = 0;

    while (idx < n || !waiting.empty() || !busy.empty()) {
        long long nextArrival = idx < n ? people[idx].arrival : LLONG_MAX;
        long long nextFinish = busy.empty() ? LLONG_MAX : busy.top().first;
        time = min(nextArrival, nextFinish);

        while (!busy.empty() && busy.top().first <= time) {
            deskFree[busy.top().second] = true;
            busy.pop();
        }
        while (idx < n && people[idx].arrival <= time) waiting.push(people[idx++]);

        while (!waiting.empty()) {
            Person p = waiting.front();
            if (!deskFree[p.type]) break;
            waiting.pop();
            bestWait = max(bestWait, time - p.arrival);
            deskFree[p.type] = false;
            busy.push({time + service[p.type], p.type});
        }
        maxQueue = max(maxQueue, (long long)waiting.size());
    }

    cout << bestWait << '\n' << maxQueue << '\n';
    return 0;
}
