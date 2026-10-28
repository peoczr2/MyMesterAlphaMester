/*
A jelentkezőket érkezési idő szerint sorba rendezzük, és az események mentén szimuláljuk az ügyintézőt. Minden eseménynél először beérkeznek a megérkezett ügyfelek egy prioritásos sorba, amelynek kulcsa (ügyintézési idő, érkezési idő, sorszám), így a három kiválasztási szabály egyetlen rendezés. Ha az ügyintéző szabad, kiveszi a sor elejét, és az ügyfél várakozása az ügyintézés kezdete mínusz az érkezés. A második kimenet a sorban álló várakozók maximális száma a behívások után, mert a most behívott ügyfél már nem számít várakozónak. A szimuláció az események között ugrik, így a futásidő O(N log N).
*/
/*
Hint 1: || Érdemes az ügyfeleket érkezési idő szerint sorba rendezni, és az ügyintéző állapotát csak az érkezések és a befejezések időpontjaiban frissíteni. ||
Hint 2: || A várakozók közül mindig a legkisebb (ügyintézési idő, érkezési idő, sorszám) hármast kell kiválasztani: ezt egy prioritásos sor (min-heap) adja. ||
Hint 3: || A várakozás hossza a kezdés és az érkezés különbsége; a maximális várakozószámot a behívás után, minden eseménynél a sor méretéből mérd le. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Client {
    int arrival, duration, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Client> clients(n);
    for (int i = 0; i < n; ++i) {
        cin >> clients[i].arrival >> clients[i].duration;
        clients[i].id = i + 1;
    }
    sort(clients.begin(), clients.end(), [](const Client &a, const Client &b) { return a.arrival < b.arrival; });

    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> waiting;
    int idx = 0;
    long long time = 0;
    bool busy = false;
    long long finish = (long long)4e18;
    int best_id = 0;
    int best_wait = 0;
    int max_waiting = 0;

    while (idx < n || busy || !waiting.empty()) {
        long long next_arrival = idx < n ? clients[idx].arrival : (long long)4e18;
        long long next_event = min(next_arrival, finish);
        if (!busy && waiting.empty() && idx < n && time < next_arrival) time = next_arrival;
        else time = next_event;

        while (idx < n && clients[idx].arrival <= time) {
            waiting.push({clients[idx].duration, clients[idx].arrival, clients[idx].id});
            ++idx;
        }

        if (busy && finish <= time) busy = false;

        if (!busy && !waiting.empty()) {
            auto [dur, arr, id] = waiting.top();
            waiting.pop();
            busy = true;
            finish = time + dur;
            int waited = (int)(time - arr);
            if (waited > best_wait || (waited == best_wait && (best_id == 0 || id < best_id))) {
                best_wait = waited;
                best_id = id;
            }
        }

        max_waiting = max<int>(max_waiting, waiting.size());
        if (!busy && waiting.empty()) finish = (long long)4e18;
    }

    if (best_wait == 0) best_id = 0;
    cout << best_id << '\n' << max_waiting << '\n';
    return 0;
}