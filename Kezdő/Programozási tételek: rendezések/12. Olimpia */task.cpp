/*
Megoldás lényege:
Egy tömbben országonként megszámoljuk az arany-, ezüst- és bronzérmeket: minden versenyen az első szám az aranyérmes, a második az ezüstérmes, a további számok (legfeljebb kettő) a bronzérmesek országa. Ezután a legalább egy érmet nyert országokat rendezzük: először az aranyérmek száma, azonos aranynál az ezüstök, majd a bronzok szerint csökkenően, és ha mindhárom egyezik, a kisebb sorszámú ország kerül előre. A táblázatba csak az érmes országok kerülnek. A számlálás a versenyek számával, a rendezés az országok számával arányos, így az időigény a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Országonként három számlálót tarts (arany, ezüst, bronz). Minden versenynél a sor első száma arany, a második ezüst, a többi szám bronz. ||
Hint 2: || A rendezés kulcsai rendre az arany, az ezüst és a bronz szám csökkenő sorrendben, döntetlen esetén az országsorszám növekvő sorrendben. A nulla éremmel rendelkező országokat ne írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    // med[i][0]: arany, med[i][1]: ezüst, med[i][2]: bronz
    vector<array<int, 3>> med(m + 1);
    string line;
    getline(cin, line);  // az első sor vége
    int read = 0;
    while (read < n && getline(cin, line)) {
        istringstream is(line);
        vector<int> e;
        int x;
        while (is >> x) e.push_back(x);
        if (e.empty()) continue;
        med[e[0]][0]++;
        med[e[1]][1]++;
        for (size_t t = 2; t < e.size(); t++) med[e[t]][2]++;
        read++;
    }

    vector<int> ord;
    for (int i = 1; i <= m; i++)
        if (med[i][0] + med[i][1] + med[i][2] > 0) ord.push_back(i);

    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (med[a][0] != med[b][0]) return med[a][0] > med[b][0];
        if (med[a][1] != med[b][1]) return med[a][1] > med[b][1];
        if (med[a][2] != med[b][2]) return med[a][2] > med[b][2];
        return a < b;
    });

    for (int i : ord)
        cout << i << ' ' << med[i][0] << ' ' << med[i][1] << ' ' << med[i][2] << '\n';
    return 0;
}
