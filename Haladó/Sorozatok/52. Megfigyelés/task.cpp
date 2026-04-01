/*
Megoldas lenyege:
Minden bolygo eszlelesi idopontjai rendezettek. Olyan legszukebb [A,B] intervallumot
keresunk, amely minden bolygorol tartalmaz legalabb egy idopontot.

Ez a klasszikus minimum tartomany feladat tobb rendezett sorozatra. Minden bolygobol
egy aktualis idopontot tartunk bent: a legkisebbet egy min-heap adja, a legnagyobbat
kulon nyilvantartjuk. Az aktualis [min,max] intervallum teljes fedest ad. Ezutan azt a
sorozatot toljuk eggyel elore, amelyik a minimumot adta. Amikor valamelyik sorozat elfogy,
mar nincs teljes fedes.
*/
/*
Hint 1: || Mindegyik bolygobol mindig csak egy jelolt idopont kell az aktualis intervallumhoz. ||
Hint 2: || A legkisebb aktualis idopontot erdemes tovabbleptetni, mert csak ettol szukulhet az intervallum. ||
Hint 3: || A kupac minimuma mellett a jelenlegi maximumot is tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Item {
    long long value;
    int listId;
    int index;

    bool operator>(const Item& other) const {
        if (value != other.value) return value > other.value;
        return listId > other.listId;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<long long>> observations(n);
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        observations[i].resize(m);
        for (int j = 0; j < m; ++j) cin >> observations[i][j];
    }

    priority_queue<Item, vector<Item>, greater<Item>> heap;
    long long currentMax = LLONG_MIN;
    for (int i = 0; i < n; ++i) {
        heap.push({observations[i][0], i, 0});
        currentMax = max(currentMax, observations[i][0]);
    }

    long long bestLeft = 0, bestRight = LLONG_MAX;
    bool found = false;

    while ((int)heap.size() == n) {
        Item current = heap.top();
        heap.pop();

        if (!found || currentMax - current.value < bestRight - bestLeft ||
            (currentMax - current.value == bestRight - bestLeft && current.value < bestLeft)) {
            found = true;
            bestLeft = current.value;
            bestRight = currentMax;
        }

        int nextIndex = current.index + 1;
        if (nextIndex >= (int)observations[current.listId].size()) break;

        long long nextValue = observations[current.listId][nextIndex];
        heap.push({nextValue, current.listId, nextIndex});
        currentMax = max(currentMax, nextValue);
    }

    cout << bestLeft << ' ' << bestRight << '\n';
    return 0;
}