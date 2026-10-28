/*
Megoldás lényege:
Minden napra meghatározzuk, melyik településen a legalacsonyabb az előrejelzett hőmérséklet: ez az adott nap leghidegebb értéke. A feladat azokat a napokat kéri, amelyeken ez a napi minimum a lehető legnagyobb, ezért a napi minimumok közül a legnagyobbat keressük, és kiírjuk azokat a napokat, ahol ezt az értéket érjük el. A napi minimumokat egy tömbben tároljuk, a sorok beolvasása közben frissítve. Az idő O(N·M), a memória O(M).
*/
/*
Hint 1: || Minden napra külön nézd meg, melyik településen a legalacsonyabb az előrejelzett hőmérséklet. Ez a nap „leghidegebb” értéke. ||
Hint 2: || Ezekből a napi minimumokból keresd meg a legnagyobbat, majd írd ki azokat a napokat, amelyeknek a minimuma ezzel egyenlő. Elég a napi minimumokat tömbben tárolni, a teljes mátrixot nem kell. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> napi_min(m + 1, INT_MAX);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int h;
            cin >> h;
            napi_min[j] = min(napi_min[j], h);
        }
    }

    int legjobb = INT_MIN;
    for (int j = 1; j <= m; j++) legjobb = max(legjobb, napi_min[j]);

    vector<int> napok;
    for (int j = 1; j <= m; j++) {
        if (napi_min[j] == legjobb) napok.push_back(j);
    }

    cout << napok.size();
    for (int d : napok) cout << ' ' << d;
    cout << '\n';
    return 0;
}
