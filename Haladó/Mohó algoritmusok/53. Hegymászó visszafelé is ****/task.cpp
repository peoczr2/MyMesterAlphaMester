/*
Megoldás lényege: felfelé minden táborban annyit veszünk fel, amennyi a hátizsákba még belefér, de a táborban
mindig legalább a közvetlenül előtte levő szakasz visszaútjához szükséges K_{i-1} marad. Ha a táborban nincs elég
élelmiszer ehhez, a hátizsákunkból teszünk le; ha így sincs elég, az előző táborból kell visszafordulni. A táborokban
hagyott élelmiszert a lejutáskor útközben felvesszük, így minden lejutási szakasz a saját tábora tartalékából
fedezhető. A hátizsák tartalma minden lépésben a lehető legnagyobb, ezért a mohó felvétel optimális.
Időigény: O(N).
*/
/*
Hint 1: || Egy táborban elég annyit hagyni, amennyi a közvetlenül előtte levő szakasz visszaútjához kell. ||
Hint 2: || Ha a táborban nincs elég élelmiszer a hagyáshoz, a hátizsákodból is letehetsz; ha így sincs elég, visszafordulsz. ||
Hint 3: || Minden táborban annyit vegyél fel, amennyi a hátizsákba még belefér, majd ellenőrizd, hogy a következő szakaszt megteheted-e. ||
Hint 4: || Az utolsó táborból a csúcsig és vissza tartó oda-vissza út költségét ugyanúgy a hátizsák maradékából kell fedezni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, H;
    cin >> N >> H;

    vector<long long> V(N, 0), K(N, 0);
    for (int i = 1; i <= N - 1; ++i) {
        cin >> V[i] >> K[i];
    }

    // take[i]: az i. táborban felvett mennyiség (1-től számozva)
    vector<long long> take(N, 0);
    long long bag = 0;

    // Kimenet: az elért K tábor, majd a K-1 darab felvétel (az 1..K-1. táborokra)
    auto print = [&](int reached) {
        cout << reached << '\n';
        for (int i = 1; i <= reached - 1; ++i) {
            if (i > 1) cout << ' ';
            cout << take[i];
        }
        cout << '\n';
    };

    for (int i = 1; i <= N - 1; ++i) {
        // a táborban legalább K[i-1] marad a visszaúthoz (az 1. táborban nincs rá szükség)
        long long reserve = (i >= 2) ? K[i - 1] : 0;

        // felvehető: a hátizsák szabad helye és a tartalékkal nem ütköző rész
        long long pick = min((long long)H - bag, max(0LL, V[i] - reserve));

        // ha a táborban nincs elég a tartalékhoz, a hátizsákunkból teszünk le
        long long deposit = max(0LL, reserve - (V[i] - pick));
        if (deposit > bag) {
            // nem tudunk elég élelmiszert hagyni: az előző táborból kell visszafordulni
            print(i - 1);
            return 0;
        }

        take[i] = pick;
        bag = bag + pick - deposit;

        if (bag < K[i]) {
            // a következő szakaszt (az utolsó táborban a csúcsig és vissza) nem tudjuk megtenni
            print(i);
            return 0;
        }
        bag -= K[i];
    }

    print(N);
    return 0;
}
