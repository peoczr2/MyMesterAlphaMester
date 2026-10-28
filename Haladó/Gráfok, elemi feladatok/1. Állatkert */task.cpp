/*
Megoldás lényege:
Minden út két végpontjánál növeljük a fokszámot eggyel, így minden állathoz megkapjuk, hány út vezet a ketrecéhez. Zsákutca végén az az állat van, akinek pontosan egy út csatlakozik, vagyis a fokszáma 1, ezeket egy bejárással megszámoljuk. A legtöbb utat az a csúcs kapja, amelyiknek a legnagyobb a fokszáma az 1..N tartományban; a 0 a bejárat, nem állat, ezt kihagyjuk. A gráfot nem kell tárolni, az idő O(N+M), és a 200000 él miatt a beolvasás gyors legyen.
*/
/*
Hint 1: || Nem kell a teljes gráfot felépíteni: elég minden csúcsra azt számolni, hány út éri, vagyis a fokszámot. ||
Hint 2: || A zsákutca pontosan az a csúcs, amelynek fokszáma 1. A legtöbb utat kapó állat a legnagyobb fokszámú csúcs 1 és N között; ügyelj rá, hogy a 0 nem állat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> deg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        deg[a]++;
        deg[b]++;
    }

    int deadEnds = 0;
    int bestAnimal = 1;
    for (int v = 1; v <= n; v++) {
        if (deg[v] == 1) deadEnds++;
        if (deg[v] > deg[bestAnimal]) bestAnimal = v;
    }

    cout << deadEnds << " " << bestAnimal << "\n";
    return 0;
}
