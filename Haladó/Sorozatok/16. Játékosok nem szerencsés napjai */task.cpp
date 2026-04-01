/*
Megoldas lenyege:
Mindharom jatekos reszvetelet napokra bontjuk egy diff-tombbel. Ezutan naprol napra
kiszamoljuk, hogy A, B es C kozul ki van jelen. Ha pontosan ketto szerepel, akkor az adott
nap az illető párhoz tartozik. Az azonos párhoz tartozó egymas utani napokat intervallumokká
osszefuzzuk.
*/
/*
Hint 1: || Először napokra bontsd a részvételi szakaszokat. ||
Hint 2: || Ha egy napon pontosan ketten vannak jelen, akkor az a nap valamelyik pároshoz tartozik. ||
Hint 3: || Az egymást követő azonos párokat egy intervallumba lehet összefogni. ||
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

    vector<int> diffA(n + 2, 0), diffB(n + 2, 0), diffC(n + 2, 0);
    auto readPlayer = [&](vector<int> &diff) {
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int start, len;
            cin >> start >> len;
            addInterval(diff, start, start + len - 1);
        }
    };

    readPlayer(diffA);
    readPlayer(diffB);
    readPlayer(diffC);

    vector<pair<int, int>> ab, ac, bc;
    pair<int, int> curPair = {0, 0};
    int curStart = -1;

    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for (int day = 1; day <= n; ++day) {
        a[day] = a[day - 1] + diffA[day];
        b[day] = b[day - 1] + diffB[day];
        c[day] = c[day - 1] + diffC[day];

        pair<int, int> pairToday = {0, 0};
        if (a[day] && b[day] && !c[day]) pairToday = {1, 2};
        else if (a[day] && c[day] && !b[day]) pairToday = {1, 3};
        else if (b[day] && c[day] && !a[day]) pairToday = {2, 3};

        if (pairToday != curPair) {
            if (curPair != make_pair(0, 0)) {
                auto seg = make_pair(curStart, day - 1);
                if (curPair == make_pair(1, 2)) ab.push_back(seg);
                else if (curPair == make_pair(1, 3)) ac.push_back(seg);
                else if (curPair == make_pair(2, 3)) bc.push_back(seg);
            }
            curPair = pairToday;
            curStart = (pairToday == make_pair(0, 0) ? -1 : day);
        }
    }

    if (curPair != make_pair(0, 0)) {
        auto seg = make_pair(curStart, n);
        if (curPair == make_pair(1, 2)) ab.push_back(seg);
        else if (curPair == make_pair(1, 3)) ac.push_back(seg);
        else if (curPair == make_pair(2, 3)) bc.push_back(seg);
    }

    auto print = [](const vector<pair<int, int>> &v) {
        cout << v.size();
        for (auto [l, r] : v) cout << ' ' << l << ' ' << r;
        cout << '\n';
    };

    print(ab);
    print(ac);
    print(bc);

    return 0;
}
