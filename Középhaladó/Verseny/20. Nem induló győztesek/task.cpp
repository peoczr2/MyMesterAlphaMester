/*
Megoldás lényege:
Versenyenként megkeressük a legnagyobb pontszámot, és a vele egyenlő pontszámú indulók mind győztesek lesznek (holtverseny esetén többen is). Tanulónként nyilvántartjuk, hány versenyen győzött, és hány versenyen indult. A kimenetbe az kerül, aki legalább egy versenyen győzött, de nem indult mind az M versenyen: ekkor biztosan van olyan verseny, ahol nem indult, és ez nem lehet az a verseny, ahol győzött. A tanulók sorszámát növekvő sorrendben írjuk ki a darabszámukkal együtt. Az időigény O(N·M), ami a korlátok mellett bőven belefér az időlimitbe.
*/
/*
Hint 1: || Győztes az a tanuló, akinek a versenyen a legnagyobb pontszáma van, egyenlőség esetén többen is lehetnek. Egy tanuló pontosan akkor kerül a kimenetbe, ha valahol győztes, és van olyan verseny, ahol nem indult. ||
Hint 2: || Tanulónként két számlálót vezess: hány versenyen indult, és hány versenyen volt győztes. Versenyenként előbb keresd meg a maximális pontszámot, utána jelöld meg az összes azt elérő indulót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> minimum(m);
    for (int i = 0; i < m; i++) {
        cin >> minimum[i];
    }

    vector<int> reszt(n + 1, 0), gyoztes(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        vector<int> s(ind), p(ind);
        for (int j = 0; j < ind; j++) {
            cin >> s[j] >> p[j];
            reszt[s[j]]++;
        }

        int legjobb = 0;
        for (int j = 0; j < ind; j++) {
            legjobb = max(legjobb, p[j]);
        }
        for (int j = 0; j < ind; j++) {
            if (p[j] == legjobb) {
                gyoztes[s[j]]++;
            }
        }
    }

    vector<int> ans;
    for (int x = 1; x <= n; x++) {
        if (gyoztes[x] > 0 && reszt[x] < m) {
            ans.push_back(x);
        }
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
