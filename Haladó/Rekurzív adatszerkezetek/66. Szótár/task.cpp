/*
Megoldási ötlet:
A keresés költsége a szótár első p elemére az adott keresett szó és a p darab szótári szó közös kezdőszeleteinek
összegéből, valamint p darab plusz egyes ellenőrzésből áll. Ha a keresett szó benne van a szótárban, akkor p a szó
első előfordulásának sorszáma, különben p = N.

Ezért elég egy trie-t építeni a szótári szavakból, majd a szavakat beszúrási sorrendben feldolgozni. Egy szó végpontján
minden előtaghoz eltároljuk, hogy az eddig beszúrt szavak közül hány halad át rajta. Egy lekérdezés így a saját útján
végigmenve adja a közös kezdőszeletek összegét.
*/
/*
Hint 1: || Egy összehasonlítás költsége nemcsak attól függ, hogy megegyeznek-e, hanem attól is, hogy meddig egyeznek. ||
Hint 2: || Ha az első p szót már beszúrtuk egy trie-ba, akkor egy keresett szó prefixeihez tartozó számlálók összege adja a közös kezdőszeletek összegét. ||
Hint 3: || A teljes válasz: az összehasonlított szavak száma + az összes közös kezdőszelet hossza. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node {
    int child[26];
    int pass = 0;
    Node() { fill(begin(child), end(child), -1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> words(n + 1);
    unordered_map<string, int> position;
    position.reserve(n * 2 + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> words[i];
        position[words[i]] = i;
    }

    int q;
    cin >> q;
    vector<pair<string, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].first;
        auto it = position.find(queries[i].first);
        queries[i].second = (it == position.end() ? n : it->second);
    }

    vector<vector<int>> byPrefix(n + 1);
    for (int i = 0; i < q; ++i) byPrefix[queries[i].second].push_back(i);

    vector<Node> trie(1);
    auto addWord = [&](const string& word) {
        int node = 0;
        for (char c : word) {
            int idx = c - 'a';
            if (trie[node].child[idx] == -1) {
                trie[node].child[idx] = static_cast<int>(trie.size());
                trie.emplace_back();
            }
            node = trie[node].child[idx];
            ++trie[node].pass;
        }
    };

    auto answerQuery = [&](const string& word, int prefixCount) {
        long long common = 0;
        int node = 0;
        for (char c : word) {
            int idx = c - 'a';
            int next = trie[node].child[idx];
            if (next == -1) break;
            node = next;
            common += trie[node].pass;
        }
        return common + prefixCount;
    };

    vector<long long> answers(q, 0);
    for (int i = 1; i <= n; ++i) {
        addWord(words[i]);
        for (int id : byPrefix[i]) {
            answers[id] = answerQuery(queries[id].first, i);
        }
    }

    for (int id : byPrefix[n]) {
        if (queries[id].second == n) continue;
    }
    for (int i = 0; i < q; ++i) {
        if (queries[i].second == n && position.find(queries[i].first) == position.end()) {
            answers[i] = answerQuery(queries[i].first, n);
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << answers[i] << '\n';
    }
    return 0;
}
