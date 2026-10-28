/*
Megoldás lényege:
A húzásokat nem kell eltárolni: egy 91 elemű tömbben (1-től 90-ig) minden nyerőszám
kihúzásainak számát növeljük. Az 1. részfeladat a nem nulla darabszámú számok száma.
A 2. részfeladatban ezeket (szám, darabszám) párokba gyűjtjük, majd darabszám szerint
csökkenően, azonos darabszámnál szám szerint növekvően rendezzük. Az időigény
O(5·N + 90 log 90), a memóriaigény elhanyagolható.
*/
/*
Hint 1: || Nem kell a húzásokat eltárolni: elég minden számhoz egy darabszámlálót vezetni, mert a számok 1 és 90 közöttiek. ||
Hint 2: || A rendezéshez (szám, darabszám) párokat használj, és a rendezési feltételben előbb a darabszámot (csökkenő), azonos darabszámnál a számot (növekvő) vedd figyelembe. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> cnt(91, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            int x;
            cin >> x;
            cnt[x]++;
        }
    }

    vector<pair<int, int>> nyer; // (szám, darabszám)
    for (int x = 1; x <= 90; x++)
        if (cnt[x] > 0)
            nyer.push_back({x, cnt[x]});

    cout << "#\n" << nyer.size() << "\n";

    sort(nyer.begin(), nyer.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });

    cout << "#\n";
    for (const auto& p : nyer)
        cout << p.first << " " << p.second << "\n";
    return 0;
}
