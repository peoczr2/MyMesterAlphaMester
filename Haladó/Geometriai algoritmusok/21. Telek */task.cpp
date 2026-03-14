/*
Megoldás lényege:
A P-Q útszakaszt a háromszög (A,B,C) fél-síkjaihoz klippeljük (paraméteres alakban, t∈[0,1]).
Így megkapjuk a szakasz háromszögbelüli részét [L,R]-ként:
- ha nincs vagy csak pontnyi metszet van (R<=L), akkor az út nem vág bele érdemben -> 3.
- ha van pozitív hosszú belső rész, és mindkét végpont szigorúan kívül van, továbbá a belső rész
  a szakasz belsejében van (L>0 és R<1), akkor két részre vág -> 1.
- minden egyéb pozitív hosszú belelógás -> 2.

Idő: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

static long long cross(const Pt& a, const Pt& b, const Pt& c) {
    __int128 x1 = b.x - a.x;
    __int128 y1 = b.y - a.y;
    __int128 x2 = c.x - a.x;
    __int128 y2 = c.y - a.y;
    __int128 v = x1 * y2 - y1 * x2;
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

// 0: outside, 1: boundary, 2: strictly inside
static int pointInTriangle(const Pt& A, const Pt& B, const Pt& C, const Pt& P) {
    long long c1 = cross(A, B, P);
    long long c2 = cross(B, C, P);
    long long c3 = cross(C, A, P);

    bool nonneg = (c1 >= 0 && c2 >= 0 && c3 >= 0);
    bool nonpos = (c1 <= 0 && c2 <= 0 && c3 <= 0);
    if (!nonneg && !nonpos) return 0;
    if (c1 == 0 || c2 == 0 || c3 == 0) return 1;
    return 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Pt A, B, C, P, Q;
    if (!(cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> P.x >> P.y >> Q.x >> Q.y)) {
        return 0;
    }

    // Make triangle CCW.
    if (cross(A, B, C) < 0) swap(B, C);

    long double L = 0.0L, R = 1.0L;
    const long double EPS = 1e-15L;

    auto clipHalfPlane = [&](const Pt& U, const Pt& V) -> bool {
        // Need cross(U, V, P + t*(Q-P)) >= 0
        long double a = (long double)(V.x - U.x) * (long double)(P.y - U.y)
                      - (long double)(V.y - U.y) * (long double)(P.x - U.x);
        long double b = (long double)(V.x - U.x) * (long double)(Q.y - P.y)
                      - (long double)(V.y - U.y) * (long double)(Q.x - P.x);

        if (fabsl(b) <= EPS) {
            if (a < -EPS) return false;
            return true;
        }

        long double t = -a / b;
        if (b > 0) L = max(L, t);
        else R = min(R, t);
        return L <= R + EPS;
    };

    if (!clipHalfPlane(A, B) || !clipHalfPlane(B, C) || !clipHalfPlane(C, A)) {
        cout << 3 << '\n';
        return 0;
    }

    long double LL = max(L, 0.0L);
    long double RR = min(R, 1.0L);

    if (RR - LL <= 1e-12L) {
        cout << 3 << '\n';
        return 0;
    }

    int sP = pointInTriangle(A, B, C, P);
    int sQ = pointInTriangle(A, B, C, Q);

    if (sP == 0 && sQ == 0 && LL > 1e-12L && RR < 1.0L - 1e-12L) {
        cout << 1 << '\n';
    } else {
        cout << 2 << '\n';
    }

    return 0;
}
