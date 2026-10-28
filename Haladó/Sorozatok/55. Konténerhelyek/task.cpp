/*
Megoldás lényege:
Egy szakasz pontosan akkor pakolható egyetlen toronnyá, ha az értékei szerint nincs benne 2413 vagy 3142 alakú
részsorozat (ezek a szeparálható sorozatok). A toronyban az elemek alulról felfelé csökkenő sorrendben állnak, és
két szomszédos szakasz csak akkor olvasztható össze, ha az értékeik elkülönülnek. A jó szakaszok részszakaszai is
jók, ezért a bal szélről mohón haladva mindig a leghosszabb jó szakaszt vágjuk le; a felszabadítható helyek száma
N − (szakaszok száma). Egy e. elem mintát zár le, ha vannak i < j < k < e indexek, amelyekre v_k < v_i < v_e < v_j.
Ezt visszafelé haladva ellenőrizzük; a 3142 esetet a számok előjelének megfordításával (w = −v) kezeljük.
Az időigény legrosszabb esetben O(N^2).
*/
/*
Hint 1: || Egy szakasz pontosan akkor pakolható egyetlen toronnyá, ha nincs benne 2413 vagy 3142 alakú részsorozat. ||
Hint 2: || Jó szakasz minden részszakasza is jó, ezért a bal szélről mohón érdemes vágni: mindig a leghosszabb jó szakaszt vesszük. ||
Hint 3: || Visszafelé haladva e elől: amikor e-nél nagyobb elemet találsz, jegyezd meg az e és közte lévő elemek minimumát. Ha később olyan i elem jön (v_i < v_e), amely nagyobb ennél a minimumnál, akkor minta van. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Igaz, ha az e. elem egy 2413 mintát zár le a [s..e] szakaszon, azaz van s <= i < j < k < e,
// amelyre v[k] < v[i] < v[e] < v[j].
static bool closesPattern(const vector<int>& v, int s, int e) {
    int x = v[e];
    bool seenBig = false;
    int nbMin = INT_MAX;   // az i-től jobbra legközelebbi e-nél nagyobb elem és e közötti minimum
    int runMin = INT_MAX;  // az i+1 .. e-1 elemek minimuma
    for (int i = e - 1; i >= s; --i) {
        if (v[i] > x) {
            seenBig = true;
            nbMin = runMin;
        } else if (seenBig && nbMin < v[i]) {
            return true;
        }
        runMin = min(runMin, v[i]);
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n), w(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        w[i] = -v[i];  // a v-ben levő 3142 minták a w-ben 2413 minták
    }

    int cuts = 0;
    int s = 0;                                // az aktuális szakasz kezdete
    int winMax = INT_MIN, winMin = INT_MAX;   // a [s..e-1] szakasz legnagyobb és legkisebb értéke
    for (int e = 0; e < n; ++e) {
        if (e > s && winMax > v[e] && winMin < v[e]) {
            if (closesPattern(v, s, e) || closesPattern(w, s, e)) {
                ++cuts;
                s = e;
                winMax = INT_MIN;
                winMin = INT_MAX;
            }
        }
        winMax = max(winMax, v[e]);
        winMin = min(winMin, v[e]);
    }

    cout << n - (cuts + 1) << '\n';
    return 0;
}
