/*
Megoldási ötlet:
Minden település áruja egyetlen útvonalon juthat el a raktárba, ezért ha a fát a raktárnál gyökerezzük,
akkor minden részfa pontosan egyetlen élen keresztül csatlakozik a raktár felé. Ezen az egy élen naponta
legfeljebb M egység szállítható, tehát egy részfa teljes hozzájárulása legfeljebb M lehet, hiába termelne többet.

Legyen `sum[u]` az `u` részfájában megtermelt teljes árumennyiség. Ekkor a szülő felé ténylegesen
`min(sum[u], M)` jut át, kivéve magát a raktárt, mert ott nincs felső korlát: oda minden gyermek-részfa
kapacitáskorlátos hozzájárulását összeadjuk, plusz a raktár saját termelését. Egy postorder bejárással
kiszámoljuk a részfaösszegeket, és közben összegezzük a raktárba beérkező maximális mennyiséget.
*/
/*
Hint 1: || Gyökerezd a fát a raktárnál, mert minden áru végül ide tart. ||
Hint 2: || Egy részfa teljes árumennyisége hiába nagyobb, a szülő felé vezető egyetlen él miatt legfeljebb `M` egység mehet át. ||
Hint 3: || Elég alulról felfelé kiszámolni a részfaösszegeket, majd minden gyerekrészfából `min(részfaösszeg, M)` mennyiséget hozzáadni a raktárhoz vezető oldalhoz. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, limit, root;
    cin >> n >> limit >> root;

    vector<long long> production(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> production[i];
    }

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> parent(n + 1, 0);
    vector<int> order = {root};
    parent[root] = -1;
    for (size_t i = 0; i < order.size(); ++i) {
        int node = order[i];
        for (int next : graph[node]) {
            if (next == parent[node]) {
                continue;
            }
            parent[next] = node;
            order.push_back(next);
        }
    }

    vector<long long> subtreeSum = production;
    for (int i = static_cast<int>(order.size()) - 1; i >= 1; --i) {
        int node = order[i];
        subtreeSum[parent[node]] += min(subtreeSum[node], static_cast<long long>(limit));
    }

    cout << subtreeSum[root] << '\n';
    return 0;
}