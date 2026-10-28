/*
Megoldás lényege:
A P-Q szakasz csak akkor metszi a háromszög belsejét, ha a három csúcs közül van a PQ egyenes mindkét oldalán. Ilyenkor a szakasz háromszögbeli része egy t-intervallum [lo, hi] (P + t(Q-P), 0 <= t <= 1): a háromszög minden éle egy lineáris egyenlőtlenség t-re, a metszet pontos racionális számokkal számolható. Ha ez nem pozitív hosszú, az út csak érinti a telket: 3. Különben, ha P vagy Q a telek belsejében van, az út a telekbe egyik végéről belevág: 2. Ellenkező esetben mindkét vég a határon vagy kívül van, és az út két határpont között halad át, két részre vágva a telket: 1. Minden összehasonlítás egész számokkal (__int128-ben) történik, így nincs kerekítési hiba. Idő: O(1)
*/
/*
Hint 1: || Először azt nézd meg, hogy a PQ egyenes átmegy-e a háromszög belsején. Ehhez a három csúcsnak az egyenes két különböző oldalán kell lennie; az oldalt a fordulás előjele (vektoriális szorzat) adja. Ha nincs ilyen, a válasz 3. ||
Hint 2: || Ha igen, számold ki a PQ szakasz háromszögbeli részét a t paraméterrel: a háromszög minden éléhez egy egyenlőtlenség tartozik t-re, így a közös tartomány [lo, hi] lesz. Ha lo nem kisebb, mint hi, akkor csak érintés van (3). Az 1 és 2 eset eldöntéséhez nézd meg, hogy P vagy Q a háromszög belsejében van-e. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

// A (a,b,c) pontok fordulásának előjele: 1 bal, -1 jobb, 0 egy egyenesen.
static int orient(const Pt& a, const Pt& b, const Pt& c) {
    __int128 v = (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

// Racionális szám (den > 0), a t paraméter értékeihez.
struct Frac {
    long long num, den;
};

static bool lessFrac(const Frac& a, const Frac& b) {
    return (__int128)a.num * b.den < (__int128)b.num * a.den;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Pt A, B, C, P, Q;
    if (!(cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> P.x >> P.y >> Q.x >> Q.y)) {
        return 0;
    }

    // A háromszöget pozitív körüljárásúra (óramutató-ellentétesre) fordítjuk.
    if (orient(A, B, C) < 0) swap(B, C);
    const Pt V[3] = {A, B, C};

    // 1) A PQ egyenes csak akkor megy át a telek belsején, ha a csúcsok a két oldalán vannak.
    int s[3] = {orient(P, Q, A), orient(P, Q, B), orient(P, Q, C)};
    bool hasPos = s[0] > 0 || s[1] > 0 || s[2] > 0;
    bool hasNeg = s[0] < 0 || s[1] < 0 || s[2] < 0;
    if (!(hasPos && hasNeg)) {
        cout << 3 << '\n';
        return 0;
    }

    // 2) A P + t(Q-P) szakasz zárt háromszögbeli része [lo, hi], t in [0,1]; pozitív hosszúság kell.
    long long dx = Q.x - P.x, dy = Q.y - P.y;
    Frac lo{0, 1}, hi{1, 1};
    bool empty = false;
    for (int i = 0; i < 3; ++i) {
        const Pt& U = V[i];
        const Pt& W = V[(i + 1) % 3];
        // f(t) = a + b*t >= 0 a háromszög belső (bal) oldalán
        long long a = (W.x - U.x) * (P.y - U.y) - (W.y - U.y) * (P.x - U.x);
        long long b = (W.x - U.x) * dy - (W.y - U.y) * dx;
        if (b == 0) {
            if (a < 0) empty = true;
            continue;
        }
        if (b > 0) {
            Frac t{-a, b};
            if (lessFrac(lo, t)) lo = t;
        } else {
            Frac t{a, -b};
            if (lessFrac(t, hi)) hi = t;
        }
    }
    if (empty || !lessFrac(lo, hi)) {
        cout << 3 << '\n';
        return 0;
    }

    // 3) Ha valamelyik végpont a telek belsejében van, az út belevág; különben két határpont között halad.
    auto strictlyInside = [&](const Pt& X) {
        return orient(V[0], V[1], X) > 0 && orient(V[1], V[2], X) > 0 && orient(V[2], V[0], X) > 0;
    };
    if (strictlyInside(P) || strictlyInside(Q)) {
        cout << 2 << '\n';
    } else {
        cout << 1 << '\n';
    }
    return 0;
}
