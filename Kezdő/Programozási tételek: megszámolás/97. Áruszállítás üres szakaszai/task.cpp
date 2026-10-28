/*
Megoldás lényege:
Az i. állomásszakasz az i. és az (i+1). állomás közötti pár. A H -> K szállítás a H, H+1, ..., K-1 szakaszokat terheli, ezt különbségtömbbel rögzítjük: d[H] eggyel nő, d[K] eggyel csökken. A prefixösszeg minden szakaszra megadja, hány szállítás fedi le, így az üres szakaszok a nulla prefixösszegű szakaszok.
Egy üres futam ott kezdődik, ahol egy üres szakasz előtt lefedett szakasz áll, vagy ahol az első szakasz üres. Ezeket a kezdeteket balról jobbra haladva egyetlen ciklusban megszámoljuk.
Az időigény O(N + M), a memóriaigény O(N).
*/
/*
Hint 1: || Egy szállítás csak szomszédos állomáspárok (szakaszok) egy összefüggő tartományát foglalja le. Ha a H -> K szállítás lefedi az i. szakaszt, akkor H <= i < K. Gondolj arra, hogy mikor tekintünk egy szakaszt üresnek. ||
Hint 2: || Ne járd végig minden szállítás szakaszait (az N*M túl sok lenne), hanem használj különbségtömböt: a H. helyre +1, a K. helyre -1, majd a prefixösszeg megadja minden szakasz lefedettségét. ||
Hint 3: || Balról jobbra haladva számold a lefedetlen szakaszokat. Egy üres futam akkor kezdődik, amikor egy lefedetlen szakasz előtt lefedett szakasz áll, vagy amikor az első szakasz üres. Ezeket a kezdeteket kell megszámolni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> d(n + 2, 0);
    for (int i = 0; i < m; i++) {
        int h, k;
        cin >> h >> k;
        d[h]++;
        d[k]--;
    }

    int cover = 0;            // az aktuális szakasz lefedettsége
    bool prevCovered = true;  // a "0. szakasz" fiktíven lefedett, így az 1. üres szakasz is futamkezdet
    int runs = 0;
    for (int i = 1; i <= n - 1; i++) {
        cover += d[i];
        bool covered = cover > 0;
        if (!covered && prevCovered) runs++;
        prevCovered = covered;
    }

    cout << runs << '\n';
    return 0;
}
