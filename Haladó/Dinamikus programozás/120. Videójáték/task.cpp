/*
Megoldási ötlet:
A lenyomott karaktersorozat minden prefixéhez csak az számít, hogy az Aho-Corasick automatában melyik állapotban
vagyunk. Egy állapotból az A, B vagy C gomb megnyomására determinisztikusan a következő állapotba jutunk, és ott
annyi pontot kapunk, ahány minta végződik ebben az állapotban vagy valamelyik hibakövető őseiben.

Legyen dp[len][state] a len hosszú sorozattal elérhető maximális pontszám. Ezt sorban felépítjük 1-től K-ig. Mivel
az állapotok száma legfeljebb néhány száz, a teljes DP kényelmesen belefér.
*/
/*
Hint 1: || A sok részben átfedő minta miatt prefixfa helyett Aho-Corasick automata kell. ||
Hint 2: || Egy gombnyomás után a következő állapot és a kapott pontszám csak a jelenlegi állapottól függ. ||
Hint 3: || A DP-ben a hossz és az automataállapot lesz az állapot. ||
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Node {
    array<int, 3> next{};
    int link = 0;
    int score = 0;

    Node() {
        next.fill(-1);
    }
};

int idOf(char ch) {
    if (ch == 'A') return 0;
    if (ch == 'B') return 1;
    return 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<Node> trie(1);
    for (int i = 0; i < n; ++i) {
        string pattern;
        cin >> pattern;
        int state = 0;
        for (char ch : pattern) {
            int c = idOf(ch);
            if (trie[state].next[c] == -1) {
                trie[state].next[c] = static_cast<int>(trie.size());
                trie.push_back(Node());
            }
            state = trie[state].next[c];
        }
        ++trie[state].score;
    }

    queue<int> q;
    for (int c = 0; c < 3; ++c) {
        int nextState = trie[0].next[c];
        if (nextState == -1) {
            trie[0].next[c] = 0;
        } else {
            trie[nextState].link = 0;
            q.push(nextState);
        }
    }

    while (!q.empty()) {
        int state = q.front();
        q.pop();
        trie[state].score += trie[trie[state].link].score;
        for (int c = 0; c < 3; ++c) {
            int nextState = trie[state].next[c];
            if (nextState == -1) {
                trie[state].next[c] = trie[trie[state].link].next[c];
            } else {
                trie[nextState].link = trie[trie[state].link].next[c];
                q.push(nextState);
            }
        }
    }

    const int states = static_cast<int>(trie.size());
    const int negInf = -1e9;
    vector<int> dp(states, negInf), nextDp(states, negInf);
    dp[0] = 0;

    for (int len = 0; len < k; ++len) {
        fill(nextDp.begin(), nextDp.end(), negInf);
        for (int state = 0; state < states; ++state) {
            if (dp[state] == negInf) continue;
            for (int c = 0; c < 3; ++c) {
                int to = trie[state].next[c];
                nextDp[to] = max(nextDp[to], dp[state] + trie[to].score);
            }
        }
        dp.swap(nextDp);
    }

    cout << *max_element(dp.begin(), dp.end()) << '\n';
    return 0;
}