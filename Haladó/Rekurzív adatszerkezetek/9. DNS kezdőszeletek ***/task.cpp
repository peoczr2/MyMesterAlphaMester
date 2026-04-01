#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
Minden szekvenciát beteszünk egy trie-ba. Egy szekvencia kezdőszeleteinek a száma
pontosan azoknak a trie-csomópontoknak a száma a gyökértől a levélig vezető úton,
amelyek végpontjai szerepelnek a bemenetben.

Ezért minden szekvenciára végigmegyünk a trie-ban, és megszámoljuk, hány olyan
csomópontot érünk el, amely egy bemeneti szekvencia végét jelöli. A maximumot keresve
megkapjuk a kért szekvenciát.

Hint 1: || A kezdőszeletek kérdése trie-val természetesen modellezhető. ||
Hint 2: || Egy szekvencia pontszáma a saját útján található végpontok száma. ||
Hint 3: || Tartsd meg az eredeti sorszámot és a lexikografikus sorrendet a holtverseny feloldásához. ||
*/

struct Node {
    int next[4];
    bool terminal = false;
    Node() { fill(begin(next), end(next), -1); }
};

int id(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<string> s(N + 1);
    vector<Node> trie(1);
    for (int i = 1; i <= N; ++i) {
        cin >> s[i];
        int u = 0;
        for (char c : s[i]) {
            int t = id(c);
            if (trie[u].next[t] == -1) {
                trie[u].next[t] = trie.size();
                trie.push_back(Node());
            }
            u = trie[u].next[t];
        }
        trie[u].terminal = true;
    }

    int bestIdx = 1, bestCount = -1;
    for (int i = 1; i <= N; ++i) {
        int u = 0, cnt = 0;
        for (char c : s[i]) {
            u = trie[u].next[id(c)];
            if (trie[u].terminal) ++cnt;
        }
        if (cnt > bestCount || (cnt == bestCount && s[i] < s[bestIdx])) {
            bestCount = cnt;
            bestIdx = i;
        }
    }

    cout << bestIdx << '\n' << bestCount << '\n';
    return 0;
}