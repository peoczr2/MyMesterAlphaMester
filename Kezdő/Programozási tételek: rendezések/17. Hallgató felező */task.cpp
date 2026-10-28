/*
Megoldás lényege:
A pontszámokat csökkenő sorrendbe rendezzük. Egy R pontszám akkor teljesíti a feltételt, ha legalább ceil(N/2) hallgató pontszáma legalább R, ezért a legnagyobb ilyen R épp a csökkenő sorozat ceil(N/2)-edik eleme.
Ezt az elemet az (N+1)/2 egész osztással kapott index adja, nullától indexelve eggyel kisebb sorszámon.
Az N = 0 esetben nincs hallgató, a feltétel minden R-re igaz; ilyenkor a pontszámtartomány felső határát, a 20-at írjuk ki.
A rendezés időigénye O(N log N), ami N ≤ 99 mellett bőven elég.
*/
/*
Hint 1: || Ha a hallgatók pontszámait csökkenő sorrendbe rendezed, a keresett R a rendezett sorozat egy konkrét helyén álló pontszám lesz. ||
Hint 2: || N hallgatónál legalább (N+1)/2 egész számú hallgatónak kell elérnie az R pontot, tehát a csökkenő sorrendben a (N+1)/2-edik pontszám lesz a válasz; a tömb indexelése nullától kezdődik, ezért ebből egyet le kell vonni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> pont(n);
    for (int &p : pont) cin >> p;

    if (n == 0) {
        cout << 20 << '\n';
        return 0;
    }

    sort(pont.begin(), pont.end(), greater<int>());
    int k = (n + 1) / 2;  // legalább ennyi hallgatónak kell R-et elérnie
    cout << pont[k - 1] << '\n';
    return 0;
}
