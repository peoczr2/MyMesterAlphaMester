/*
Megoldás lényege:
Három szakaszból akkor szerkeszthető háromszög, ha bármely két oldal összege nagyobb a harmadiknál. A Héron-képletből a területnégyzet 16-szorosa egész szám: 16*T^2 = (a+b+c)*(-a+b+c)*(a-b+c)*(a+b-c), így a törtek egészekkel, pontosan kezelhetők. A területnégyzetet p/q alakban úgy kapjuk, hogy a 16*T^2 értéket 16-tal egyszerűsítjük a legnagyobb közös osztóval (gcd). A derékszögű esethez az oldalakat növekvő sorrendbe rendezzük, és a két rövidebb oldal négyzetösszegét hasonlítjuk a leghosszabb oldal négyzetéhez. Minden részfeladat egyetlen, N darab szakaszhármason végzett bejárással megoldható, az időigény O(N).
*/
/*
Hint 1: || A háromszög-egyenlőtlenséget mindhárom párra kell ellenőrizni. A területnégyzet Héron-képletéből a 16-szorosa egész szám lesz, ezt használd, hogy elkerüld a törtekkel való számolást. ||
Hint 2: || A 16*T^2 szorzat akár 10^11 nagyságrendű is lehet, ezért 64 bites egész típust használj. A törtet a legnagyobb közös osztóval (gcd) egyszerűsítsd, és figyelj arra, hogy üres összegnél is p/q alakban (0/1) kell kiírni. ||
Hint 3: || A derékszögű ellenőrzéshez rendezd az oldalakat növekvő sorrendbe, és a két kisebb oldal négyzetösszegét hasonlítsd a legnagyobb oldal négyzetéhez. Egész számokkal dolgozz, így nincs lebegőpontos hiba. ||
*/
#include <bits/stdc++.h>
using namespace std;

// 16 * T^2 egész értéke a Héron-képlet szorzatalakjából
long long area16(long long a, long long b, long long c) {
    return (a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c);
}

bool constructible(long long a, long long b, long long c) {
    return a + b > c && a + c > b && b + c > a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n), b(n), c(n);
    vector<string> col(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i] >> c[i] >> col[i];

    // 1. részfeladat: szerkeszthető háromszögek
    vector<int> tri;
    for (int i = 0; i < n; i++)
        if (constructible(a[i], b[i], c[i])) tri.push_back(i + 1);
    cout << "#\n";
    cout << tri.size();
    for (int id : tri) cout << ' ' << id;
    cout << "\n";

    // 2. részfeladat: legnagyobb területnégyzetű szerkeszthető háromszög
    int bestIdx = -1;
    long long bestVal = -1;
    for (int i = 0; i < n; i++) {
        if (!constructible(a[i], b[i], c[i])) continue;
        long long v = area16(a[i], b[i], c[i]);
        if (v > bestVal) {
            bestVal = v;
            bestIdx = i + 1;
        }
    }
    cout << "#\n";
    if (bestIdx < 0) {
        cout << "-1\n";
    } else {
        long long g = gcd(bestVal, 16LL);
        cout << bestIdx << ' ' << bestVal / g << '/' << 16 / g << "\n";
    }

    // 3. részfeladat: piros szerkeszthető háromszögek területnégyzeteinek összege
    long long sum = 0;
    for (int i = 0; i < n; i++)
        if (col[i] == "piros" && constructible(a[i], b[i], c[i])) sum += area16(a[i], b[i], c[i]);
    long long g3 = gcd(sum, 16LL);
    cout << "#\n";
    cout << sum / g3 << '/' << 16 / g3 << "\n";

    // 4. részfeladat: derékszögű háromszöget adó szakaszhármasok
    vector<int> rt;
    for (int i = 0; i < n; i++) {
        if (!constructible(a[i], b[i], c[i])) continue;
        long long arr[3] = {a[i], b[i], c[i]};
        sort(arr, arr + 3);
        if (arr[0] * arr[0] + arr[1] * arr[1] == arr[2] * arr[2]) rt.push_back(i + 1);
    }
    cout << "#\n";
    cout << rt.size();
    for (int id : rt) cout << ' ' << id;
    cout << "\n";
    return 0;
}
