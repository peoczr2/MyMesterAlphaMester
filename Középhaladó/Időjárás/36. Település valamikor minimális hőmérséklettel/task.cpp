/*
Megoldás lényege:
Minden napra meghatározzuk a települések előrejelzéseinek minimumát, vagyis azt a hőmérsékletet, amelyet az adott napra a leghidegebbnek jósoltak. Egy település akkor kerül a kimenetbe, ha legalább egy napon a saját értéke megegyezik ezzel a napi minimummal. A napi minimum csak az összes sor ismeretében biztos, ezért a mátrixot eltároljuk, majd két lépésben dolgozunk: először a napi minimumok, utána a jelölés. A kimenet első száma a kiválasztott települések darabszáma, utána a sorszámaik növekvő sorrendben. Az idő O(N·M), a memória O(N·M).
*/
/*
Hint 1: || Minden napra külön határozd meg a települések közül a legkisebb előrejelzést. Egy település akkor kerül a kimenetbe, ha legalább egy napon az értéke megegyezik az adott nap minimumával. ||
Hint 2: || A napi minimum csak az összes sor beolvasása után ismert, ezért a mátrixot először tárold el. Utána egy tömbben gyűjtsd a napi minimumokat, majd egy logikai tömbbel jelöld meg azokat a településeket, amelyek valamelyik napon elérik ezt az értéket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> h(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> h[i][j];
        }
    }

    vector<int> napi_min(m + 1, INT_MAX);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            napi_min[j] = min(napi_min[j], h[i][j]);
        }
    }

    vector<bool> kivalasztott(n + 1, false);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (h[i][j] == napi_min[j]) {
                kivalasztott[i] = true;
                break;
            }
        }
    }

    vector<int> valasz;
    for (int i = 1; i <= n; i++) {
        if (kivalasztott[i]) valasz.push_back(i);
    }

    cout << valasz.size();
    for (int i : valasz) cout << ' ' << i;
    cout << '\n';
    return 0;
}
