/*
Megoldási ötlet:
A termek egy rendezett bináris fát alkotnak, ezért a bal kéz szabály szerinti bejárási sorrend a fa preorderje.
A mélység legfeljebb 32, így minden terem útvonala rövid. Egy terem elérhetőségét a gyökértől felfelé haladva
ellenőrizhetjük az útjához tartozó ajtók nyitottságát.

Két terem közül az lesz előbb bejárva, amelyiknek a gyökértől vezető útja lexikografikusan kisebb: először a közös
előtag után az első eltérő lépés dönt, ahol a bal oldali út megelőzi a jobbot. Ha az egyik terem nem érhető el, a
másik az előbb elérhető, ha pedig egyik sem érhető el, 0 a válasz.
*/
/*
Hint 1: || Egy terem elérhetősége a gyökér felé vezető nyitott ajtók ellenőrzésével eldönthető. ||
Hint 2: || A bejárási sorrend a gyökértől vett út leírásának lexikografikus sorrendje. ||
Hint 3: || A bal oldali lépés mindig megelőzi a jobboldalit. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Room {
    int left = 0, right = 0;
    bool leftOpen = false, rightOpen = false;
    int parent = 0;
    bool fromLeft = false;
};

static vector<Room> rooms;

static bool reachable(int node) {
    while (node != 1) {
        int p = rooms[node].parent;
        if (p == 0) return false;
        if (rooms[node].fromLeft) {
            if (!rooms[p].leftOpen) return false;
        } else {
            if (!rooms[p].rightOpen) return false;
        }
        node = p;
    }
    return true;
}

static vector<int> pathBits(int node) {
    vector<int> bits;
    while (node != 1) {
        bits.push_back(rooms[node].fromLeft ? 0 : 1);
        node = rooms[node].parent;
    }
    reverse(bits.begin(), bits.end());
    return bits;
}

static int compareRooms(int a, int b) {
    bool ra = reachable(a);
    bool rb = reachable(b);
    if (!ra && !rb) return 0;
    if (ra && !rb) return -1;
    if (!ra && rb) return 1;
    auto pa = pathBits(a);
    auto pb = pathBits(b);
    int len = min(pa.size(), pb.size());
    for (int i = 0; i < len; ++i) {
        if (pa[i] != pb[i]) return pa[i] < pb[i] ? -1 : 1;
    }
    if (pa.size() != pb.size()) return pa.size() < pb.size() ? -1 : 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    rooms.assign(1, Room());
    rooms.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        int left, right;
        cin >> left >> right;
        rooms[i].left = left;
        rooms[i].right = right;
        if (left != 0) {
            rooms[left].parent = i;
            rooms[left].fromLeft = true;
            rooms[i].leftOpen = true;
        }
        if (right != 0) {
            rooms[right].parent = i;
            rooms[right].fromLeft = false;
            rooms[i].rightOpen = true;
        }
    }

    int q;
    cin >> q;
    int nextRoom = n;
    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 1) {
            cout << compareRooms(a, b) << '\n';
        } else if (type == 2) {
            if (b == 1) {
                if (rooms[a].left == 0) {
                    rooms.push_back(Room());
                    ++nextRoom;
                    rooms[a].left = nextRoom;
                    rooms[nextRoom].parent = a;
                    rooms[nextRoom].fromLeft = true;
                }
                rooms[a].leftOpen = true;
            } else {
                if (rooms[a].right == 0) {
                    rooms.push_back(Room());
                    ++nextRoom;
                    rooms[a].right = nextRoom;
                    rooms[nextRoom].parent = a;
                    rooms[nextRoom].fromLeft = false;
                }
                rooms[a].rightOpen = true;
            }
        } else {
            if (b == 1) rooms[a].leftOpen = false;
            else rooms[a].rightOpen = false;
        }
    }
    return 0;
}
