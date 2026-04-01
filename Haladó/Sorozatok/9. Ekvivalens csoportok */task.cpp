/*
Megoldas lenyege:
Minden felhasznalohoz eltesszuk, hogy mely csoportokban szerepel. Mivel legfeljebb 30 csoport
van, ezt egy 30 bites maszkban tarthatjuk. Ket felhasznalo pontosan akkor ekvivalens, ha a
hozza tartozo maszk azonos. Ezutan a felhasznalokat azonos maszk szerint csoportosítjuk.
*/
/*
Hint 1: || A felhasználókat nem a neve, hanem a csoporttagságot leíró maszk különbözteti meg. ||
Hint 2: || Duplicált megadás nem számít külön, elég a bitet beállítani. ||
Hint 3: || A végén az azonos maszkú felhasználók alkotnak egy ekvivalenciaosztályt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    unordered_map<int, unsigned int> mask;
    mask.reserve(12000);

    for (int i = 0; i < k; ++i) {
        int groupId;
        cin >> groupId;
        unsigned int bit = 1u << (groupId - 1);
        for (;;) {
            int user;
            cin >> user;
            if (user == 0) break;
            mask[user] |= bit;
        }
    }

    unordered_map<unsigned int, vector<int>> classes;
    classes.reserve(mask.size() * 2 + 1);
    for (const auto &entry : mask) {
        classes[entry.second].push_back(entry.first);
    }

    vector<vector<int>> groups;
    groups.reserve(classes.size());
    for (auto &entry : classes) {
        auto &vec = entry.second;
        sort(vec.begin(), vec.end());
        groups.push_back(vec);
    }

    sort(groups.begin(), groups.end(), [](const vector<int> &a, const vector<int> &b) {
        return a.front() < b.front();
    });

    cout << groups.size() << '\n';
    for (const auto &vec : groups) {
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i) cout << ' ';
            cout << vec[i];
        }
        cout << '\n';
    }

    return 0;
}
