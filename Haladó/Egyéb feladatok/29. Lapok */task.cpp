/*
Megoldás:
Az utoljára lerakott lap látszik felül, ezért a végső színezést legegyszerűbben fordított sorrendben
felépíteni. Minden sorra külön „következő még fehér cella” diszjunkt-halmazon tartjuk nyilván,
így visszafelé haladva minden egységnégyzetet legfeljebb egyszer festünk ki. Ez O(H^2 + összes
valóban kifestett cella) időben előállítja a végső rácsot.

Ezután a teljes H x H rácson megszámoljuk a 4-szomszédos, azonos színű összefüggő komponenseket.
Ezt egyetlen pásztázással és újabb diszjunkt-halmazon végezzük: minden új cella új komponenst indít,
majd azonos színű felső és bal szomszéddal összefésüljük.

Az algoritmus belefér, mert H legfeljebb 1000, tehát összesen legfeljebb egymillió cella van.
*/
/*
Hint 1: || A végső képet érdemes hátulról felépíteni, mert ami egyszer felülre került, azt már nem írja felül semmi. ||
Hint 2: || Soronként egy „következő még szabad oszlop” DSU-val át lehet ugrani a már kifestett cellákat. ||
Hint 3: || Miután megvan a végső színrács, már csak az azonos színű komponensek számolása marad. ||
*/

#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct Rect {
    int x;
    int y;
    int dx;
    int dy;
    int color;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, l;
    cin >> h >> l;
    vector<Rect> rects(l);
    for (int i = 0; i < l; ++i) {
        cin >> rects[i].x >> rects[i].y >> rects[i].dx >> rects[i].dy >> rects[i].color;
    }

    vector<vector<int>> color(h + 1, vector<int>(h + 1, 0));
    vector<vector<int>> nextFree(h + 1, vector<int>(h + 2, 0));
    for (int row = 1; row <= h; ++row) {
        for (int col = 1; col <= h + 1; ++col) {
            nextFree[row][col] = col;
        }
    }

    auto findNext = [&](auto self, int row, int col) -> int {
        if (nextFree[row][col] == col) {
            return col;
        }
        return nextFree[row][col] = self(self, row, nextFree[row][col]);
    };

    for (int idx = l - 1; idx >= 0; --idx) {
        int x1 = rects[idx].x;
        int x2 = rects[idx].x + rects[idx].dx - 1;
        int y1 = rects[idx].y;
        int y2 = rects[idx].y + rects[idx].dy - 1;
        for (int row = y1; row <= y2; ++row) {
            int col = findNext(findNext, row, x1);
            while (col <= x2) {
                color[row][col] = rects[idx].color;
                nextFree[row][col] = findNext(findNext, row, col + 1);
                col = findNext(findNext, row, col);
            }
        }
    }

    int cells = h * h;
    vector<int> parent(cells);
    iota(parent.begin(), parent.end(), 0);

    auto findRoot = [&](auto self, int node) -> int {
        if (parent[node] == node) {
            return node;
        }
        return parent[node] = self(self, parent[node]);
    };

    auto unite = [&](int a, int b) {
        a = findRoot(findRoot, a);
        b = findRoot(findRoot, b);
        if (a == b) {
            return false;
        }
        parent[a] = b;
        return true;
    };

    long long components = 0;
    for (int row = 1; row <= h; ++row) {
        for (int col = 1; col <= h; ++col) {
            ++components;
            int id = (row - 1) * h + (col - 1);
            if (row > 1 && color[row][col] == color[row - 1][col]) {
                int up = (row - 2) * h + (col - 1);
                if (unite(id, up)) {
                    --components;
                }
            }
            if (col > 1 && color[row][col] == color[row][col - 1]) {
                int left = (row - 1) * h + (col - 2);
                if (unite(id, left)) {
                    --components;
                }
            }
        }
    }

    cout << components << '\n';
    return 0;
}