/*
Feladat: A vendégeket asztalokhoz kell osztani. Egy asztalhoz legfeljebb K vendég ülhet, és egy asztal vendégeinek intervallumai metsszék egymást (legyen közös időpont, amikor mind jelen vannak). A cél az asztalok számának minimalizálása.
Ötlet: Határidő (távozás) szerinti mohó csoportosítás. Vesszük a legkorábban távozó még be nem osztott vendéget, és az ő távozási idején (t=T) készítünk egy asztalt. Erre az asztalra legfeljebb K olyan még szabad vendéget teszünk, akik tartalmazzák t-t, prioritásban a legkorábban távozókat. Így a sürgős intervallumokat nem késleltetjük, és kapacitás szerint maximálisan töltjük az asztalokat.
Hint 1: || Azonos asztalhoz egy közös t időpont kell, amit minden intervallum tartalmaz. ||
Hint 2: || Jó „horgony” a legkorábban távozó vendég végpontja. ||
Hint 3: || A horgonynál aktív vendégek közül a legkorábban távozókat érdemes előbb kiosztani. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Guest {
    int e, t, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<Guest> g(N);
    for (int i = 0; i < N; ++i) {
        cin >> g[i].e >> g[i].t;
        g[i].id = i + 1;
    }

    vector<Guest> byStart = g, byEnd = g;
    sort(byStart.begin(), byStart.end(), [](const Guest& a, const Guest& b) {
        if (a.e != b.e) return a.e < b.e;
        if (a.t != b.t) return a.t < b.t;
        return a.id < b.id;
    });
    sort(byEnd.begin(), byEnd.end(), [](const Guest& a, const Guest& b) {
        if (a.t != b.t) return a.t < b.t;
        if (a.e != b.e) return a.e < b.e;
        return a.id < b.id;
    });

    vector<char> assigned(N + 1, 0);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> active; // (t, id)

    vector<vector<int>> tables;
    tables.reserve((N + K - 1) / K);

    int p = 0;
    for (const auto& anchor : byEnd) {
        if (assigned[anchor.id]) continue;
        int time = anchor.t;

        while (p < N && byStart[p].e <= time) {
            active.push({byStart[p].t, byStart[p].id});
            ++p;
        }

        while (!active.empty() && (assigned[active.top().second] || active.top().first < time)) {
            active.pop();
        }

        if (assigned[anchor.id]) continue;

        vector<int> table;
        table.reserve(K);

        // Biztosan felvesszük a horgonyt is ezen az időponton.
        assigned[anchor.id] = 1;
        table.push_back(anchor.id);

        // Ha az anchor benne volt az active kupacban, majd később lustán eldobjuk a kijelölt elemeket.
        while ((int)table.size() < K) {
            while (!active.empty() && (assigned[active.top().second] || active.top().first < time)) {
                active.pop();
            }
            if (active.empty()) break;
            int id = active.top().second;
            active.pop();
            if (assigned[id]) continue;
            assigned[id] = 1;
            table.push_back(id);
        }

        tables.push_back(move(table));
    }

    // Ha bárki kimaradt (óvatossági ág), külön asztalokban pótoljuk.
    for (int id = 1; id <= N; ++id) {
        if (!assigned[id]) tables.push_back({id});
    }

    cout << tables.size() << '\n';
    for (const auto& tb : tables) {
        for (int i = 0; i < (int)tb.size(); ++i) {
            if (i) cout << ' ';
            cout << tb[i];
        }
        cout << '\n';
    }
    return 0;
}
