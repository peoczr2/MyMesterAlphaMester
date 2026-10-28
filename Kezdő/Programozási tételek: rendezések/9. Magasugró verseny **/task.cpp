/*
Megoldás lényege:
Versenyzőnként magasságonként kell egy eredményt képezni: ha a versenyző az adott magasságot teljesítette, az eredmény a szükséges kísérletek száma (1, 2 vagy 3), különben egy nagy érték, vagyis nem teljesítette (akár kihagyta, akár kiesett). A szabály szerint a legmagasabb magasságtól lefelé keressük az első olyan magasságot, ahol az eredmények különböznek, és ott az a jobb, amelyik kevesebb kísérlettel teljesítette a magasságot. Így minden versenyzőhöz egy vektor tartozik (a magasságok fordított sorrendjében), a vektorok lexikografikus rendezése adja a helyezéseket, az azonos vektorú versenyzők pedig holtversenyben vannak.
A bemenetet tokenenként olvassuk: a magasság egy szám, a kísérlet szám és betű (pl. 3J), így a sorok határaival nem kell foglalkozni. Az időigény O(N · M + N · M log N), ami N ≤ 1000 és M ≤ 100 mellett bőven belefér.
*/
/*
Hint 1: || Ne időrendben gondolkodj, hanem a legmagasabb magasságtól lefelé: az első olyan magasság dönt, ahol két versenyző eredménye különbözik. Egy versenyző egy magasságon annyi kísérletet tett, ahány J vagy R betűje van ott, és a J jelenti a sikeres ugrást. ||
Hint 2: || Minden versenyzőhöz készíts egy vektort a magasságok fordított sorrendjében: ha volt J, az érték a kísérletek száma, különben egy nagy szám. A helyezést a vektorok lexikografikus összehasonlítása adja, így a rendezés egyetlen szabályba foglalja az egész versenyt. ||
Hint 3: || A rendezés után az azonos vektorú versenyzőket gyűjtsd egy csoportba, és csoportonként, növekvő sorszámmal, egy sorba írd ki őket. A kiírt sorok száma így a különböző helyezések száma lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // kiserlet[j][c]: a c. versenyző kísérleteinek száma a j. magasságon
    // sikeres[j][c]: a c. versenyző teljesítette-e a j. magasságot
    vector<vector<int>> kiserlet(m, vector<int>(n + 1, 0));
    vector<vector<bool>> sikeres(m, vector<bool>(n + 1, false));

    int j = -1;
    string token;
    while (cin >> token) {
        if (isdigit((unsigned char)token.back())) {
            j++;  // új magasság
            continue;
        }
        int c = stoi(token.substr(0, token.size() - 1));
        kiserlet[j][c]++;
        if (token.back() == 'J') {
            sikeres[j][c] = true;
        }
    }

    // kulcs: a legmagasabbtól lefelé; teljesítés esetén a kísérletek száma, különben nagy érték
    const int NEM_TELJESITETTE = 1000;
    vector<vector<int>> kulcs(n + 1, vector<int>(m));
    for (int c = 1; c <= n; c++) {
        for (int t = 0; t < m; t++) {
            int magassag = m - 1 - t;
            kulcs[c][t] = sikeres[magassag][c] ? kiserlet[magassag][c] : NEM_TELJESITETTE;
        }
    }

    vector<int> sorrend(n);
    iota(sorrend.begin(), sorrend.end(), 1);
    stable_sort(sorrend.begin(), sorrend.end(),
                [&](int x, int y) { return kulcs[x] < kulcs[y]; });

    for (int i = 0; i < n;) {
        int v = i;
        vector<int> csoport;
        while (v < n && kulcs[sorrend[v]] == kulcs[sorrend[i]]) {
            csoport.push_back(sorrend[v]);
            v++;
        }
        sort(csoport.begin(), csoport.end());
        for (size_t q = 0; q < csoport.size(); q++) {
            cout << csoport[q] << (q + 1 < csoport.size() ? ' ' : '\n');
        }
        i = v;
    }

    return 0;
}
