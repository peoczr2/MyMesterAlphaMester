/*
Megoldás lényege:
A betűk között legalább egy üres oszlop van, ezért az oszlopok szerinti összefüggő tartományok egy-egy betűt adnak.
Minden betűre megszámoljuk a végpontokat (pontok, amelyeknek pontosan 1 sötét szomszédjuk van) és az elágazásokat
(legalább 3 szomszéd). Az I egy oszlop két végponttal. A V két felső sarokból induló vonal, amelyek alul középen
találkoznak. Az N két végpontja a bal alsó és a jobb felső sarokban van, és van elágazás a szárak találkozásánál.
Az X négy végpontja a négy sarokban van, az elágazások pedig a betű közepén, a középső oszlopokban vannak.
Minden más betű a '-' jelet kapja. Az idő O(K), a bemenet mérete miatt bőven belefér az időlimitbe.
*/
/*
Hint 1: || Először bontsd szét a sorokat betűkre az üres oszlopok mentén: két betű között legalább egy üres oszlop van. ||
Hint 2: || A vázat a pontok szomszédszáma adja: a vonalak végén 1, a találkozásoknál 3 vagy 4 szomszéd van. Számold meg a végpontokat és az elágazásokat, és nézd meg a helyüket is. ||
Hint 3: || I: egy oszlopból áll, két végponttal. V: két felső sarokban végpont, alul középen egy csúcs. N: végpontok a bal alsó és a jobb felső sarokban, és van elágazás. X: négy végpont a sarkokban, és középen négyes elágazás. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Pont {
    int r, c;
};

// Igaz, ha a v listában szerepel a (r, c) pont.
bool van(const vector<Pont>& v, int r, int c) {
    for (const Pont& q : v)
        if (q.r == r && q.c == c) return true;
    return false;
}

// A g rácsból a [c0, c1] oszlopintervallumon lévő betűt felismeri: 'I', 'N', 'V', 'X' vagy '-'.
char felismer(const vector<string>& g, int c0, int c1) {
    int w = c1 - c0 + 1;
    int r0 = 8, r1 = -1;
    for (int r = 0; r < 8; r++)
        for (int c = c0; c <= c1; c++)
            if (g[r][c] == '1') {
                r0 = min(r0, r);
                r1 = max(r1, r);
            }
    int h = r1 - r0 + 1;

    // A betű saját koordinátarendszere: p[r][c], a felső-bal sarok (0, 0).
    vector<string> p(h, string(w, '0'));
    for (int r = 0; r < h; r++)
        for (int c = 0; c < w; c++)
            p[r][c] = g[r0 + r][c0 + c];

    auto sotet = [&](int r, int c) {
        return r >= 0 && r < h && c >= 0 && c < w && p[r][c] == '1';
    };

    vector<Pont> vegpont, elag;
    for (int r = 0; r < h; r++)
        for (int c = 0; c < w; c++) {
            if (p[r][c] != '1') continue;
            int fok = 0;
            for (int dr = -1; dr <= 1; dr++)
                for (int dc = -1; dc <= 1; dc++)
                    if ((dr || dc) && sotet(r + dr, c + dc)) fok++;
            if (fok == 1) vegpont.push_back({r, c});
            else if (fok >= 3) elag.push_back({r, c});
        }

    // I: egyetlen oszlop, két végponttal.
    if (w == 1 && vegpont.size() == 2) return 'I';

    // V: két felső sarokból induló vonal, alul középen találkoznak (a csúcs az alsó két sorban lehet elágazás).
    if (w >= 2 && h >= 2 && vegpont.size() == 2 &&
        van(vegpont, 0, 0) && van(vegpont, 0, w - 1)) {
        vector<int> alul;
        for (int c = 0; c < w; c++)
            if (p[h - 1][c] == '1') alul.push_back(c);
        bool ok = !alul.empty() && alul.size() <= 2 &&
                  alul.back() - alul.front() + 1 == (int)alul.size();
        for (int c : alul)
            if (abs(2 * c - (w - 1)) > 2) ok = false;
        for (size_t i = 0; i < elag.size(); i++)
            if (elag[i].r < h - 2 || abs(2 * elag[i].c - (w - 1)) > 2) ok = false;
        if (ok) return 'V';
    }

    // Elágazás nélkül, és nem V: '-'.
    if (elag.empty()) return '-';

    // Két végpont és elágazás: N, ha a végpontok a bal alsó és a jobb felső sarokban vannak.
    if (vegpont.size() == 2) {
        if (van(vegpont, 0, w - 1) && van(vegpont, h - 1, 0)) return 'N';
        return '-';
    }

    // Négy végpont a sarkokban, és az elágazások középen: X.
    if (vegpont.size() == 4 && van(vegpont, 0, 0) && van(vegpont, 0, w - 1) &&
        van(vegpont, h - 1, 0) && van(vegpont, h - 1, w - 1)) {
        bool ok = true;
        for (const Pont& q : elag)
            if (abs(2 * q.c - (w - 1)) > 1) ok = false;
        if (ok) return 'X';
    }
    return '-';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;
    vector<string> g(8);
    for (string& sor : g) cin >> sor;

    vector<bool> hasznalt(K, false);
    for (int c = 0; c < K; c++)
        for (int r = 0; r < 8; r++)
            if (g[r][c] == '1') hasznalt[c] = true;

    string eredmeny;
    int c = 0;
    while (c < K) {
        if (!hasznalt[c]) {
            c++;
            continue;
        }
        int c0 = c;
        while (c < K && hasznalt[c]) c++;
        eredmeny += felismer(g, c0, c - 1);
    }
    cout << eredmeny << "\n";
    return 0;
}
