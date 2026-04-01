/*
Megoldás lényege:
Minden ember kedvenc színeit egy rendezett, egyedi listában tároljuk. Egy ember akkor számít bele
az eredménybe, ha létezik egy másik ember, akinek a színhalmaza tartalmazza az övét. Ez egyszerű
részhalmaz-kérdés.

Mivel N<1000 és egy embernek legfeljebb 10 kedvenc színe van, az összes emberpárt végig lehet
próbálni, és két rendezett lista kétmutatós összehasonlításával gyorsan eldönthető a részhalmaz-viszony.
*/
/*
Hint 1: || A kérdés valójában az, hogy hány kedvenchalmaz részhalmaza valamely másik halmaznak. ||
Hint 2: || Egy ember színlistáját érdemes rendezni és duplikátummentesíteni. ||
Hint 3: || Két rendezett lista között a részhalmaz-viszony két mutatóval ellenőrizhető. ||
*/

#include <bits/stdc++.h>
using namespace std;

static bool isSubset(const vector<int>& smallSet, const vector<int>& bigSet) {
    int i = 0;
    int j = 0;
    while (i < (int)smallSet.size() && j < (int)bigSet.size()) {
        if (smallSet[i] == bigSet[j]) {
            ++i;
            ++j;
        } else if (smallSet[i] > bigSet[j]) {
            ++j;
        } else {
            return false;
        }
    }
    return i == (int)smallSet.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_map<string, int> colorId;
    vector<vector<int>> favorites(n);

    for (int i = 0; i < n; ++i) {
        int d;
        cin >> d;
        favorites[i].reserve(d);
        for (int j = 0; j < d; ++j) {
            string color;
            cin >> color;
            auto it = colorId.find(color);
            int id;
            if (it == colorId.end()) {
                id = (int)colorId.size();
                colorId[color] = id;
            } else {
                id = it->second;
            }
            favorites[i].push_back(id);
        }
        sort(favorites[i].begin(), favorites[i].end());
        favorites[i].erase(unique(favorites[i].begin(), favorites[i].end()), favorites[i].end());
    }

    int answer = 0;
    for (int i = 0; i < n; ++i) {
        bool ok = false;
        for (int j = 0; j < n && !ok; ++j) {
            if (i == j) {
                continue;
            }
            if (favorites[i].size() > favorites[j].size()) {
                continue;
            }
            ok = isSubset(favorites[i], favorites[j]);
        }
        answer += ok;
    }

    cout << answer << '\n';
    return 0;
}