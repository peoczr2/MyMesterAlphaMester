/*
Megoldas lenyege:
Minden ország listája csökkenő sorrendben adott, ezért egy max-heap segítségével
k-way merge-et végzünk. A heap mindig az aktuálisan legnagyobb még fel nem
használt vagyont adja. Az első L elem kiválasztása közben megszámoljuk, melyik
országból hányan kerültek be a rangsorba.
*/
/*
Hint 1: || A K ország listáját egyszerre kell összefésülni. ||
Hint 2: || A heap tetején mindig az aktuálisan legnagyobb vagyon álljon. ||
Hint 3: || A kiválasztott L ember között számold meg az országonkénti darabszámot. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int country;
    int idx;
    int wealth;
    bool operator<(const Node& other) const {
        return wealth < other.wealth;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, l;
    cin >> k >> l;
    vector<vector<int>> wealth(k);
    for (int i = 0; i < k; ++i) {
        int m;
        cin >> m;
        wealth[i].resize(m);
        for (int j = 0; j < m; ++j) cin >> wealth[i][j];
    }

    priority_queue<Node> pq;
    for (int i = 0; i < k; ++i) {
        if (!wealth[i].empty()) pq.push({i, 0, wealth[i][0]});
    }

    vector<int> cnt(k, 0);
    vector<int> top;
    top.reserve(l);
    for (int taken = 0; taken < l && !pq.empty(); ++taken) {
        Node cur = pq.top();
        pq.pop();
        top.push_back(cur.wealth);
        ++cnt[cur.country];
        if (cur.idx + 1 < (int)wealth[cur.country].size()) {
            pq.push({cur.country, cur.idx + 1, wealth[cur.country][cur.idx + 1]});
        }
    }

    int bestCountry = 0;
    for (int i = 1; i < k; ++i) {
        if (cnt[i] > cnt[bestCountry]) bestCountry = i;
    }

    cout << bestCountry + 1 << '\n';
    for (int x : top) cout << x << '\n';
    return 0;
}
