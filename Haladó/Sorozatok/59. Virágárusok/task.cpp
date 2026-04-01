/*
Megoldas lenyege:
Mindket arus es a kivansaglista is nev szerint rendezett. Egy fix arusnal a hianyzo viragok
szama az osszes fajtara vett max(0, igeny - keszlet) osszeg. Ezt egy rendezett osszefesulessel
ki lehet szamolni.

Kulon kiszamoljuk az 1. es a 2. arusnal a hianyok osszegét, majd azt valasztjuk, amelyiknel
ez kisebb. Holtversenyben barmelyik jo, itt az 1.-et irjuk ki.
*/
/*
Hint 1: || Egy fajta csak akkor okoz hianyt, ha az arusnal kevesebb van belole a szuksegesnel. ||
Hint 2: || A nevek rendezettek, ezert ket mutatos osszefesules eleg. ||
Hint 3: || Ugyanazt a merge-logikat kulon futtasd le mindket arusra. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Flower {
    string name;
    long long count;
};

static long long missingCount(const vector<Flower>& need, const vector<Flower>& stock) {
    long long missing = 0;
    int i = 0, j = 0;
    while (i < (int)need.size()) {
        if (j == (int)stock.size() || need[i].name < stock[j].name) {
            missing += need[i].count;
            ++i;
        } else if (stock[j].name < need[i].name) {
            ++j;
        } else {
            if (stock[j].count < need[i].count) missing += need[i].count - stock[j].count;
            ++i;
            ++j;
        }
    }
    return missing;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Flower> need(n);
    for (int i = 0; i < n; ++i) cin >> need[i].name >> need[i].count;

    int a1;
    cin >> a1;
    vector<Flower> shop1(a1);
    for (int i = 0; i < a1; ++i) cin >> shop1[i].name >> shop1[i].count;

    int a2;
    cin >> a2;
    vector<Flower> shop2(a2);
    for (int i = 0; i < a2; ++i) cin >> shop2[i].name >> shop2[i].count;

    long long miss1 = missingCount(need, shop1);
    long long miss2 = missingCount(need, shop2);

    if (miss1 <= miss2) {
        cout << 1 << '\n' << miss1 << '\n';
    } else {
        cout << 2 << '\n' << miss2 << '\n';
    }

    return 0;
}