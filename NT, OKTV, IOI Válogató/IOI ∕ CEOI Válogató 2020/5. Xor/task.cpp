/*
Megoldás lényege:
Legyen b a legmagasabb bit, ahol L és R eltér. E fölött minden szám bitje azonos, így a három szám xor-jában ez a közös rész háromszor szerepel, azaz változatlanul marad; az alsó biteket kell maximalizálni. Az optimális hármasban van két szomszédos szám, x és x+1: ezek xor-ja 2^(t+1)−1, ahol t az x végén álló 1-esek száma. A harmadik szám z xor-jának ezzel a maszkkal akkor a legnagyobb, ha z magasabb bitjei a lehető legnagyobbak, alsó t+1 bitje pedig a lehető legkisebb. Minden t-re ezért csak néhány jelölt z-t (a legjobb négy értéket [L,R]-ben) és néhány jelölt x-et (az első négy, megfelelő végződésű számot) próbálunk ki. Mivel t legfeljebb 61, egy teszt O(log R) időben fut.
*/
/*
Hint 1: || Nézd meg a legmagasabb bitet, ahol L és R különbözik. A fölötte lévő bitek minden számban azonosak, így a xor-ban háromszor szerepelnek, tehát ezeket nem tudod változtatni. Az alsó biteket kell maximalizálni. ||
Hint 2: || Próbálj olyan hármast keresni, amelyben van két egymást követő szám, x és x+1. Ezek xor-ja csupa 1-es bitből álló szám (2^(t+1)−1 alakú), ahol t az x végén álló 1-esek száma. Így a harmadik szám xor-ját kell a lehető legnagyobbra vinni. ||
Hint 3: || Adott maszkkal a z xor maszk akkor a legnagyobb, ha z magasabb bitjei a lehető legnagyobbak, az alsó t+1 bit pedig a lehető legkisebb. Ezért minden t-re csak az intervallum végéhez közeli néhány z-t és néhány x-et kell kipróbálni. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        ll L, R;
        cin >> L >> R;

        ll best = -1, ansA = 0, ansB = 0, ansC = 0;
        for (int t = 0; t <= 60; ++t) {
            ll target = (1LL << t) - 1;  // x végén t darab 1-es, előtte 0
            if (target > R) break;
            int sh = t + 1;
            ll S = 1LL << sh;
            ll mask = S - 1;  // x ^ (x+1) = mask

            // a z-jelöltek: [L, R] legnagyobb (mask ^ z) értékű 4 eleme, csökkenő sorrendben
            ll cand[4];
            int nc = 0;
            for (ll h = R >> sh; h >= (L >> sh) && nc < 4; --h) {
                ll lo = max(L, h << sh), hi = min(R, (h << sh) + mask);
                for (ll z = lo; z <= hi && nc < 4; ++z) cand[nc++] = z;
            }

            // az x-jelöltek: az első 4 olyan x ∈ [L, R-1], amelyre x mod S = target
            ll x = L + ((target - (L & mask) + S) & mask);
            for (int k = 0; k < 4 && x + 1 <= R; ++k, x += S) {
                for (int q = 0; q < nc; ++q) {
                    ll z = cand[q];
                    if (z == x || z == x + 1) continue;
                    ll val = mask ^ z;
                    if (val > best) {
                        best = val;
                        ll tr[3] = {x, x + 1, z};
                        sort(tr, tr + 3);
                        ansA = tr[0];
                        ansB = tr[1];
                        ansC = tr[2];
                    }
                    break;
                }
            }
        }
        cout << ansA << ' ' << ansB << ' ' << ansC << '\n';
    }
    return 0;
}
