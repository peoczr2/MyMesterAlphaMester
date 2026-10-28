/*
Megoldás lényege:
A meghívható tagok olyan halmazt alkotnak, amelyben minden tagot legalább két, szintén a halmazban lévő tag javasolt. Két ilyen halmaz uniója is megfelel, ezért van egyetlen legnagyobb ilyen halmaz.
Ezt iteratív levágással kapjuk: kezdetben minden tag benne van, és minden tagnál számoljuk, hány benne lévő tag javasolta. Ha egy tagot kevesebb mint két benne lévő tag javasol, kivesszük a halmazból, és az általa javasolt tagok számlálóját csökkentjük. Ez addig ismétlődik, amíg minden benne maradt tagot legalább két benne maradt tag javasol.
Minden tag legfeljebb egyszer kerül ki, és minden javaslatot egyszer dolgozunk fel, így az idő O(N).
*/
/*
Hint 1: || Egy tag akkor maradhat a meghívottak között, ha legalább két másik meghívott tag javasolta. Keresd a legnagyobb olyan halmazt, amelyben ez minden tagra teljesül. ||
Hint 2: || Ha két ilyen halmaz van, az uniójuk is megfelel a feltételnek, így a legnagyobb halmaz egyértelmű. Számold, hányan javasolják jelenleg az egyes tagokat, és a kettőnél kevesebbet kapó tagokat hagyd ki. ||
Hint 3: || Egy tag kihagyásakor csökkentsd eggyel annak a két tagnak a számlálóját, akiket ő javasolt; ha valakinek a számlálója két alá esik, az is kikerül. Minden tagot legfeljebb egyszer dolgozz fel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<array<int, 2>> proposes(n + 1);  // proposes[i]: akiket i javasolt
    vector<int> cnt(n + 1, 0);              // cnt[j]: hány (még bent lévő) tag javasolta j-t
    for (int i = 1; i <= n; i++) {
        cin >> proposes[i][0] >> proposes[i][1];
        cnt[proposes[i][0]]++;
        cnt[proposes[i][1]]++;
    }

    vector<char> out(n + 1, 0);
    vector<int> queue;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] < 2) {
            out[i] = 1;
            queue.push_back(i);
        }
    }
    for (size_t k = 0; k < queue.size(); k++) {
        int v = queue[k];
        for (int w : proposes[v]) {
            if (out[w]) continue;
            if (--cnt[w] < 2) {
                out[w] = 1;
                queue.push_back(w);
            }
        }
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++)
        if (!out[i]) ans.push_back(i);

    cout << ans.size() << '\n';
    for (size_t j = 0; j < ans.size(); j++) {
        if (j) cout << ' ';
        cout << ans[j];
    }
    cout << '\n';
    return 0;
}
