/*
Megoldas: az utasokat egy érkezési sorban, a mozgólépcsőt pedig két párhuzamos
szalagon szimuláljuk. Minden időlépésben előbb a metro viszi el a váróteremben
lévő utasokat, utána jönnek az új utasok, majd legfeljebb ketten felállnak a
mozgólépcsőre és a lépcső egyet lejjebb lép.
*/
/*
Hint 1: || A két irányú forgalmat és a metró érkezését külön eseményként kezeld. ||
Hint 2: || A mozgólépcsőn egyszerre csak a következő szabad helyre lehet belépni, a sorok sorrendje viszont megtartja az érkezést. ||
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

    deque<int> pending;
    vector<deque<int>> belt(2, deque<int>(k, -1));
    int idx = 0;
    int room = 0;
    vector<int> served;

    auto takeMetro = [&](int t) {
        if (t > 0 && t % m == 0) {
            if (room > 0) served.push_back(room);
            room = 0;
        }
    };

    int lastTime = n + k + m;
    for (int t = 0; t <= lastTime; ++t) {
        takeMetro(t);

        while (idx < u && arrival[idx] == t) {
            pending.push_back(arrival[idx]);
            ++idx;
        }

        for (int lane = 0; lane < 2; ++lane) {
            if (!pending.empty() && belt[lane].front() == -1) {
                belt[lane].front() = pending.front();
                pending.pop_front();
            }
        }

        for (int lane = 0; lane < 2; ++lane) {
            for (int pos = k - 1; pos >= 0; --pos) {
                if (belt[lane][pos] == -1) continue;
                if (pos == k - 1) {
                    if (room == l) {
                        cout << served.size() << '\n';
                        for (int i = 0; i < (int)served.size(); ++i) {
                            if (i) cout << ' ';
                            cout << served[i];
                        }
                        cout << '\n';
                        return 0;
                    }
                    ++room;
                    belt[lane][pos] = -1;
                } else if (belt[lane][pos + 1] == -1) {
                    belt[lane][pos + 1] = belt[lane][pos];
                    belt[lane][pos] = -1;
                }
            }
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