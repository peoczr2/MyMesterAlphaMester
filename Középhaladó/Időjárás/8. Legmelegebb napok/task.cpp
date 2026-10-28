/*
Megoldás lényege:
Egy nap akkor a legmelegebb, ha valamely településen ezen a napon szerepel a teljes táblázat legnagyobb előrejelzett értéke. Minden napra a sorok beolvasása közben kiszámoljuk a napi maximumot, majd a napi maximumok közül kiválasztjuk a legnagyobbat. A kiírt napok azok, amelyeknek a napi maximuma ezzel egyezik meg, növekvő sorrendben. Az idő O(N·M), a memória O(M).
*/
/*
Hint 1: || Egy nap a keresett napok közé tartozik, ha ezen a napon bármelyik településen a legnagyobb előrejelzett érték szerepel. Először tehát a legnagyobb értéket kell megtalálnod. ||
Hint 2: || Minden napra tartsd nyilván a napi maximumot egy tömbben a sorok beolvasása közben. Utána keresd meg a napi maximumok közül a legnagyobbat, és írd ki azokat a napokat, ahol a napi maximum ezzel egyenlő. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> napi_max(m + 1, INT_MIN);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int h;
            cin >> h;
            napi_max[j] = max(napi_max[j], h);
        }
    }

    int legmelegebb = INT_MIN;
    for (int j = 1; j <= m; j++) legmelegebb = max(legmelegebb, napi_max[j]);

    vector<int> napok;
    for (int j = 1; j <= m; j++) {
        if (napi_max[j] == legmelegebb) napok.push_back(j);
    }

    cout << napok.size();
    for (int d : napok) cout << ' ' << d;
    cout << '\n';
    return 0;
}
