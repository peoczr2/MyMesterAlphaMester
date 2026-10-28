/*
Megoldás lényege: Egy kamion S nap alatt ér Bergengóciába, és 2S nap alatt tér vissza, így ugyanaz a kamion csak az 1, 2S+1, 4S+1, ... napokon indulhat. Az igényeket határidő szerint növekvő sorrendben dolgozzuk fel: az i. igény legkésőbbi megengedett indulási köre j_i = (H_i - S) div 2S, mert ekkor a kamion még a határidőre ér. Az első i igény legalább ceil(i/(j_i+1)) kamiont igényel, így a minimális kamionszám K = max ceil(i/(j_i+1)). N szállítmányt K kamionnal legalább ceil(N/K) indulási körre van szükség, ezért az utolsó visszaérés legkorábban 2S*ceil(N/K) nap, és ez el is érhető: az i. igényt az ((i-1) div K). körben indítjuk. Az időigény O(N log N) a rendezés miatt, a memóriaigény O(N).
*/
/*
Hint 1: || Egy kamion a visszaérés után 2S nappal később indulhat újra, így ugyanaz a kamion egy 2S napos ciklusban csak egyszer szállíthat. Gondold végig, hogy egy adott határidőre legkésőbb melyik indulási kör jó még. ||
Hint 2: || Rendezd a határidőket, és az i. (1-től számozott) igényre számold ki a legkésőbbi megengedett kör sorszámát: ennél a körnél a kamion indulási napja plusz S-1 még nem haladja meg a határidőt. Ebből az első i igény teljesítéséhez szükséges kamionok száma már megkapható. ||
Hint 3: || A minimális kamionszám a fenti értékek maximuma. Az utolsó visszaérésnél a skatulyaelvet használd: N szállítmányt K kamion visz, tehát valamelyik kamion legalább ceil(N/K)-szor indul, és két egymást követő indulása között legalább 2S nap telik el. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, s;
    cin >> n >> s;
    vector<long long> h(n);
    for (auto &x : h) cin >> x;
    sort(h.begin(), h.end());

    long long k = 1;
    for (long long i = 1; i <= n; i++) {
        long long j = (h[i - 1] - s) / (2 * s);
        k = max(k, (i + j) / (j + 1));
    }
    long long last = 2 * s * ((n + k - 1) / k);

    cout << k << "\n" << last << "\n";
    return 0;
}
