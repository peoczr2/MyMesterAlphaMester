/*
Megoldás lényege:
A kifejezés karaktereit csúcsoknak tekintjük: a szomszédos karakterek között él van, és minden egyező zárójelpár
között is. A minimális ugrásszám egyszerű szélességi bejárással adódik az első x-ből. A maximumhoz a gráf
szerkezetét használjuk: a zárójelpárok egymásba ágyazódnak, ezért egy zárójelcsoport bal és jobb vége között
vagy végigmegyünk a csoport minden karakterén, vagy átugrunk a párján. Minden csoportra kiszámoljuk, hogy a benne
lévő x-ből a legtöbb hány csúcson át juthatunk el a csoport bal, illetve jobb végéig; ezt a legbelső csoporttól
kifelé haladva frissítjük. A két x legbelső közös csoportjában két eset közül kell választani: vagy egyenesen
végigmegyünk közöttük, vagy kimegyünk a csoport bal végéig, átugrunk a párra, és a jobb oldalon visszajövünk.
Az időigény O(N), mert minden csoportot konstans sokat dolgozunk fel.
*/
/*
Hint 1: || Tekintsd a karaktereket csúcsoknak: két szomszédos karakter között él van, és minden egyező zárójelpár között is. A minimum így egyszerű szélességi bejárás az első x-ből a másodikig. ||
Hint 2: || A maximumhoz azt kell tudni, hogy egy zárójelcsoport bal és jobb vége között vagy végigmész a csoport minden karakterén, vagy átugrasz a párra. Egy csoporton belül az x-ből a csoport bal, illetve jobb végéig a legjobb út hosszát kell ismerni. ||
Hint 3: || Ezeket az értékeket a legbelső csoporttól kifelé haladva lehet frissíteni: egy külső csoportban a belső csoport bal vagy jobb vége felé vagy végigmész a belső csoporton, vagy a belső csoport párján ugrasz, és a külső csoport másik végéről folytatod. ||
Hint 4: || Ha a két x ugyanabban a legbelső csoportban van, két eset van: egyenesen végigmenni közöttük, vagy az első x-ből balra kimenni a csoport bal végéig, a zárójelpáron átugrani, és a jobb oldalról visszajönni a második x-hez. Ez utóbbinál a csoporton kívüli részeket is be lehet járni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n;
string s;
vector<int> pr;   // pr[i]: a zárójel párja, egyébként -1
vector<int> gp;   // gp[l]: a '(' l-t körülvevő legbelső csoport '(' pozíciója, vagy -1
vector<int> enc;  // enc[u]: az u-t tartalmazó legbelső csoport '(' pozíciója, vagy -1

// a legbelső csoport 'g' ősei között a legfelső csoport
int topmost(int g) {
    while (gp[g] != -1) g = gp[g];
    return g;
}

// u-ból a G csoport (G = enc[u] vagy annak őse) bal és jobb végéig vezető legjobb út csúcsszáma
pair<int, int> lrValues(int u, int G) {
    vector<int> chain;
    int g = enc[u];
    while (true) {
        chain.push_back(g);
        if (g == G) break;
        g = gp[g];
    }
    // u a legbelső csoportban közvetlen elem: balra vagy jobbra megy, majd átugrik a párra
    int l0 = chain[0], r0 = pr[chain[0]];
    int L = max(u - l0 + 1, r0 - u + 2);
    int R = max(r0 - u + 1, u - l0 + 2);
    // kifelé haladva: a belső c csoport (bal c, jobb d) a külső X csoportban (bal x1, jobb x2)
    for (size_t t = 1; t < chain.size(); ++t) {
        int c = chain[t - 1], d = pr[c];
        int x1 = chain[t], x2 = pr[chain[t]];
        int nL = max(L + (c - x1), R + (x2 - d) + 1);
        int nR = max(R + (x2 - d), L + (c - x1) + 1);
        L = nL;
        R = nR;
    }
    return {L, R};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int declared;
    cin >> declared >> s;
    n = s.size();
    pr.assign(n, -1);
    gp.assign(n, -1);
    enc.assign(n, -1);
    vector<int> st;
    for (int u = 0; u < n; ++u) {
        char ch = s[u];
        if (ch == '(') {
            gp[u] = st.empty() ? -1 : st.back();
            st.push_back(u);
        } else if (ch == ')') {
            int l = st.back();
            st.pop_back();
            pr[l] = u;
            pr[u] = l;
        } else {
            enc[u] = st.empty() ? -1 : st.back();
        }
    }
    vector<int> xs;
    for (int u = 0; u < n; ++u)
        if (s[u] == 'x') xs.push_back(u);
    int p = xs[0], q = xs[1];

    // minimum: szélességi bejárás
    vector<int> dist(n, -1);
    queue<int> qu;
    dist[p] = 0;
    qu.push(p);
    while (!qu.empty()) {
        int u = qu.front();
        qu.pop();
        int nb[3] = {u - 1, u + 1, pr[u]};
        for (int v : nb) {
            if (v >= 0 && v < n && dist[v] < 0) {
                dist[v] = dist[u] + 1;
                qu.push(v);
            }
        }
    }
    int mn = dist[q];

    // maximum: a két x legbelső közös csoportja
    int X = enc[p];
    while (X != -1 && !(X < q && q < pr[X])) X = gp[X];

    int best;
    if (X == -1) {
        // nincs közös csoport: p és q különböző legfelső szintű elemekben van
        int Rp, rtermP;
        if (enc[p] == -1) {
            Rp = 1;
            rtermP = p;
        } else {
            int B = topmost(enc[p]);
            Rp = lrValues(p, B).second;
            rtermP = pr[B];
        }
        int Lq, ltermQ;
        if (enc[q] == -1) {
            Lq = 1;
            ltermQ = q;
        } else {
            int B = topmost(enc[q]);
            Lq = lrValues(q, B).first;
            ltermQ = B;
        }
        // a köztes elemek mind bejárhatók
        best = Rp + (ltermQ - rtermP - 1) + Lq;
    } else {
        // p és q az X csoport két különböző eleme (vagy X közvetlen eleme)
        auto item = [&](int u, int &L, int &R, int &lt, int &rt) {
            if (enc[u] == X) {
                L = R = 1;
                lt = rt = u;
                return;
            }
            int C = enc[u];
            while (gp[C] != X) C = gp[C];
            auto lr = lrValues(u, C);
            L = lr.first;
            R = lr.second;
            lt = C;
            rt = pr[C];
        };
        int Lp, Rp, lp, rp, Lq, Rq, lq, rq;
        item(p, Lp, Rp, lp, rp);
        item(q, Lq, Rq, lq, rq);
        int x1 = X, x2 = pr[X];
        // (a) egyenesen végigmegyünk p és q között
        int Va = Rp + (lq - rp - 1) + Lq;
        // (b) balra kimegyünk p-ből, az X párján átugrunk, és jobbról jövünk q-hoz
        int Vb = Lp + (lp - x1 - 1) + 2 + (x2 - rq - 1) + Rq;
        // ha X egy külső csoportban van, a külső részek is bejárhatók az x1 -> x2 körútban
        int O = 0;
        if (gp[X] != -1) {
            int top = topmost(X);
            O = (x1 - top) + (pr[top] - x2);
        }
        best = max(Va, Vb + O);
    }
    cout << mn << '\n' << best - 1 << '\n';
    return 0;
}
