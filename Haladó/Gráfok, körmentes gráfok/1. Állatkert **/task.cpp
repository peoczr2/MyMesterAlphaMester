/*
Megoldás lényege:
Az állatkerti utak egy gráfot alkotnak, ahol a csúcsok a bejárat (0) és az állatok (1..N). Egy állat akkor van zsákutca
végén, ha pontosan egy út vezet hozzá, vagyis a fokszáma 1. A legtöbb utat az a állat kapja, amelynek a legnagyobb a fokszáma.
Ezért nincs szükség bejárásra: minden út két végpontjának fokszámát eggyel növeljük, majd az 1..N állatokat egyszer
végigjárva megkapjuk mindkét választ. Az időigény O(N + M).
*/
/*
Hint 1: || Egy állat akkor van zsákutca végén, ha pontosan egy út vezet hozzá, vagyis a fokszáma 1. ||
Hint 2: || Ne bejárd a gráfot: minden út két végpontjának fokszámát számold egy tömbben, az út végpontjait egyenként növelve. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> degree(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        ++degree[a];
        ++degree[b];
    }

    int deadEnds = 0;
    int best = 1;
    for (int animal = 1; animal <= n; ++animal) {
        if (degree[animal] == 1) {
            ++deadEnds;
        }
        if (degree[animal] > degree[best]) {
            best = animal;
        }
    }

    cout << deadEnds << " " << best << "\n";
    return 0;
}
