/*
Megoldas lenyege:
A verseny kezdo sorrendje adja az erkezesek sorrendjet. Minden csapatkodhoz eltesszuk a ket
beert tagot es azok erkezesi helyet. Ha egy csapatbol mindket tag megvan, akkor az a csapat
kiirhato az elso sorba. A gyoztes az a teljes csapat, amelynek a ket erkezesi hely osszege
minimalis; holtversenyben a kisebb csapatkod nyer.
*/
/*
Hint 1: || Az input sorrendje az érkezési sorrend, ezért az indexeket külön nem kell keresni. ||
Hint 2: || Egy csapat pontszáma a két tag érkezési helyének összege. ||
Hint 3: || Az első sorhoz csak a teljes csapatok kódjait kell rendezve kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct TeamInfo {
    vector<int> members;
    vector<int> positions;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_map<int, TeamInfo> teams;
    teams.reserve(n * 2 + 1);

    for (int pos = 1; pos <= n; ++pos) {
        int participant, code;
        cin >> participant >> code;
        auto &info = teams[code];
        if ((int)info.members.size() < 2) {
            info.members.push_back(participant);
            info.positions.push_back(pos);
        }
    }

    vector<int> completeCodes;
    completeCodes.reserve(teams.size());

    int bestCode = 0;
    int bestSum = INT_MAX;
    vector<int> bestMembers;

    for (const auto &entry : teams) {
        int code = entry.first;
        const auto &info = entry.second;
        if ((int)info.members.size() == 2) {
            completeCodes.push_back(code);
            int sum = info.positions[0] + info.positions[1];
            if (sum < bestSum || (sum == bestSum && code < bestCode)) {
                bestSum = sum;
                bestCode = code;
                bestMembers = info.members;
            }
        }
    }

    sort(completeCodes.begin(), completeCodes.end());

    if (completeCodes.empty()) {
        cout << 0 << '\n';
        cout << 0 << '\n';
        return 0;
    }

    for (size_t i = 0; i < completeCodes.size(); ++i) {
        if (i) cout << ' ';
        cout << completeCodes[i];
    }
    cout << '\n';

    cout << bestCode;
    for (int member : bestMembers) cout << ' ' << member;
    cout << '\n';

    return 0;
}
