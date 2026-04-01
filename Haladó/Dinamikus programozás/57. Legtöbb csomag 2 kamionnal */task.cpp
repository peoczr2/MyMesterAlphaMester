/*
Az elso M csomag akkor es csak akkor pakolhato fel, ha az elso M sulyt ket K kapacitasu halmazra
szet lehet osztani. Ehhez eleg az egyik kamion aktualis terheleset tarolni: ha az elso kamionon
x suly van, akkor a masodikon a prefixosszeg-x. Legyen egy allapot elerheto az i. csomag utan,
ha ilyen x letezik, es mindket terheles legfeljebb K. Sorban dolgozzuk fel a csomagokat; ha egy
uj csomag utan mar nincs elerheto allapot, akkor az elozo prefix volt a legnagyobb jo M. A
szulo-informaciobol egy optimalis pakolas visszaepitheto.
*/
/*
Hint 1: || Ha az egyik kamion aktualis terheleset tudod, a masike a prefixosszegbol kiszamolhato. ||
Hint 2: || Az i-edik csomag vagy az elso, vagy a masodik kamionra kerulhet. ||
Hint 3: || Az elso sikertelen prefix elott allj meg, es onnan epitsd vissza a valasztasokat. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> k >> n;

    vector<int> weight(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> weight[i];
    }

    vector<vector<char>> parent(n + 1, vector<char>(k + 1, -1));
    vector<char> current(k + 1, false), next(k + 1, false);
    current[0] = true;
    parent[0][0] = 0;

    int prefix_sum = 0;
    int best_m = 0;
    int best_load = 0;

    for (int i = 1; i <= n; ++i) {
        fill(next.begin(), next.end(), false);
        fill(parent[i].begin(), parent[i].end(), -1);
        for (int load = 0; load <= k; ++load) {
            if (!current[load]) {
                continue;
            }
            int other = prefix_sum - load;
            if (load + weight[i] <= k && !next[load + weight[i]]) {
                next[load + weight[i]] = true;
                parent[i][load + weight[i]] = 1;
            }
            if (other + weight[i] <= k && !next[load]) {
                next[load] = true;
                parent[i][load] = 2;
            }
        }

        prefix_sum += weight[i];
        bool any = false;
        for (int load = 0; load <= k; ++load) {
            if (next[load]) {
                any = true;
                best_load = load;
            }
        }
        if (!any) {
            break;
        }
        best_m = i;
        current.swap(next);
    }

    vector<int> first_truck;
    vector<int> second_truck;
    int load = best_load;
    for (int i = best_m; i >= 1; --i) {
        if (parent[i][load] == 1) {
            first_truck.push_back(i);
            load -= weight[i];
        } else {
            second_truck.push_back(i);
        }
    }
    reverse(first_truck.begin(), first_truck.end());
    reverse(second_truck.begin(), second_truck.end());

    cout << best_m << '\n';
    for (int i = 0; i < static_cast<int>(first_truck.size()); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << first_truck[i];
    }
    cout << '\n';
    for (int i = 0; i < static_cast<int>(second_truck.size()); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << second_truck[i];
    }
    cout << '\n';
    return 0;
}