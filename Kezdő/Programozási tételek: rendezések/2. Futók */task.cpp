/*
Megoldás lényege:
Minden futó távolsága a céltól egyenletes sebességgel lineárisan csökken, ezért két futó távolságkülönbsége is lineáris, így két futó sorrendje legfeljebb egyszer változhat meg.
A távolabbról induló i futó akkor előzi meg a közelebbről induló j futót, ha gyorsabb nála (A_i > A_j), és ez a találkozás a t0 = (T_i - T_j) / (A_i - A_j) időpontban történik.
Mivel az időpontok egész másodpercek, az első olyan egész másodperc e = t0 egészrésze + 1, amikor az előzés már ténylegesen megtörtént.
Az előzést csak akkor számoljuk, ha a megelőzött j futó még nem ért célba, azaz A_j * e < T_j.
Az azonos másodpercben történő előzések egy időpontnak számítanak, ezért a különböző időpontokat halmazban gyűjtjük; az időigény O(N^2 log N).
*/
/*
Hint 1: || Két futó távolságának különbsége lineáris függvénye az időnek, ezért minden futópárt külön, egyszer kell vizsgálnod. ||
Hint 2: || Egy távolabbról induló futó csak akkor előzhet, ha gyorsabb a közelebbről indulónál; a találkozás idejét a kezdő távolságok és a sebességek különbségéből kapod, majd a következő egész másodpercet kell figyelembe venni, de csak akkor, ha a megelőzött futó addig nem ért célba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> t(n), a(n);
    for (int i = 0; i < n; i++) cin >> t[i] >> a[i];

    set<long long> idopontok;  // a sorrendváltozások egész másodpercei
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // t[i] > t[j]; előzés csak akkor van, ha i gyorsabb
            if (a[i] <= a[j]) continue;
            long long e = (t[i] - t[j]) / (a[i] - a[j]) + 1;  // első egész másodperc az előzés után
            if (a[j] * e < t[j]) idopontok.insert(e);          // j még nem ért célba
        }
    }

    cout << idopontok.size();
    for (long long e : idopontok) cout << ' ' << e;
    cout << '\n';
    return 0;
}
