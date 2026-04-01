/*
Megoldás lényege:
Minden postáshoz egy rendezett naplista tartozik, és olyan legrövidebb intervallum kell, amely minden
listából tartalmaz legalább egy elemet. Ez a klasszikus "smallest range covering one element from each
sorted list" feladat.

Minden listából fenntartjuk az aktuális kiválasztott napot. Ezek minimumát kupacból kapjuk, a maximumát
külön változóban tartjuk. Mindig annál a postásnál lépünk tovább, aki az aktuális minimumot adja.
*/
/*
Hint 1: || Olyan intervallum kell, amely minden postás listájából lefed legalább egy napot. ||
Hint 2: || Ha ismert az aktuális P darab kiválasztott nap, akkor az intervallumot a minimum és maximum határozza meg. ||
Hint 3: || Érdemes mindig azt a listát előreléptetni, amelyik az aktuális minimumot adja. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int day;
    int postman;
    int index;
    bool operator>(const Node& other) const {
        if (day != other.day) return day > other.day;
        return postman > other.postman;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    cin >> n >> p;
    vector<vector<int>> days(p, vector<int>(n));
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < n; ++j) cin >> days[i][j];
    }

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    int currentMax = 0;
    for (int i = 0; i < p; ++i) {
        pq.push({days[i][0], i, 0});
        currentMax = max(currentMax, days[i][0]);
    }

    int bestL = pq.top().day;
    int bestR = currentMax;

    while (true) {
        Node current = pq.top();
        pq.pop();
        int currentL = current.day;
        int currentR = currentMax;
        if (currentR - currentL < bestR - bestL || (currentR - currentL == bestR - bestL && currentL < bestL)) {
            bestL = currentL;
            bestR = currentR;
        }

        if (current.index + 1 == n) {
            break;
        }
        int nextDay = days[current.postman][current.index + 1];
        pq.push({nextDay, current.postman, current.index + 1});
        currentMax = max(currentMax, nextDay);
    }

    cout << bestL << ' ' << bestR << '\n';
    return 0;
}