/*
Megoldás lényege:
Minden vállalkozó munkái egymást követő napokon vannak, ezért a sorrend három összefüggő blokkból áll, és a blokkok
sorrendje a három vállalkozó egy permutációja. Csak 3! = 6 permutáció lehetséges: ezek közül azt keressük, amelyben
minden különböző vállalkozókhoz tartozó előírás a helyes irányba mutat. Ha ilyen permutáció van, a munkákat Kahn-féle
topologikus rendezéssel állítjuk elő úgy, hogy mindig a korábbi blokk elérhető munkáját vesszük elő, így a blokkok
összefüggők maradnak. Ha egy blokkon belül körkörös függés van, vagy nincs megfelelő permutáció, a válasz 0.
Az időigény O(N + M), a permutációk ellenőrzése pedig konstans (6 · 9) lépés.
*/
/*
Hint 1: || Mivel minden vállalkozó munkái egymás utáni napokon vannak, a három vállalkozó sorrendje csak 6-féle lehet. ||
Hint 2: || Egy előírás a és b munka között két különböző vállalkozót kötsön össze: a sorrendben annak az előbb kell állnia. Ha egy permutáció ezt megsérti, dobd el. ||
Hint 3: || A topologikus rendezést Kahn-algoritmussal végezd, a rendelkezésre álló munkák közül mindig a legkorábbi blokkhoz tartozót válaszd. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> contractor(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> contractor[i];
    }

    vector<vector<int>> successors(n + 1);
    vector<int> indegree(n + 1, 0);
    bool linked[4][4] = {};
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        successors[a].push_back(b);
        ++indegree[b];
        if (contractor[a] != contractor[b]) {
            linked[contractor[a]][contractor[b]] = true;
        }
    }

    // A vállalkozók blokkjainak sorrendje: az első olyan permutáció, amely minden előírást betart.
    vector<int> order = {1, 2, 3};
    vector<int> position(4, 0);
    bool found = false;
    do {
        for (int k = 0; k < 3; ++k) {
            position[order[k]] = k;
        }
        found = true;
        for (int x = 1; x <= 3; ++x) {
            for (int y = 1; y <= 3; ++y) {
                if (linked[x][y] && position[x] > position[y]) {
                    found = false;
                }
            }
        }
        if (found) {
            break;
        }
    } while (next_permutation(order.begin(), order.end()));

    if (!found) {
        cout << 0 << "\n";
        return 0;
    }

    // Kahn-algoritmus: mindig a legkorábbi blokk elérhető munkáját vesszük elő.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> ready;
    for (int task = 1; task <= n; ++task) {
        if (indegree[task] == 0) {
            ready.push({position[contractor[task]], task});
        }
    }

    vector<int> result;
    result.reserve(n);
    while (!ready.empty()) {
        int task = ready.top().second;
        ready.pop();
        result.push_back(task);
        for (int next : successors[task]) {
            if (--indegree[next] == 0) {
                ready.push({position[contractor[next]], next});
            }
        }
    }

    if ((int)result.size() < n) {
        cout << 0 << "\n";
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << result[i];
    }
    cout << "\n";
    return 0;
}
