/*
Megoldas lenyege:
Pontosan ugyanaz a helyzet, mint a viragarusos feladatban: egy fix tenyesztonel a hianyzo
allatok szama az osszes fajtara vett max(0, igeny - keszlet) osszeg. Mivel minden lista nev
szerint rendezett, ez egy linearis osszefesulessel kiszamithato.

Kulon meghatarozzuk az 1. es a 2. tenyeszto hianyossagat, majd a kisebb hianyhoz tartozo
tenyesztot irjuk ki. Holtversenyben barmelyik jo, itt az 1.-et valasztjuk.
*/
/*
Hint 1: || Egy fajta csak akkor novel hianyt, ha a tenyesztonel kevesebb van belole a szuksegesnel. ||
Hint 2: || A nevek rendezetten jonnek, igy egy merge eleg a hianyok kiszamitasahoz. ||
Hint 3: || Ugyanazt a merge-fuggvenyt kulon futtasd le mindket tenyesztore. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Animal {
    string name;
    long long count;
};

static long long missingCount(const vector<Animal>& need, const vector<Animal>& stock) {
    unordered_map<string, long long> available;
    available.reserve(stock.size() * 2 + 1);
    for (const auto& item : stock) available[item.name] += item.count;

    long long missing = 0;
    for (const auto& item : need) {
        long long have = 0;
        auto it = available.find(item.name);
        if (it != available.end()) have = it->second;
        if (have < item.count) missing += item.count - have;
    }
    return missing;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Animal> need(n);
    for (int i = 0; i < n; ++i) cin >> need[i].name >> need[i].count;

    int a1;
    cin >> a1;
    vector<Animal> breeder1(a1);
    for (int i = 0; i < a1; ++i) cin >> breeder1[i].name >> breeder1[i].count;

    int a2;
    cin >> a2;
    vector<Animal> breeder2(a2);
    for (int i = 0; i < a2; ++i) cin >> breeder2[i].name >> breeder2[i].count;

    long long miss1 = missingCount(need, breeder1);
    long long miss2 = missingCount(need, breeder2);

    if (miss1 <= miss2) {
        cout << 1 << '\n' << miss1 << '\n';
    } else {
        cout << 2 << '\n' << miss2 << '\n';
    }

    return 0;
}