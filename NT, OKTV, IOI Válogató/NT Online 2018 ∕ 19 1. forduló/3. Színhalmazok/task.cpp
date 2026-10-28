/*
    Minden ember kedvenc színeit halmazba tesszük, a színneveket egész azonosítókra képezzük
    le. Egy ember akkor jó, ha van olyan másik ember, akinek a kedvenc színei között
    megtalálhatók az ő összes kedvenc színei, azaz az ő halmaza részhalmaza a másik halmazának.
    Minden i emberre végignézzük az összes j ≠ i embert, és a std::includes függvénnyel
    ellenőrizzük a részhalmaz-viszonyt; ha találunk ilyet, i jó. Mivel N ≤ 1000 és egy
    embernek legfeljebb 10 színe van, az O(N² · D) időigény az időlimiten belül marad.
*/
/*
Hint 1: || Egy embert akkor tekinthetsz jónak, ha van olyan másik ember, akinek a kedvenc színei tartalmazzák az övéit. Ez két halmaz részhalmaz-vizsgálata. ||
Hint 2: || A színneveket képezd egész számokra (például map<string, int>-tel), hogy minden ember kedvenc színei egész számokból álló rendezett halmazként (set<int>) tárolhatók legyenek. Két rendezett halmaz részhalmaz-viszonya a std::includes függvénnyel ellenőrizhető. ||
Hint 3: || Minden i-re nézd végig az összes j ≠ i embert, és ha i halmaza benne van j halmazában, akkor i jó, így nem kell több j-t vizsgálnod. Az N ≤ 1000 és D ≤ 10 miatt ez az időlimiten belül van. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    map<string, int> szin_id;       // szín neve -> egyedi azonosító
    vector<set<int>> kedvencek(n);  // egy ember kedvenc színei azonosítókkal

    for (int i = 0; i < n; ++i) {
        int d;
        cin >> d;
        for (int j = 0; j < d; ++j) {
            string s;
            cin >> s;
            if (szin_id.count(s) == 0) {
                int uj = szin_id.size();
                szin_id[s] = uj;
            }
            kedvencek[i].insert(szin_id[s]);
        }
    }

    int valasz = 0;
    for (int i = 0; i < n; ++i) {
        bool jo = false;
        for (int j = 0; j < n && !jo; ++j) {
            if (j == i) continue;
            if (includes(kedvencek[j].begin(), kedvencek[j].end(),
                         kedvencek[i].begin(), kedvencek[i].end())) {
                jo = true;
            }
        }
        if (jo) ++valasz;
    }

    cout << valasz << '\n';
    return 0;
}
