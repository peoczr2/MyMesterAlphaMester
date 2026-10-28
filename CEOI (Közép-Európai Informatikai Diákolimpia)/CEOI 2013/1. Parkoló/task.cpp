/*
Megoldás lényege:
Az autók akkor nem blokkoltak, ha minden foglalt hely szomszédos a kijárathoz kötött szabad összefüggő halmazzal C, így a feladat: keresünk olyan összefüggő C halmazt, amely tartalmazza a kijáratot és nem tartalmaz autót, és a C-nek a szomszédai (az autók) száma maximális, miközben a meglévő autók mind a szomszédok közé esnek. A leírást jobbról balra, veremmel dolgozzuk fel, minden részparkolóra (kijárat a, terminál b) állapottáblát számolunk: a két terminál állapotát (C, C-nek szomszédos, vagy egyéb) és azt, hogy a két terminál a részen belül összefüggően kapcsolódik-e. Két részt a soros vagy párhuzamos szabály szerint összevonva egy legfeljebb 6 csúcsú segédgráfon, unió-kereséssel ellenőrizzük az összefüggést, és a belső csúcsok autóit megszámoljuk. Az állapotok száma állandó, így az egész O(n) lépésben fut, a végső elhelyezést a választásokból vezetjük vissza.
*/
/*
Hint 1: || Egy szabad hely akkor nem blokkolt, ha szomszédos a kijárathoz kötött szabad részével. Ezért a kérdés egy összefüggő szabad halmaz megtalálása, amelynek szomszédai az autók. ||
Hint 2: || A leírás rekurzív, és egy részparkoló csak a kijáratán és terminálján keresztül kapcsolódik a többihez. Ezért elég minden részhez a két terminál állapotát és a köztük lévő összefüggést tárolni. ||
Hint 3: || A soros és párhuzamos összevonásnál a két terminál közötti új élek adják az összefüggést, és a régi terminálok belső csúcsokká válnak; ezeknél kell megszámolni az autókat és ellenőrizni az x betűk fedettségét. ||
Hint 4: || A részparkolók táblázatait a leírás jobb végétől indulva, veremmel számold ki, így nincs mély rekurzió. A végső elhelyezést a legjobb állapotból felülről lefelé vezesd vissza. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int NEG = -1000000000;
const int SZ = 18;   // állapotok: (ta, tb, cn), ta és tb ∈ {0,1,2}, cn ∈ {0,1}

// ta = 0: a terminál szabad és a kijárathoz kötött halmazhoz tartozik (C)
// ta = 1: a terminál nem szabad-C, de van C-szomszédja a részen belül (autó lesz)
// ta = 2: a terminál nem C, és nincs C-szomszédja a részen belül
// cn = 1: mindkét terminál C, és a részen belül összefüggenek

inline int enc(int ta, int tb, int cn) { return ta * 6 + tb * 2 + cn; }

struct Csomopont {
    int tipus;                       // 0: betű, 1: soros (S), 2: párhuzamos (P)
    int a, b;                        // kijárat és terminál pozíciója a szövegben
    int e1, e2;                      // gyermek csomópontok
    int ertek[SZ];                   // legjobb belső autószám az adott állapotban
    unsigned char g1[SZ], g2[SZ];    // a gyermekek választott állapota
    unsigned char gs[SZ], gt[SZ];    // P: az új kijárat és terminál foglaltsága (0 szabad, 1 foglalt)
};

// Segédgráf legfeljebb 6 csúccsal: a csúcsok pozíciója, C-állapota, C-szomszédság, unió-kereső.
struct Halmaz {
    int n = 0;
    int poz[6];
    bool C[6];
    bool N[6];
    int par[6];
    int hely(int p) {
        for (int i = 0; i < n; ++i)
            if (poz[i] == p) return i;
        poz[n] = p;
        C[n] = false;
        N[n] = false;
        par[n] = n;
        return n++;
    }
    int gyoker(int x) const {
        while (par[x] != x) x = par[x];
        return x;
    }
    void egyesit(int x, int y) {
        x = gyoker(x);
        y = gyoker(y);
        if (x != y) par[x] = y;
    }
};

// Gyermek részparkoló határpontjainak beillesztése a segédgráfba az st állapotban.
void gyermek(Halmaz &H, const Csomopont &G, int st) {
    int ta = st / 6, tb = (st % 6) / 2, cn = st % 2;
    int i = H.hely(G.a);
    H.C[i] = (ta == 0);
    H.N[i] = (ta == 1);
    if (G.b != G.a) {
        int j = H.hely(G.b);
        H.C[j] = (tb == 0);
        H.N[j] = (tb == 1);
        if (ta == 0 && tb == 0 && cn == 1) H.egyesit(i, j);
    }
}

// Új él u és v között: a C-szomszédság és az összefüggés frissítése.
void el(Halmaz &H, int u, int v) {
    int iu = H.hely(u), iv = H.hely(v);
    if (H.C[iu]) H.N[iv] = true;
    if (H.C[iv]) H.N[iu] = true;
    if (H.C[iu] && H.C[iv]) H.egyesit(iu, iv);
}

// Az összetett rész ellenőrzése: a belső autók száma, és az új terminálok állapota.
// ka, kb: az új kijárat és terminál indexe. Hamis, ha érvénytelen.
bool ertekel(const Halmaz &H, int ka, int kb, const string &s, int &belso, int &al) {
    belso = 0;
    for (int i = 0; i < H.n; ++i) {
        if (i == ka || i == kb) continue;
        if (!H.C[i] && H.N[i]) ++belso;
        else if (!H.C[i] && s[H.poz[i]] == 'x') return false;   // az x autó: szomszédos C kell
    }
    int ra = H.C[ka] ? H.gyoker(ka) : -1;
    int rb = H.C[kb] ? H.gyoker(kb) : -1;
    for (int i = 0; i < H.n; ++i) {
        if (!H.C[i]) continue;
        int r = H.gyoker(i);
        if (r != ra && r != rb) return false;   // a kijárathoz nem kötött szabad rész
    }
    int ta = H.C[ka] ? 0 : (H.N[ka] ? 1 : 2);
    int tb = H.C[kb] ? 0 : (H.N[kb] ? 1 : 2);
    int cn = (ta == 0 && tb == 0 && H.gyoker(ka) == H.gyoker(kb)) ? 1 : 0;
    al = enc(ta, tb, cn);
    return true;
}

void kombinalS(vector<Csomopont> &t, int v, const string &s) {
    int i1 = t[v].e1, i2 = t[v].e2;
    for (int s1 = 0; s1 < SZ; ++s1) {
        if (t[i1].ertek[s1] == NEG) continue;
        for (int s2 = 0; s2 < SZ; ++s2) {
            if (t[i2].ertek[s2] == NEG) continue;
            Halmaz H;
            gyermek(H, t[i1], s1);
            gyermek(H, t[i2], s2);
            el(H, t[i1].b, t[i2].a);
            int ka = H.hely(t[i1].a), kb = H.hely(t[i2].b);
            int belso, al;
            if (!ertekel(H, ka, kb, s, belso, al)) continue;
            int ossz = t[i1].ertek[s1] + t[i2].ertek[s2] + belso;
            if (ossz > t[v].ertek[al]) {
                t[v].ertek[al] = ossz;
                t[v].g1[al] = (unsigned char)s1;
                t[v].g2[al] = (unsigned char)s2;
            }
        }
    }
}

void kombinalP(vector<Csomopont> &t, int v, const string &s) {
    int i1 = t[v].e1, i2 = t[v].e2;
    int es = t[v].a, et = t[v].b;
    for (int ces = 0; ces < 2; ++ces) {          // 0: szabad (C), 1: foglalt
        if (ces == 0 && s[es] == 'x') continue;
        for (int cet = 0; cet < 2; ++cet) {
            if (cet == 0 && s[et] == 'x') continue;
            for (int s1 = 0; s1 < SZ; ++s1) {
                if (t[i1].ertek[s1] == NEG) continue;
                for (int s2 = 0; s2 < SZ; ++s2) {
                    if (t[i2].ertek[s2] == NEG) continue;
                    Halmaz H;
                    int ies = H.hely(es);
                    H.C[ies] = (ces == 0);
                    int iet = H.hely(et);
                    H.C[iet] = (cet == 0);
                    gyermek(H, t[i1], s1);
                    gyermek(H, t[i2], s2);
                    el(H, es, t[i1].a);
                    el(H, es, t[i2].a);
                    el(H, t[i1].b, et);
                    el(H, t[i2].b, et);
                    int belso, al;
                    if (!ertekel(H, ies, iet, s, belso, al)) continue;
                    int ossz = t[i1].ertek[s1] + t[i2].ertek[s2] + belso;
                    if (ossz > t[v].ertek[al]) {
                        t[v].ertek[al] = ossz;
                        t[v].g1[al] = (unsigned char)s1;
                        t[v].g2[al] = (unsigned char)s2;
                        t[v].gs[al] = (unsigned char)ces;
                        t[v].gt[al] = (unsigned char)cet;
                    }
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int len = (int)s.size();

    vector<Csomopont> t;
    t.reserve(len + 1);
    vector<int> verem;
    vector<pair<int, int>> elek;       // a gráf élei (pozíciók)

    // A leírást jobbról balra olvassuk: betű -> levél, S -> két gyerek, P -> négy elem a veremben.
    for (int i = len - 1; i >= 0; --i) {
        char ch = s[i];
        if (ch == 'o' || ch == 'x') {
            Csomopont u{};
            u.tipus = 0;
            u.a = u.b = i;
            for (int k = 0; k < SZ; ++k) u.ertek[k] = NEG;
            if (ch == 'o') u.ertek[enc(0, 0, 1)] = 0;
            u.ertek[enc(2, 2, 0)] = 0;
            t.push_back(u);
            verem.push_back((int)t.size() - 1);
        } else if (ch == 'S') {
            int e1 = verem.back(); verem.pop_back();
            int e2 = verem.back(); verem.pop_back();
            Csomopont u{};
            u.tipus = 1;
            u.a = t[e1].a;
            u.b = t[e2].b;
            u.e1 = e1;
            u.e2 = e2;
            for (int k = 0; k < SZ; ++k) u.ertek[k] = NEG;
            elek.push_back({t[e1].b, t[e2].a});
            t.push_back(u);
            int v = (int)t.size() - 1;
            kombinalS(t, v, s);
            verem.push_back(v);
        } else if (ch == 'P') {
            int es = verem.back(); verem.pop_back();
            int e1 = verem.back(); verem.pop_back();
            int e2 = verem.back(); verem.pop_back();
            int et = verem.back(); verem.pop_back();
            int ePos = t[es].a, tPos = t[et].a;
            Csomopont u{};
            u.tipus = 2;
            u.a = ePos;
            u.b = tPos;
            u.e1 = e1;
            u.e2 = e2;
            for (int k = 0; k < SZ; ++k) u.ertek[k] = NEG;
            elek.push_back({ePos, t[e1].a});
            elek.push_back({ePos, t[e2].a});
            elek.push_back({t[e1].b, tPos});
            elek.push_back({t[e2].b, tPos});
            t.push_back(u);
            int v = (int)t.size() - 1;
            kombinalP(t, v, s);
            verem.push_back(v);
        }
        // a '|' és '#' karakterek nem csúcsok, kimaradnak
    }

    int root = verem.back();
    if (t[root].tipus == 0) {          // egyetlen parkolóhely: egy autó fér el
        cout << 1 << '\n' << "x" << '\n';
        return 0;
    }
    int ra = t[root].a, rb = t[root].b;
    if (s[ra] == 'x') {                // foglalt kijárat: csak az egy autó nem blokkolt
        cout << 1 << '\n' << s << '\n';
        return 0;
    }

    // A legjobb végső állapot kiválasztása: a kijárat C, a terminál összefüggően kötött, ha szabad.
    int best = NEG, bestSt = -1;
    for (int k = 0; k < SZ; ++k) {
        if (t[root].ertek[k] == NEG) continue;
        int ta = k / 6, tb = (k % 6) / 2, cn = k % 2;
        if (ta != 0) continue;
        if (tb == 0 && cn == 0) continue;
        if (tb == 2 && s[rb] == 'x') continue;
        int tot = t[root].ertek[k] + (tb == 1 ? 1 : 0);
        if (tot > best) {
            best = tot;
            bestSt = k;
        }
    }

    // Visszavezetés felülről lefelé: minden pozíció C (0) vagy O (1) címkét kap.
    vector<char> lab(len, 0);
    vector<pair<int, int>> stk;
    stk.push_back({root, bestSt});
    while (!stk.empty()) {
        auto [v, st] = stk.back();
        stk.pop_back();
        const Csomopont &nd = t[v];
        if (nd.tipus == 0) {
            lab[nd.a] = (st / 6 == 0) ? 0 : 1;
        } else {
            if (nd.tipus == 2) {
                lab[nd.a] = (char)nd.gs[st];
                lab[nd.b] = (char)nd.gt[st];
            }
            stk.push_back({nd.e1, nd.g1[st]});
            stk.push_back({nd.e2, nd.g2[st]});
        }
    }

    vector<vector<int>> adj(len);
    for (auto [u, v] : elek) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    string out = s;
    int darab = 0;
    for (int i = 0; i < len; ++i) {
        if (s[i] != 'o' && s[i] != 'x') continue;
        bool foglalt = false;
        if (lab[i] == 1)
            for (int u : adj[i])
                if (lab[u] == 0) {
                    foglalt = true;
                    break;
                }
        out[i] = foglalt ? 'x' : 'o';
        if (foglalt) ++darab;
    }
    cout << darab << '\n' << out << '\n';
    return 0;
}
