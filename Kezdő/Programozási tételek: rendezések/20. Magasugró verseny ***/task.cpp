/*
Megoldás lényege:
A magasságokat csökkenő sorrendben vesszük, és minden versenyzőhöz magasságonként egy értéket rendelünk: ha átugrotta a magasságot, az érték 1000 mínusz a sikeres ugráshoz szükséges kísérletek száma, különben 0. Ezeket az értékeket magasság szerint csökkenő sorrendben egy vektorba írjuk, így a vektorok lexikografikus összehasonlítása pontosan a feladat szabályát adja: az első eltérő magasságon a jobb érték dönt. A versenyzőket a vektoraik szerint csökkenően rendezzük, az azonos vektorúak holtversenyben vannak, és egy sorba kerülnek sorszám szerint növekvően. Az időigény O(N·M·log N), ami a korlátok mellett bőven elég.
*/
/*
Hint 1: || Ne a verseny menetét szimuláld: elég magasságonként rögzíteni, ki ugrotta át a magasságot és hány kísérletből. ||
Hint 2: || Minden versenyzőt jellemezhetsz magasságonként egy számmal úgy, hogy a nagyobb szám mindig jobb helyezést jelentsen, és a magasságokat csökkenő sorrendben nézed. ||
Hint 3: || A rangsor lexikografikus rendezés: két versenyző összehasonlításakor az első eltérő magasságon dönt az érték, és ha minden magasságon azonos az eredmény, akkor holtverseny van. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> magassag;            // a magasságok, beolvasási sorrendben
    vector<vector<int>> siker;       // siker[t][x]: a sikeres ugráshoz szükséges kísérletek száma, 0 ha nem sikerült
    vector<int> kiserlet(n + 1, 0);  // az aktuális magasságon eddigi kísérletek száma
    string tok;
    while (cin >> tok) {
        if (isdigit(static_cast<unsigned char>(tok.back()))) {
            magassag.push_back(stoi(tok));
            siker.emplace_back(n + 1, 0);
            fill(kiserlet.begin(), kiserlet.end(), 0);
        } else if (!magassag.empty()) {
            int x = stoi(tok.substr(0, tok.size() - 1));
            int t = (int)magassag.size() - 1;
            if (siker[t][x] == 0) {
                ++kiserlet[x];
                if (tok.back() == 'J') siker[t][x] = kiserlet[x];
            }
        }
    }

    int M = (int)magassag.size();
    vector<int> sorrend(M);  // magasság-indexek csökkenő magassági sorrendben
    iota(sorrend.begin(), sorrend.end(), 0);
    sort(sorrend.begin(), sorrend.end(), [&](int a, int b) { return magassag[a] > magassag[b]; });

    // kulcs[x]: a versenyző értékei magasságonként csökkenő sorrendben (nagyobb = jobb)
    vector<vector<int>> kulcs(n + 1, vector<int>(M, 0));
    for (int x = 1; x <= n; ++x)
        for (int i = 0; i < M; ++i) {
            int s = siker[sorrend[i]][x];
            kulcs[x][i] = s ? 1000 - s : 0;
        }

    vector<int> ids(n);
    iota(ids.begin(), ids.end(), 1);
    stable_sort(ids.begin(), ids.end(), [&](int a, int b) { return kulcs[a] > kulcs[b]; });

    // azonos kulcsú versenyzők egy sorba kerülnek
    string ki;
    for (int i = 0; i < n;) {
        int j = i;
        while (j < n && kulcs[ids[j]] == kulcs[ids[i]]) ++j;
        for (int k = i; k < j; ++k) {
            if (k > i) ki += ' ';
            ki += to_string(ids[k]);
        }
        ki += '\n';
        i = j;
    }
    cout << ki;
    return 0;
}
