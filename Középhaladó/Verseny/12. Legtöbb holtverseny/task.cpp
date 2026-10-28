/*
Megoldás lényege:
Egy versenyen holtversenyes az a versenyző, akinek a pontszáma megegyezik legalább egy másik résztvevő pontszámával. Versenyenként a résztvevők pontszámait rendezzük, így az egyenlő pontok egymás mellé kerülnek, és a legalább kételemű csoportok tagjait összeszámoljuk. A versenyekhez tartozó számlálók maximumát keressük, és kiírjuk az ezt elérő versenyek sorszámait növekvő sorrendben. Ha a maximum 0, akkor nem volt holtverseny, és a feladat szerint csak a 0 számot írjuk ki. Az időigény O(N·M·log N), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Egy versenyen belül azokat a versenyzőket kell megszámolni, akiknek a pontszáma megegyezik valakiével ugyanabban a versenyben. A versenyeket külön-külön vizsgáld. ||
Hint 2: || Rendezd a versenyen szereplő pontokat, így az egyező pontok egymás mellé kerülnek. Egy legalább kételemű csoport minden tagja holtversenyes, ezért a csoport méretét add hozzá a versenyhez tartozó számlálóhoz. ||
Hint 3: || A számlálók maximumát keresd meg. Ha a maximum 0, nem volt holtverseny, és egyetlen 0-t kell kiírni, nem az összes versenyt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int minimum;  // ebben a feladatban nem kell
        cin >> minimum;
    }

    vector<int> tied(m, 0);
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        vector<int> scores(ind);
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            scores[j] = p;
        }
        sort(scores.begin(), scores.end());

        int j = 0;
        while (j < ind) {
            int k = j;
            while (k < ind && scores[k] == scores[j]) {
                k++;
            }
            if (k - j >= 2) {
                tied[i] += k - j;
            }
            j = k;
        }
    }

    int best = *max_element(tied.begin(), tied.end());
    vector<int> ans;
    if (best > 0) {
        for (int i = 0; i < m; i++) {
            if (tied[i] == best) {
                ans.push_back(i + 1);
            }
        }
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
