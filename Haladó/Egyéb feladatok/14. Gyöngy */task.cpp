/*
Megoldás lényege:
Minden lehetséges vágási helyre ki kell számolni a bal oldali K gyöngyben lévő piros, és a jobb oldali K gyöngyben lévő zöld gyöngyök számát.
A bal ablak a vágott gyöngyet is tartalmazza, a jobb ablak az utána következő K gyöngyöt. Két szomszédos vágás között
csak egy-egy gyöngy lép ki, illetve be az ablakokba, ezért mindkét számláló O(1) lépésben frissíthető.
A kört maradékos indexeléssel kezeljük. A K. gyöngy utáni vágástól indulunk, és N lépésben végigjárjuk az összes vágást.
A szigorú összehasonlítás miatt az első olyan vágás marad meg, amely a legkisebb különbséget adja.
Az időigény O(N), a memória a beolvasott szövegen kívül O(1).
*/
/*
Hint 1: || Ne számold újra minden vágásnál a teljes ablakot. Két szomszédos vágás között csak egy-egy gyöngy változik: gondold végig, melyik gyöngy lép be és melyik lép ki a bal, illetve a jobb ablakból, ha a vágás egy gyöngyel odébb kerül. ||
Hint 2: || Tarts két számlálót: a bal ablakban a pirosak, a jobb ablakban a zöldek számát. Az indexeket maradékosan (modulo N) kezeld, hogy a kör határán is jól működjön. Az első vágás ablakait egyszer számold ki közvetlenül, utána csak frissíts. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    // Kezdő ablakok a K. gyöngy utáni vágáshoz (0-indexelve a p = K-1 pozíció után).
    int red_left = 0, green_right = 0;
    for (int x = 0; x < k; ++x)
        if (s[x] == 'P') ++red_left;
    for (int x = k; x < 2 * k; ++x)
        if (s[x] == 'Z') ++green_right;

    int best = INT_MAX, best_cut = k;
    int p = k - 1;  // a vágás a p. (0-indexelt) gyöngy után van
    for (int step = 0; step < n; ++step) {
        int diff = abs(red_left - green_right);
        if (diff < best) {
            best = diff;
            best_cut = p + 1;
        }

        // Lépés a következő vágásra: q = p + 1, körbe zárva.
        int q = (p + 1 == n) ? 0 : p + 1;
        // Bal ablak: a q gyöngy belép, a q - K gyöngy kilép.
        int out_left = (q - k < 0) ? q - k + n : q - k;
        // Jobb ablak: a q gyöngy kilép, a q + K gyöngy belép.
        int in_right = (q + k >= n) ? q + k - n : q + k;

        red_left += (s[q] == 'P') - (s[out_left] == 'P');
        green_right += (s[in_right] == 'Z') - (s[q] == 'Z');
        p = q;
    }

    cout << best_cut << '\n';
    return 0;
}
