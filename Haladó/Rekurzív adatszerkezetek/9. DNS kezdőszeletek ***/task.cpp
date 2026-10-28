/*
Megoldási ötlet:
Minden szekvenciát beteszünk egy trie-ba, a karaktereket változatlanul kezelve. Egy szekvencia kezdőszeleteinek száma
pontosan azoknak a trie-csomópontoknak a száma a gyökértől a szekvencia végpontjáig vezető úton, amelyek bemeneti
szekvencia végét jelölik. Ezért minden szekvenciára végigmegyünk a trie-ban, és megszámoljuk ezeket a csomópontokat.
Döntetlen esetén a nagyobb sorszámút tartjuk meg, ezt követeli meg a példa kimenete. Az idő a bemenet teljes hosszával arányos.
*/
/*
Hint 1: || A kezdőszeletek kérdése trie-val természetesen modellezhető. ||
Hint 2: || Egy szekvencia pontszáma a saját útján található végpontok száma. ||
Hint 3: || Minden szekvenciánál járd végig a karaktereit a trie-ban, és minden olyan csúcsnál növeld a számlálót, ahol egy bemeneti szekvencia véget ér. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<pair<char, int>> next;
    bool terminal = false;
    int child(char c) const {
        for (const auto& e : next)
            if (e.first == c) return e.second;
        return -1;
    }
};

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
            int v = trie[u].child(c);
            if (v == -1) {
                v = trie.size();
                trie[u].next.push_back({c, v});
                trie.push_back(Node());
            }
            u = v;
        }
        trie[u].terminal = true;
    }

    int bestIdx = 1, bestCount = -1;
    for (int i = 1; i <= N; ++i) {
        int u = 0, cnt = 0;
        for (char c : s[i]) {
            u = trie[u].child(c);
            if (trie[u].terminal) ++cnt;
        }
        if (cnt >= bestCount) {
            bestCount = cnt;
            bestIdx = i;
        }
    }

    cout << bestIdx << '\n' << bestCount << '\n';
    return 0;
}
