/*
Feladat: A hegymászó táboronként élelmiszert vehet fel (H kapacitásig), de minden táborban legalább annyit kell hátrahagyni, amennyi onnan visszafelé az 1. táborig szükséges. Felfelé mindig a lehető legtöbbet viszi. Meg kell adni, meddig jut fel úgy, hogy onnan még visszaérjen, és az egyes táborokban mennyit vett fel.
Ötlet: Szimuláció táboronként. Legyen needBack[i] az i. táborból az 1.-ig szükséges összes élelem (prefix a K értékekből). Az i. táborban legfeljebb Vi-needBack[i] vehető fel úgy, hogy a kötelező tartalék megmaradjon. A mohó szabály miatt mindig ennek és a szabad kapacitásnak a minimumát vesszük fel. Ha ezzel sem érjük el a következő szakasz költségét, ott meg kell állni.
Hint 1: || A visszaútra szükséges tartalék az i. táborban: K1+K2+...+K(i-1). ||
Hint 2: || A felvehető mennyiség felső korlátja egyszerre a hátizsák maradék helye és a táborban hagyandó tartalék miatt adódik. ||
Hint 3: || Ha a maximálisan felvehető mennyiséggel sem tudod kifizetni a következő szakaszt, innen már nem mehetsz tovább. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, H;
    cin >> N >> H;

    vector<int> V(N, 0), K(N, 0);
    for (int i = 1; i <= N - 1; ++i) {
        cin >> V[i] >> K[i];
    }

    vector<long long> needBack(N + 1, 0);
    for (int i = 2; i <= N; ++i) {
        needBack[i] = needBack[i - 1] + K[i - 1];
    }

    vector<int> take;
    take.reserve(N - 1);

    long long bag = 0;

    for (int i = 1; i <= N - 1; ++i) {
        long long reserve = needBack[i];
        long long maxTakeByReserve = (long long)V[i] - reserve;
        if (maxTakeByReserve < 0) {
            int reached = i - 1;
            cout << reached << '\n';
            for (int j = 0; j < (int)take.size(); ++j) {
                if (j) cout << ' ';
                cout << take[j];
            }
            cout << '\n';
            return 0;
        }

        long long canTake = min((long long)H - bag, maxTakeByReserve);
        if (canTake < 0) canTake = 0;

        long long maxCarryAfterPickup = bag + canTake;
        if (maxCarryAfterPickup < K[i]) {
            int reached = i;
            cout << reached << '\n';
            for (int j = 0; j < (int)take.size(); ++j) {
                if (j) cout << ' ';
                cout << take[j];
            }
            cout << '\n';
            return 0;
        }

        take.push_back((int)canTake);
        bag = maxCarryAfterPickup - K[i];
    }

    cout << N << '\n';
    for (int i = 0; i < (int)take.size(); ++i) {
        if (i) cout << ' ';
        cout << take[i];
    }
    cout << '\n';
    return 0;
}
