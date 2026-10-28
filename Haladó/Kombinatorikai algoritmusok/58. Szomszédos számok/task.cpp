/*
Megoldás lényege: az érdekes számokat hosszuk, majd lexikografikus sorrendjük adja. Ugyanolyan
hosszú szomszédot úgy keresünk, hogy jobbról balra haladva megkeressük az első olyan pozíciót,
ahol a jegy megváltoztatható (a rákövetkezőhöz növelhető, az előzőhöz csökkenthető), és a
maradék összeg elhelyezhető a hátralévő pozíciókon (0..M jegyekkel, összeg legfeljebb
hátralévő darab * M). A maradékot a rákövetkező esetén a lehető legkisebb, az előző esetén a
lehető legnagyobb jegyekkel töltjük ki. Ha nincs ilyen pozíció, a rákövetkező a hosszabb
legkisebb érdekes szám (első jegye 1), az előző a rövidebb legnagyobb érdekes szám (M, utána
csupa 0). Az idő O(L), ahol L a jegyek száma; a számok 64 biten kezelhetők.
*/
/*
Hint 1: || Ugyanolyan hosszú szomszéd keresésekor jobbról balra haladj, és keresd az első olyan jegyet, amelyet növelve (vagy csökkentve) a maradék összeg még kitölthető. ||
Hint 2: || A maradék összeget a hátralévő jegyekre úgy oszthatod szét, hogy minden jegy legfeljebb M lehet: egy pozíción a kitöltés határa a maradék összeg és a hátralévő pozíciók száma alapján adódik. ||
Hint 3: || Ha nincs ilyen pozíció, a szám hosszát egyel változtatod: a rákövetkező a legkisebb, a megelőző a legnagyobb érdekes szám a szomszédos hosszon. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Lexikografikusan legkisebb, len hosszú, sum összegű sorozat (jegyek 0..M);
// firstPositive esetén az első jegy legalább 1.
static vector<int> smallestFill(int len, long long sum, long long M, bool firstPositive) {
    vector<int> a;
    long long rem = sum;
    for (int i = 0; i < len; ++i) {
        long long left = len - 1 - i;
        long long low = max(0LL, rem - left * M);
        if (i == 0 && firstPositive) low = max(low, 1LL);
        a.push_back((int)low);
        rem -= low;
    }
    return a;
}

// Lexikografikusan legnagyobb, len hosszú, sum összegű sorozat (jegyek 0..M).
static vector<int> largestFill(int len, long long sum, long long M) {
    vector<int> a;
    long long rem = sum;
    for (int i = 0; i < len; ++i) {
        long long high = min(M, rem);
        a.push_back((int)high);
        rem -= high;
    }
    return a;
}

static void printDigits(const vector<int>& a) {
    if (a.empty()) {
        cout << "-1\n";
        return;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N, M;
    cin >> N >> M;
    vector<int> s;
    int x;
    while (cin >> x) s.push_back(x);
    int L = s.size();

    // P[i] = s[0] + ... + s[i-1]
    vector<long long> P(L + 1, 0);
    for (int i = 0; i < L; ++i) P[i + 1] = P[i] + s[i];

    // Rákövetkező: azonos hossz, különben a hosszabb legkisebb
    vector<int> nxt;
    bool hasNxt = false;
    for (int i = L - 1; i >= 0 && !hasNxt; --i) {
        long long pref = P[i];
        long long left = L - 1 - i;
        long long lo = M - pref - left * M;
        long long hi = min(M, M - pref);
        long long d = max({(long long)s[i] + 1, lo, 0LL});
        if (d <= hi) {
            nxt.assign(s.begin(), s.begin() + i);
            nxt.push_back((int)d);
            auto tail = smallestFill(L - 1 - i, M - pref - d, M, false);
            nxt.insert(nxt.end(), tail.begin(), tail.end());
            hasNxt = true;
        }
    }
    if (!hasNxt && L < N) {
        nxt = smallestFill(L + 1, M, M, true);
        hasNxt = true;
    }

    // Megelőző: azonos hossz, különben a rövidebb legnagyobb
    vector<int> prv;
    bool hasPrv = false;
    for (int i = L - 1; i >= 0 && !hasPrv; --i) {
        long long pref = P[i];
        long long left = L - 1 - i;
        long long lo = M - pref - left * M;
        long long hi = min((long long)s[i] - 1, M - pref);
        long long dlo = max({lo, (i == 0 ? 1LL : 0LL), 0LL});
        if (dlo <= hi) {
            prv.assign(s.begin(), s.begin() + i);
            prv.push_back((int)hi);
            auto tail = largestFill(L - 1 - i, M - pref - hi, M);
            prv.insert(prv.end(), tail.begin(), tail.end());
            hasPrv = true;
        }
    }
    if (!hasPrv && L >= 2) {
        prv = largestFill(L - 1, M, M);
        hasPrv = true;
    }

    printDigits(hasPrv ? prv : vector<int>());
    printDigits(hasNxt ? nxt : vector<int>());
    return 0;
}
