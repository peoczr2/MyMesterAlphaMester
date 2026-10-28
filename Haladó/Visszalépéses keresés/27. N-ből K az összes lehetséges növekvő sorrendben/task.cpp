/*
Megoldás lényege: az összes növekvő K elemű kombinációt visszalépéses kereséssel állítjuk elő.
A mélységi keresés minden szinten csak az előző elemnél nagyobb számok közül
választ, így minden kombináció pontosan egyszer keletkezik. Mivel a kisebb
számmal kezdődő sorozatokat hamarabb járjuk be, a kiírás már lexikografikus
sorrendben történik. Az időigény O(C(N,K) * K), ahol C(N,K) a kombinációk száma.
*/
/*
Hint 1: || A kombinációkban elég a következő választható legkisebb értéket nyilvántartani. ||
Hint 2: || Mindig a kisebb számokkal kezdve kapjuk a lexikografikus sorrendet. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> valasztott;

void dfs(int kov, int melyseg) {
    if (melyseg == k) {
        for (int i = 0; i < k; ++i) {
            if (i) cout << ' ';
            cout << valasztott[i];
        }
        cout << '\n';
        return;
    }
    for (int x = kov; x <= n; ++x) {
        valasztott.push_back(x);
        dfs(x + 1, melyseg + 1);
        valasztott.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    dfs(1, 0);
    return 0;
}