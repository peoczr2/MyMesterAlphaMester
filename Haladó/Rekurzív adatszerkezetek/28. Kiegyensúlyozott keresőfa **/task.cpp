/*
Megoldási ötlet:
Tetszőleges olyan bináris keresőfa jó, amelyben minden csúcsnál a bal és jobb részfa mérete legfeljebb
eggyel tér el. Ezt közvetlenül fel lehet építeni a részfa méretéből. Ha egy részfában `cnt` csúcs van,
akkor a gyökér egyik oldalára `cnt/2`, a másikra `cnt-1-cnt/2` csúcs kerül, így a két méret biztosan
legfeljebb egyet különbözik. Ezt rekurzívan ismételve megkapjuk a teljes fa alakját. Ezután inorder
bejárásban kiosztjuk az 1..N értékeket; így automatikusan teljesül a bináris keresőfa tulajdonság.
Mivel a pontazonosítók tetszőlegesek lehetnek, a csúcsokat létrehozási sorrendben számozzuk 1-től N-ig.
*/
/*
Hint 1: || Először ne az értékekkel foglalkozz, hanem csak a fa alakjával: hogyan osztanád szét `cnt` csúcsot két majdnem egyforma részre? ||
Hint 2: || Ha a bal részfában `L`, a jobb részfában `R` csúcs van, akkor elég `|L-R|<=1` feltételt biztosítani minden rekurzív lépésben. ||
Hint 3: || Ha a kész fa inorder bejárásakor sorban az 1,2,...,N számokat írod a csúcsokba, akkor biztosan keresőfát kapsz. ||
*/

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value = 0;
    int left = 0;
    int right = 0;
};

vector<Node> nodes;
int nextId = 1;
int nextValue = 1;

int buildTree(int count) {
    if (count == 0) {
        return 0;
    }

    int current = nextId++;
    int leftCount = count / 2;
    int rightCount = count - 1 - leftCount;

    nodes[current].left = buildTree(leftCount);
    nodes[current].right = buildTree(rightCount);
    return current;
}

void assignValues(int nodeId) {
    if (nodeId == 0) {
        return;
    }

    assignValues(nodes[nodeId].left);
    nodes[nodeId].value = nextValue++;
    assignValues(nodes[nodeId].right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    nodes.assign(n + 1, Node{});
    int root = buildTree(n);
    assignValues(root);

    for (int id = 1; id <= n; ++id) {
        cout << nodes[id].value << ' ' << nodes[id].left << ' ' << nodes[id].right << '\n';
    }

    return 0;
}