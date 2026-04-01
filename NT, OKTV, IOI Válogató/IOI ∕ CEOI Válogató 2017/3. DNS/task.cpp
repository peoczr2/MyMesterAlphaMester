/*
Megoldás lényege:
Minden tiltott minta minden előfordulását intervallumnak tekintjük a vizsgált
szekvenciában. Ha egy pozíciót U-ra módosítunk, akkor az összes olyan előfordulás
megszűnik, amely ezt a pozíciót tartalmazza. Így a feladat minden sztringre az
összes tiltott előfordulási intervallum minimális számú ponttal való lefedése.

Az intervallumokat Aho-Corasick automatával generáljuk: a trie-t felépítjük a
tiltott mintákból, majd a bukóélek mentén minden állapothoz kiszámítjuk a benne
végződő legrövidebb tiltott minta hosszát. Egy sztringet balról jobbra olvasva,
ha egy végződő előfordulás bal széle még nem lefedett, akkor az aktuális jobb
végpontra teszünk egy módosítást. Ez a klasszikus greedy intervallumfedés.
*/

#include <bits/stdc++.h>
using namespace std;

static const int ALPHA = 4;
static const int INF = 1e9;

int id(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3;
}

struct Node {
    int next[ALPHA];
    int link = 0;
    int best = INF;
    Node() {
        fill(begin(next), end(next), -1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Node> trie(1);
    for (int i = 0; i < n; ++i) {
        string p;
        cin >> p;
        int v = 0;
        for (char c : p) {
            int x = id(c);
            if (trie[v].next[x] == -1) {
                trie[v].next[x] = (int)trie.size();
                trie.emplace_back();
            }
            v = trie[v].next[x];
        }
        trie[v].best = min(trie[v].best, (int)p.size());
    }

    queue<int> q;
    for (int c = 0; c < ALPHA; ++c) {
        int u = trie[0].next[c];
        if (u != -1) {
            trie[u].link = 0;
            q.push(u);
        } else {
            trie[0].next[c] = 0;
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        trie[v].best = min(trie[v].best, trie[trie[v].link].best);
        for (int c = 0; c < ALPHA; ++c) {
            int u = trie[v].next[c];
            if (u != -1) {
                trie[u].link = trie[trie[v].link].next[c];
                q.push(u);
            } else {
                trie[v].next[c] = trie[trie[v].link].next[c];
            }
        }
    }

    vector<int> answer;
    answer.reserve(m);
    for (int qi = 0; qi < m; ++qi) {
        string s;
        cin >> s;

        int state = 0;
        int lastChosen = 0;
        int changes = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            state = trie[state].next[id(s[i])];
            if (trie[state].best != INF) {
                int left = i + 1 - trie[state].best + 1;
                if (left > lastChosen) {
                    ++changes;
                    lastChosen = i + 1;
                }
            }
        }

        answer.push_back(changes);
    }

    for (int i = 0; i < (int)answer.size(); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}