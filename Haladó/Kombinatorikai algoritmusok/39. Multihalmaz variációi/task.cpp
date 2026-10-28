/*
Megoldás lényege:
A variációk lexikografikus sorrendje ugyanaz a prefixfa-bejárás, mint a lerakásoknál: a következő variáció vagy a jelenlegi szó bővítése a legkisebb fel nem használt elemmel, vagy a jobb végétől visszalépve az első olyan pozícióban a nála nagyobb legkisebb elérhető elem. Az előző variáció hasonlóan kapható: ha az utolsó elem a pozíciójában a legkisebb elérhető érték, akkor a szó eggyel rövidebb lesz; ha ez az egyetlen, legkisebb elem, akkor a ciklikus miatt a teljes multihalmaz csökkenő sorrendje az előző. Különben az utolsó elemet a nála kisebb legnagyobb elérhető értékre cseréljük, és a maradék elemeket csökkenő sorrendbe tesszük a végére, mert ez adja a legnagyobb, még kisebb variációt.
A prefixenkénti darabszámok tömbje miatt az időigény O(N²), ami N ≤ 1000 mellett bőven belefér.
*/
/*
Hint 1: || Ugyanaz a prefixfa-szemlélet működik, mint az előző feladatnál: a következő variáció vagy a jelenlegi bővítése, vagy egy hosszabb prefix utáni nagyobb elem. Az előző variációnál azt vizsgáld, az utolsó elem helyettesíthető-e egy kisebb elérhető elemmel. ||
Hint 2: || Számold meg értékenként az összes példányt, és a prefixekben a felhasznált példányokat. Így minden pozícióban lineáris bejárással megkapod a legkisebb vagy a legnagyobb még elérhető értéket. ||
Hint 3: || Az előző variációnál, ha az utolsó elem a pozícióban elérhető legkisebb érték, a rövidebb prefix a válasz (egyelemű legkisebb elem esetén a teljes multihalmaz csökkenő sorrendje). Különben az utolsó elemet a nála kisebb legnagyobb elérhető értékre cseréld, és a maradékot csökkenő sorrendben fűzd a végére. ||
*/

#include <bits/stdc++.h>
using namespace std;

static vector<int> appendDescending(const vector<int>& values, const vector<int>& counts) {
    vector<int> out;
    for (int i = (int)values.size() - 1; i >= 0; --i) {
        for (int c = 0; c < counts[i]; ++c) out.push_back(values[i]);
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> multisetValues(n);
    for (int i = 0; i < n; ++i) cin >> multisetValues[i];

    int m;
    cin >> m;
    vector<int> cur(m);
    for (int i = 0; i < m; ++i) cin >> cur[i];

    vector<int> values = multisetValues;
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    vector<int> total(values.size(), 0);
    for (int x : multisetValues) {
        int id = lower_bound(values.begin(), values.end(), x) - values.begin();
        ++total[id];
    }

    vector<vector<int>> pref(m + 1, vector<int>(values.size(), 0));
    for (int i = 0; i < m; ++i) {
        pref[i + 1] = pref[i];
        int id = lower_bound(values.begin(), values.end(), cur[i]) - values.begin();
        ++pref[i + 1][id];
    }

    auto smallestAvailable = [&](int pos) -> int {
        for (int id = 0; id < (int)values.size(); ++id) {
            if (total[id] - pref[pos][id] > 0) return id;
        }
        return -1;
    };

    vector<int> nxt;
    if (m < n) {
        vector<int> used = pref[m];
        for (int id = 0; id < (int)values.size(); ++id) {
            if (used[id] < total[id]) {
                nxt = cur;
                nxt.push_back(values[id]);
                break;
            }
        }
    } else {
        for (int i = m - 1; i >= 0; --i) {
            int curId = lower_bound(values.begin(), values.end(), cur[i]) - values.begin();
            for (int id = curId + 1; id < (int)values.size(); ++id) {
                if (total[id] - pref[i][id] > 0) {
                    nxt.assign(cur.begin(), cur.begin() + i);
                    nxt.push_back(values[id]);
                    goto next_ready;
                }
            }
        }
        nxt.push_back(values[0]);
    }
next_ready:

    vector<int> prv;
    if (m == 1 && cur[0] == values[0]) {
        prv = appendDescending(values, total);
    } else {
        int lastSmallest = smallestAvailable(m - 1);
        int lastId = lower_bound(values.begin(), values.end(), cur[m - 1]) - values.begin();
        if (lastId == lastSmallest) {
            prv.assign(cur.begin(), cur.end() - 1);
        } else {
            bool done = false;
            for (int i = m - 1; i >= 0 && !done; --i) {
                int smallest = smallestAvailable(i);
                int curId = lower_bound(values.begin(), values.end(), cur[i]) - values.begin();
                if (curId == smallest) continue;

                for (int id = curId - 1; id >= 0; --id) {
                    if (total[id] - pref[i][id] > 0) {
                        vector<int> rem = total;
                        for (int j = 0; j < (int)values.size(); ++j) rem[j] -= pref[i][j];
                        --rem[id];
                        prv.assign(cur.begin(), cur.begin() + i);
                        prv.push_back(values[id]);
                        vector<int> tail = appendDescending(values, rem);
                        prv.insert(prv.end(), tail.begin(), tail.end());
                        done = true;
                        break;
                    }
                }
                if (done) break;
            }
            if (!done) prv = appendDescending(values, total);
        }
    }

    cout << prv.size() << '\n';
    for (int i = 0; i < (int)prv.size(); ++i) {
        if (i) cout << ' ';
        cout << prv[i];
    }
    cout << '\n';
    cout << nxt.size() << '\n';
    for (int i = 0; i < (int)nxt.size(); ++i) {
        if (i) cout << ' ';
        cout << nxt[i];
    }
    cout << '\n';
    return 0;
}
