/*
Megoldás lényege:
Egy adott K időkorlátnál minden termelőre eldönthető, hogy csak az A hűtőházba viheti, csak a B-be, vagy mindkettőbe. A K akkor megvalósítható, ha nincs olyan termelő, aki egyikbe sem ér oda, a kényszerített A-k száma legfeljebb N1, a kényszerített B-k száma pedig legfeljebb N2. Mivel N1 + N2 >= N, a rugalmas termelők mindig elhelyezhetők.

Az optimumot K-ra bináris keresés adja: a keresett K az 1 és 10 000 közötti egész, így kb. 14 ellenőrzés fut le, mindegyik O(N) időben. Utána egyszer végigmegyünk a termelőkön: a kényszerítetteket a saját hűtőházukba tesszük, a rugalmasak közül pedig annyit viszünk A-ba, amennyi a kapacitás kitöltéséhez kell, a többit B-be. Az összes időigény O(N log C), ahol C a legnagyobb időérték (legfeljebb 10 000).
*/
/*
Hint 1: || Először csak azt döntsd el, hogy egy adott K időkorlát egyáltalán megvalósítható-e. ||
Hint 2: || Egy termelő háromféle lehet: csak A-ba fér bele, csak B-be fér bele, vagy mindkettőbe. ||
Hint 3: || Ha a kényszerített darabszámok beleférnek a kapacitásokba, akkor a maradék rugalmas termelőket már egyszerűen szét lehet osztani. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, n1, n2;
    cin >> n >> n1 >> n2;
    vector<int> a(n), b(n);
    int upperBound = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        upperBound = max(upperBound, a[i]);
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        upperBound = max(upperBound, b[i]);
    }

    auto feasible = [&](int limit) {
        int forcedA = 0;
        int forcedB = 0;
        for (int i = 0; i < n; ++i) {
            bool canA = a[i] <= limit;
            bool canB = b[i] <= limit;
            if (!canA && !canB) return false;
            if (canA && !canB) ++forcedA;
            if (!canA && canB) ++forcedB;
        }
        return forcedA <= n1 && forcedB <= n2;
    };

    int low = -1;
    int high = upperBound;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (feasible(mid)) {
            high = mid;
        } else {
            low = mid;
        }
    }

    vector<int> toA;
    vector<int> toB;
    vector<int> flexible;
    for (int i = 0; i < n; ++i) {
        bool canA = a[i] <= high;
        bool canB = b[i] <= high;
        if (canA && !canB) {
            toA.push_back(i + 1);
        } else if (!canA && canB) {
            toB.push_back(i + 1);
        } else {
            flexible.push_back(i + 1);
        }
    }

    int needA = n1 - (int)toA.size();
    for (int i = 0; i < (int)flexible.size(); ++i) {
        if (i < needA) {
            toA.push_back(flexible[i]);
        } else {
            toB.push_back(flexible[i]);
        }
    }

    cout << high << '\n';
    for (int i = 0; i < (int)toA.size(); ++i) {
        if (i) cout << ' ';
        cout << toA[i];
    }
    cout << '\n';
    for (int i = 0; i < (int)toB.size(); ++i) {
        if (i) cout << ' ';
        cout << toB[i];
    }
    cout << '\n';
    return 0;
}