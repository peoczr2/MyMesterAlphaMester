/*
Megoldási ötlet:
A feladat a klasszikus „szótárdarabokból rakjuk ki a szöveget” probléma minimális darabszámmal. Legyen dp[i] az első i karakter kirakásához
szükséges legkisebb töredékszám. Ha egy töredék illeszkedik az i. pozíciótól indulva, akkor frissíti a dp végét.

Az illeszkedések gyors kereséséhez prefixfát építünk a töredékekből. Minden kezdőpozícióból a szövegben addig sétálunk lefelé a trie-ban,
amíg van él; minden végpont egy lehetséges darabvéget jelent.
*/
/*
Hint 1: || A DP természetes állapota a kirakott prefix hossza. ||
Hint 2: || Egy pozícióból több különböző hosszú töredék is indulhat, ezeket érdemes egyszerre megtalálni. ||
Hint 3: || Ehhez a szövegtöredékekből épített trie jó eszköz. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int next[26];
    bool end;
    Node() : end(false) {
        fill(next, next + 26, -1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n;
    cin >> n;

    vector<Node> trie(1);
    for (int i = 0; i < n; ++i) {
        string t;
        cin >> t;
        int v = 0;
        for (char ch : t) {
            int c = ch - 'a';
            if (trie[v].next[c] == -1) {
                trie[v].next[c] = static_cast<int>(trie.size());
                trie.push_back(Node());
            }
            v = trie[v].next[c];
        }
        trie[v].end = true;
    }

    const int INF = 1e9;
    int m = static_cast<int>(s.size());
    vector<int> dp(m + 1, INF);
    dp[0] = 0;

    for (int i = 0; i < m; ++i) {
        if (dp[i] == INF) continue;
        int v = 0;
        for (int j = i; j < m; ++j) {
            int c = s[j] - 'a';
            if (trie[v].next[c] == -1) break;
            v = trie[v].next[c];
            if (trie[v].end) dp[j + 1] = min(dp[j + 1], dp[i] + 1);
        }
    }

    cout << (dp[m] == INF ? -1 : dp[m]) << '\n';
    return 0;
}