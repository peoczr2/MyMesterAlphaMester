/*
Megoldás lényege:
Lécenként nyilvántartjuk, hány festés érte a lécet, és az utolsó két festés színét.
A léc végső színe: ha még nem festették, fehér; ha pontosan egyszer festették, az a szín;
ha legalább kétszer festették és az utolsó két festés színe megegyezik, akkor az a szín;
minden más esetben (váltakozó festés) barna. Az embereket sorban dolgozzuk fel, és a
szakaszuk minden lécénél frissítjük a darabszámot és az utolsó két színt. A végén egy
végigmenéssel megszámoljuk a piros és a zöld lécek számát. Az idő O(N·M), ami N≤1000 és
M≤100 mellett bőven elég.
*/
/*
Hint 1: || Egy léc végső színét nem csak az dönti el, hány festés érte, hanem az is, hogy az utolsó két festés azonos színű volt-e. Váltakozó festésnél a léc barna lesz. ||
Hint 2: || Lécenként elég három adatot nyilvántartani: a festések számát, az utolsó festés színét és az azt megelőző festés színét. ||
Hint 3: || Az emberek sorrendben haladnak, és mindegyik a saját szakaszának minden lécét festi. A festések után egyetlen végigmenéssel számold meg a piros és a zöld lécek számát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> cnt(n + 1, 0);
    vector<char> last(n + 1, 'F'), prev(n + 1, 'F'); // 'F': még nem festették
    for (int k = 0; k < m; k++) {
        char c;
        int a, b;
        cin >> c >> a >> b;
        for (int i = a; i <= b; i++) {
            prev[i] = last[i];
            last[i] = c;
            cnt[i]++;
        }
    }

    int piros = 0, zold = 0;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == 0) continue;
        if (cnt[i] == 1 || last[i] == prev[i]) {
            if (last[i] == 'P') piros++;
            else zold++;
        }
    }
    cout << piros << " " << zold << "\n";
    return 0;
}
