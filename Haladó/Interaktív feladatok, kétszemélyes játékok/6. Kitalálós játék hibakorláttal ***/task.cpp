/*
Megoldás lényege:
Minden kérdés után a lehetséges számok egy intervallumot alkotnak. Egy kérdésre a 0 válasz nem fogyaszt hibakeretet, a nem 0 válasz viszont igen, és a két szélső rész a nem 0 válaszokhoz tartozik. Legyen S(q,t) annak a legnagyobb intervallumhossznak a maximuma, amit q kérdéssel és t hátralévő nem 0 válasszal még biztosan ki lehet találni. Ekkor S(0,t)=1, S(q,0)=1 és S(q,t) = S(q-1,t) + 2*S(q-1,t-1), vagyis S(q,t) = C(q,0) + 2C(q,1) + ... + 2^t C(q,t). A legkevesebb kérdés a legkisebb q, amelyre S(q,H) >= N. A játékban az aktuális L hosszú intervallumot úgy osztjuk, hogy a középső, 0 válaszhoz tartozó rész hossza min(L-1, S(q-1,t)), a bal és jobb szélső rész pedig nem nagyobb S(q-1,t-1)-nél. Amikor egy szám maradt, Megoldas-szal válaszolunk. Az idő O(q*H). Az I/O az eva modulon keresztül történik, nem cin/cout-tal.
*/
/*
Hint 1: || Egy 0 választ adó kérdés nem fogyaszt hibakeretet, a nem 0 válasz viszont csökkenti azt. Ezért a jó kérdés úgy osztja az intervallumot, hogy a középső rész a 0 válaszra essen, a két szélső rész pedig a nem 0 válaszokra. ||
Hint 2: || Legyen S(q,t) annak a számnak a maximuma, amit q kérdéssel és t hátralévő nem 0 válasszal még biztosan ki lehet találni. Ekkor S(0,t)=1, S(q,0)=1, és S(q,t) = S(q-1,t) + 2 S(q-1,t-1). ||
Hint 3: || Keresd meg a legkisebb q-t, amelyre S(q,H) legalább N. A játékban egy L hosszú intervallum középső részének hossza legyen min(L-1, S(q-1,t)), a maradék részt pedig oszd el a két szélső ág között úgy, hogy egyik se legyen nagyobb S(q-1,t-1)-nél. ||
*/
#include "eva.h"
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    long n = GetN();
    int h = GetH();
    int w = h + 1;

    // S[q*w + t]: legfeljebb hány jelölt különíthető el q kérdéssel és t hátralévő nem 0 válasszal (n-re levágva)
    vector<long> S(w, 1);
    int q = 0;
    while (S[q * w + h] < n) {
        S.resize((q + 2) * w);
        S[(q + 1) * w] = 1;
        for (int t = 1; t <= h; t++)
            S[(q + 1) * w + t] = min(n, S[q * w + t] + 2 * S[q * w + t - 1]);
        q++;
    }
    auto get = [&](int qq, int tt) { return S[qq * w + tt]; };

    long a = 1, b = n;
    int t = h;
    int rem = q;
    while (a < b) {
        long L = b - a + 1;
        long m = min(L - 1, get(rem - 1, t));
        long R = L - m;
        long l = (t >= 1) ? min(R, get(rem - 1, t - 1)) : 0;
        long A = a + l, B = a + l + m - 1;
        int res = Kerdes(A, B);
        if (res == 0) {
            a = A;
            b = B;
        } else if (res == -1) {
            b = A - 1;
            t--;
        } else {
            a = B + 1;
            t--;
        }
        rem--;
    }
    Megoldas(a);
    return 0;
}
