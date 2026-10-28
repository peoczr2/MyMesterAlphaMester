/*
Megoldás lényege:
A csúcsok láthatósági gráfján keressük az 1. és a K. csúcs közötti legrövidebb utat; a közvetítők száma az út élszámánál
eggyel kevesebb. A gráfnak O(N^2) éle is lehet, ezért a K-ból indított szélességi keresést két szám követésével
szimuláljuk: lo és hi a t lépéssel elérhető csúcsok közül a legbaloldalibb, illetve a legjobboldalibb. A láthatósági gráfra
igaz, hogy ha a<b<c<d, a látja c-t és b látja d-t, akkor a látja d-t is. Ebből adódik, hogy a legtávolabbra balra látó
elérhető csúcs csak lo vagy hi lehet (különben a lo és hi közti úton át kellene mennie egy korábban már elért csúcson,
ami ellentmondás). Így a következő lépésben a bal szél min(L[lo], L[hi]), a jobb szél max(R[lo], R[hi]), ahol L[v] és
R[v] a v-ből legmesszebb látható bal-, illetve jobb oldali csúcs. R[v] a v utáni csúcsok felső konvex burkához húzott
érintési pont, amit jobbról balra haladva egy veremmel, amortizáltan O(1) idő alatt kapunk (L[v] ugyanígy balról
jobbra); a pontosan a látóvonalon álló csúcs is takar, ezért a verem csak a szigorúan a vonal alatti csúcsot dobja ki.
Addig lépünk, amíg lo = 1 nem lesz; t lépés után a válasz t-1. Idő: O(N), memória: O(N).
*/
/*
Hint 1: || Két csúcs akkor látja egymást, ha a köztük lévő csúcsok mind szigorúan a köztük húzott egyenes alatt vannak
(a szomszédosak mindig látják egymást). A feladat ezen a láthatósági gráfon az 1. és a K. csúcs közötti legrövidebb út
hossza, a közvetítők száma ennél eggyel kevesebb. A gráf akár N^2 élű is lehet, ezért nem szabad az éleit bejárni. ||
Hint 2: || Indulj a K. csúcsból visszafelé, és kövesd, hogy t lépéssel mely csúcsokat érheted el. Ebből elég a
legbaloldalibb (lo) és a legjobboldalibb (hi) elérhető csúcsot nyilvántartani: a következő lépésben a bal szél a lo és hi
közül az egyik legmesszebbre balra látó csúcsa lesz, a jobb szél hasonlóan. Ez azért igaz, mert ha a<b<c<d és a látja
c-t, b pedig d-t, akkor a látja d-t is. ||
Hint 3: || Minden v csúcsra előre ki kell számolni a legmesszebb látható bal- és jobb oldali csúcsot. A jobb oldali a
v-től jobbra lévő csúcsok felső konvex burkához húzott érintési pont, vagyis a legnagyobb meredekségű csúcs v-ből nézve.
Ha jobbról balra építed a burkot veremmel, akkor v beszúrásakor a lecsúsztatott csúcsok után a verem tetején éppen ez a
csúcs áll. A bal oldali ugyanígy, balról jobbra adódik. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

static char buf[1 << 16];
static size_t bufLen = 0, bufPos = 0;

static inline int readChar() {
    if (bufPos == bufLen) {
        bufLen = fread(buf, 1, sizeof(buf), stdin);
        bufPos = 0;
        if (bufLen == 0) return -1;
    }
    return buf[bufPos++];
}

static bool readInt(int& v) {
    int c = readChar();
    while (c != -1 && (c < '0' || c > '9')) c = readChar();
    if (c == -1) return false;
    v = 0;
    while (c >= '0' && c <= '9') {
        v = v * 10 + (c - '0');
        c = readChar();
    }
    return true;
}

int main() {
    int n, k;
    if (!readInt(n) || !readInt(k)) return 0;

    vector<int> x(n + 1), y(n + 1), L(n + 1), R(n + 1), st;
    for (int i = 1; i <= n; ++i) {
        readInt(x[i]);
        readInt(y[i]);
    }
    st.reserve(n);

    // R[v]: a v-ből látható legtávolabbi jobb oldali csúcs (a jobbra lévő csúcsok felső burkának érintési pontja)
    st.push_back(n);
    R[n] = n;
    for (int v = n - 1; v >= 1; --v) {
        while (st.size() >= 2) {
            int a = st[st.size() - 1], b = st[st.size() - 2];
            // c > 0: a a v-b egyenes fölött van; c < 0: szigorúan alatta
            ll c = (ll)(x[b] - x[v]) * (y[a] - y[v]) - (ll)(y[b] - y[v]) * (x[a] - x[v]);
            if (c < 0) st.pop_back();
            else break;
        }
        R[v] = st.back();
        st.push_back(v);
    }

    // L[v]: a v-ből látható legtávolabbi bal oldali csúcs
    st.clear();
    st.push_back(1);
    L[1] = 1;
    for (int v = 2; v <= n; ++v) {
        while (st.size() >= 2) {
            int a = st[st.size() - 1], b = st[st.size() - 2];
            ll c = (ll)(x[v] - x[b]) * (y[a] - y[b]) - (ll)(y[v] - y[b]) * (x[a] - x[b]);
            if (c < 0) st.pop_back();
            else break;
        }
        L[v] = st.back();
        st.push_back(v);
    }

    int lo = k, hi = k, t = 0;
    while (lo != 1) {
        int nlo = min(L[lo], L[hi]);
        int nhi = max(R[lo], R[hi]);
        lo = nlo;
        hi = nhi;
        ++t;
    }
    printf("%d\n", t - 1);
    return 0;
}
