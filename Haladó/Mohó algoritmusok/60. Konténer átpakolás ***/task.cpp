/*
Feladat: A robot csak balról jobbra szállíthat. Egy konténer nagyobbra vagy üres helyre tehető. A cél a lehető legtöbb felszabadított hely (minél kevesebb végső torony).
Ötlet: Egy végső toronyhoz tartozó konténerek index szerint növekvő láncot adnak, és a méretüknek is szigorúan növekednie kell (kisebb mehet nagyobbra). Tehát a teljes sorozatot minimális számú szigorúan növekvő értékű részsorozatra kell bontani index-sorrendben. Ez standard mohó: minden új méretet arra a láncra tesszük, amelynek utolsó eleme a lehető legnagyobb, de még kisebb nála. A láncok száma minimális, így a szabad helyek száma maximális. A műveletekhez minden lánc elemeit a lánc utolsó pozíciójára pakoljuk jobbról balra haladó forrás-sorrendben.
Hint 1: || Egy toronyba csak olyan konténerek kerülhetnek, amelyek indexe és mérete is növekvő láncot alkot. ||
Hint 2: || Minimális láncszámhoz „best fit” kell: legnagyobb lehetséges kisebb farokra illesztés. ||
Hint 3: || Kiírásnál egy láncon belül a forrásokat fordított indexsorrendben mozgasd ugyanarra a célhelyre. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    int Kmax;
    cin >> N >> Kmax;
    (void)Kmax;

    vector<int> a(N + 1);
    for (int i = 1; i <= N; ++i) cin >> a[i];

    // tailValue -> chain ids ending with this value
    map<int, vector<int>> tails;
    vector<vector<int>> chains;

    auto pop_chain_with_tail = [&](int tail) {
        auto it = tails.find(tail);
        int cid = it->second.back();
        it->second.pop_back();
        if (it->second.empty()) tails.erase(it);
        return cid;
    };

    for (int i = 1; i <= N; ++i) {
        auto it = tails.lower_bound(a[i]);
        int cid;
        if (it == tails.begin()) {
            cid = (int)chains.size();
            chains.push_back({});
        } else {
            --it;
            cid = pop_chain_with_tail(it->first);
        }
        chains[cid].push_back(i);
        tails[a[i]].push_back(cid);
    }

    vector<pair<int,int>> ops;
    for (const auto& ch : chains) {
        if ((int)ch.size() <= 1) continue;
        int base = ch.back();
        for (int t = (int)ch.size() - 2; t >= 0; --t) {
            ops.push_back({ch[t], base});
        }
    }

    cout << ops.size() << '\n';
    for (auto [i, j] : ops) {
        cout << i << ' ' << j << '\n';
    }
    return 0;
}
