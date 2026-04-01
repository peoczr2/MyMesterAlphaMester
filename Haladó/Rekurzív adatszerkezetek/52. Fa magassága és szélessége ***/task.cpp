/*
Megoldási ötlet:
A bemenet egy általános gyökerezett fa zárójeles leírása. A magasság a leghosszabb gyökér-levél út csúcsszáma, a
szélesség pedig az egy szinten levő csúcsok maximális száma.

Rekurzív parse közben minden csúcsról tudjuk, milyen mélységben van, ezért a megfelelő szintszámlálót növeljük.
Egy csúcs vagy levél, vagy `x(gy1,gy2,...,gyk)` alakú. A gyereklista vesszőkkel tagolt, amíg el nem érjük a zárójelet.
Így egyetlen bejárásban megkapjuk a maximális magasságot és a szintenkénti darabszámokat is.
*/
/*
Hint 1: || A bináris változathoz képest csak annyi változik, hogy egy csúcsnak tetszőleges számú gyereke lehet. ||
Hint 2: || A szélességhez itt is csak szintenként kell számlálni a csúcsokat. ||
Hint 3: || Ha `(` után addig parse-olsz gyereket, amíg `)` nem jön, automatikusan feldolgozod az összes közvetlen részfát. ||
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
        while (true) {
            parseTree(depth + 1);
            if (tree[pos] == ',') {
                ++pos;
                continue;
            }
            break;
        }
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