/*
Megoldási ötlet:
A szabályzat egy gyökerezett fa zárójeles leírása. Egy csomópont neve után vagy rögtön vége jön, ekkor levél,
vagy egy zárójelpár, benne a közvetlen címzettek vesszővel elválasztott listája.

Nem kell külön adatszerkezetet felépíteni: elég egyszer végigparszolni a leírást. Minden embernél meghatározható,
hány közvetlen címzettje van, milyen mélyen van a gyökértől, és levél-e.
- az első válasz a maximális gyerekszám;
- a második válasz a maximális mélység élben mérve;
- a harmadik válasz a levelek száma.
*/
/*
Hint 1: || A szöveg valójában egy fa prefix nevekkel és zárójelezett gyereklistákkal. ||
Hint 2: || Egy ember levelet kap ugyan, de csak akkor nem küldi tovább, ha nincs utána zárójel. ||
Hint 3: || Parzolás közben rögtön frissítheted a maximális gyerekszámot, a maximális mélységet és a levélszámot is. ||
*/

#include <cctype>
#include <iostream>
#include <string>

using namespace std;

string text;
int pos = 0;
int maxChildren = 0;
int maxDepth = 0;
int leafCount = 0;

void parseNode(int depth) {
    while (pos < static_cast<int>(text.size()) && isalpha(static_cast<unsigned char>(text[pos]))) {
        ++pos;
    }

    maxDepth = max(maxDepth, depth);

    if (pos >= static_cast<int>(text.size()) || text[pos] != '(') {
        ++leafCount;
        return;
    }

    ++pos;  // '('
    int children = 0;
    while (true) {
        parseNode(depth + 1);
        ++children;
        if (text[pos] == ',') {
            ++pos;
            continue;
        }
        break;
    }
    ++pos;  // ')'
    maxChildren = max(maxChildren, children);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    getline(cin, text, '#');
    parseNode(0);

    cout << maxChildren << '\n';
    cout << maxDepth << '\n';
    cout << leafCount << '\n';
    return 0;
}