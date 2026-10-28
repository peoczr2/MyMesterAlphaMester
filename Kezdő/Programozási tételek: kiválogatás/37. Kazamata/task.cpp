/*
Megoldás lényege: minden újraindítás után a szobákban lévő kulcsok típusa eggyel nő (mod N), ezért az i. szoba kulcsa az r. újraindítás után (k_i + r) mod N. Egy futásban a nulladik szobától indulva addig haladunk, amíg a következő szobához megvan a kulcs; a futás végén minden megszerzett kulcs megmarad. Az elért szobák határa (az első át nem jutható szoba) csak előre mozdulhat, és a határ előtti szobák mindig átjárhatók, ezért nem kell minden futást a nulladik szobától bejárni. Egy j szoba az r. futásban akkor járható, ha a j. típusú kulcs vagy egy korábbi futásban már birtokunkban volt, vagy ebben a futásban egy j-nél nem későbbi szobából megszerezhető. A korábbi futásokban megszerzett kulcsok „mozgó jelzésként” követhetők: egy kulcs nyoma minden futásban egyet lép a körkörös típustérben, így az első fedési időpont prefixum- és suffixum-minimummal (Fenwick-fa) számolható. A határ megállásakor a következő olyan futást ugorjuk át, amelyben a határszoba átjárhatóvá válik, ezt egy halmazban való ciklikus megelőző kereséssel számoljuk. A határ legfeljebb N-szer mozdul, így a teljes futás O(N log N).
*/
/*
Hint 1: || Egy újraindítás után minden szoba kulcsának típusa eggyel nő (mod N): írd fel az r. futásban az i. szoba kulcsát, és gondold végig, melyik szoba ajtaját nyitja ez a kulcs. ||
Hint 2: || Ha a 0..j-1 szobák már átjárhatók, a j. szoba akkor járható egy futásban, ha a j. típusú kulcsot már korábban megszereztük, vagy egy j-nél nem későbbi szobából pont ez a típus jön; az első át nem jutható szoba (a határ) csak előre mozdulhat. ||
Hint 3: || Ne szimuláld minden futást a nulladik szobától: a korábbi futásokban megszerzett kulcsok nyomát tartsd nyilván úgy, hogy egy kulcs minden futásban eggyel tovább lép, és ugord át azokat a futásokat, amelyekben a határszoba még nem járható. ||
*/
#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX / 4;

int n;
vector<long long> bitA, bitB;  // Fenwick fák prefixum-minimumhoz

void upd(vector<long long>& b, int i, long long val) {
    for (; i <= n; i += i & -i) b[i] = min(b[i], val);
}

long long qry(const vector<long long>& b, int i) {
    long long res = INF;
    for (; i > 0; i -= i & -i) res = min(res, b[i]);
    return res;
}

// x: a kulcs kezdő típusa (pozíció), sigma: az első futás, amelyben aktív
void addToken(int x, long long sigma) {
    long long val = sigma - x;
    upd(bitA, x + 1, val);
    upd(bitB, n - x, val);
}

// Az első futás, amelyben a j. szoba a kulcsok révén átjárható
// (csak a korábbi futásokban megszerzett kulcsokat veszi figyelembe).
long long tau(int j) {
    long long a = qry(bitA, j + 1);
    long long b = (n - 1 - j >= 1) ? qry(bitB, n - 1 - j) : INF;
    long long m = min(a, b >= INF ? INF : (long long)n + b);
    if (m >= INF) return INF;
    return j + m;
}

int main() {
    cin >> n;
    vector<int> k(n);
    for (auto& x : k) cin >> x;

    vector<int> fp(n, INT_MAX);  // egy típus első előfordulása
    for (int i = 0; i < n; i++)
        if (fp[k[i]] == INT_MAX) fp[k[i]] = i;

    bitA.assign(n + 1, INF);
    bitB.assign(n + 1, INF);
    set<int> V;  // a k_i értékek, i <= határ

    auto passable = [&](int j, long long r) -> bool {
        long long idx = ((j - r) % n + n) % n;
        if (fp[idx] <= j) return true;
        return tau(j) < r;
    };

    // 0. futás: a határ kezdetben a 0. szoba
    int f = 0;
    while (f < n && passable(f, 0)) f++;
    for (int i = 0; i <= min(f, n - 1); i++) {
        V.insert(k[i]);
        if (fp[k[i]] == i) addToken(k[i] % n, 0);
    }
    if (f == n) {
        cout << 0 << "\n";
        return 0;
    }

    int p = f;       // a határ: F_{r-1}
    long long r = 1; // a következő futás sorszáma
    long long answer = 0;
    while (true) {
        long long t = tau(p);
        int q = (int)(((p - r) % n + n) % n);
        long long d;
        auto it = V.upper_bound(q);
        if (it != V.begin()) {
            d = q - *prev(it);
        } else {
            d = q - *V.rbegin() + n;
        }
        long long owned = (t >= INF) ? INF : t + 1;
        long long rstar = min(max(r, owned), r + d);

        int j = p;
        while (j < n && passable(j, rstar)) j++;
        for (int i = p + 1; i <= min(j, n - 1); i++) {
            V.insert(k[i]);
            if (fp[k[i]] == i) addToken((int)((k[i] + rstar) % n), rstar);
        }
        if (j == n) {
            answer = rstar;
            break;
        }
        p = j;
        r = rstar + 1;
    }
    cout << answer << "\n";
    return 0;
}
