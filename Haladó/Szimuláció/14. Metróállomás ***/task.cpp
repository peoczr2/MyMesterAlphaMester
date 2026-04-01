/*
Megoldás lényege: külön kezeljük a váróteremben a metróra váró utasokat és a
metróról leszállt, kifelé tartó utasokat. Két, K hosszú mozgólépcsőt
szimulálunk darabszámokkal (fokonként legfeljebb 2 fő): a lefelé menő lépcső
az érkezőket viszi a váróterembe, a felfelé menő a leszállókat viszi ki.
Minden időegységben az alábbi sorrend szerint lépünk: késleltetett leszállók
aktiválása, metró esemény, lefelé mozgás, felfelé mozgás, külső érkezés,
lefelé felszállás, felfelé felszállás.
*/
/*
Hint 1: || A váróteremben kétféle utas van: aki metróra vár, és aki éppen leszállt a metróról, de még nem jutott fel a kijárathoz. ||
Hint 2: || A leszálló utasok nem ugyanabban az időpillanatban léphetnek a felfelé lépcsőre, ezért külön késleltetett számlálót használj. ||
Hint 3: || A kapacitáskorlát csak a váróteremre vonatkozik, nem a lépcsőkön állókra. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, l, m, u;
    cin >> n >> k >> l >> m >> u;
    vector<int> arrival(u);
    for (int i = 0; i < u; ++i) cin >> arrival[i];

    vector<int> metroDrop;
    for (int x; cin >> x; ) metroDrop.push_back(x);

    long long queueDown = 0;      // Utcáról érkezők, lefelé lépcsőre várnak.
    long long roomToMetro = 0;    // Váróteremben metróra várók.
    long long roomToExit = 0;     // Váróteremben kifelé várók (leszálltak).
    long long delayedExit = 0;    // Most leszálltak, a következő időegységben aktiválódnak.

    vector<int> downEsc(k, 0);    // Lefelé lépcső: fokonként 0..2 fő.
    vector<int> upEsc(k, 0);      // Felfelé lépcső: fokonként 0..2 fő.

    int idx = 0;
    vector<int> served;
    int metroIndex = 0;

    auto processMetro = [&](int t, int enteredThisTick) {
        if (t > 0 && t % m == 0) {
            long long canTake = roomToMetro - enteredThisTick;
            if (canTake < 0) canTake = 0;
            if (canTake > 0) served.push_back((int)canTake);
            roomToMetro -= canTake;
            if (metroIndex < (int)metroDrop.size()) {
                delayedExit += metroDrop[metroIndex++];
            }
        }
    };

    int lastTime = n + k + m;
    for (int t = 0; t <= lastTime; ++t) {
        int enteredThisTick = 0;

        roomToExit += delayedExit;
        delayedExit = 0;

        processMetro(t, enteredThisTick);

        for (int pos = k - 1; pos >= 0; --pos) {
            if (downEsc[pos] == 0) continue;
            if (pos == k - 1) {
                roomToMetro += downEsc[pos];
                enteredThisTick += downEsc[pos];
                downEsc[pos] = 0;
            } else {
                int moveCnt = min(downEsc[pos], 2 - downEsc[pos + 1]);
                downEsc[pos] -= moveCnt;
                downEsc[pos + 1] += moveCnt;
            }
        }

        for (int pos = k - 1; pos >= 0; --pos) {
            if (upEsc[pos] == 0) continue;
            if (pos == k - 1) {
                upEsc[pos] = 0;
            } else {
                int moveCnt = min(upEsc[pos], 2 - upEsc[pos + 1]);
                upEsc[pos] -= moveCnt;
                upEsc[pos + 1] += moveCnt;
            }
        }

        while (idx < u && arrival[idx] == t) {
            ++queueDown;
            ++idx;
        }

        int takeDown = min<long long>(queueDown, 2 - downEsc[0]);
        downEsc[0] += takeDown;
        queueDown -= takeDown;

        int takeUp = min<long long>(roomToExit, 2 - upEsc[0]);
        upEsc[0] += takeUp;
        roomToExit -= takeUp;

        if (roomToMetro + roomToExit > l) {
            cout << served.size() << '\n';
            for (int i = 0; i < (int)served.size(); ++i) {
                if (i) cout << ' ';
                cout << served[i];
            }
            cout << '\n';
            return 0;
        }
    }

    cout << served.size() << '\n';
    for (int i = 0; i < (int)served.size(); ++i) {
        if (i) cout << ' ';
        cout << served[i];
    }
    cout << '\n';
    return 0;
}