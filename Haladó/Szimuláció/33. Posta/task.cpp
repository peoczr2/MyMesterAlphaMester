/*
A posta működése típusonkénti sorokra és az ablakok szabadságára épül. A helyes szimulációval kiolvasható a munkaidő vége és a legnagyobb várakozás is.
*/
/*
Hint 1: || A típusonkénti sorok mellett a megfelelő ablak szabadságát is követni kell. ||
Hint 2: || A munkaidő vége és a maximális várakozás ugyanabból az időléptetésből adódik. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Person {
    long long arrival;
    int type;
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> service(k + 1);
    for (int i = 1; i <= k; ++i) cin >> service[i];

    vector<Person> people(n);
    for (int i = 0; i < n; ++i) {
        cin >> people[i].arrival >> people[i].type;
        people[i].id = i + 1;
    }

    queue<Person> waiting;
    vector<int> free(k + 1, 1);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> busy;

    vector<int> desk_of(n + 1, 0);
    long long best_wait = 0;
    long long max_queue = 0;
    long long workday_end = 0;
    int idx = 0;
    long long time = 0;

    while (idx < n || !waiting.empty() || !busy.empty()) {
        long long next_arrival = idx < n ? people[idx].arrival : LLONG_MAX;
        long long next_finish = busy.empty() ? LLONG_MAX : busy.top().first;
        if (waiting.empty() && busy.empty() && idx < n && time < next_arrival) time = next_arrival;
        else time = min(next_arrival, next_finish);

        while (!busy.empty() && busy.top().first <= time) {
            free[busy.top().second] = 1;
            busy.pop();
        }

        while (idx < n && people[idx].arrival <= time) waiting.push(people[idx++]);

        while (!waiting.empty()) {
            const Person &p = waiting.front();
            if (!free[p.type]) break;
            waiting.pop();
            desk_of[p.id] = p.type;
            long long waited = time - p.arrival;
            best_wait = max(best_wait, waited);
            free[p.type] = 0;
            long long finish = time + service[p.type];
            workday_end = max(workday_end, finish);
            busy.push({finish, p.type});
        }

        max_queue = max<long long>(max_queue, waiting.size());
    }

    cout << workday_end << ' ' << best_wait << ' ' << max_queue << '\n';
    for (int i = 1; i <= n; ++i) cout << desk_of[i] << '\n';
    return 0;
}
