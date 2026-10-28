/*
Minden kilométer-szakaszra megszámoljuk, hányszor volt felújítva. Egy (K, V) felújítás a K..V szakaszokat érinti, ezért a különbségtömbben diff[K]-t eggyel növeljük, diff[V+1]-et eggyel csökkentjük. Prefixösszeggel kapjuk az egyes szakaszok felújítási számát. Ezután balról jobbra megnézzük az első olyan 10 szakaszból álló ablakot, amelyben minden szakasz legalább háromszor volt felújítva; ennek kezdete a válasz, ha nincs ilyen, a -1. Az időigény O(N + 10·N), a memóriaigény O(N).
*/
/*
Hint 1: || Ne járd végig külön minden felújítás minden kilométerét. Egy felújítás csak két határon változtatja meg a darabszámot: a K-nál nő, a V+1-nél csökken. ||
Hint 2: || Ha minden szakasz felújítási számát ismered, az x kezdetű 10 hosszú szakasz akkor jó, ha x-től x+9-ig mindegyik szám legalább 3. Keresd a legkisebb ilyen x-et, és ügyelj arra, hogy az ablak ne lógjon ki az útból. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int HOSSZ = 10; // a keresett szakasz hossza km-ben
    int n, m;
    cin >> n >> m;

    // diff[s]: az s-edik szakasz felújítási számának változása
    vector<int> diff(n + 2, 0);
    for (int i = 0; i < m; i++) {
        int k, v;
        cin >> k >> v;
        diff[k]++;
        diff[v + 1]--;
    }

    vector<int> cov(n + 1, 0);
    int futo = 0;
    for (int s = 0; s <= n; s++) {
        futo += diff[s];
        cov[s] = futo;
    }

    int valasz = -1;
    for (int x = 0; x + HOSSZ - 1 <= n && valasz == -1; x++) {
        bool jo = true;
        for (int s = x; s < x + HOSSZ && jo; s++) {
            if (cov[s] < 3) jo = false;
        }
        if (jo) valasz = x;
    }

    cout << valasz << "\n";
    return 0;
}
