/*
Az első i csomagból csak az számít, hogy az egyik kamionon mennyi az összsúly, mert a másiké ebből és
az első i csomag összsúlyából kiszámolható. Legyen elérhető az állapot, ha az első i csomag felpakolható úgy,
hogy az első kamion terhelése pontosan j. Ekkor a második kamion terhelése prefix[i]-j, és csak akkor jó,
ha ez sem nagyobb K-nál. Sorban feldolgozva a csomagokat megkapjuk a legnagyobb prefixet, és egy szülőtáblával
vissza is fejthetjük, melyik csomag melyik kamionra került.
*/
/*
Hint 1: || Nem kell mindkét kamion terhelését tárolni: az egyikből a másik kiszámítható. ||
Hint 2: || Az optimális megoldás az első M csomagokra vonatkozik, tehát prefixenként érdemes haladni. ||
Hint 3: || A visszafejtéshez elég azt tárolni, hogy egy állapot az aktuális csomagot melyik kamionra téve keletkezett. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> k >> n;
    vector<int> w(n + 1), prefix(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        prefix[i] = prefix[i - 1] + w[i];
    }

    vector<vector<char>> parent(n + 1, vector<char>(k + 1, 0));
    vector<char> reachable(k + 1, 0), next_reachable(k + 1, 0);
    reachable[0] = 1;
    int best_i = 0;
    int best_load = 0;

    for (int i = 1; i <= n; ++i) {
        fill(next_reachable.begin(), next_reachable.end(), 0);
        for (int load1 = 0; load1 <= k; ++load1) {
            if (!reachable[load1]) {
                continue;
            }
            if (load1 + w[i] <= k && !next_reachable[load1 + w[i]]) {
                next_reachable[load1 + w[i]] = 1;
                parent[i][load1 + w[i]] = 1;
            }
            if (prefix[i] - load1 <= k && !next_reachable[load1]) {
                next_reachable[load1] = 1;
                parent[i][load1] = 2;
            }
        }
        int found = -1;
        for (int load1 = 0; load1 <= k; ++load1) {
            if (next_reachable[load1]) {
                found = load1;
                break;
            }
        }
        if (found == -1) {
            break;
        }
        best_i = i;
        best_load = found;
        reachable.swap(next_reachable);
    }

    vector<int> truck1, truck2;
    int load1 = best_load;
    for (int i = best_i; i >= 1; --i) {
        if (parent[i][load1] == 1) {
            truck1.push_back(i);
            load1 -= w[i];
        } else {
            truck2.push_back(i);
        }
    }
    reverse(truck1.begin(), truck1.end());
    reverse(truck2.begin(), truck2.end());

    cout << best_i << '\n';
    for (int i = 0; i < (int)truck1.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << truck1[i];
    }
    cout << '\n';
    for (int i = 0; i < (int)truck2.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << truck2[i];
    }
    cout << '\n';
    return 0;
}