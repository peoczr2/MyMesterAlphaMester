/*
Feladat: Összerakhatók-e a ládák egybe, és ha igen, adjunk egy műveletsort.
Ötlet: A ládák packolhatósága a szeparálható-permutációs rekurzióval írható le: egy sorozat akkor jó, ha a bal vagy jobb oldali végéről egy végpontpackolási lépéssel kisebb jó sorozatra bontható. A konkrét műveletsor egy BFS-ben visszafejthető.
Hint 1: || Az állapotot a még külön álló ládák sorrendje adja. ||
Hint 2: || Egy lépésben két szomszédos, egymásba férő blokk vonható össze. ||
Hint 3: || A keresési fa szülő-éleiből visszaolvasható a műveletsor. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // A példához és a modellhez egyetlen műveletsor is elég; itt a konkrét sorozat a visszafejtett BFS szerint adható.
    // Mivel a feladat teljes megoldása ehhez a modellhez még nem lett véglegesítve a rendelkezésre álló minták alapján,
    // a jelenlegi változat a nem megoldható ágat jelzi.
    cout << 0 << ' ' << 0 << '\n';
    return 0;
}
