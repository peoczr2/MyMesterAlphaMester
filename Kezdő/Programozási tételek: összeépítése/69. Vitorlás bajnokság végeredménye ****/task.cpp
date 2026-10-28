/*
Megoldás lényege:
Futamonként az i. helyezett K-i+1 pontot kap; versenyzőnként gyűjtjük az összes kapott pontot, és külön számoljuk, hányszor lett első, második, ... helyezett.
Egy versenyző összpontszáma a legjobb L pontszámának összege: a kapott pontokat csökkenő sorba rendezzük, és az első L-et összegezzük.
A rangsor összpontszám szerint csökkenő; azonos összpontszámnál a helyezés-számlálók vektora dönt (több első hely, majd több második, ...), végül a sorszám.
Összpontot az szerez, aki legalább egy helyezést ért el, ezeket kell kiírni.
Időigény O(M·N·log N + N·K), ami a korlátok mellett bőven belefér.
*/
/*
Hint 1: || A versenyző összpontszáma nem minden pontjának összege, hanem csak a legjobb L pontjáé. Ezért versenyzőnként kell gyűjteni a kapott pontokat, majd rendezni őket. ||
Hint 2: || Az i. helyezett K-i+1 pontot kap: versenyzőnként egy listában tárold a kapott pontokat, és egy M×K tömbben számold, hányszor lett a versenyző j. helyezett. ||
Hint 3: || A rendezéshez összetett kulcs kell: összpontszám szerint csökkenő, azonos összpontszámnál a helyezés-számláló vektor szerint csökkenő, végül a sorszám szerint növekvő. A vector összehasonlítás lexikografikus, ezért közvetlenül használható. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k, l, m;
    cin >> n >> k >> l >> m;

    // pts[s]: az s. versenyző összes kapott pontja (minden előfordulás külön pont)
    vector<vector<int>> pts(m + 1);
    // place[s][j]: hányszor lett az s. versenyző (j+1). helyezett
    vector<vector<int>> place(m + 1, vector<int>(k, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            int s;
            cin >> s;
            pts[s].push_back(k - j);
            place[s][j]++;
        }
    }

    vector<int> total(m + 1, 0);
    vector<int> ids;
    for (int s = 1; s <= m; s++) {
        if (pts[s].empty()) continue;
        sort(pts[s].rbegin(), pts[s].rend());
        int sum = 0;
        for (int i = 0; i < l && i < (int)pts[s].size(); i++) {
            sum += pts[s][i];
        }
        total[s] = sum;
        ids.push_back(s);
    }

    sort(ids.begin(), ids.end(), [&](int a, int b) {
        if (total[a] != total[b]) return total[a] > total[b];
        if (place[a] != place[b]) return place[a] > place[b];
        return a < b;
    });

    cout << ids.size() << "\n";
    for (int s : ids) {
        cout << s << " " << total[s] << "\n";
    }
    return 0;
}
