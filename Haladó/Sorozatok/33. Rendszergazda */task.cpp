/*
Megoldas lenyege:
A napokat 1-től N-ig végignézzük. Egy nap biztonságos, ha egyik rendszergazda
sem van szabadságon, és veszélyes, ha mindketten szabadságon vannak. Az
intervallumok hatásait diff-tömbbel jelöljük, majd a napi állapotból összefűzzük
az azonos típusú egymást követő napokat.
*/
/*
Hint 1: || Minden szabadságot napokra bonts le egy külön jelölő tömbbel. ||
Hint 2: || Egy nap akkor biztonságos, ha mindkét jelölő nulla. ||
Hint 3: || Egy nap akkor veszélyes, ha mindkettő egyidejűleg pozitív. ||
*/
#include <bits/stdc++.h>
using namespace std;

static void addInterval(vector<int>& diff, int l, int r) {
    ++diff[l];
    if (r + 1 < (int)diff.size()) --diff[r + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> diffA(n + 2, 0), diffB(n + 2, 0);

    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int l, r;
        cin >> l >> r;
        addInterval(diffA, l, r);
    }

    int lcnt;
    cin >> lcnt;
    for (int i = 0; i < lcnt; ++i) {
        int l, r;
        cin >> l >> r;
        addInterval(diffB, l, r);
    }

    vector<pair<int, int>> safe, danger;
    int curA = 0, curB = 0;
    int startSafe = -1, startDanger = -1;
    for (int day = 1; day <= n; ++day) {
        curA += diffA[day];
        curB += diffB[day];
        bool isSafe = (curA == 0 && curB == 0);
        bool isDanger = (curA > 0 && curB > 0);

        if (isSafe) {
            if (startSafe == -1) startSafe = day;
        } else if (startSafe != -1) {
            safe.push_back({startSafe, day - 1});
            startSafe = -1;
        }

        if (isDanger) {
            if (startDanger == -1) startDanger = day;
        } else if (startDanger != -1) {
            danger.push_back({startDanger, day - 1});
            startDanger = -1;
        }
    }
    if (startSafe != -1) safe.push_back({startSafe, n});
    if (startDanger != -1) danger.push_back({startDanger, n});

    cout << safe.size() << '\n';
    for (auto [l, r] : safe) cout << l << ' ' << r << '\n';
    cout << danger.size() << '\n';
    for (auto [l, r] : danger) cout << l << ' ' << r << '\n';
    return 0;
}
