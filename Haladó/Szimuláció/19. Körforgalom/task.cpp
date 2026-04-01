/*
Megoldás lényege: a körforgalmat négy helyre bontjuk, de a belépési és a kilépési
helyek nem azonosak. Minden autó előbb megérkezik a saját belépési helyére, majd a
körben helyről helyre halad, és amikor eléri a saját kilépési helyét, még egy
időegység múlva hagyja el a körforgalmat. Egy időegységen belül előbb a belépés
feltételeit vizsgáljuk, csak utána mozognak a bent lévő autók.
*/
/*
Hint 1: || A belépési és a kilépési hely nem ugyanaz a négy hely a körben, ezért érdemes külön leképezést használni a kettőre. ||
Hint 2: || Az autók belépése egy időpillanatban közösen is megtörténhet, ha ugyanazon időpillanat elején még szabadnak látszanak a szükséges helyek. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Car {
    int inRoad, outRoad;
    int arrival;
    int ready;
};

static int nextPos(int pos) {
    return pos == 4 ? 1 : pos + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K, L;
    cin >> n >> K >> L;
    vector<Car> cars(n);
    for (int i = 0; i < n; ++i) {
        cin >> cars[i].inRoad >> cars[i].arrival >> cars[i].outRoad;
        cars[i].ready = cars[i].arrival + L;
    }

    const array<int, 5> enterPos = {0, 1, 4, 3, 2};
    const array<int, 5> exitPos = {0, 2, 3, 4, 1};

    vector<deque<int>> waiting(5);
    for (int i = 0; i < n; ++i) {
        waiting[cars[i].inRoad].push_back(i);
    }

    array<int, 5> slotCar;
    slotCar.fill(-1);
    vector<int> finishTime(n, -1);

    long long bestWait = 0;
    int done = 0;
    int time = 1;

    while (done < n) {
        // Mozgási fázis.
        for (int pos = 4; pos >= 1; --pos) {
            int id = slotCar[pos];
            if (id == -1 || finishTime[id] != time) continue;

            if (pos == exitPos[cars[id].outRoad]) {
                bestWait = max(bestWait, 1LL * time - cars[id].arrival);
                slotCar[pos] = -1;
                ++done;
            } else {
                int np = nextPos(pos);
                if (slotCar[np] == -1) {
                    slotCar[pos] = -1;
                    slotCar[np] = id;
                    finishTime[id] = time + (np == exitPos[cars[id].outRoad] ? 1 : K);
                } else {
                    finishTime[id] = time;
                }
            }
        }

        // Belépési fázis: a sor elején álló autók egymás után próbálnak belépni.
        bool changed = true;
        while (changed) {
            changed = false;
            for (int road = 1; road <= 4; ++road) {
                if (waiting[road].empty()) continue;
                int id = waiting[road].front();
                if (cars[id].ready > time) continue;

                int pos = enterPos[road];
                int next = nextPos(pos);
                int prev = pos == 1 ? 4 : pos - 1;

                if (slotCar[pos] != -1) continue;
                if (slotCar[next] != -1) continue;
                if (slotCar[prev] != -1) continue;

                waiting[road].pop_front();
                slotCar[pos] = id;
                finishTime[id] = time + (pos == exitPos[cars[id].outRoad] ? 1 : K);
                changed = true;
            }
        }

        ++time;
    }

    cout << bestWait << '\n';
    return 0;
}