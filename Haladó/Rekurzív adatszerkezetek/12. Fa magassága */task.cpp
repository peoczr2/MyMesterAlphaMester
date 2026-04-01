#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
Ugyanazt a F-láncos rekurzív szerkezetet használjuk, mint a következő faelágazós
feladatnál. Egy részfa elején álló F-ek egy láncot adnak, majd az ezen a ponton
kinövő gyermekek zárójelben következnek.

Ha ismerjük egy részfa lánchosszát, akkor a magassága egyszerűen a saját lánchossz
plusz a gyermekek közül a legnagyobb magasság. A leghosszabb elágazás nélküli
szakasz pedig a saját lánchossz és a gyermekek leghosszabb ilyen szakaszának
maximuma.

Hint 1: || A magasság a lánchossz és a legnagyobb gyermekmagasság összegeként áll elő. ||
Hint 2: || Az elágazás nélküli leghosszabb szakasz a lánchossz maximuma a részfában található többi szakasz felett. ||
Hint 3: || Egyetlen rekurzív bejárásban gyűjtsd össze a gyerekek eredményét, majd ezekből képezd a saját válaszodat. ||
*/

struct Res {
    int height = 0;
    int maxChain = 0;
};

string s;
int pos;

Res parseTree() {
    int chain = 0;
    while (pos < (int)s.size() && s[pos] == 'F') {
        ++chain;
        ++pos;
    }

    Res cur;
    int bestChildHeight = 0;
    int bestChildChain = 0;
    while (pos < (int)s.size() && s[pos] == '(') {
        ++pos;
        Res child = parseTree();
        bestChildHeight = max(bestChildHeight, child.height);
        bestChildChain = max(bestChildChain, child.maxChain);
        if (pos < (int)s.size() && s[pos] == ')') ++pos;
    }

    cur.height = chain + bestChildHeight;
    cur.maxChain = max(chain, bestChildChain);
    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    pos = 0;
    Res ans = parseTree();
    cout << ans.height << '\n' << ans.maxChain << '\n';
    return 0;
}