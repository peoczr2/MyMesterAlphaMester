/*
Megoldás lényege:
A fa térfogata V = r^2 * pi * l, ahol r = d/2 és pi = 3, így V = 3/4 * d^2 * l. A konstans szorzó minden fánál ugyanaz, ezért a termelők összehasonlításához elég a d^2 * l értékeket összegezni. Ezek egész számok, így a számolás pontos, nincs lebegőpontos hiba. Termelőnként összegezzük az összes fa d^2 * l értékét, és egy menetben megtartjuk az eddigi legnagyobb összeget. Egyenlőség esetén a korábbi termelő marad, mert csak szigorúan nagyobb összegnél cserélünk. A győztes termelő legmagasabb fája adja a második választ. Az időigény a bemenet méretével arányos.
*/
/*
Hint 1: || A térfogat képletében a konstans szorzó minden fánál ugyanaz, ezért a sorrend szempontjából elhagyhatod. Elég a d^2 * l értékekkel dolgozni, így egész számokkal is pontosan számolhatsz. ||
Hint 2: || Termelőnként összegezd a fák d^2 * l értékeit, és közben jegyezd meg a fák maximális magasságát. Csak akkor cseréld a győztest, ha az összeg szigorúan nagyobb az eddigi legjobbnál. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long legjobb_ossz = -1;
    int legjobb_sorszam = 0;
    int legjobb_magassag = 0;

    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        long long ossz = 0;
        int max_magassag = 0;
        for (int j = 0; j < k; ++j) {
            long long l, d;
            cin >> l >> d;
            ossz += l * d * d;
            max_magassag = max(max_magassag, static_cast<int>(l));
        }
        if (ossz > legjobb_ossz) {
            legjobb_ossz = ossz;
            legjobb_sorszam = i;
            legjobb_magassag = max_magassag;
        }
    }

    cout << legjobb_sorszam << '\n' << legjobb_magassag << '\n';
    return 0;
}
