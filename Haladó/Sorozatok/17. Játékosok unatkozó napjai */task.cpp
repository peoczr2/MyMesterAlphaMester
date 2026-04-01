/*
Megoldas lenyege:
A jatekosok reszvetelet napokra bontjuk differencia-tombokkal, majd naprol napra meghatarozzuk,
hogy melyik jatekosok vannak jelen. Ha pontosan egy jatekos van jelen, az az adott nap az o
unatkozo szakaszaba tartozik. Az azonos jatekoshoz tartozo egymas utani napokat intervallummá
fuzzuk.
*/
/*
Hint 1: || Először napokra bontsd a játékosok részvételi szakaszait. ||
Hint 2: || Pontosan egy jelenlévő játékos esetén az adott nap az ő intervallumába kerül. ||
Hint 3: || Az egymást követő azonos játékosnapokat össze lehet vonni. ||
*/
#include <bits/stdc++.h>
using namespace std;

static void addInterval(vector<int> &diff, int l, int r) {
    ++diff[l];
    if (r + 1 < (int)diff.size()) --diff[r + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string line;
    getline(cin, line);

    vector<int> diffA(n + 2, 0), diffB(n + 2, 0), diffC(n + 2, 0);
    auto readPlayer = [&](vector<int> &diff) {
        do {
            getline(cin, line);
        } while (line.empty() && cin);

        stringstream ss(line);
        int m;
        while (ss >> m) {
            for (int i = 0; i < m; ++i) {
                int start, len;
                ss >> start >> len;
                if (len == 0) addInterval(diff, start, start);
                else addInterval(diff, start, start + len - 1);
            }
        }
    };

    readPlayer(diffA);
    readPlayer(diffB);
    readPlayer(diffC);

    vector<pair<int, int>> ans[3];
    pair<int, int> cur = {0, 0};
    int curStart = -1;

    vector<int> a(n + 2), b(n + 2), c(n + 2);
    for (int day = 0; day <= n; ++day) {
        if (day > 0) {
            a[day] = a[day - 1] + diffA[day];
            b[day] = b[day - 1] + diffB[day];
            c[day] = c[day - 1] + diffC[day];
        } else {
            a[day] = diffA[day];
            b[day] = diffB[day];
            c[day] = diffC[day];
        }

        pair<int, int> who = {0, 0};
        int cnt = (a[day] > 0) + (b[day] > 0) + (c[day] > 0);
        if (cnt == 1) {
            if (a[day]) who = {1, 1};
            else if (b[day]) who = {2, 2};
            else who = {3, 3};
        }

        if (who != cur) {
            if (cur != make_pair(0, 0)) {
                ans[cur.first - 1].push_back({curStart, day - 1});
            }
            cur = who;
            curStart = (who == make_pair(0, 0) ? -1 : day);
        }
    }

    if (cur != make_pair(0, 0)) ans[cur.first - 1].push_back({curStart, n});

    for (int p = 0; p < 3; ++p) {
        cout << ans[p].size();
        for (auto [l, r] : ans[p]) cout << ' ' << l << ' ' << r;
        cout << '\n';
    }

    return 0;
}
