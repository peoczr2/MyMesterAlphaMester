/*
Eseményvezérelt szimuláció: a várakozók érkezési sorrendben állnak egy FIFO sorban, a szabad pultok egy min-heapben vannak, így mindig a legkisebb sorszámú szabad pult adódik. A foglalt pultok egy prioritásos sorban (távozási idő, pult) szerepelnek. Minden eseményidőpontban előbb a felszabaduló pultokat tesszük szabaddá, utána a megérkezőket sorba állítjuk, végül a sor elejét a legkisebb szabad pultra ültetjük, és rögzítjük a várakozást. A munkanap vége a legkésőbbi E+H, a várakozók maximuma az egyes időpontok utáni sorhossz maximuma. A futásidő O(N log(N+M)).
*/
/*
Hint 1: || Az ügyfeleket érkezési sorrendben egy sorban tartsd, a szabad pultok közül pedig mindig a legkisebb sorszámút válaszd. ||
Hint 2: || A következő esemény mindig a legkorábbi érkezés vagy a legkorábbi pultfelszabadulás; eseménynél előbb a felszabadulásokat dolgozd fel, utána az érkezőket, és csak ezután ültesd le a sor elejét. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<long long> arrival(n), service(n);
    for (int i = 0; i < n; ++i) cin >> arrival[i] >> service[i];

    priority_queue<int, vector<int>, greater<int>> freeDesks;
    for (int d = 1; d <= m; ++d) freeDesks.push(d);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> busy;

    vector<int> deskOf(n, 0);
    queue<int> waiting;
    long long bestWait = 0, maxQueue = 0, dayEnd = 0;
    int idx = 0;

    while (idx < n || !waiting.empty() || !busy.empty()) {
        long long nextArrival = idx < n ? arrival[idx] : LLONG_MAX;
        long long nextFinish = busy.empty() ? LLONG_MAX : busy.top().first;
        long long now = min(nextArrival, nextFinish);

        while (!busy.empty() && busy.top().first <= now) {
            freeDesks.push(busy.top().second);
            busy.pop();
        }
        while (idx < n && arrival[idx] <= now) waiting.push(idx++);

        while (!waiting.empty() && !freeDesks.empty()) {
            int c = waiting.front();
            waiting.pop();
            int d = freeDesks.top();
            freeDesks.pop();
            deskOf[c] = d;
            bestWait = max(bestWait, now - arrival[c]);
            long long finish = now + service[c];
            dayEnd = max(dayEnd, finish);
            busy.push({finish, d});
        }
        maxQueue = max(maxQueue, (long long)waiting.size());
    }

    cout << dayEnd << ' ' << bestWait << ' ' << maxQueue << '\n';
    for (int i = 0; i < n; ++i) cout << deskOf[i] << '\n';
    return 0;
}
