/*
Megoldás lényege:
Az anyagok nem fogynak el, ezért a vasból (1) elérhető anyagok halmaza egyszerű szélességi bejárással megkapható:
ha egy anyag elérhető, a hozzá tartozó katalizátorral előállított anyag is elérhető. Egy katalizátor akkor nélkülözhetetlen,
ha az aranyat (0) nem lehet elérni, amikor ezt a betűt tiltjuk. Ezért minden betűre (A-tól Z-ig) lefuttatjuk a bejárást a
többi katalizátorral. Ha már az összes katalizátorral sem érhető el az arany, a válasz NEM LEHET. Az időigény
O(26 * (N + anyagok száma)), ami bőven belefér a korlátokba.
*/
/*
Hint 1: || Az anyagok nem fogynak el, ezért a vasból kiindulva egy bejárással megkapod az összes elérhető anyagot: ha egy anyag elérhető, és van hozzá bejegyzés a megfelelő katalizátorral, a céltermék is elérhető. ||
Hint 2: || Egy betű akkor nélkülözhetetlen, ha a bejárást úgy futtatod, hogy ezt a betűt tiltod, és az arany (0) már nem érhető el. Minden betűre futtasd le egyszer. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Entry {
    int from;
    char catalyst;
    int to;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Entry> entries(n);
    int maxId = 1;
    for (Entry &e : entries) {
        cin >> e.from >> e.catalyst >> e.to;
        maxId = max({maxId, e.from, e.to});
    }

    vector<vector<int>> byFrom(maxId + 1);
    for (int i = 0; i < n; ++i)
        byFrom[entries[i].from].push_back(i);

    // allowed: bit c jelzi, hogy az 'A' + c katalizátor használható
    auto goldReachable = [&](unsigned allowed) {
        vector<char> seen(maxId + 1, 0);
        queue<int> q;
        seen[1] = 1;
        q.push(1);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i : byFrom[x]) {
                const Entry &e = entries[i];
                unsigned bit = 1u << (e.catalyst - 'A');
                if (!(allowed & bit) || seen[e.to])
                    continue;
                seen[e.to] = 1;
                q.push(e.to);
            }
        }
        return seen[0] == 1;
    };

    const unsigned all = (1u << 26) - 1;
    if (!goldReachable(all)) {
        cout << "NEM LEHET\n";
        return 0;
    }

    string needed;
    for (int c = 0; c < 26; ++c) {
        if (!goldReachable(all & ~(1u << c))) {
            if (!needed.empty())
                needed += ' ';
            needed += char('A' + c);
        }
    }
    cout << (needed.empty() ? string("EGYIK SEM KELL") : needed) << "\n";
    return 0;
}
