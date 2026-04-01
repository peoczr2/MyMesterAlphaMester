/*
Megoldás lényege: időlépésenként szimuláljuk az autókat balról jobbra. Egy autó
egy lépésben legfeljebb egy cellát haladhat, az újonnan érkező autók pedig a
következő időegységben kezdhetnek el mozogni. A lámpa állapotát az adott időegység
száma alapján döntjük el, és csak a zebrára lépést tiltjuk pirosnál.
*/
/*
Hint 1: || A kocsik sorrendje nem változik, ezért elég a jelenlegi pozícióikat és egy sorban várakozó belépőket tárolni. ||
Hint 2: || A lámpa csak azt akadályozza, hogy valaki a zebrára lépjen; a többi cellára a szokásos ütközési szabályok érvényesek. ||
*/

#include <bits/stdc++.h>
using namespace std;

static bool isGreen(long long t, long long P, long long U) {
    long long phase = (t - 1) % P;
    return phase < P - U;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, B;
    if (!(cin >> N >> B)) return 0;

    vector<long long> arrive(B);
    for (int i = 0; i < B; ++i) cin >> arrive[i];
    long long P, U;
    cin >> P >> U;

    const int zebra = N + 1;
    const int exitPos = 2 * N + 2;

    struct Car {
        int id;
        int pos;
    };

    vector<Car> active;
    active.reserve(B);
    deque<int> waiting;
    vector<long long> exitTime(B, -1);

    int nextArr = 0;
    int exited = 0;
    for (long long t = 0; exited < B; ++t) {
        while (nextArr < B && arrive[nextArr] == t) {
            waiting.push_back(nextArr);
            ++nextArr;
        }

        if (!waiting.empty() && (active.empty() || active.back().pos > 1)) {
            active.push_back({waiting.front(), 1});
            waiting.pop_front();
        }

        vector<Car> nextActive;
        nextActive.reserve(active.size() + 1);

        bool green = isGreen(t + 1, P, U);
        for (int i = 0; i < (int)active.size(); ++i) {
            int cur = active[i].pos;
            int target = cur + 1;
            bool canMove = true;
            if (i > 0 && target >= active[i - 1].pos) canMove = false;
            if (target == zebra && !green) canMove = false;
            if (canMove) {
                if (target == exitPos) {
                    exitTime[active[i].id] = t + 1;
                    ++exited;
                } else {
                    nextActive.push_back({active[i].id, target});
                }
            } else {
                nextActive.push_back(active[i]);
            }
        }

        active.swap(nextActive);
    }

    for (int i = 0; i < B; ++i) {
        cout << exitTime[i] << '\n';
    }
    return 0;
}