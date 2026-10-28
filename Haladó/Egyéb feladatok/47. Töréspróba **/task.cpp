/*
Megoldás lényege:
Egy töréspróba két kimenetelű: ha az erő nagyobb a szilárdságnál, a minta eltörik és többet nem használható, különben ép marad. Ezért t próbával és m mintával legfeljebb D(t,m) = C(t,0) + C(t,1) + ... + C(t,m) különböző szilárdság különböztethető meg, mert egy próba után vagy eggyel kevesebb minta és próba marad (törés), vagy ugyanannyi minta és eggyel kevesebb próba (ép), így D(t,m) = D(t-1,m-1) + D(t-1,m). A feladat a legkisebb t-t kéri, amelyre D(t,M) legalább H, és ez t-ben monoton, ezért bináris kereséssel keressük. A binomiális tagokat egyenként, egész osztással számoljuk, és azonnal megállunk, amint az összeg eléri H-t, így nincs túlcsordulás. Az időigény O(M · log H).
*/
/*
Hint 1: || Minden próba két kimenetelű, és a törés után a minta elvész. Gondold végig, hány különböző szilárdságot tudsz t próbával és m mintával biztosan megkülönböztetni, és keress erre rekurziót. ||
Hint 2: || Ha az első próba eltöri a mintát, marad t-1 próba és m-1 minta; ha nem törik el, marad t-1 próba és m minta. Ebből D(t,m) = D(t-1,m-1) + D(t-1,m), amelynek zárt alakja binomiális együtthatók összege. ||
Hint 3: || A t-re monoton keresés bináris kereséssel gyors. Az összeget a C(t,i) tagok folytonos számolásával építsd, és ha már eléri H-t, állj meg: így a számok nem nőnek túl. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Igaz, ha t próbával és m mintával legalább H különböző szilárdság megkülönböztethető,
// vagyis sum_{i=0}^{m} C(t,i) >= H. A tagokat egyenként számoljuk, és már a H elérésekor megállunk.
bool enough(ll t, ll m, ll H) {
    ll c = 1;   // C(t,0)
    ll s = 1;   // az eddigi összeg
    if (s >= H) return true;
    for (ll i = 1; i <= m && i <= t; ++i) {
        c = c * (t - i + 1) / i;   // C(t,i) = C(t,i-1) * (t-i+1) / i, mindig pontosan osztható
        s += c;
        if (s >= H) return true;
    }
    return false;
}

int main() {
    ll M, H;
    cin >> M >> H;
    // H-1 próba mindig elég (lineáris keresés egy mintával), ezért ez a felső határ
    ll lo = 1, hi = H - 1;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (enough(mid, M, H)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << '\n';
    return 0;
}
