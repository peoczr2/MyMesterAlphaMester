/*
Megoldási ötlet:
A megszűntetendő patologikus minták előfordulásai intervallumok a DNS-szekvenciában. Mivel csak az a művelet
engedélyezett, hogy egy bázist `U`-ra változtatunk, azzal csak törlünk előfordulásokat, újakat nem hozunk létre.

Ezért a feladat minden szekvenciára a minták összes előforduló intervallumának lefedése a lehető legkevesebb ponttal.
Az intervallumfedés minimális száma greedy módon számolható, ha balról jobbra haladva azt nézzük, hogy az adott végpontig
véget érő minták közül van-e olyan, amelynek kezdete még nincs lefedve. Ehhez az Aho-Corasick automata minden pozícióban
megadja a legkisebb hosszúságú egyező mintát, vagyis a legnagyobb kezdőpozíciót az aktuális végpontnál.
*/
/*
Hint 1: || Egy `U`-ra cserélt hely egyszerre több mintabeli előfordulást is megszüntethet. ||
Hint 2: || Az összes előfordulás intervallumként kezelhető, és ezeket kell minimális ponthalmazzal lefedni. ||
Hint 3: || Ahol az aktuális végpontnál valamelyik minta még nincs lefedve, ott érdemes a végpontot választani. ||
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Node {
    array<int, 4> next{};
    int fail = 0;
    int bestLen = 1000000000;
    Node() { next.fill(-1); }
};

int idx(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    if (c == 'T') return 3;
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Node> trie(1);
    for (int i = 0; i < n; ++i) {
        string pat;
        cin >> pat;
        int v = 0;
        for (char c : pat) {
            int k = idx(c);
            if (trie[v].next[k] == -1) {
                trie[v].next[k] = static_cast<int>(trie.size());
                trie.emplace_back();
            }
            v = trie[v].next[k];
        }
        trie[v].bestLen = min(trie[v].bestLen, static_cast<int>(pat.size()));
    }

    queue<int> q;
    for (int c = 0; c < 4; ++c) {
        int to = trie[0].next[c];
        if (to != -1) {
            trie[to].fail = 0;
            q.push(to);
        } else {
            trie[0].next[c] = 0;
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        trie[v].bestLen = min(trie[v].bestLen, trie[trie[v].fail].bestLen);
        for (int c = 0; c < 4; ++c) {
            int to = trie[v].next[c];
            if (to != -1) {
                trie[to].fail = trie[trie[v].fail].next[c];
                q.push(to);
            } else {
                trie[v].next[c] = trie[trie[v].fail].next[c];
            }
        }
    }
    vector<int> answers;
    answers.reserve(m);
    for (int seqIdx = 0; seqIdx < m; ++seqIdx) {
        string s;
        cin >> s;
        int state = 0;
        int lastChosen = 0;
        int cnt = 0;
        for (int i = 1; i <= static_cast<int>(s.size()); ++i) {
            int c = idx(s[i - 1]);
            if (c == -1) {
                state = 0;
                continue;
            }
            state = trie[state].next[c];
            if (trie[state].bestLen < (int)1e9) {
                int start = i - trie[state].bestLen + 1;
                if (start > lastChosen) {
                    ++cnt;
                    lastChosen = i;
                }
            }
        }
        answers.push_back(cnt);
    }

    for (int i = 0; i < static_cast<int>(answers.size()); ++i) {
        if (i > 0) cout << ' ';
        cout << answers[i];
    }
    cout << '\n';
    return 0;
}