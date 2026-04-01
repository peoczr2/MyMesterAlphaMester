/*
Feladat: A tejet érkezési sorrendben kell elszállítani. Egy termelő tétele nem bontható, a tejeskocsi kapacitása K, és minden tételt legfeljebb T időn belül el kell vinni. Minimum hány tejeskocsi kell?
Ötlet: A sorrendkényszer miatt a termelők egy kamionban mindig egy folytonos blokkot alkotnak. Egy blokk akkor vihető el egy kocsival, ha összmennyiség <= K és az első/utolsó érkezés különbsége <= T (mert kell közös indulási idő). Ezért balról jobbra mohón mindig a lehető leghosszabb még érvényes blokkot vesszük; ez minimális darabszámot ad.
Hint 1: || Sorrend miatt a kocsikhoz rendelt termelők szakaszokra bontják a listát. ||
Hint 2: || Egy szakasz akkor jó, ha belefér kapacitásba és van közös időablaka. ||
Hint 3: || Mindig a leghosszabb következő érvényes szakasz választása optimális. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, T;
    cin >> N >> K >> T;

    vector<int> e(N + 1), m(N + 1);
    for (int i = 1; i <= N; ++i) cin >> e[i] >> m[i];

    int trucks = 0;
    int i = 1;
    while (i <= N) {
        long long sum = 0;
        int j = i;
        while (j <= N) {
            if (sum + m[j] > K) break;
            if (e[j] - e[i] > T) break;
            sum += m[j];
            ++j;
        }
        ++trucks;
        i = j;
    }

    cout << trucks << '\n';
    return 0;
}
