/*
Megoldás lényege:
Mivel a házak árai növekvők, a négy kiválasztott ház indexei i<j<k<l alakúak. Az i és j rögzítése után a maradék két ház árának összegét kell pontosan P-a_i-a_j értékre kihozni, ezt a k és l kétmutatós kereséssel nézzük: k a j utáni elsőtől, l az utolsótól indul, és az összeg alapján mozgatjuk őket. A rendezettség nyesésekre is ad lehetőséget: ha az aktuális négy egymást követő ár összege már nagyobb P-nél, a külső ciklus megáll, és ha a rögzített két ház mellett még a két legnagyobb ár sem elég, a következő j következik. A legrosszabb eset O(N^3), így N=10 000 és 0,2 mp időlimit mellett a legnehezebb tesztekre nem garantált a futásidő, a nyesések azonban sok esetben jelentősen csökkentik a munkát.
*/
/*
Hint 1: || Mivel az árak növekvők, a négy házat i<j<k<l sorszámokkal keresd. Az i és j rögzítése után a maradék két ház árának összege pontosan P - a_i - a_j kell legyen. ||
Hint 2: || A k és l keresése rendezett tömbön kétmutatós módszerrel történik: k a j utáni elsőtől, l az utolsótól indul. Ha az összeg kisebb a kellő értéknél, k-t növeld, ha nagyobb, l-et csökkentsd. ||
Hint 3: || Nyesd a keresést: ha az i-edik ártól kezdve a négy egymást követő ár összege már nagyobb P-nél, a külső ciklus megállhat. Ha a rögzített i és j mellett még a két legnagyobb ár összegével sem érhető el a cél, a következő j-t próbáld. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long p;
    cin >> n >> p;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i + 3 < n; i++) {
        if (a[i] + a[i + 1] + a[i + 2] + a[i + 3] > p) {
            break;
        }
        for (int j = i + 1; j + 2 < n; j++) {
            long long base = a[i] + a[j];
            if (base + a[j + 1] + a[j + 2] > p) {
                break;
            }
            if (base + a[n - 2] + a[n - 1] < p) {
                continue;
            }
            int k = j + 1, l = n - 1;
            while (k < l) {
                long long s = base + a[k] + a[l];
                if (s == p) {
                    cout << i + 1 << " " << j + 1 << " " << k + 1 << " " << l + 1 << "\n";
                    return 0;
                }
                if (s < p) {
                    k++;
                } else {
                    l--;
                }
            }
        }
    }

    cout << -1 << "\n";
    return 0;
}
