/*
Megoldás lényege:
A fesztiválokat a befejezésük napja szerint rendezzük, és dinamikus programozással számolunk: dp[i] az első i fesztivál közül választva elérhető legnagyobb bevétel. Az i. fesztivál választásakor csak azok a korábbiak férnek be előtte, amelyek vége kisebb az i. fesztivál kezdeténél; a rendezés miatt ezek mindig a sorrend elején állnak, így számukat binária kereséssel (lower_bound) gyorsan megkapjuk. A dp-tábla visszafelé követésével kiderül, mely fesztiválok adják az optimumot. Az időigény O(N log N), ami a rendezésből és a binária keresésekből adódik.
*/
/*
Hint 1: || Rendezd a fesztiválokat a befejezésük napja szerint. Ha az i. fesztivált választod, akkor a többi kiválasztott fesztivál vége kisebb kell legyen az i. kezdeténél. ||
Hint 2: || Legyen dp[i] az első i fesztivál közül választva elérhető legnagyobb bevétel. Ekkor vagy kihagyod az i. fesztivált (dp[i-1]), vagy választod, és akkor a korábbi részt a p[i] előtagra korlátozod, ahol p[i] azon fesztiválok száma, amelyek vége kisebb az i. kezdeténél. ||
Hint 3: || A p[i] értékeket lower_bound adja meg a rendezett befejezési napokon, a dp-táblát pedig visszafelé járva szedd össze a kiválasztott sorszámokat: ha dp[i] különbözik dp[i-1]-től, az i. fesztivál kell, és a következő lépés a p[i]. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Fesztival {
    int kezd, veg, bevetel, sorszam;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Fesztival> f(n);
    for (int i = 0; i < n; i++) {
        cin >> f[i].kezd >> f[i].veg >> f[i].bevetel;
        f[i].sorszam = i + 1;
    }

    stable_sort(f.begin(), f.end(), [](const Fesztival& a, const Fesztival& b) {
        return a.veg < b.veg;
    });

    vector<int> vegek(n);
    for (int i = 0; i < n; i++) vegek[i] = f[i].veg;

    // p[i]: az i. (1-től számozott) fesztivál előtt hány fesztivál végződik a kezdete előtt
    vector<int> p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        p[i] = int(lower_bound(vegek.begin(), vegek.end(), f[i - 1].kezd) - vegek.begin());
    }

    vector<long long> dp(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        dp[i] = max(dp[i - 1], dp[p[i]] + f[i - 1].bevetel);
    }

    vector<int> valasztott;
    int i = n;
    while (i > 0) {
        if (dp[i] == dp[i - 1]) {
            i--;
        } else {
            valasztott.push_back(f[i - 1].sorszam);
            i = p[i];
        }
    }

    cout << dp[n] << "\n";
    cout << valasztott.size();
    for (int x : valasztott) cout << " " << x;
    cout << "\n";
    return 0;
}
