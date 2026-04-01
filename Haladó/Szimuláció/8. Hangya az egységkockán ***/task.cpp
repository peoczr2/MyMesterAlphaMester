/*
Az állapotot a választott lap és az azon követett irány adja meg. Jobbra forduláskor
ugyanazon lap következő éle jön, balra forduláskor pedig a csúcsnál a harmadik, a lap
által nem használt élre lépünk át, és megkeressük azt a szomszédos lapot, amely ezen az
élen ebben az irányban halad tovább.
*/
/*
Hint 1: || A hangya mozgását állapotgépként kezeld: mindig a jelenlegi lap és az aktuális irány dönt a következő lépésről. ||
Hint 2: || A végső válaszokhoz elég megszámolni az érintett lapokat és a gyakoriságukat. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Vec {
    int x, y, z;
};

static Vec operator+(const Vec& a, const Vec& b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

static bool operator==(const Vec& a, const Vec& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

static void printVec(const Vec& v) {
    cout << v.x << ' ' << v.y << ' ' << v.z << '\n';
}

static int faceCycles[6][4][3] = {
    {{0, 0, 0}, {0, 1, 0}, {0, 1, 1}, {0, 0, 1}},
    {{1, 0, 0}, {1, 0, 1}, {1, 1, 1}, {1, 1, 0}},
    {{0, 0, 0}, {0, 0, 1}, {1, 0, 1}, {1, 0, 0}},
    {{0, 1, 0}, {1, 1, 0}, {1, 1, 1}, {0, 1, 1}},
    {{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}},
    {{0, 0, 1}, {0, 1, 1}, {1, 1, 1}, {1, 0, 1}}
};

static Vec cycleVertex(int face, int idx) {
    return {faceCycles[face][idx][0], faceCycles[face][idx][1], faceCycles[face][idx][2]};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    Vec pos{0, 0, 0};
    int face = 2; // y = 0
    int edge = 0;  // 000 -> 001 on the y = 0 face

    printVec(pos);

    pos = cycleVertex(face, (edge + 1) % 4);
    printVec(pos);

    for (char c : s) {
        Vec cur = cycleVertex(face, edge);

        if (c == 'J') {
            edge = (edge + 1) % 4;
            pos = cycleVertex(face, (edge + 1) % 4);
        } else {
            Vec target;
            bool found = false;
            Vec rightNext = cycleVertex(face, (edge + 2) % 4);

            Vec candidates[3] = {
                {1 - pos.x, pos.y, pos.z},
                {pos.x, 1 - pos.y, pos.z},
                {pos.x, pos.y, 1 - pos.z}
            };

            for (const Vec& cand : candidates) {
                if (cand == cur || cand == rightNext) continue;

                for (int f = 0; f < 6 && !found; ++f) {
                    for (int i = 0; i < 4 && !found; ++i) {
                        Vec a = cycleVertex(f, i);
                        Vec b = cycleVertex(f, (i + 1) % 4);
                        if (a == pos && b == cand) {
                            face = f;
                            edge = i;
                            target = cand;
                            found = true;
                        }
                    }
                }
            }

            pos = target;
        }
        printVec(pos);
    }

    return 0;
}