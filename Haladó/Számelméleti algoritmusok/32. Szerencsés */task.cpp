/*
Megoldás lényege:
Szitát futtatunk: a megmaradt számok listáját tároljuk, és minden körben a következő még nem használt megmaradt szám a lépésköz, amely szerint minden lépésköz-adik elemet törlünk.
A következő lépésköz mindig az előző lépésköznél nagyobb legkisebb megmaradt szám, ezt a listában upper_bound adja meg.
Ha a lépésköz nagyobb a lista hosszánál, már nem történik törlés, ezért az eljárás megáll, és a maradék számokat írjuk ki.
Mivel a lista minden körben zsugorodik, N ≤ 300 000 esetén a futásidő bőven az időlimit alatt marad.
*/
/*
Hint 1: || Ez egy szita, csak itt nem prímes számokat törölsz, hanem mindig a következő megmaradt szám lépésközével. ||
Hint 2: || Tartsd nyilván a megmaradt listát, és minden körben az előző lépésköznél nagyobb legkisebb megmaradt számmal szűrd újra. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    int idx = 1;
    while (idx < (int)a.size() && a[idx] <= (int)a.size()) {
        int step = a[idx];
        vector<int> b;
        b.reserve(a.size());
        for (int j = 0; j < (int)a.size(); ++j) {
            if ((j + 1) % step != 0) b.push_back(a[j]);
        }
        a.swap(b);
        idx = upper_bound(a.begin(), a.end(), step) - a.begin();
    }
    for (int i = 0; i < (int)a.size(); ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
    return 0;
}
