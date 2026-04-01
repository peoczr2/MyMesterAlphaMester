/*
Megoldási ötlet:
A bemenet egy bináris fa zárójeles leírása. A magasság a leghosszabb gyökér-levél út csúcsszáma, a szélesség pedig
egy szinten levő csúcsok maximális száma.

Elég egyszer rekurzívan feldolgozni a leírást. Minden csúcsnál ismerjük a saját szintjét, ezért egy számláló tömbben
megnöveljük az adott szinthez tartozó csúcsszámot. A magasság a bejárás közben látott legnagyobb szint + 1.
Mivel bináris fa, egy belső csúcs alakja mindig `x(bal,jobb)`.
*/
/*
Hint 1: || A magasság és a szélesség is kiszámítható ugyanabból a rekurzív parse-ból. ||
Hint 2: || Ha tudod a csúcs szintjét, a szélességhez csak meg kell számolni, hány csúcs esik ugyanarra a szintre. ||
Hint 3: || A bináris változatban egy belső csúcs után pontosan egy bal és egy jobb részfa jön. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string tree;
int pos = 0;
vector<int> levelCount;
int maxHeight = 0;

void parseTree(int depth) {
    if (depth >= static_cast<int>(levelCount.size())) {
        levelCount.resize(depth + 1, 0);
    }
    ++levelCount[depth];
    maxHeight = max(maxHeight, depth + 1);

    ++pos;  // node label
    if (pos < static_cast<int>(tree.size()) && tree[pos] == '(') {
        ++pos;
        parseTree(depth + 1);
        ++pos;  // ','
        parseTree(depth + 1);
        ++pos;  // ')'
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    getline(cin, tree);
    parseTree(0);

    int maxWidth = 0;
    for (int count : levelCount) {
        maxWidth = max(maxWidth, count);
    }

    cout << maxHeight << '\n';
    cout << maxWidth << '\n';
    return 0;
}