/*
Megoldás lényege:
Minden naphoz hozzárendeljük az átvonuló madarak darabszámát és a nap sorszámát, majd ezeket a (darabszám, nap) párokat rendezzük. A párok rendezése először a darabszám szerint növekvő sorrendet ad, egyenlő darabszámnál pedig a nap sorszáma szerint rendez, így a kért sorrend adódik. A kiíráskor az azonos darabszámú, egymás utáni napok egy sorba kerülnek, szóközzel elválasztva, a darabszám változásánál új sort kezdünk. Az időigény O(N log N), ami N ≤ 5000 mellett bőven gyors.
*/
/*
Hint 1: || Egy napot érdemes a madarak darabszámával együtt tárolni, így a rendezésnél a darabszám lesz az elsődleges szempont. ||
Hint 2: || Rendezés után az azonos darabszámú napok egymás mellett állnak. Egy bejárással, az egyenlő darabszámú szakaszokat találva, minden szakaszt egy sorba írhatsz ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> v;  // (darabszám, nap sorszáma)
    for (int i = 1; i <= n; i++) {
        int d;
        cin >> d;
        v.push_back({d, i});
    }
    sort(v.begin(), v.end());
    size_t i = 0;
    while (i < v.size()) {
        size_t j = i;
        while (j < v.size() && v[j].first == v[i].first) {
            if (j > i) {
                cout << ' ';
            }
            cout << v[j].second;
            j++;
        }
        cout << '\n';
        i = j;
    }
    return 0;
}
