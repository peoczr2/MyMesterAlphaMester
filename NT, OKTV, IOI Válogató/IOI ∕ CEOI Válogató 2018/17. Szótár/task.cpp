/*
Megoldás lényege:
Egy szótári szóval való összehasonlítás h+1 lépés, ahol h a két szó közös kezdőszeletének hossza.
Ez átírható: h a keresett szó azon prefixeinek száma, amelyek a szótári szónak is prefixei. Így egy
keresés összehasonlításainak száma = (az átnézett szótári szavak száma) + (a keresett szó prefixeinek
előfordulásainak összege az átnézett szavakban). Az átnézett szavak a szótár elejétől az első egyező
szóig tartanak, vagy a teljes szótárig, ha a keresett szó nincs benne.
A szavakat sorrendben beszúrjuk egy prefixfába (trie), és minden csúcsban számoljuk, hány eddig beszúrt
szó halad át rajta. Amikor az i. szó már bekerült, az i. szóig tartó keresések értékét a keresett szó
prefixeinek csúcsszámlálóiból összegezzük. Az időigény O(összhossz), a memória a csúcsok számával arányos.
*/
/*
Hint 1: || Egy szótári szóval való összehasonlítás h+1 lépés, ahol h a közös kezdőszelet hossza. Próbáld meg a h-t úgy felírni, hogy a keresett szó prefixeit számolod meg. ||
Hint 2: || Ha a keresett szó minden prefixéhez tudod, hány eddig átnézett szótári szónak van ugyanaz a prefixe, akkor az összes összehasonlítás ebből összegezhető. Ehhez prefixfa (trie) kell, amelynek csúcsaiban a beszúrt szavakat számolod. ||
Hint 3: || Szúrd be a szavakat sorrendben, és amikor az i. szó bekerült, válaszolj meg minden olyan keresést, amely az i. szónál ér véget (ott találja meg a szót). A nem talált keresések az összes szó beszúrása után kerülnek sorra. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> dict(n);
    size_t total = 0;
    for (string &s : dict) {
        cin >> s;
        total += s.size();
    }

    int k;
    cin >> k;
    vector<string> query(k);
    for (string &s : query) cin >> s;

    // Minden keresés azon indexig tart, ahol a szótári szó megegyezik a keresettel (vagy n, ha nincs benne)
    unordered_map<string, int> firstPos;
    firstPos.reserve(2 * n);
    for (int i = 0; i < n; i++) firstPos[dict[i]] = i + 1;

    vector<vector<int>> endingAt(n + 1);
    for (int j = 0; j < k; j++) {
        auto it = firstPos.find(query[j]);
        endingAt[it == firstPos.end() ? n : it->second].push_back(j);
    }

    // Prefixfa: nxt[v][c] a v csúcs c betűs gyereke (0 = nincs), cnt[v] a rajta áthaladó beszúrt szavak száma
    vector<array<int, 26>> nxt;
    vector<int> cnt;
    nxt.reserve(total + 1);
    cnt.reserve(total + 1);
    nxt.push_back(array<int, 26>{});
    cnt.push_back(0);

    auto insert = [&](const string &s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[v][c] == 0) {
                nxt[v][c] = (int)nxt.size();
                nxt.push_back(array<int, 26>{});
                cnt.push_back(0);
            }
            v = nxt[v][c];
            cnt[v]++;
        }
    };

    vector<long long> answer(k);
    auto answerEndingAt = [&](int stop) {
        for (int j : endingAt[stop]) {
            // stop db átnézett szó: minden szóra (közös prefix + 1), ezt a prefixek számlálóiból kapjuk
            long long res = stop;
            int v = 0;
            for (char ch : query[j]) {
                v = nxt[v][ch - 'a'];
                if (v == 0) break;
                res += cnt[v];
            }
            answer[j] = res;
        }
    };

    for (int i = 1; i <= n; i++) {
        insert(dict[i - 1]);
        answerEndingAt(i);
    }

    for (int j = 0; j < k; j++) cout << answer[j] << '\n';
    return 0;
}
