/*
Megoldás lényege:
Árvíz most is a 800 cm-nél magasabb, maximális, egymás melletti vízállásokból álló szakasz. Egy árvízben akkor van két harmadfokú (1000 cm-nél magasabb)
pont között elsőfokú (801-900 cm közötti) folyószakasz, ha van olyan elsőfokú mérés, amelyet a bal oldalon és a jobb oldalon is harmadfokú mérés vesz körül.
Az árvizeken belül balról jobbra haladva két jelzővel követjük, láttunk-e már harmadfokút, és volt-e utána elsőfokú mérés.
Ha újabb harmadfokú mérés jön ilyen állapotban, az árvíz megfelel. Az időigény O(N).
*/
/*
Hint 1: || Először keresd meg az árvizeket: a 800 cm-nél magasabb, egymás melletti vízállások maximális tartományait. A feltételt minden árvízre külön kell vizsgálni. ||
Hint 2: || A feltétel: legyen harmadfokú mérés, utána elsőfokú mérés (801-900 cm), majd újabb harmadfokú mérés. Egy bejárás közben ezt két logikai jelzővel követheted. ||
Hint 3: || Ha harmadfokú mérés jön, és közben már volt harmadfokú mérés előtte, valamint volt köztük elsőfokú mérés, az árvíz beletartozik. Minden új árvíz elején a jelzőket nullázd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int szint(int h) {
    if (h > 1000) return 3;
    if (h > 900) return 2;
    if (h > 800) return 1;
    return 0;
}

void printPairs(const vector<pair<int, int>>& v) {
    for (size_t k = 0; k < v.size(); k++) {
        if (k > 0) cout << ' ';
        cout << v[k].first << ' ' << v[k].second;
    }
    cout << '\n';
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<pair<int, int>> arviz;
    vector<pair<int, int>> megfelelo;

    int i = 1;
    while (i <= n) {
        if (a[i] <= 800) {
            i++;
            continue;
        }
        int l = i;
        int r = i;
        while (r + 1 <= n && a[r + 1] > 800) r++;
        arviz.push_back({l, r});

        bool volt3 = false;
        bool volt1UtanaA3 = false;
        bool jo = false;
        for (int k = l; k <= r; k++) {
            int s = szint(a[k]);
            if (s == 3) {
                if (volt1UtanaA3) jo = true;
                volt3 = true;
                volt1UtanaA3 = false;
            } else if (s == 1) {
                if (volt3) volt1UtanaA3 = true;
            }
        }
        if (jo) megfelelo.push_back({l, r});

        i = r + 1;
    }

    cout << arviz.size() << '\n';
    if (arviz.empty()) return 0;
    printPairs(arviz);

    cout << megfelelo.size() << '\n';
    if (megfelelo.empty()) return 0;
    printPairs(megfelelo);

    return 0;
}
