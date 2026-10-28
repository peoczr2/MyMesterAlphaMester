/*
Megoldás lényege:
Az események kezdési idő szerint haladunk, és minimum-kupacban nyilvántartjuk, mikor szabadul fel az egyes terem. Ha van olyan terem, amelynek utolsó eseménye az új esemény kezdete előtt véget ért (az azonos időpont ütközés), az eseményt oda tesszük; különben új termet nyitunk. Új termet csak akkor nyitunk, ha minden meglévő terem foglalt, ezért a termek száma pontosan a legtöbb egyidejűleg zajló esemény számával egyezik, ami alsó korlát is. Az időigény O(N log N).
*/
/*
Hint 1: || Ha több terem is szabad, azt válaszd, amelyik a legkorábban felszabadul. ||
Hint 2: || Ha egyik terem sem szabad, új termet kell nyitni. ||
Hint 3: || Az események kezdési idő szerint rendezve haladj, és a termek felszabadulási idejét minimum-kupacban tartsd nyilván. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Event { int s, e, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Event> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].s >> a[i].e;
        a[i].id = i + 1;
    }
    sort(a.begin(), a.end(), [](const Event &x, const Event &y) {
        if (x.s != y.s) return x.s < y.s;
        if (x.e != y.e) return x.e < y.e;
        return x.id < y.id;
    });

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<vector<int>> rooms;
    for (auto &ev : a) {
        if (!pq.empty() && pq.top().first < ev.s) {
            auto [endTime, roomId] = pq.top();
            pq.pop();
            rooms[roomId].push_back(ev.id);
            pq.push({ev.e, roomId});
        } else {
            int roomId = rooms.size();
            rooms.push_back({ev.id});
            pq.push({ev.e, roomId});
        }
    }

    cout << rooms.size() << '\n';
    for (auto &room : rooms) {
        for (int i = 0; i < (int)room.size(); ++i) {
            if (i) cout << ' ';
            cout << room[i];
        }
        cout << '\n';
    }
    return 0;
}