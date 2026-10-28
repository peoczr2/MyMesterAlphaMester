/*
Megoldás lényege:
A pontokat (x, y) szerint rendezzük, és egyenként hozzáadva építjük a konvex burkot alsó és felső láncként (mint a monoton lánc algoritmusban), közben a lefedett részt háromszögeljük: az új p pont minden burokéllel (u, v), amelyet szigorúan kívülről lát, egy (u, v, p) háromszöget alkot.
Az egy egyenesre eső burokpontokat a láncban hagyjuk, ezért minden háromszög üres, és a később jövő pontok sem esnek bele.
Minden burokélhez megjegyezzük a belső oldalán lévő háromszög harmadik csúcsát (w); amikor p eltakarja az (u, v) élt, a két háromszög együtt a (w, u, p, v) üres négyszöget adja, amely pontosan akkor szigorúan konvex, ha a wp és az uv szakasz belső pontban metszi egymást.
Ha ilyet találunk, kiírjuk óramutatóval ellentétes sorrendben.
Az egyszerre keletkező új háromszögek közös élei sosem adnak konvex négyszöget (a látott burokrész p felől nézve befelé hajlik), így a háromszögelés minden belső élét megvizsgáljuk.
Ha egyik sem jó, nincs megoldás: Lawson tétele szerint bármely két háromszögelés élcserékkel egymásba vihető, tehát ez az egyetlen háromszögelés, egy üres konvex négyszög átlója viszont cserélhető élt adna.
Ugyanígy 0 0 0 0 a válasz, ha N < 4 vagy minden pont egy egyenesen van.
Az időigény blokkonként O(N log N) a rendezés miatt, maga a buroképítés O(N).
*/
/*
Hint 1: || Rendezd a pontokat x, azon belül y szerint, és add hozzá őket egyenként, mint a konvex burok monoton lánc algoritmusában! Az új pont minden általa szigorúan kívülről látott burokéllel egy üres háromszöget alkot, így a pontokból egy háromszögelés épül. ||
Hint 2: || Két szomszédos háromszög együtt üres négyszöget ad; ez akkor konvex, ha a közös él és a két szemközti csúcsot összekötő szakasz belső pontban metszi egymást. Ezért minden burokélnél tárold a mögötte lévő háromszög harmadik csúcsát, és amikor az új pont eltakarja az élt, vizsgáld meg ezt a négyszöget. ||
Hint 3: || Az egy egyenesre eső pontokat ne dobd ki a burokból, az elején egy egyenesre eső pontokat pedig kezeld külön. Ha egyik vizsgált négyszög sem konvex, nincs megoldás: egy háromszögelés, amelyben egyik él sem cserélhető, az egyetlen háromszögelés, egy üres konvex négyszög átlója viszont cserélhető élt adna. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Pont {
    long long x, y;
    int id;
};

vector<Pont> P;  // (x, y) szerint rendezve

long long pszorzat(int o, int a, int b) {
    return (P[a].x - P[o].x) * (P[b].y - P[o].y) - (P[a].y - P[o].y) * (P[b].x - P[o].x);
}

// w és p az uv él két oldalán van; a (w, u, p, v) négyszög szigorúan konvex, ha u és v a wp egyenes két oldalán van.
bool konvex(int w, int u, int p, int v) {
    long long a = pszorzat(w, p, u), b = pszorzat(w, p, v);
    return (a > 0 && b < 0) || (a < 0 && b > 0);
}

// Gyors beolvasás a cin pufferéből (a bemenet akár 2 millió szám).
long long olvas() {
    streambuf* sb = cin.rdbuf();
    int c = sb->sbumpc();
    while (c != EOF && c != '-' && (c < '0' || c > '9')) c = sb->sbumpc();
    bool negativ = (c == '-');
    if (negativ) c = sb->sbumpc();
    long long r = 0;
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = sb->sbumpc();
    }
    return negativ ? -r : r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K = int(olvas());
    while (K--) {
        int n = int(olvas());
        P.resize(n);
        for (int i = 0; i < n; i++) {
            P[i].x = olvas();
            P[i].y = olvas();
            P[i].id = i + 1;
        }
        sort(P.begin(), P.end(), [](const Pont& a, const Pont& b) { return a.x != b.x ? a.x < b.x : a.y < b.y; });

        array<int, 4> valasz = {-1, -1, -1, -1};
        int k = 2;
        while (k < n && pszorzat(0, 1, k) == 0) k++;

        if (n >= 4 && k < n) {
            // A 0..k-1 pontok egy egyenesen vannak, k az első, amelyik nem: háromszögek (i, i+1, k).
            // Láncok: ell[j] a (lanc[j-1], lanc[j]) él belső háromszögének harmadik csúcsa.
            vector<int> egyenes(k + 1), egyenes_ell(k + 1, k);
            iota(egyenes.begin(), egyenes.end(), 0);
            egyenes_ell[k] = k - 2;
            vector<int> rovid = {0, k}, rovid_ell = {-1, 1};
            vector<int> also, also_ell, felso, felso_ell;
            if (pszorzat(0, k - 1, k) < 0) {
                also = rovid, also_ell = rovid_ell;
                felso = egyenes, felso_ell = egyenes_ell;
            } else {
                also = egyenes, also_ell = egyenes_ell;
                felso = rovid, felso_ell = rovid_ell;
            }

            for (int p = k + 1; p < n && valasz[0] < 0; p++) {
                int also_elso = -1, also_utolso = -1, felso_elso = -1, felso_utolso = -1;
                // Az alsó láncról a p által szigorúan kívülről látott éleket vesszük le.
                while (also.size() >= 2 && pszorzat(also[also.size() - 2], also.back(), p) < 0) {
                    int u = also[also.size() - 2], v = also.back(), w = also_ell.back();
                    if (konvex(w, u, p, v)) {
                        valasz = {w, u, p, v};
                        break;
                    }
                    if (also_elso < 0) also_elso = u;
                    also_utolso = v;
                    also.pop_back();
                    also_ell.pop_back();
                }
                if (valasz[0] >= 0) break;
                // Ugyanez a felső láncon.
                while (felso.size() >= 2 && pszorzat(felso[felso.size() - 2], felso.back(), p) > 0) {
                    int u = felso[felso.size() - 2], v = felso.back(), w = felso_ell.back();
                    if (konvex(w, u, p, v)) {
                        valasz = {w, u, p, v};
                        break;
                    }
                    if (felso_elso < 0) felso_elso = u;
                    felso_utolso = v;
                    felso.pop_back();
                    felso_ell.pop_back();
                }
                if (valasz[0] >= 0) break;
                // Az új burokél belső háromszöge: ha a saját láncról vettünk le élt, az utoljára levett csúcs,
                // különben a másik láncról elsőként levett él bal végpontja.
                also_ell.push_back(also_utolso >= 0 ? also_utolso : felso_elso);
                also.push_back(p);
                felso_ell.push_back(felso_utolso >= 0 ? felso_utolso : also_elso);
                felso.push_back(p);
            }
        }

        if (valasz[0] < 0) {
            cout << "0 0 0 0\n";
            continue;
        }
        // valasz = (w, u, p, v), átlói uv és wp: óramutatóval ellentétes sorrendbe rakjuk,
        // és a rendezés szerint legkisebb csúccsal kezdjük.
        int w = valasz[0], u = valasz[1], p = valasz[2], v = valasz[3];
        array<int, 4> kor = pszorzat(u, p, v) > 0 ? array<int, 4>{u, p, v, w} : array<int, 4>{u, w, v, p};
        int kezd = int(min_element(kor.begin(), kor.end()) - kor.begin());
        for (int i = 0; i < 4; i++) cout << P[kor[(kezd + i) % 4]].id << (i < 3 ? " " : "\n");
    }
    return 0;
}
